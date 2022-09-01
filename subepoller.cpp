#include"subepoller.h"
#include<iostream>
#include<unistd.h>
#include <sys/eventfd.h>

subepoller::subepoller() : wakeupfd(createEventfd()) , timerfd(createTimerfd()),start_(1),state_(0)
{
    addeventInloop(wakeupfd,EPOLLIN);
    circularbuffer_.push_back(std::unordered_set<std::shared_ptr<Entry>>());
    setnewtimer(1);
    addeventInloop(timerfd,EPOLLIN);
    index_ = 0;
    std::cout << "wakeupfd = " << wakeupfd << std::endl;
    std::cout << "timerfd = " << timerfd << std::endl;
    std::cout << "epollerfd = " << epollfd_ << std::endl;

}

subepoller::~subepoller()
{

}


//线程安全的添加新连接描述符进入容器的函数
void subepoller::addevent(int fd,int eve)
{
    // std::cout << "begin addevent" << std::endl;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        connfdlist_.push_back({fd,eve});
    }

    wakeup();
}




void subepoller::addeventInloop(int fd,int eve)
{
    
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = eve;
    if(ev.data.fd > 3000)
                std::cerr << "add fd = " << ev.data.fd << std::endl;
    if(epoll_ctl(epollfd_,EPOLL_CTL_ADD,fd,&ev) < 0)
    {
        std::cerr << "EPOLL_CTL_ADD " << std::endl;
        //fixme
    }
     
}

void subepoller::addeventInloop(int fd,int eve,int index)
{
    
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = eve;
    ev.data.u32 = index;
    if(epoll_ctl(epollfd_,EPOLL_CTL_ADD,fd,&ev) < 0)
    {
        //fixme
    }
     
}


void subepoller::wakeup()
{
    // std::cout << "begin wakeup" << std::endl;
    //这里一定要赋初值，否则无法正确写入
    uint64_t one = 1;
    ssize_t n = write(wakeupfd, &one, sizeof(one));
    if (n != sizeof(one))
    {
        std::cout << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

void subepoller::removefromlist(int fd)
{
    // std::cerr << "removefromlist fd = " << fd << std::endl;
    connectionlist_.erase(fd);
}

void subepoller::pool()
{
    state_ = 1;
    while(start_)
    {
        int nfds = epoll_wait(epollfd_,&(*(events_.begin())),events_.capacity(),10000);
        if(nfds < 0)
        {
            //fixme;
            std::cerr << "epollerror" << std::endl;
        }
        else if(nfds == 0)
        {
            // std::cout << "nothing happen" << std::endl;
        }
        else
        {

            
            for(int i = 0;i < nfds;++i)
            {
                int curfd = events_[i].data.fd;
                int curevent = events_[i].events;
                if(curfd > 3000)
                std::cerr << "fd = " << curfd << std::endl;
                else
                handleconnection(curfd,curevent);               
            }

            //vector满了就扩容
            if(nfds == events_.size())
            {
                events_.resize(nfds*2);
            }
        }
        events_.clear();
    }
    state_ = 0;
}


int subepoller::createEventfd()
{
  int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0)
  {
    abort();
  }
  return evtfd;
}

int subepoller::createTimerfd()
{
    int timerfd = timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);
    // std::cout << "timerfd = " << timerfd << std::endl;
    if(timerfd < 0)
    {
        std::cerr << "CreateTimerfd";
    }

    return timerfd;
}




void subepoller::readTimerfd()
{
    uint64_t howmany;
    int size = read(timerfd,&howmany,sizeof(howmany));

    if(size != sizeof(howmany))
    {
        std::cerr << "TimerQueue::handleRead() reads " << size << " bytes instead of 8";
    }
}




//设定定时器
void subepoller::setnewtimer(int interval)
{
    struct timespec now;
    if (clock_gettime(CLOCK_REALTIME, &now) == -1)
        std::cerr << "clock_gettime" << std::endl;
    // std::cout << "cur time = " << now.tv_sec << std::endl;
    struct itimerspec new_value;
    new_value.it_value.tv_sec = interval;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = 0;
    int ret = timerfd_settime(timerfd,0,&new_value,nullptr);
    if(ret < 0)
    {
        std::cerr << "timerfd_settime";
    }

    timerfd_gettime(timerfd, &new_value);
    // std::cout << "last time = " << new_value.it_value.tv_sec << std::endl;

}




void subepoller::handletime()
{
    readTimerfd();
    setnewtimer(1);
    circularbuffer_.push_back(std::unordered_set<std::shared_ptr<Entry>>());    
}






void subepoller::handleconnection(int fd,int event)
{
    // std::cout << "fd = " << fd << std::endl;
    //fd为wakeupfd时证明有异步事件需要加入新的连接
    if(fd == wakeupfd)
    {
        uint64_t readlen;
        int s = read(wakeupfd,&readlen,sizeof(readlen));
        if(s != sizeof(readlen))
        {
            std::cerr << "readeventfd" << " return " << s << "byets instead of 8 bytes";
        }
        
        std::vector<std::pair<int,int>> temp;
        {
             std::lock_guard<std::mutex> lock(mutex_);
             
             temp.swap(connfdlist_);

        }

        for(int i = 0;i < temp.size();++i)
        {
            
            int fd = temp[i].first;
            if(fd > 3000)
            {
                std::cerr << "errfd = " << fd << std::endl;
            }
            int eve = temp[i].second;
            // std::cout << "make_new_shared fd = " << temp[i].first << std::endl;
            // std::cout << "origin list have newfd  " << temp[i].first <<  " size = " << connectionlist_.count(temp[i].first) <<std::endl;
            
            //先创建TcpConnection类
            connectionlist_[temp[i].first] = std::make_shared<TcpConnection>(temp[i].first,this);
            
       
           
            
            
            //注册关注事件
            addeventInloop(fd,eve);




           



            //在同种加入shared_ptr实现引用计数
            EntryPtr newEntry = std::make_shared<Entry>(connectionlist_[temp[i].first]);
            circularbuffer_.back().insert(newEntry);
         
            connectionlist_[temp[i].first]->setentry(newEntry);
        }
    }
    else if(fd == timerfd)
    {
        
        handletime();
    }
    else
    {
        // std::cout << "get read event" << std::endl;
        // 保证在处理事件时Tcpconnection不会析构
        
        // std::weak_ptr<TcpConnection> guard = connectionlist_[fd];
        // ConnectionPtr curcon = guard.lock();
        ConnectionPtr curcon = connectionlist_[fd];
        // std::cout << "before shared_count = " << curcon.use_count() << std::endl;
        
        // std::cout << "before shared_count = " << curcon.use_count() << std::endl;


        //可写事件
        if(event & EPOLLOUT)
        {
            curcon->handlewrite();
        }
        //可读事件
        if(event & EPOLLIN)
        {
            curcon->readtobuffer();
            
        }

        // std::cout << "after shared_count = " << curcon.use_count() << std::endl;    
        
        
       
    // std::cout << "connectionlist_size = " << connectionlist_.size() << std::endl;
       

    }
}   







void subepoller::addtocircularbuffer(std::shared_ptr<Entry> en)
{
    circularbuffer_.back().insert(en);
}


void subepoller::addwrite(int fd)
{
    epoll_event event;
    bzero(&event,sizeof(event));
    event.events = EPOLLIN|EPOLLOUT;
    event.data.fd = fd;
    if(epoll_ctl(epollfd_,EPOLL_CTL_MOD,fd,&event) < 0)
    {
        std::cerr << "addwrite error" << std::endl;
    }
}



void subepoller::cancelwrite(int fd)
{
    epoll_event event;
    bzero(&event,sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = fd;
    if(epoll_ctl(epollfd_,EPOLL_CTL_MOD,fd,&event) < 0)
    {
        std::cerr << "addwrite error" << std::endl;
    }
}



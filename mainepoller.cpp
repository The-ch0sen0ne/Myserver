#include "mainepoller.h"
#include<iostream>



void mainepoller::addevent(int fd,int eve)
{
    ev.data.fd = fd;
    ev.events = eve;
    if(epoll_ctl(epollfd_,EPOLL_CTL_ADD,fd,&ev) < 0)
    {
        //fixme
    }
    events_.reserve(16);
}




//���̵߳ȴ�������
void mainepoller::pool()
{
    while(1)
    {
        int nfds = epoll_wait(epollfd_,&(*(events_.begin())),events_.capacity(),10000);

        if(nfds < 0)
        {
            //fixme;
            std::cout << "epollerror" << std::endl;
        }
        else if(nfds == 0)
        {
            //û�������ӵ���ʲô������
        }
        else
        {
            
            for(int  i = 0;i < nfds;++i)
            {
                makenewconection(events_[i].data.fd);
            }

            if(nfds == events_.size())
            {
                events_.resize(events_.size()*2);
            }

        }

        events_.clear();
    }
}


//���µ���������������Ϻ󣬽��µ����ӵ��ļ��������������߳�
//���Źرմ����ļ�����������
void mainepoller::makenewconection(int fd)
{
    int newfd = accept4(fd,(sockaddr*)&client_addr,&client_len,SOCK_NONBLOCK|SOCK_CLOEXEC);
    // std::cout << "newfd = " <<  newfd <<std::endl;
            if(newfd < 0)
            {
                if(errno == EMFILE || errno == ENFILE)
                {
                    std::cout << "run out of fd" << std::endl;
                    close(backupfd);
                    newfd = accept4(fd,(sockaddr*)&client_addr,&client_len,SOCK_NONBLOCK|SOCK_CLOEXEC);
                    close(newfd);
                    backupfd = open("/dev/null",O_RDONLY);
                }
            }
            else
            {
                inet_ntop(AF_INET,&client_addr,clinet_addr_string,100);
                // printf("conniction ready  ip = %s port = %d \n",clinet_addr_string,ntohs(client_addr.sin_port));
                        
                subepoller* subepoller_ = pool_.getnextpoller();
                if(subepoller_ == nullptr)
                std::cerr << "subepoller = nullptr" << std::endl;
                // std::cout << "already get poller" << std::endl;
                
                subepoller_->addevent(newfd,EPOLLIN);
         
                // close(newfd);
            }
}
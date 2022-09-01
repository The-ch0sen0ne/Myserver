#include "epoller.h"
#include<unistd.h>
#include <iostream>
epoller::epoller()
{
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
    if(epollfd_ < 0)
    {
        //fixme
        std::cerr << "epoll_create1" << std::endl;
    }
    events_.reserve(16);
}

epoller::~epoller()
{
    
}


void epoller::removeevent(int fd)
{
    // std::cerr << "removeevent fd = " << fd <<std::endl;
    if(epoll_ctl(epollfd_,EPOLL_CTL_DEL,fd,nullptr) < 0)
    {
        //fixme
        std::cerr << "EPOLL_CTL_DEL error" << std::endl;
    }
    
}
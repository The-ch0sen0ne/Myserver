#ifndef EPOLLER_H
#define EPOLLER_H

#include<vector>
#include<sys/epoll.h>
#include<stdio.h>



class epoller
{
public:
    epoller(); 
    virtual ~epoller();
   
    virtual void addevent(int fd,int eve) = 0;

    void removeevent(int fd);

    virtual void pool() = 0;
protected:
    int epollfd_;
    std::vector<epoll_event> events_;
    
};


#endif
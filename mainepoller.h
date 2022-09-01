#ifndef MAIN_EPOLLER_H
#define MAIN_EPOLLER_H


#include "epoller.h"
#include "subepoller.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>
#include<arpa/inet.h>
#include"subepollerthreadpool.h"
//主epoller负责accpet新的连接
//只能添加socketfd

class subepollerthreadpool;
class subepollerthread;
class subepoller;

class mainepoller : public epoller
{
public:
    mainepoller():pool_(5)
    {
        backupfd = open("/dev/null",O_RDONLY|O_CLOEXEC);
    }

    ~mainepoller() override
    {

    }
    //非线程安全，只能同步调用
    void addevent(int fd,int eve) override;

    


    void pool() override;
private:
    epoll_event ev;
    int backupfd;
    //定义一个变量用于存放客户端地址
    sockaddr_in client_addr; 
    socklen_t client_len = sizeof(client_addr);
    char clinet_addr_string[100];
    // subepollerthread pollerthread_;
    threadpool pool_;
    void makenewconection(int fd);

};



#endif
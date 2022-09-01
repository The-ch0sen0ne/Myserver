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
//��epoller����accpet�µ�����
//ֻ�����socketfd

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
    //���̰߳�ȫ��ֻ��ͬ������
    void addevent(int fd,int eve) override;

    


    void pool() override;
private:
    epoll_event ev;
    int backupfd;
    //����һ���������ڴ�ſͻ��˵�ַ
    sockaddr_in client_addr; 
    socklen_t client_len = sizeof(client_addr);
    char clinet_addr_string[100];
    // subepollerthread pollerthread_;
    threadpool pool_;
    void makenewconection(int fd);

};



#endif
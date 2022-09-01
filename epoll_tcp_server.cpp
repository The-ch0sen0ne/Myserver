#include <sys/types.h>         
#include <sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/epoll.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"mainepoller.h"
#include"address.h"

void Exit_error(const char* error_msg)
{
    char msg[100];
    snprintf(msg,sizeof(msg),"%s : ",error_msg);
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc,char*argv[])
{
    int socketfd = socket(PF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC,0);
    if(socketfd == -1)
    {
        Exit_error("socket");
        
    }


    // int socketfd1 = socket(PF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC,0);
    // if(socketfd1 == -1)
    // {
    //     Exit_error("socket");
        
    // }
    


    

    //����socketfd���ö˿ڸ���
    int on = 1;
    if(setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&on,sizeof(on)) < 0)
    {
        Exit_error("setsockopt");
    }


    // if(setsockopt(socketfd1,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&on,sizeof(on)) < 0)
    // {
    //     Exit_error("setsockopt");
    // }
    
    //���÷������ĵ�ַ
    //ip����Ϊ���յ�����Ķ˿�Ҳ����INADDR_ANY����Ҫת��Ϊ�����ֽ���

    Address a1(8001);

 
    Bind(socketfd,a1);
    //���׽���ת��Ϊ�����׽���
    if(listen(socketfd,1024) < 0)
    {
       Exit_error("listen");
    }


    // Address a2(8002);
    // Bind(socketfd1,a2);
    
    //���׽���ת��Ϊ�����׽���
    // if(listen(socketfd1,1024) < 0)
    // {
    //    Exit_error("listen");
    // }


    mainepoller m_epoller;
    m_epoller.addevent(socketfd,EPOLLIN);
    // m_epoller.addevent(socketfd1,EPOLLIN);
    m_epoller.pool();

}




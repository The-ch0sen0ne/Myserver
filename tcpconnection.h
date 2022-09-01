#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include "subepoller.h"
#include <memory>
#include <unistd.h>
#include"connectionbuffer.h"
#include"httpcontext.h"
#include "entry.h"
#include "httpresponse.h"
#include <iostream>

class HttpContext;
class ConnectionBuffer;
class subepoller;
class Entry;

//��ÿ��TCPConnection��װ�ɵ�������
//���������ӵ���ʱ����
//����ʱ�Զ��ر�����
class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd,subepoller* epoller) : fd_(fd),epoller_(epoller)
    {

    }

    ~TcpConnection()
    {
        // std::cout << "~TcpConnection fd = " <<  fd_ << std::endl;
        //�ر����� 
        if(close(fd_) != 0)
        {
            std::cout << "close error" << std::endl;
        }
    }



    

    void readtobuffer();

    //destoryconnectionʵ�ֵĹ�����ȡ��epoll�Ĺ�ע���ر������ļ�������
    void destoryconnection();
    
    ConnectionBuffer* getreadbuffer()
    {
        return &readbuffer_;
    }
    

    void setentry(std::shared_ptr<Entry> en)
    {
        entry_ = en;
    }

    std::weak_ptr<Entry>& getentry()
    {
        return entry_;
    }


    void handleread();
    void handlewrite();
   
private:
    int fd_;
    
    ConnectionBuffer readbuffer_;
    ConnectionBuffer writebuffer_;
    HttpContext context_;
    //���ƹ���������
    subepoller* epoller_;
    std::weak_ptr<Entry> entry_;
    void request();
    void send(ConnectionBuffer&); 
    
   
};








#endif
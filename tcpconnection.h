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

//将每个TCPConnection封装成单独的类
//当有新连接到来时就在
//析构时自动关闭连接
class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd,subepoller* epoller) : fd_(fd),epoller_(epoller)
    {

    }

    ~TcpConnection()
    {
        // std::cout << "~TcpConnection fd = " <<  fd_ << std::endl;
        //关闭连接 
        if(close(fd_) != 0)
        {
            std::cout << "close error" << std::endl;
        }
    }



    

    void readtobuffer();

    //destoryconnection实现的功能是取消epoll的关注并关闭连接文件描述符
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
    //不掌管生命周期
    subepoller* epoller_;
    std::weak_ptr<Entry> entry_;
    void request();
    void send(ConnectionBuffer&); 
    
   
};








#endif
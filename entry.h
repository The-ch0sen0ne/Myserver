#ifndef ENTRY_H
#define ENTRY_H

#include<memory>
#include"tcpconnection.h"


class TcpConnection;


class Entry
{
public:
    Entry(std::shared_ptr<TcpConnection> weak_) : connectionptr_(weak_)
    {

    }


    ~Entry();
    
private:
    std::weak_ptr<TcpConnection> connectionptr_;

};








#endif
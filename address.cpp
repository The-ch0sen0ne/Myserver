#include "address.h"
#include<iostream>


Address::Address(const char* ip,uint16_t port)
{
    bzero(&addr_,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    if(inet_pton(AF_INET,ip,&addr_) < 0)
    {
        std::cout << "inet_pton error" << std::endl;
    }
}



 Address::Address(uint16_t port, bool loopbackOnly)
 {
    bzero(&addr_,sizeof(addr_));
    addr_.sin_family = AF_INET;
    in_addr_t ip = loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(ip);
 }


void Bind(int sockfd, Address& addr)
{
    const sockaddr_in& addr_ = addr.getSockAddrInet();
    int ret = bind(sockfd,(sockaddr*)(&addr),static_cast<socklen_t>(sizeof(addr)));
    if(ret < 0)
    {
        std::cout << "Bind error" << std::endl;
    }
}

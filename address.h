#ifndef ADDRESS_H
#define ADDRESS_H


#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string>
#include <string.h>

class Address
{
public:
    Address(const char* ip, uint16_t port);


    Address(const Address& addr):addr_(addr.addr_)
    {

    }

    Address(const struct sockaddr_in& addr): addr_(addr)
    { 

    }


    //如果仅指定port，不指定ip，则ip为INADDR_ANY(即0.0.0.0表示在任意的地址监听)
    explicit Address(uint16_t port = 0, bool loopbackOnly = false);
    const sockaddr_in& getSockAddrInet() const { return addr_; }


    void setSockAddrInet(const struct sockaddr_in& addr) { addr_ = addr; }

    //返回网络序的IP地址
    uint32_t ipNetEndian() const { return addr_.sin_addr.s_addr; }
    //返回网络序的端口号
    uint16_t portNetEndian() const { return addr_.sin_port; }
private:
    sockaddr_in addr_;
};


void Bind(int sockfd, Address& addr);


#endif
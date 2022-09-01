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


    //�����ָ��port����ָ��ip����ipΪINADDR_ANY(��0.0.0.0��ʾ������ĵ�ַ����)
    explicit Address(uint16_t port = 0, bool loopbackOnly = false);
    const sockaddr_in& getSockAddrInet() const { return addr_; }


    void setSockAddrInet(const struct sockaddr_in& addr) { addr_ = addr; }

    //�����������IP��ַ
    uint32_t ipNetEndian() const { return addr_.sin_addr.s_addr; }
    //����������Ķ˿ں�
    uint16_t portNetEndian() const { return addr_.sin_port; }
private:
    sockaddr_in addr_;
};


void Bind(int sockfd, Address& addr);


#endif
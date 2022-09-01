#include"entry.h"


Entry::~Entry()
{
    // std::cout << "~Entry" << std::endl;
    std::shared_ptr<TcpConnection> conn = connectionptr_.lock();
    if(conn)
    {
        conn->destoryconnection();

    }
}
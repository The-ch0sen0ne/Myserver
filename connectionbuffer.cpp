#include "ConnectionBuffer.h"
#include <string.h>
#include<iostream>
#include<unistd.h>
#include<sys/uio.h>
#include<errno.h>



const char ConnectionBuffer::kCRLF[] = "\r\n";



int ConnectionBuffer::readfromfd(int fd,int* savedErrno)
{
    //char backup[]
    // int n = read(fd,beginwrite(),writeable());
    // return n;
    int writelen =  writeable();
    char extrabuf[65535];
    // char extrabuf[30];
    
    iovec vec[2];
    vec[0].iov_base = beginwrite();
    vec[0].iov_len = writeable();

    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);

    const int iovcnt = (writelen <= sizeof(extrabuf)) ? 2 : 1;
    const int n = readv(fd,vec,iovcnt);

    if(n < 0)
    {
        *savedErrno = errno;
    }
    else if(n < writeable())
    {
        writeindex += n;
    }
    else
    {
        writeindex = end();
        append(extrabuf,n - writelen);
    }



    return n;
}



void ConnectionBuffer::append(const char* sour,int len)
{
    if(len > writeable())
        makesapce(len);

    memcpy(beginwrite(),sour,len);

    writeindex += len;

}


void ConnectionBuffer::makesapce(int n)
{
    if(readindex + writeable() >= n)
    {
        //左移缓冲区
        int readlen = readable();
        memcpy(&(*buf_.begin()),peek(),readlen);
        //更新两个下标
        readindex = 0;
        writeindex = readlen;

        //for test
        if(readable() != readlen || writeable() < n)
        {
            std::cerr << "move error" << std::endl;
        }
    }
    else
    {
        int newlen = buf_.size() + 2*n;
        buf_.resize(newlen);
    }
}
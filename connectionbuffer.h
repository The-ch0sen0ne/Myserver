#ifndef CONNECTIONBUFFER_H
#define CONNECTIONBUFFER_H

#include<string>
#include<vector>
#include<assert.h>
#include<algorithm>
//为了避免vector扩充时迭代器失效，选择使用下标来指示当前位置
//beg是容器开始下标，end是尾后下标，扩充容器选择resize接口
//readindex是开始读位置的下标，writeindex是开始写位置的下标也是读位置的尾后下标
//readable = writeindex - readindex
//writeable = end - writeindex

//从缓冲区读取内容时有两种情况
//1、能将所有readable内容读完时：读取完成后readindex = writeindex = 0
//2、只能读完部分时，只向后移动readindex


//向缓冲区写入内容需要确保容器大小满足要求，如果空间不足时有两种情况,写入目标大小为0
//1、readindex - beg + writeable < n ，直接使用resize扩容
//2、readindex - beg + writeable >= n,整体向左移动进行扩容


static const int bufsize = 1024;

class ConnectionBuffer
{
public:
    ConnectionBuffer() : buf_(bufsize),readindex(0),writeindex(0)
    {

    }

    ~ConnectionBuffer() {}


    //将socket的内容读入缓冲区,要保存errno的原因是为了避免多线程改变errno值
    int readfromfd(int fd,int* savedErrno);



    const char* peek() { return &(*buf_.begin())+readindex; }

    const char* peek() const { return &(*buf_.begin())+readindex; }
    char* beginwrite() { return &(*buf_.begin())+writeindex; }

    const char* beginwrite() const { return &(*buf_.begin())+writeindex; }
    void append(const char* sour,int len);

    //移动readindex
    void retrive(int n)
    {
        assert(n <= readable());
        readindex += n;
    }


    std::string readalltostring()
    {
        std::string s(&(*buf_.begin()),readable());
        readindex = writeindex = 0;
        return s;
    }

    int readable() { return writeindex - readindex; }

    int writeable() { return end() - writeindex; }



   const char* findCRLF() const
    {
        const char* crlf = std::search(peek(),beginwrite(), kCRLF, kCRLF+2);
        
        return (crlf == beginwrite()) ? nullptr : crlf;
    }


    const char* findCRLF(const char* start) const
    {
        const char* crlf = std::search(start,beginwrite(), kCRLF, kCRLF+2);
        
        return (crlf == beginwrite()) ? nullptr : crlf;
    }

    
private:
    std::vector<char> buf_;
    int readindex;
    int writeindex;
    const int beg = 0;

    int end() { return buf_.size(); }

    void makesapce(int n);
    
    static const char kCRLF[];
    
};



#endif
#ifndef CONNECTIONBUFFER_H
#define CONNECTIONBUFFER_H

#include<string>
#include<vector>
#include<assert.h>
#include<algorithm>
//Ϊ�˱���vector����ʱ������ʧЧ��ѡ��ʹ���±���ָʾ��ǰλ��
//beg��������ʼ�±꣬end��β���±꣬��������ѡ��resize�ӿ�
//readindex�ǿ�ʼ��λ�õ��±꣬writeindex�ǿ�ʼдλ�õ��±�Ҳ�Ƕ�λ�õ�β���±�
//readable = writeindex - readindex
//writeable = end - writeindex

//�ӻ�������ȡ����ʱ���������
//1���ܽ�����readable���ݶ���ʱ����ȡ��ɺ�readindex = writeindex = 0
//2��ֻ�ܶ��겿��ʱ��ֻ����ƶ�readindex


//�򻺳���д��������Ҫȷ��������С����Ҫ������ռ䲻��ʱ���������,д��Ŀ���СΪ0
//1��readindex - beg + writeable < n ��ֱ��ʹ��resize����
//2��readindex - beg + writeable >= n,���������ƶ���������


static const int bufsize = 1024;

class ConnectionBuffer
{
public:
    ConnectionBuffer() : buf_(bufsize),readindex(0),writeindex(0)
    {

    }

    ~ConnectionBuffer() {}


    //��socket�����ݶ��뻺����,Ҫ����errno��ԭ����Ϊ�˱�����̸߳ı�errnoֵ
    int readfromfd(int fd,int* savedErrno);



    const char* peek() { return &(*buf_.begin())+readindex; }

    const char* peek() const { return &(*buf_.begin())+readindex; }
    char* beginwrite() { return &(*buf_.begin())+writeindex; }

    const char* beginwrite() const { return &(*buf_.begin())+writeindex; }
    void append(const char* sour,int len);

    //�ƶ�readindex
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
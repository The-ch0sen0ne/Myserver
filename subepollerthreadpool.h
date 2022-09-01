#ifndef SUBEPOLLERTHREADPOOL_H
#define SUBEPOLLERTHREADPOOL_H

#include "subepollerthread.h"
#include <vector>
#include<memory>
class subepoller;
class subepollerthread;


//固定大小的线程池
class threadpool
{
public:
    threadpool(int nums = 5);

    ~threadpool();

    subepoller* getnextpoller();
private:
    bool started_;
    //线程池的实际线程数，初始化后不能改变了
    const int nums_;
    int cur_;
    std::vector<std::unique_ptr<subepollerthread>> pool_;
    std::vector<subepoller*> pollers_;
};








#endif
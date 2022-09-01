#ifndef SUBEPOLLERTHREADPOOL_H
#define SUBEPOLLERTHREADPOOL_H

#include "subepollerthread.h"
#include <vector>
#include<memory>
class subepoller;
class subepollerthread;


//�̶���С���̳߳�
class threadpool
{
public:
    threadpool(int nums = 5);

    ~threadpool();

    subepoller* getnextpoller();
private:
    bool started_;
    //�̳߳ص�ʵ���߳�������ʼ�����ܸı���
    const int nums_;
    int cur_;
    std::vector<std::unique_ptr<subepollerthread>> pool_;
    std::vector<subepoller*> pollers_;
};








#endif
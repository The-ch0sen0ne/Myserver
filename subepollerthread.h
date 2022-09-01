#ifndef SUBEPOLLERTHREAD_H
#define SUBEPOLLERTHREAD_H


#include<thread>
#include<condition_variable>
#include<mutex>
#include "subepoller.h"

class subepoller;

class subepollerthread
{

public:
    subepollerthread();
    ~subepollerthread();
    subepoller* getpoller();

private:
    std::mutex mutex_;
    std::condition_variable condition_;
    std::thread thread_;
    subepoller* subepoller_;
    void init();
    
};








#endif
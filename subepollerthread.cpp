#include"subepollerthread.h"
#include<functional>
#include<iostream>

subepollerthread::subepollerthread() : subepoller_(nullptr),thread_(std::bind(&subepollerthread::init,this))
{
    
}



subepollerthread::~subepollerthread()
{
    //ֻ�г������ʱ�Ż��ߵ���һ����ʵ�������ò�����
    std::cout << "~subepollerthread" << std::endl;
    if(thread_.joinable())
    {
        thread_.join();
    }
    
}


subepoller* subepollerthread::getpoller()
{
    // if(subepoller_ == nullptr)
    
    std::unique_lock<std::mutex> lock(mutex_);
    while(subepoller_ == nullptr)
    condition_.wait(lock);

    return subepoller_;
}


void subepollerthread::init()
{
    subepoller cur;
    {
        std::lock_guard<std::mutex> lock_(mutex_);
        subepoller_ = &cur;
        condition_.notify_all();
    }
    
    // std::cout << "init thread" << std::endl;
    subepoller_->pool();

    
}



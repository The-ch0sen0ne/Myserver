#include "subepollerthreadpool.h"
#include <iostream>


threadpool::threadpool(int nums):started_(0),nums_(nums),cur_(0)
{
    // std::cout << "nums = " << nums_ << std::endl;
    for(int i = 0;i < nums_;++i)
    {
        // std::cout << "i = " << i << std::endl;
        subepollerthread* temp = new subepollerthread();
        pool_.push_back(std::unique_ptr<subepollerthread>(temp));
        pollers_.push_back(temp->getpoller());
    }

    started_ = 1;
}



threadpool::~threadpool()
{
    started_ = 0;
    //关闭所有线程
    for(int i = 0;i < nums_;++i)
    {
        // std::cout << "i = " << i << std::endl;
        subepoller* temp = pollers_[i];
        temp->stop();
        while(temp->getstate());
        pollers_[i] = nullptr;
    }
    pool_.clear();
}


subepoller* threadpool::getnextpoller()
{
    
    if(!started_)
        return nullptr;
    if(cur_ >= nums_)
        cur_ = 0;
    
    return pollers_[cur_++];
}
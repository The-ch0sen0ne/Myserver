#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include<array>
#include<vector>
#include<iostream>
// #include <unordered_set>
// #include "entry.h"
//对外提供的接口
// cb.size();//缓冲区已存放数据的大小，如果没有插入，则为0
// cb.capacity();//缓冲区的容量
// cb.empty();//判断缓冲区是否为空
// cb.full();//判断缓冲区是否已满
// cb.push_back(4); //尾部插入。如果容量已满，踢出头部元素
// cb.push_front(5);//头部插入。如果容量已满，踢出尾部元素
// cb.pop_back();//删除尾部的元素
// cb.pop_front();//删除头部的元素
// cb[0];//访问第一个元素
// cb.at(0);//访问第一个元素
// cb.front();//访问第一个元素
// cb.back();//访问最后一个元素








//下标front_和end_分别指代第一个元素和最末尾1个元素的下标，初始化时都为-1，当缓冲区内元素个数减为0时



// class Entry;

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(int capacity = 30):
    capacity_(capacity),buf_(std::vector<T>(capacity)),front_(-1),end_(-1),size_(0)
    {}
    bool empty() { return size_ == 0;}
    bool full() { return size_ == capacity_;}



    void push_back(T v)
    {
        if(empty())
        {
            front_ = end_ = 0;
            // buf_[end_] = v;
        }
        else
        {
            if(full())
            {
                pop_front();
                
            }           
            end_ = (end_ + 1 < capacity_) ? end_ + 1 : 0;
                                     
        }

        size_++;
        buf_[end_] = v; 
    }


    void push_front(T v)
    {
        if(empty())
        {
            front_ = end_ = 0;
            // buf_[end_] = v;
        }
        else
        {
            if(full())
            {
                pop_back();
                
            }           
            front_ = (front_ - 1 >= 0) ? front_ - 1 : capacity_ - 1;
                                     
        }

        size_++;
        buf_[front_] = v; 
    }


    void pop_back()
    {
        if(empty())
        std::cerr << "buffer is empty" << std::endl;
        size_--;
        if(size_ == 0)
        front_ = end_ = -1;
        else
        {
            end_ = (end_ - 1 >= 0) ? end_ - 1 : capacity_ - 1;
        }

    }


    void pop_front()
    {
        if(empty())
        std::cerr << "buffer is empty" << std::endl;
        size_--;
        if(size_ == 0)
        front_ = end_ = -1;
        else
        {
            front_ = (front_ + 1 < capacity_) ? front_ + 1 : 0;
        }
    }


    T& front()
    {
        if(empty())
        std::cerr << "buffer is empty" << std::endl;
        return buf_[front_];
    }
    T& back()
    {
        if(empty())
        std::cerr << "buffer is empty" << std::endl;
        return buf_[end_];
    }


    void test()
    {
    if(empty())
    std::cout << "empty" << std::endl;
    else
    {
        std::cout << "size = " << size_ << std::endl;
        if(end_ >= front_)
        {
            for(int i = front_;i <= end_;++i)
            {
                std::cout << buf_[i] << "  ";
            }
            std::cout << std::endl;
        }
        else
        {
            for(int i = front_;i < capacity_;++i)
            {
                std::cout << buf_[i] << "  ";
            }
            for(int i = 0;i < front_;++i)
            {
                std::cout << buf_[i] << "  ";
            }
            std::cout << std::endl;
        }
    }
    }


    const int size() const
    {
        return size_;
    }
private:
    int capacity_;
    std::vector<T> buf_;
    int front_;
    int end_;
    int size_;

    
    
};







#endif
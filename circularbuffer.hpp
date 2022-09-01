#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include<array>
#include<vector>
#include<iostream>
// #include <unordered_set>
// #include "entry.h"
//�����ṩ�Ľӿ�
// cb.size();//�������Ѵ�����ݵĴ�С�����û�в��룬��Ϊ0
// cb.capacity();//������������
// cb.empty();//�жϻ������Ƿ�Ϊ��
// cb.full();//�жϻ������Ƿ�����
// cb.push_back(4); //β�����롣��������������߳�ͷ��Ԫ��
// cb.push_front(5);//ͷ�����롣��������������߳�β��Ԫ��
// cb.pop_back();//ɾ��β����Ԫ��
// cb.pop_front();//ɾ��ͷ����Ԫ��
// cb[0];//���ʵ�һ��Ԫ��
// cb.at(0);//���ʵ�һ��Ԫ��
// cb.front();//���ʵ�һ��Ԫ��
// cb.back();//�������һ��Ԫ��








//�±�front_��end_�ֱ�ָ����һ��Ԫ�غ���ĩβ1��Ԫ�ص��±꣬��ʼ��ʱ��Ϊ-1������������Ԫ�ظ�����Ϊ0ʱ



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
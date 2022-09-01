// #include"circularbuffer.h"
// #include<iostream>

// template <typename T>
// void CircularBuffer<T>::push_back(T v)
// {
//     if(empty())
//     {
//         front_ = end_ = 0;
//         buf_[end_] = v;
//     }
//     else
//     {
//         if(full())
//         {
//             pop_front();
//             end_ = (end_ + 1 < capacity_) ? end_ + 1 : 0;
//             buf_[end_] = v;
//         }
//         else
//         {
//             end_ = (end_ + 1 < capacity_) ? end_ + 1 : 0;
//             buf_[end_] = v;
//             size_++;
//         }
//     }
// }



// template <typename T>
// void CircularBuffer<T>::push_front(T v)
// {

// }

// template <typename T>
// void CircularBuffer<T>::pop_back()
// {
//     if(empty())
//     std::cerr << "buffer is empty" << std::endl;
//     size_--;
//     if(size_ == 0)
//     front_ = end_ = -1;
//     else
//     {
//         end_ = (end_ - 1 >= 0) ? end_ - 1 : capacity_ - 1;
//     }

// }

// template <typename T>
// void CircularBuffer<T>::pop_front()
// {
//     if(empty())
//     std::cerr << "buffer is empty" << std::endl;
//     size_--;
//     if(size_ == 0)
//     front_ = end_ = -1;
//     else
//     {
//         front_ = (front_ + 1 < capacity_) ? front_ + 1 : 0;
//     }
// }

// template <typename T>
// T CircularBuffer<T>::front()
// {
//     if(empty())
//     std::cerr << "buffer is empty" << std::endl;
//     return buf_[front_];
// }

// template <typename T>
// T CircularBuffer<T>::back()
// {
//     if(empty())
//     std::cerr << "buffer is empty" << std::endl;
//     return buf_[end_];
// }


// template <typename T>
// void CircularBuffer<T>::test()
// {
//     if(empty())
//     std::cout << "empty" << std::endl;
//     else
//     {
//         std::cout << "size = " << size_ << std::endl;
//         if(end_ >= front_)
//         {
//             for(int i = front_;i <= end_;++i)
//             {
//                 std::cout << buf_[i] << "  ";
//             }
//             std::cout << std::endl;
//         }
//         else
//         {
//             for(int i = front_;i < capacity_;++i)
//             {
//                 std::cout << buf_[i] << "  ";
//             }
//             for(int i = 0;i < front_;++i)
//             {
//                 std::cout << buf_[i] << "  ";
//             }
//             std::cout << std::endl;
//         }
//     }
// }
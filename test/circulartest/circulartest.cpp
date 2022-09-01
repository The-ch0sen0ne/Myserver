#include"circularbuffer.hpp"


int main()
{
    CircularBuffer<int> buf;
    for(int i = 0;i < 20;++i)
    {
        buf.push_front(i);
        buf.test();
    }


    return 0;
}
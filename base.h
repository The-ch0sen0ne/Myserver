#ifndef BASE_H
#define BASE_H


class noncopyable
{
public:
    noncopyable()
    {
        
    }
private:
    noncopyable(const noncopyable& a);

    noncopyable& operator= (const noncopyable a);
};

//ȥ��const
template<typename To, typename From>
inline To implicit_cast(From const &f)
{
    return f;
}





#endif
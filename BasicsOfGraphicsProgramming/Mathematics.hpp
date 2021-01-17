#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

template <typename T>
int signum(T a)
{
    if(a > 0)
    {
        return 1;
    }
    else
    {
        if(a < 0)
        {
            return -1;
        }
    }
    return 0;
};

template <typename Type>
class Vector2D
{
    public:
        Type x;
        Type y;
    Vector2D(Type x, Type y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif

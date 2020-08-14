//#define _STD_
#define _SELF_

struct S
{
    double operator()(char, int&);
    float operator()(int){return 1.0;}
};

struct A_class
{
public:
    int some_func(int a1, int a2)
    {
        return a1 + a2;
    }
};

int test(const int& __a, const int& __b)
{
    return __a * __b;
}

#ifdef _STD_

#include <iostream>
#include <type_traits>

int main()
{
    std::result_of<S(char, int&)>::type d  = 3.14;

    std::result_of<int(*)(int, int)>
    return 0;
}


#endif

#ifdef _SELF_
#include "type_traits.cpp"
#include "stdio.h"

int main()
{
    yjh_def::__check_complete<int(int, int)> __t;       // 这两个类的实例，没有任何的意义，这个类主要用于编译期的检错
    yjh_def::__check_complete<int (A_class::*)(int, int)> __tt;     // 注意指向类的对象函数的指针的写法
    yjh_def::result_of<S(char, int&)>::type d  = 3.14;
    printf("%f\n", d);
    return 0;
}

#endif
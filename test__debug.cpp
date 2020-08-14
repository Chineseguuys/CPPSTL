#include <iostream>

#ifndef _LIBCPP_ASSERT
#define _LIBCPP_ASSERT(x,m)  ((void)0)
#endif


const unsigned int LENGTH = 100;

void test(unsigned int __n)
{
    _LIBCPP_ASSERT(__n < LENGTH, "the number is out of range");
    std::cout << "have gone"<< '\n';
}



int main(int argc, char** argv)
{
    test(120);
    return 0;
}
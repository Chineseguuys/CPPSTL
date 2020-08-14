
#include <iostream>
#define _SELF_
//#define _STD_

struct A
{
private:
    double  floating_n;
    int     integer_n;
public:
    A() : floating_n(0.0f), integer_n(0) {}
};

#ifdef _SELF_
#include "type_traits.cpp"

int main(int argc, char* argv[])
{
    std::cout << std::boolalpha;
    std::cout << yjh_def::is_assignable<int, int>::value << '\n';
    std::cout << yjh_def::is_assignable<double, int>::value << '\n';
    std::cout << yjh_def::is_assignable<int, A>::value << '\n';
    return 0;
}

#endif


#ifdef _STD_
#include <type_traits>

int main()
{
    std::is_assignable<int, int>
}


#endif
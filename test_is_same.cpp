#include "type_traits.cpp"




#include <iostream>

int main()
{
    std::cout << yjh_def::_IsSame<int, int>::value << '\n';
    std::cout << yjh_def::_IsNotSame<int, const int>::value << '\n';
    return 0;
}
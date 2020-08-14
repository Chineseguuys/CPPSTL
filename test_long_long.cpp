#include <iostream>



int main()
{
    intmax_t integer = 1LL;
    integer = (integer << (sizeof(intmax_t) * 8 - 1));
    std::cout << integer << '\n';
    return 0;
}
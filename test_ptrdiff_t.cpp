#include <iostream>

#define __CHAR_BIT_ 8

int main()
{
    std::cout << std::hex << (~std::ptrdiff_t(0)) << '\n';
    std::cout << (std::ptrdiff_t(std::ptrdiff_t(1) << (sizeof(std::ptrdiff_t) * __CHAR_BIT_ - 1))) << '\n';
    std::cout << (~std::ptrdiff_t(0) ^ std::ptrdiff_t(std::ptrdiff_t(1) << (sizeof(std::ptrdiff_t) * __CHAR_BIT_ - 1))) << '\n';
    const std::ptrdiff_t __m = (~std::ptrdiff_t(0) ^ 
                std::ptrdiff_t(ptrdiff_t(1) << (sizeof(std::ptrdiff_t) * __CHAR_BIT_ - 1)))
                / sizeof(int);
    std::cout<< std::dec << __m << '\n';
    return 0;
}
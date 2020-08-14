#include <iostream>
#include <type_traits>
#include <typeinfo>


enum Color
{
    Red = 0xff0000,
    Blue = 0x00ff00,
    Green = 0x0000ff
};

int main(int argc, char** argv)
{
    std::cout << typeid(__underlying_type(Color)).name() << '\n';
    return 0;
}


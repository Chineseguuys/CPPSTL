#include <type_traits>
#include <iostream>

enum Color{Green = 1, Red = 2};

int main(int argc, char** argv)
{
    std::cout << __is_enum(Color) << '\n';
    return 0;
}
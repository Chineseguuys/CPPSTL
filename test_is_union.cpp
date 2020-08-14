#include "type_traits.cpp"
#include <type_traits>
#include <iostream>

union integer_char
{
    int a_integer;
    char chars[4];
};

class a_class
{
private:
    int vec;
public:
    a_class() : vec(0) {}
};

int main()
{
    std::cout << yjh_std::is_union<integer_char>::value << '\n';
    std::cout << yjh_std::is_union<a_class>::value << '\n';
    std::cout << yjh_std::is_class<a_class>::value << '\n';

    //std::cout << __is_union(integer_char) << '\n';
    return 0;
}

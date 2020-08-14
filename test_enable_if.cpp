#include <iostream>
#include <type_traits>



int main()
{
    std::enable_if<sizeof(int) >= sizeof(char), bool>::type = false; //
}
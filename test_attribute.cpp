#include <iostream>



union My_union
{
    unsigned char _data[3];
    struct __attribute__((__aligned__(8))) { } _align;
};




int main()
{
    std::cout << sizeof(My_union) << '\n';
    return 0;
}
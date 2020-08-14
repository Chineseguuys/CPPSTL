#include "bit.cpp"


#include <iostream>
int main(int argc, char** argv)
{
    unsigned int temp = 0x00007777;
    unsigned int rotate_temp = yjh_def::__rotl(temp, 16);
    std::cout << std::hex << temp << '\n';
    std::cout << std::hex << rotate_temp << '\n';
    return 0;
}
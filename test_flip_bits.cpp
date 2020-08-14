#include <iostream>


int main()
{
	int integer_zero = 0;
	int flip_zero = ~0;
	std::cout << std::hex << integer_zero << '\n'; //0x00000000
	std::cout << std::hex << flip_zero << std::dec<< flip_zero << '\n'; // 0xffffffff  对应最大的整数负数 -1
	std::cout << std::dec << flip_zero / sizeof(int) << '\n';
	return 0;
}
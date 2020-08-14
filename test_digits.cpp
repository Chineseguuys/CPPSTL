#include <iostream>
#include <bitset>

int main(int argc, char** argv)
{
	int integer_a = 1;
	std::cout << std::hex << (integer_a << 31) << '\n';
	return 0;
}
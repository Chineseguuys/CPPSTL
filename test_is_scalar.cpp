#include <iostream>
#include <type_traits>

union int_char
{
	int integer;
	char ch[4];
};

enum Color {Blue = 1, Green = 2, Red = 3};


int main(int argc, char** argv)
{
	std::cout << __is_enum(int_char) << '\n';
	std::cout << __is_enum(Color) << '\n';

	return 0;
}


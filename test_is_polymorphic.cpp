#include <iostream>
#include <type_traits>


int main()
{
	std::cout << __is_polymorphic(int) << '\n';
	return 0;
}
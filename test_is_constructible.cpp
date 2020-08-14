#include "type_traits.cpp"
#include <iostream>




int main()
{
	std::cout << std::boolalpha;
	std::cout << yjh_def::is_constructible<int>::value << '\n';
	std::cout << yjh_def::is_constructible<int[10]>::value << '\n';
	return 0;
}
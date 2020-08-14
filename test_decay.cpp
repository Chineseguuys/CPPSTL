#include <iostream>
#include <typeinfo>


#define _STD_

#ifdef _SELF_

#include "type_traits.cpp"

int main(int argc, char** argv)
{
	std::cout << typeid(yjh_def::decay<int[4]>::type).name() << '\n';
	std::cout << typeid(yjh_def::decay<int(*)(int, double)>::type).name() << '\n';
	return 0;
}

#endif

#ifdef _STD_
#include <type_traits>

int main()
{
	std::cout << typeid(std::decay<int[4]>::type).name() << '\n';
	std::cout << typeid(std::decay<int(int, int)>::type).name() << '\n';
	std::cout << std::boolalpha;
	std::cout << std::is_function<int(int, double, char)>::value << '\n';
	return 0;	
}

#endif
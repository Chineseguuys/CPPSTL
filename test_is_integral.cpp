#include <iostream>


#define _SELF_


#ifdef _SELF_

#include "type_traits.cpp"

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << yjh_def::is_integral<const int&>::value << '\n';	//false
	std::cout << yjh_def::is_integral<const int>::value << '\n';	//true
	std::cout << yjh_def::is_integral<const int*>::value << '\n';	//false
	return 0;
}

#endif // _SELF_

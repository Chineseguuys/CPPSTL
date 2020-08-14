#include "type_traits.cpp"
#include <iostream>
#include <typeinfo>

//#define _TEST_DECLTYPE_
#define _TESTING_COMMON_TYPE_

#ifdef _TESTING_COMMON_TYPE_
int main()
{
	int integer = 100;
	double floating = 11.23;
	std::cout << typeid(yjh_def::common_type<int, double>::type).name() << '\n';
	std::cout << typeid(yjh_def::common_type<short, double, int>::type).name() << '\n';
	std::cout << typeid(yjh_def::common_type<double, int, short, char>::type).name() << '\n';
	return 0;
}
#endif


#ifdef _TEST_DECLTYPE_

int main()
{
	int integer  = 100;
	double floating = 12.345;
	std::cout << typeid(decltype((floating, integer))).name() << '\n';
	return 0;
}

#endif
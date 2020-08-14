#include <iostream>
#include <typeinfo>

#define _SELF_





#ifdef _SELF_
#include "utility.cpp"
int main()
{
	//std::cout << typeid(yjh_def::__make_pair_return<int>::type).name() << '\n';
	int integer_a = 101;
	int integer_b = 101;
	yjh_def::pair<int, int> integer_1x2_b = yjh_def::make_pair(integer_a, integer_b);
	//std::cout << integer_a << "  " << integer_b << '\n';
	return 0;
}

#endif
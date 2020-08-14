#include <iostream>

#define _SELF_



#ifdef _SELF_

#include "typeinfo.cpp"

int main(int argc, char** argv)
{
	const int integer_a = 100;
	const yjh_def::type_info& tp_inf = typeid(integer_a);
	std::cout << tp_inf.name() << '\n';
	return 0;
}


#endif // _SELF_


#ifdef _STD_

#include <typeinfo>

int main()
{
	const double floating_a = 3.141590f;
	const std::type_info& type_information = typeid(floating_a);
	std::cout << type_information.name() << '\n';
	return 0;
}


#endif // _STD_

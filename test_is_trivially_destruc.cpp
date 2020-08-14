#include <iostream>

#define _STD_DEFINED_
//#define _SELF_DEFINED_

struct A
{
private:
	int integer;
public:
	A(const int& __integer) : integer(__integer) {}
};

struct B
{
private:
	int integer;
public:
	B(const int& __integer) : integer(__integer) {}
	~B() {}
};

#ifdef _STD_DEFINED_
#include <type_traits>

int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	std::cout << std::is_trivially_destructible<A>::value << '\n';	//true
	std::cout << std::is_trivially_destructible<B>::value << '\n';	//flase
	std::cout << std::is_trivially_destructible<int>::value << '\n'; //true
	return 0;
}

#endif


#ifdef _SELF_DEFINED_
#include "type_traits.cpp"

int main()
{
	std::cout << std::boolalpha;
	std::cout << yjh_def::is_trivially_destructible<A>::value << '\n';
	std::cout << yjh_def::is_trivially_destructible<B>::value << '\n';
	std::cout << yjh_def::is_trivially_destructible<int>::value << '\n';
	return 0;
}
#endif
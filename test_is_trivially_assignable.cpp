#include <iostream>


//#define _STD_
#define _SELF_

struct A
{
private:
	int integer;
public:
	A() : integer(0) {};
	void operator=(const A& __x){integer = __x.integer;}
};

struct B
{
private:
	int integer;
public:
	B() : integer(0) {};
};

#ifdef _STD_
#include <type_traits>
int main()
{
	std::cout << std::boolalpha;
	std::cout << std::is_trivially_assignable<A, const A&>::value << '\n';
	std::cout << std::is_trivially_assignable<B, const B&>::value << '\n';
	return 0;
}
#endif

#ifdef _SELF_
#include "type_traits.cpp"
int main()
{
	std::cout << std::boolalpha;
	std::cout << yjh_def::is_trivially_assignable<A, A>::value << '\n';
	std::cout << yjh_def::is_trivially_assignable<B, const B&>::value << '\n';
	return 0;
}
#endif
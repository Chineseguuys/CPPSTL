#include <iostream>

//#define _SELF_
struct A
{
private:
    double  floating_n;
    int     integer_n;
public:
    A() : floating_n(0.0f), integer_n(0) {}
	A(A&& __x) noexcept{}
	A(const A& __x) noexcept{}
};


#ifdef _SELF_

#include "type_traits.cpp"

int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	std::cout << yjh_def::is_nothrow_move_constructible<A>::value << '\n';
	std::cout << yjh_def::is_nothrow_move_constructible<int>::value << '\n';
	std::cout << yjh_def::is_nothrow_copy_constructible<A>::value << '\n';
	std::cout<< yjh_def::is_nothrow_constructible<A, A&>::value << '\n';
	return 0;
}

#endif

#ifndef _SELF_
#include <type_traits>

int main()
{
	std::cout << std::boolalpha;
	std::cout << std::is_nothrow_move_constructible<A>::value << '\n'; //1
	std::cout << std::is_nothrow_move_constructible<int>::value << '\n'; // 1
	std::cout << std::is_nothrow_copy_constructible<A>::value << '\n'; // 0
	std::cout << std::is_nothrow_constructible<A,A&>::value << '\n';
	return 0;
}

#endif
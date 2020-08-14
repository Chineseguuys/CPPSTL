#include <iostream>

#define _SELF_

struct A
{
private:
    double  floating_n;
    int     integer_n;
public:
    A() : floating_n(0.0f), integer_n(0) {}
};

struct B
{
public:
	/**
	 * 含有纯虚函数的类是一个抽象类
	 */
	virtual const char* what() const = 0;
};

#ifdef _SELF_
#include "type_traits.cpp"
int main()
{
	std::cout << yjh_def::is_destructible<A>::value << '\n';
	std::cout << yjh_def::is_destructible<B>::value << '\n';
	return 0;
}

#endif
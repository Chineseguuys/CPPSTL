#include <iostream>

#define _STD_

struct A
{
private:
    double  floating_n;
    int     integer_n;
public:
    A() : floating_n(0.0f), integer_n(0) {}
};

#ifdef _STD_
#include <type_traits>
int main()
{
	std::cout << __has_nothrow_constructor(A) << '\n';
    std::cout << __has_nothrow_copy(A) << '\n';
	return 0;
}

#endif
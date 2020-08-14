#include <iostream>
#include <typeinfo>
#include "type_traits.cpp"

struct A {
	A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
	A(int& n)  { std::cout << "lvalue overload, n=" << n << "\n"; }
};

class B {
public:
	template<class T1, class T2, class T3>
	B(T1&& t1, T2&& t2, T3&& t3) :
		a1_{std::forward<T1>(t1)},
		a2_{std::forward<T2>(t2)},
		a3_{std::forward<T3>(t3)}
	{
	}

private:
	A a1_, a2_, a3_;
};

template <class U>
A make_A(U&& u)
{
    A res(yjh_def::forward<U>(u));
    return res;
}


int main()
{
    A temp = make_A(10);
    int integer = 100;
    temp = make_A(integer);
    return 0;
}
#include <iostream>


/**
 * datatype ClassName::* pointer 表示一个指向一个 ClassName 的实例中的一个 datatype 的数据的指针
 */

class A
{
public:
	int i;
	int j;
	int k;
};

void f(const A &a, int A::*pint)
{
	std::cout << a.*pint << std::endl;
}

int main()
{
	A a = { 1, 2, 3 };

	f(a, &A::i);
	f(a, &A::j);
	f(a, &A::k);

	return 0;
}
#include <iostream>
#include <algorithm>

template <class _Tp>
struct test_array_template {};

template <class _Tp>
struct test_array_template<_Tp[]>
{
	typedef _Tp			type_name;
	void print_typeName()
	{
		std::cout << typeid(type_name).name() << '\n';
	}
};

template <class _Tp, size_t _Np>
struct test_array_template<_Tp[_Np]>
{
	typedef _Tp			type_name;
	void print_typeName()
	{
		std::cout << typeid(type_name).name() << '\n';
	}
};

int main(int argc, char** argv)
{
	test_array_template<int[][10][10]> a_test;  
	test_array_template<int[10][20]> b_test;
	a_test.print_typeName();	//result : int[10][10]
	b_test.print_typeName();	//result : int[20]
	return 0;
}
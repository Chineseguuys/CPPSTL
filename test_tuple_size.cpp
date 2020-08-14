#define _SELF_DEFINED_

#ifdef _STD_DEFINED_

#include <iostream>
#include <array>

template <typename T>
void test(T t)
{
	int a[std::tuple_size<T>::value];
	std::cout<< std::tuple_size<T>::value <<'\n';
}

int main()
{
	std::array<float, 3> arr;
	test(arr);
	return 0;
}
#endif

#ifdef _SELF_DEFINED_
#include "./array"


int main(int argc, char** argv)
{
	yjh_def::array<float, 10> arr;
	yjh_def::tuple_size<yjh_def::array<float, 10>::value_type, 10> temp;
	return 0;
}

#endif
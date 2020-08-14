#include <iostream>



//#define _SELF_
#define _TEST_ARRAY_PARA_


#ifdef _SELF_
#include "utility.cpp"

int main(int argc, char* argv[])
{
	int integer_a = 111;
	int integer_b = 222;
	int int_array_a[5] = {1,2,3,4,5};
	int int_array_b[5] = {11,22,33,44,55};
	yjh_def::swap(integer_a, integer_b);
	yjh_def::swap(int_array_a, int_array_b);
	std::cout << integer_a << "  " << integer_b << '\n';
	return 0;
}

#endif



#ifdef _TEST_ARRAY_PARA_

template <int _Np>
/**
 * 以引用的方式进行传递参数
 */
void func(int (&__x)[_Np])
{
	for (int index = 0; index < _Np; ++index)
		__x[index] = __x[index] + 10;
}

void func_pointer(int* __x)
{
	std::cout << __x[0] << '\n';
}

template <int _Np>
/**
 * 二维矩阵的传递指针的方法
 * 上面的函数中 func(int (&__x)[_Np]) 是传递引用的方式
 */
void func_arr_pointer(int (*__x)[_Np])
{
	std::cout << __x[0][0] << '\n';
}

int main()
{
	int iVec_5[5] = {1,2,3,4,5};
	int iVec_5x5[2][2] = { {122, 233}, {344, 455} };
	func(iVec_5);
	func_pointer(iVec_5);
	func_arr_pointer(iVec_5x5);
	for (int index = 0; index < 5; ++index)
		std::cout << iVec_5[index] << "  ";
	return 0;
}

#endif
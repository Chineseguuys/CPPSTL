#include <iostream>
#include <type_traits>

//#define _USING_STD_
#define _USING_SELF_DEFINED_

class Base_class
{
    void test() {}
};

class Child_class : public Base_class
{
    void test() {};
};

void a_function(int matrix[][3], int line, int clo)
{
    std::cout << matrix[2][2] << '\n';
}

#ifdef _USING_STD_

int main()
{
    int a[3][3] = {{1,2,3},{2,4,6},{3,6,9}};
    a_function(a, 3, 3);
    std::cout << std::boolalpha;
    std::cout << __is_convertible_to(int[10], const int* const) << '\n';
    std::cout << __is_convertible_to(int[10][10], int**) << '\n';
    std::cout << __is_convertible_to(void, void) << '\n';
    std::cout << __is_convertible_to(int[10], void) << '\n';
    //std::cout << __is_convertible_to(a_function, a_function) << '\n';
    std::cout << std::is_convertible<int[10][10], int[][10]>::value << '\n';
	std::cout << std::is_convertible<const int*, int*>::value << '\n';
	std::cout << std::is_convertible<int* const, int*>::value << '\n';
    return 0;
}

#endif

#ifdef _USING_SELF_DEFINED_

#include "type_traits.cpp"

int main()
{
    std::cout << std::boolalpha;
    std::cout << yjh_def::is_convertible<int[10], int*>::value << '\n';
    std::cout << yjh_def::is_convertible<int[10][10], const int* const>::value << '\n';
    std::cout << yjh_def::is_convertible<int[10][10], int**>::value << '\n';
    std::cout << yjh_def::is_convertible<int[10][10], int[][10]>::value << '\n';
    std::cout << yjh_def::is_convertible<Child_class, Base_class>::value << '\n';
	std::cout << yjh_def::is_convertible<const int, int>::value << '\n';
	std::cout << yjh_def::is_convertible<const int*, int*>::value << '\n';
	std::cout << yjh_def::is_convertible<int* const, int*>::value << '\n';
    return 0;
}

#endif
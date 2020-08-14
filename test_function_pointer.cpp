#include <iostream>
#include <type_traits>

int some_func(int a1, int a2)
{
    return a1 + a2;
}

void test(int&& __a, int&& __b)
{
    std::cout << "void test(int&& __a, int&& __b)" <<'\n';
}

void test(int& __a, int& __b)
{
    std::cout << "void test(int& __a, int& __b)" <<'\n';
}

struct A_class
{
public:
    int some_func(int a1, int a2)
    {
        return a1 + a2;
    }
};


int func_pointer(int(*func)(int, int), int a1, int a2)
{
    return func(a1, a2);
}

int func_pointer_ref(int(*const& func)(int, int), int a1, int a2)
{
    return func(a1, a2);
}

int func_reference(int(&func)(int, int), int a1, int a2)
{
    return func(a1, a2);
}

int class_func_pointer(int(A_class::*func)(int, int), A_class& __c, int a1, int a2)
{
    // 目前不知道这个应该怎么用
    return (__c.*func)(a1, a2);
}

int class_func_pointer(int(A_class::*func)(int, int), A_class* __c, int a1, int a2)
{
    return ((*__c).*func)(a1, a2);
}

int main()
{
    A_class __c;
    int res_p = func_pointer(some_func, 111, 222);
    int res_p_r = func_pointer_ref(some_func, 1111, 2222);
    int res_c_p = class_func_pointer(__c.some_func, __c, 111111, 222222);
    int res_cp_p = class_func_pointer(__c.some_func, &__c, 121212, 121212);
    std::cout << res_p << '\n';
    std::cout << res_p_r << '\n';
    std::cout << res_c_p << '\n';
    std::cout << res_cp_p << '\n';
    int int_a = 314;
    int int_b = 159;
    //test(std::forward(int_a), std::forward(int_b));  //无法将右值应用绑定到左值
    return 0;
}

#define _STD_

int some_func(int a1, int a2)
{
    return a1 + a2;
}


int func_pointer(int(*func)(int, int), int a1, int a2)
{
    return func(a1, a2);
}

struct A_class
{
public:
    int add_nums(int a1, int a2)
    {   return a1 + a2; }
};


#ifdef _STD_
#include <functional>
#include <type_traits>
#include <iostream>

int main()
{
    A_class c_obj;
    std::reference_wrapper<int (A_class::*)(int, int)> c_f_ref(c_obj.add_nums);
    std::cout << c_f_ref(c_obj, 123, 321) << '\n';
    return 0;
}

#endif

#ifdef _SELF_
#include "__functional_base.cpp"
#include <stdio.h>
int main(int argc, char** argv)
{
    A_class c_obj;
    yjh_def::reference_wrapper<int(int, int)> a_reference(some_func);
    yjh_def::reference_wrapper<int (A_class::*)(int, int)> class_func_reference(c_obj.add_nums);
    printf("%d\n", class_func_reference(c_obj, 123, 321));  // 这种用法被禁止
    printf("%d\n", a_reference(100,200));
    return 0;
}

#endif
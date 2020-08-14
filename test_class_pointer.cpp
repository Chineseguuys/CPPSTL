#include <iostream>


struct A_class
{
    int a;
    A_class(int __a) : a(__a){}
};


struct B_class
    : public A_class
{
    double b;
    B_class(int __a, double __b) : A_class(__a), b(__b) {}
};

#ifdef _NO_DEFINED_

int main(int argc, char** argv)
{
    A_class ans(100);
    B_class* pointer_A_class = static_cast<B_class*>(&ans);
    std::cout << pointer_A_class->b << '\n';
    return 0;
}

#endif

int main(int argc, char** argv)
{
    B_class ans(100, 3.14159);
    A_class*    p_A_B = static_cast<A_class*>(&ans);
    void*       p_void_A = static_cast<void*>(p_A_B);
    B_class*    p_B_void = static_cast<B_class*>(p_void_A);
    std::cout << p_B_void->b << '\n';
    std::cout << p_B_void->a << '\n';
}
#include <memory>
#include <iostream>

struct A_Class 
{
    int integer;
    double floating;
    A_Class() : integer(0), floating(3.14) {}
    A_Class(int __i, double __d) : integer(__i), floating(__d) {}
};

struct pointer_A_Class
{
    A_Class* __next_;
};

struct B_Class
    : public pointer_A_Class
{
    A_Class __value_;
};


int main()
{
    std::allocator<A_Class> _A_class_alloc;
    A_Class ans(100, 23.32);
    B_Class* p_b = static_cast<B_Class*>(operator new(sizeof(B_Class)));
    std::allocator_traits<std::allocator<A_Class>>::construct(_A_class_alloc, &(p_b->__value_),100, 3.1415);
    p_b->__next_ = &ans;
    std::cout << p_b->__next_->floating << '\n';
    std::cout << p_b->__next_->integer << '\n';
    std::cout << p_b->__value_.floating << '\n';
    std::cout << p_b->__value_.integer << '\n';

    operator delete(p_b);
    return 0;
}
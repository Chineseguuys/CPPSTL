#include <iostream>



struct A_class
{
public:
    A_class() {}
    A_class(const A_class& __x) { std::cout << "A_class(const A_class&)"<< '\n'; }
public:
    A_class(A_class&& __x) { std::cout << "A_class(A_class&&)"<< '\n'; }
};


void test(A_class __x)
{}


int main()
{
    A_class ans;
    test(ans);
    test(A_class());
    return 0;
}
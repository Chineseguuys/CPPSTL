#include <iostream>


struct Empty_A {};


class NON_Empty : private Empty_A
{
public:
    unsigned int age;
    double height;

    NON_Empty(unsigned int __a, double __h) : Empty_A(), age(__a), height(__h)
    {}

    Empty_A& get() { return static_cast<Empty_A&>(*this); } // 这种用法的意义何在
    double  get_height() { return this->height; }
};



int main(int argc, char** argv)
{
    NON_Empty res(23, 156.6);
    Empty_A& ref_res = res.get();
    // Empty_A& ref_res = static_cast<Empty_A&>(res); // 不可以在类的外部，将一个类转换为其不可见的基类对象
}
#include <iostream>



class A_Class 
{
public:
    int integer;
};


class B_Class
    : public A_Class
{
public:
    double floating;
};


int main(int argc, char* argv[])
{
    B_Class object_b1;
    object_b1.floating = 3.14;
    object_b1.integer = 314;
    B_Class object_b2;
    object_b2.floating = 1.414;
    object_b2.integer = 1414;
    object_b1 = object_b2;
    std::cout << "(" << object_b1.integer << ", " << object_b1.floating << ")\n";
    return 0;
}
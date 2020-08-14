#include <iostream>



template <class ..._Args>
void test(_Args... __t)
{
    std::cout << "Empty for all "<<'\n';
    return;
}



int main()
{
    test();         // 什么都不给也可以，给任意多个也是可以的
    test(100, 200, 300);
    test(100, 200, 12.34);
    return 0;
}
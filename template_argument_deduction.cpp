/**
 * 为实例化一个函数模板，必须知晓每个模板实参，但不必每个模板实参都被指定。
 * 只要可能，编译器就会从函数实参推导缺失的模板实参。这在尝试调用函数、取函数模板地址时，和某些其他语境中发生
 */
#ifndef _IOSTREAM_
#include <iostream>
#endif


template <typename _Tp, int _Np> void h_func(_Tp const (&__a)[_Np])
{
    for (int inx = 0; inx < _Np; ++inx)
    {
        std::cout << __a[inx] << "  ";
    }
    std::cout << '\n';
}

template <class _Tp, int _Mp, int _Np> void m_func(_Tp const (&__a)[_Mp][_Np])
{
    for (int ind_x = 0; ind_x < _Mp; ++ind_x)
    {
        for (int ind_y = 0; ind_y < _Np; ++ind_y)
            std::cout << __a[ind_x][ind_y] << "  ";
        std::cout << '\n';
    }
}


int main(int argc, char* argv[])
{
    h_func({1,2,3,4,5});
    m_func({{1,2,3},{4,5,6},{7,8,9}});
    return 0;
}
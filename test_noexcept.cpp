#include <iostream>
#include <type_traits>


struct true_type
{
    static const bool type = false;
};


class A_class
{
public:
    typedef true_type __HAS_VALUE_;
    int integer;
};

template <class _Tp>
void test(_Tp& __x)
    noexcept(_Tp::__HAS_VALUE_::type)
{
    std::cout << "false" << '\n';
}

int main()
{
    A_class ans;
    test(ans);
    return 0;
}
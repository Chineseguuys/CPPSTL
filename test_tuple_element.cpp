
template <class ..._Tp> struct __tuple_types {};

template <size_t _Ip, class _Tp> struct tuple_element {
};


template <class _Hp, class ..._Tp>
struct tuple_element<0, __tuple_types<_Hp, _Tp...> >
{
    typedef _Hp     type;
};

template <size_t _Ip, class _Hp, class ..._Tp>
struct tuple_element<_Ip, __tuple_types<_Hp, _Tp...> >
{
    typedef typename tuple_element<_Ip - 1, __tuple_types<_Tp...> >::type type;
};

template <class ..._Tp>
class my_tuple {
public:
    my_tuple() {}
};

#include <iostream>
#include <typeinfo>
#include <tuple>
int main()
{
    std::cout << typeid(tuple_element<2, std::tuple<int, double, unsigned int> >::type).name() << '\n';
    return 0;
}


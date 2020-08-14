#include "type_traits.cpp"


#include <stdio.h>


struct A_class
{
    typedef char flags;
};

template <class _Tp, class = void>
struct has_flags    : yjh_def::false_type {};

template <class _Tp>
struct has_flags<_Tp, typename yjh_def::__void_t<typename _Tp::flags>::type>
    : yjh_def::true_type {};

template <class _Up, bool = has_flags<_Up>::value>
struct is_always_flags
{
    typedef typename yjh_def::is_empty<_Up>::type type;
};

template <class _Up>
struct is_always_flags<_Up, true>
{
    typedef typename _Up::flags type;
};

#include <typeinfo>
int main()
{
    printf("%s\n", typeid(is_always_flags<A_class>::type).name());
    return 0;
}
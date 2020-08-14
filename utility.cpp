#ifndef _LIBCPP_UTILITY
#define _LIBCPP_UTILITY

#include "__config.cpp"
#include "type_traits.cpp"
#include "__tuple.cpp"  // pair is also a tuple like data structure
/**
 * utility 中主要就定义了 pair 这个类，以及 pair 类的工厂函数 make_pair
 */
namespace yjh_def
{

namespace rel_ops
{
template <class _Tp>
inline bool
operator!=(const _Tp& __x, const _Tp& __y)
{
    return !(__x == __y);
}

template <class _Tp>
inline bool
operator> (const _Tp& __x, const _Tp& __y)
{
    return __y < __x;
}

template <class _Tp>
inline bool
operator <= (const _Tp& __x, const _Tp& __y)
{
    return !(__y < __x);
}

template <class _Tp>
inline bool
operator >= (const _Tp& __x, const _Tp& __y)
{
    return !(__y > __x);
}

}

// swap_ranges
template <class _ForwardIterator1, class _ForwardIterator2>
inline _ForwardIterator2
swap_ranges(_ForwardIterator1 _first1, _ForwardIterator1 _last1, _ForwardIterator2 _first2)
{
    for(; _first1 != _last1; ++_first1, ++_first2)
        swap(*_first1, *_first2);
    return _first2;
}

template <class _Tp, size_t _Np>
/**
 * _Tp (&__a)[_Np] 可以接受的数据的类型
 * 已知的有下面的几种
 *      type_name[_Np] 初始化的数组 ，例如 int[5] = {1,2,3,4,5};
 *      另外  const t(&__a)[_Np] 还可以接受  {1,2,3,4,5} 这种临时对象
 */
/**
 * 针对一维数组的一种传递引用的方式  _Tp (&__a)[_Np]
 * 当然还可以使用传递指针的方式进行  _Tp (*__a)[_Np]
 */
inline void
swap (_Tp (&__a)[_Np], _Tp (&__b)[_Np]) noexcept(__is_nothrow_swappable<_Tp>::value)
{
    yjh_def::swap_ranges(__a, __a + _Np, __b);
}

template <class _Tp>
inline 
typename conditional
<
    !is_nothrow_move_constructible<_Tp>::value && is_copy_constructible<_Tp>::value,
    const _Tp&,
    _Tp&&
>::type
move_if_noexcept(_Tp& __x) noexcept
{
    return yjh_def::move(__x);
}

// piecewise_construct
/**
 * 常量 std::piecewise_construct 是空的结构体标签类型 std::piecewise_construct_t 的一个实例
 */
struct piecewise_construct_t {};
constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();

// pair
/**
 * 注意 ：  pair tuple array 都看作是 __tuple_like 的 [from __typle.cpp]
 */
template <class _T1, class _T2>
struct pair
{
    typedef _T1 first_type;
    typedef _T2 second_type;

    _T1 first;
    _T2 second;

    constexpr pair() : first(), second() {}

    pair(const _T1& __x, const _T2& __y)
        : first(__x), second(__y) {}
    /**
     * 拷贝构造函数，当然被复制的 pair 和当前的数据的类型可能是不一致的，但是，如果不同的数据结构之间
     * 可以进行相互转换的话，那么可以进行拷贝在构造
     */
    template <class _U1, class _U2>
    pair(const pair<_U1, _U2>& __p,
                typename enable_if<is_convertible<const _U1&, _T1>::value &&
                                    is_convertible<const _U2&, _T2>::value>::type* = 0)
        : first(__p.first), second(__p.second) {}
    
    pair(const pair& __p)
        noexcept(   is_nothrow_copy_constructible<first_type>::value &&
                    is_nothrow_copy_constructible<second_type>::value)
        : first(__p.first),
          second(__p.second)
    {}

    pair& operator=(const pair& __p)
        noexcept(   is_nothrow_copy_assignable<first_type>::value && 
                    is_nothrow_copy_assignable<second_type>::value)
    {
        first =     __p.first;
        second =    __p.second;
        return *this;
    }

    template <class _U1, class _U2,
                class = typename enable_if<is_convertible<_U1, first_type>::value && 
                                            is_convertible<_U2, second_type>::value>::type>
    pair(_U1&& __u1, _U2&& __u2)
        /**
         * forward 模板函数的实现原理一直都没有完全搞明白
         */
        : first(yjh_def::forward<_U1>(__u1)),
          second(yjh_def::forward<_U2>(__u2))
    {}

    template <class _U1, class _U2>
        pair(pair<_U1, _U2>&& __p,
                typename enable_if<is_convertible<_U1, _T1>::value &&
                                    is_convertible<_U2, _T2>::value>::type* = 0)
            : first(yjh_def::forward<_U1>(__p.first)),
              second(yjh_def::forward<_U2>(__p.second)) {}
    
#ifndef _YJH_HAS_NO_VARIADICS
    /**
     * 将 tuple 到  pair 的转换，因为 tuple 可以存储超过两个元素
     * 如果 tuple 的元素不是了两个的话，那么这里的转换是无法成功的
     * enable_if<>的解析会失败
     * _Tuple 可能是 pair tuple 或者 array 中的一个
     * 上面的条件满足，还需要 _Tuple 的两个数据的数据类型可以转化为 pair 的两个数据类型
     * [数据类型不一定要完全的相同，只要可以进行转换就可以了]
     */
    template <class _Tuple,
                class = typename enable_if<__tuple_convertible<_Tuple, pair>::value>::type>
    pair(_Tuple&& __p)
        : first(yjh_def::forward<typename tuple_element<0,
                                typename __make_tuple_types<_Tuple>::type>::type>(get<0>(__p))),
          second(yjh_def::forward<typename tuple_element<0,
                                typename __make_tuple_types<_Tuple>::type>::type>(get<1>(__p)))
    {}

    template <class ..._Args1, class... _Args2>
    pair(piecewise_construct_t __pc, tuple<_Args1...> __first_args,
                                    tuple<_Args2...> __second_args)
        : pair(__pc, __first_args, __second_args,
                    typename __make_tuple_indices<sizeof...(_Args1)>::type(),
                    typename __make_tuple_indices<sizeof...(_Args2)>::type())
        {}

    template <  class _Tuple,
                class = typename enable_if<__tuple_assignable<_Tuple, pair>::value>::type>
    pair&
    operator = (_Tuple&& __p)
    {
        typedef typename __make_tuple_types<_Tuple>::type _TupleRef;
        typedef typename tuple_element<0, _TupleRef>::type _U0;
        typedef typename tuple_element<1, _TupleRef>::type _U1;
        first = yjh_def::forward<_U0>(yjh_def::get<0>(__p));
        second = yjh_def::forward<_U1>(yjh_def::get<1>(__p));
        return *this;
    }
#endif

    void
    swap(pair& __p) noexcept(__is_nothrow_swappable<first_type>::value &&
                            __is_nothrow_swappable<second_type>::value)
    {
        yjh_def::iter_swap(&first, __p.first);
        yjh_def::iter_swap(&second, __p.second);
    }

private:
#ifndef _YJH_HAS_NO_VARIADICS
    /**
     * 这个构造函数没有进行实现
     * 具体的实现在 tuple.cpp 类当中
     */
    template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
    pair(   piecewise_construct_t,
            tuple<_Args1...>& __first_args, tuple<_Args2...>& __second_args,
            __tuple_indices<_I1...>, __tuple_indices<_I2...>);
#endif
};

template <class _T1, class _T2>
inline
bool
operator== (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __x.first == __y.first && __x.second == __y.second;
}

template <class _T1, class _T2>
inline
bool
operator!= (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x == __y);
}

template <class _T1, class _T2>
inline
bool
operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class _T1, class _T2>
inline
bool
operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __y < __x;
}

template <class _T1, class _T2>
inline
bool
operator>= (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x < __y);
}

template <class _T1, class _T2>
inline
bool
operator<= (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x > __y);
}

template <class _T1, class _T2>
inline
typename enable_if
<
    __is_swappable<_T1>::value &&
    __is_swappable<_T2>::value,
    void
>::type
swap(pair<_T1, _T2>& __x, pair<_T1, _T2>& __y)
        noexcept((__is_nothrow_swappable<_T1>::value &&
                    __is_nothrow_swappable<_T2>::value))
{
    __x.swap(__y);
}

template <class _Tp> class reference_wrapper;

template <class _Tp>
struct ___make_pair_return
{
    typedef _Tp type;
};

template <class _Tp>
struct ___make_pair_return<reference_wrapper<_Tp>>
{
    typedef _Tp& type;
};

template <class _Tp>
struct __make_pair_return
{
    typedef typename ___make_pair_return<typename decay<_Tp>::type >::type  type;
};

// make_pair
template <class _T1, class _T2>
inline
pair<typename __make_pair_return<_T1>::type, typename __make_pair_return<_T2>::type>
make_pair(_T1&& __t1, _T2&& __t2)
{
    return pair<typename __make_pair_return<_T1>::type, typename __make_pair_return<_T2>::type>
            (yjh_def::forward<_T1>(__t1), yjh_def::forward<_T2>(__t2));
}

// tuple_size
/**
 * 对 __tuple.cpp 中的类 tuple_size 的一个局部特化
 * 下面的 tuple_element 也是同理
 */
template <class _T1, class _T2>
class tuple_size<pair<_T1, _T2> >
    : public integral_constant<size_t, 2> {};

template <class _T1, class _T2>
class tuple_size<const pair<_T1, _T2> >
    : public integral_constant<size_t, 2> {};

template <class _T1, class _T2>
class tuple_element<0, pair<_T1, _T2>>
{
public:
    typedef _T1 type;
};

template <class _T1, class _T2>
class tuple_element<1, pair<_T1, _T2>>
{
public:
    typedef _T2 type;
};

template <class _T1, class _T2>
class tuple_element<0, const pair<_T1, _T2>>
{
public:
    typedef const _T1 type;
};

template <class _T1, class _T2>
class tuple_element<1, const pair<_T1, _T2>>
{
public:
    typedef const _T2 type;
};

// get
template <size_t _Ip> struct __get_pair;

// 两个全特化
template <>
/**
 * 获取 pair 的第一个元素值
 */
struct __get_pair<0>
{
    template <class _T1, class _T2>
    static
    _T1&
    get(pair<_T1, _T2>& __p) noexcept {return __p.first;}

    template <class _T1, class _T2>
    static
    const _T1&
    get(const pair<_T1, _T2>& __p) noexcept {return __p.first;}

    template <class _T1, class _T2>
    static
    _T1&&
    get(pair<_T1, _T2>&& __p) noexcept {return yjh_def::forward<_T1>(__p.first);}
};

template <>
/**
 * 获取 pair 的第二个元素值
 */
struct __get_pair<1>
{
    template <class _T1, class _T2>
    static
    _T2&
    get(pair<_T1, _T2>& __p) noexcept {return __p.second;}

    template <class _T1, class _T2>
    static
    const _T2&
    get(const pair<_T1, _T2>& __p) noexcept {return __p.second;}

    template <class _T1, class _T2>
    static
    _T2&&
    get(pair<_T1, _T2>&& __p) noexcept {return __p.second;}
};

template <size_t _Ip, class _T1, class _T2>
inline
typename tuple_element<_Ip, pair<_T1, _T2> >::type&
get(pair<_T1, _T2>& __p) noexcept
{
    return __get_pair<_Ip>::get(__p);
}

template <size_t _Ip, class _T1, class _T2>
inline
const typename tuple_element<_Ip, pair<_T1, _T2> >::type&
get(const pair<_T1, _T2>& __p) noexcept
{
    return __get_pair<_Ip>::get(__p);
}

template <size_t _Ip, class _T1, class _T2>
inline
typename tuple_element<_Ip, pair<_T1, _T2> >::type&&
get(pair<_T1, _T2>&& __p) noexcept
{
    return __get_pair<_Ip>::get(yjh_def::move(__p));
}

}


#endif
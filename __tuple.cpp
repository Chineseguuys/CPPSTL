#ifndef _LIBCPP___TUPLE
#define _LIBCPP___TUPLE

#include "__config.cpp"
#include "type_traits.cpp"


namespace yjh_def
{
// tuple_size 
/**
 * tuple size 返回 _Tp 类型中数据的个数
 */
template <class _Tp>	class tuple_size;

template <class _Tp>
class tuple_size<const _Tp>
	: public tuple_size<_Tp> {};

template <class _Tp>
class tuple_size<volatile _Tp>
	: public tuple_size<_Tp> {};

template <class _Tp>
class tuple_size<const volatile _Tp>
	: public tuple_size<_Tp> {};

// tuple_element
/**
 * tuple_element 返回 _Tp 中每一个元素的类型
 * _Ip  index position
 * _Tp  type 
 * 这个地方只是进行一下声明，具体的实现在该头文件的下面，另外包括　utility.cpp array.cpp 中也有自己的实现方法
 */
template <size_t _Ip, class _Tp>	class tuple_element;

template <size_t _Ip, class _Tp>
class tuple_element<_Ip, const _Tp>
{
public:
	typedef typename yjh_def::add_const<typename tuple_element<_Ip, _Tp>::type>::type type;
};

template <size_t _Ip, class _Tp>
class tuple_element<_Ip, volatile _Tp>
{
public:
	typedef typename yjh_def::add_volatile<typename tuple_element<_Ip, _Tp>::type>::type type;
};

template <size_t _Ip, class _Tp>
class tuple_element<_Ip, const volatile _Tp>
{
public:
	typedef typename yjh_def::add_cv<typename tuple_element<_Ip, _Tp>::type>::type type;
};

template <class ..._Tp>	class tuple;
template <class _T1, class _T2>	struct pair;
template <class _Tp, size_t _Size>	struct array;

// __tuple_like
template <class _Tp> struct __tuple_like : false_type {};

template <class _Tp> struct __tuple_like<const _Tp> : public __tuple_like<_Tp> {};
template <class _Tp> struct __tuple_like<volatile _Tp> : public __tuple_like<_Tp> {};
template <class _Tp> struct __tuple_like<const volatile _Tp> : public __tuple_like<_Tp> {};

template <class... _Tp> struct __tuple_like<tuple<_Tp...> > : true_type {};
template <class _T1, class _T2> struct __tuple_like<pair<_T1, _T2> > : true_type {};
template <class _Tp, size_t _Size> struct __tuple_like<array<_Tp, _Size> > : true_type {};

// get
template <size_t _Ip, class ..._Tp>
typename tuple_element<_Ip, tuple<_Tp...> >::type&
get(tuple<_Tp...>&) _NOEXCEPT;

template <size_t _Ip, class ..._Tp>
const typename tuple_element<_Ip, tuple<_Tp...> >::type&
get(const tuple<_Tp...>&) _NOEXCEPT;

template <size_t _Ip, class ..._Tp>
typename tuple_element<_Ip, tuple<_Tp...> >::type&&
get(tuple<_Tp...>&&) _NOEXCEPT;

template <size_t _Ip, class _T1, class _T2>
typename tuple_element<_Ip, pair<_T1, _T2> >::type&
get(pair<_T1, _T2>&) _NOEXCEPT;

template <size_t _Ip, class _T1, class _T2>
const typename tuple_element<_Ip, pair<_T1, _T2> >::type&
get(const pair<_T1, _T2>&) _NOEXCEPT;

template <size_t _Ip, class _T1, class _T2>
typename tuple_element<_Ip, pair<_T1, _T2> >::type&&
get(pair<_T1, _T2>&&) _NOEXCEPT;

template <size_t _Ip, class _Tp, size_t _Size>
_Tp&
get(array<_Tp, _Size>&) _NOEXCEPT;

template <size_t _Ip, class _Tp, size_t _Size>
const _Tp&
get(const array<_Tp, _Size>&) _NOEXCEPT;

template <size_t _Ip, class _Tp, size_t _Size>
_Tp&&
get(array<_Tp, _Size>&&) _NOEXCEPT;

// __make_tuple_indices

template <size_t...> struct __tuple_indices {};

/**
 * _Sp : start position  	开始位置	默认值是 0
 * _Ep : end position 		结束的位置
 * tuple 只存储从 _Sp 开始到 _Ep 结束的位置的数据类型
 */
template <size_t _Sp, class _IntTuple, size_t _Ep>
struct __make_indices_imp;

template <size_t _Sp, size_t ..._Indices, size_t _Ep>
struct __make_indices_imp<_Sp, __tuple_indices<_Indices...>, _Ep>
{
    typedef typename __make_indices_imp<_Sp+1, __tuple_indices<_Indices..., _Sp>, _Ep>::type type;
};

/**
 * 上面的_Sp+1 在不断的增加的过程中，最终会达到 _sp = _Ep 的情况，这种情况将会执行下面的模板类
 */
template <size_t _Ep, size_t ..._Indices>
struct __make_indices_imp<_Ep, __tuple_indices<_Indices...>, _Ep>
{
    typedef __tuple_indices<_Indices...> type;
};

template <size_t _Ep, size_t _Sp = 0>
struct __make_tuple_indices
{
    static_assert(_Sp <= _Ep, "__make_tuple_indices input error");
    /**
     * __tuple_indices 是一个接受众多的 size_t 参数的一个空的模板类
     */
    typedef typename __make_indices_imp<_Sp, __tuple_indices<>, _Ep>::type type;
};

// __tuple_types
/**
 * 一个空类，可以接收多个参数
 */
template <class ..._Tp> struct __tuple_types {};

/**
 * 对于 pair<_T1, _T2> 在 utility.cpp 中对这个类进行了重载
 */
template <size_t _Ip>
class tuple_element<_Ip, __tuple_types<> >
{
public:
    static_assert(_Ip == 0, "tuple_element index out of range");
    static_assert(_Ip != 0, "tuple_element index out of range");
};

/**
 * tuple_element 的具体实现是在这个地方完成的
 * 传递给 tuple_element的可能是 tuple_elemet<0, tuple<_Hp, _Tp, .....>>
 * tuple<_Hp, _Tp, ... 是如何和 __typle_types 兼容的 ？>
 */
template <class _Hp, class ..._Tp>
class tuple_element<0, __tuple_types<_Hp, _Tp...> >
{
public:
    typedef _Hp type;
};

/**
 * 递归
 */
template <size_t _Ip, class _Hp, class ..._Tp>
class tuple_element<_Ip, __tuple_types<_Hp, _Tp...> >
{
public:
    typedef typename tuple_element<_Ip-1, __tuple_types<_Tp...> >::type type;
};

template <class ..._Tp>
class tuple_size<__tuple_types<_Tp...> >
    : public integral_constant<size_t, sizeof...(_Tp)>
{
};

template <class... _Tp> struct __tuple_like<__tuple_types<_Tp...> > : true_type {};

// __make_tuple_types

// __make_tuple_types<_Tuple<_Types...>, _Ep, _Sp>::type is a
// __tuple_types<_Types...> using only those _Types in the range [_Sp, _Ep).
// _Sp defaults to 0 and _Ep defaults to tuple_size<_Tuple>.  If _Tuple is a
// lvalue_reference type, then __tuple_types<_Types&...> is the result.

template <class _TupleTypes, class _Tp, size_t _Sp, size_t _Ep>
struct __make_tuple_types_imp;
/**
 * _Sp : start position  	开始位置	默认值是 0
 * _Ep : end position 		结束的位置
 * tuple 只存储从 _Sp 开始到 _Ep 结束的位置的数据类型
 * __tuple_types<> 用来存储所有从 _Sp 到 _Ep 为止的所有的数据类型
 */
template <class ..._Types, class _Tp, size_t _Sp, size_t _Ep>
struct __make_tuple_types_imp<__tuple_types<_Types...>, _Tp, _Sp, _Ep>
{
    typedef typename remove_reference<_Tp>::type _Tpr;
    typedef typename __make_tuple_types_imp<__tuple_types<_Types...,
                                            typename conditional<is_lvalue_reference<_Tp>::value,
                                                typename tuple_element<_Sp, _Tpr>::type&,
                                                typename tuple_element<_Sp, _Tpr>::type>::type>,
                                            _Tp, _Sp+1, _Ep>::type type;
};

/**
 * 上面的递归的过程在 _Sp 增长到和 _Ep 的值相等的时候结束
 */
template <class ..._Types, class _Tp, size_t _Ep>
struct __make_tuple_types_imp<__tuple_types<_Types...>, _Tp, _Ep, _Ep>
{
    typedef __tuple_types<_Types...> type;
};
/**
 * _Tp like tuple<int, double, std::string, char, const char* ...>
 */
template <class _Tp, size_t _Ep = tuple_size<typename remove_reference<_Tp>::type>::value, size_t _Sp = 0>
struct __make_tuple_types
{
    static_assert(_Sp <= _Ep, "__make_tuple_types input error");
    typedef typename __make_tuple_types_imp<__tuple_types<>, _Tp, _Sp, _Ep>::type type;
};

// __tuple_convertible

template <bool, class _Tp, class _Up>
struct __tuple_convertible_imp : public false_type {};

/**
 * 这是一个递归的过程 _Tp 和 _Up 中存储的数据元素的类型，必须每一个对应的都可以进行转化
 */
template <class _Tp0, class ..._Tp, class _Up0, class ..._Up>
struct __tuple_convertible_imp<true, __tuple_types<_Tp0, _Tp...>, __tuple_types<_Up0, _Up...> >
    : public integral_constant<bool,
                               is_convertible<_Tp0, _Up0>::value &&
                               __tuple_convertible_imp<true, __tuple_types<_Tp...>, __tuple_types<_Up...> >::value> {};
/**
 * 递归终止的条件在这里，直接返回 true_type
 */
template <>
struct __tuple_convertible_imp<true, __tuple_types<>, __tuple_types<> >
    : public true_type {};

template <class _Tp, class _Up, bool = __tuple_like<typename remove_reference<_Tp>::type>::value,
                                bool = __tuple_like<_Up>::value>
struct __tuple_convertible
    : public false_type {};
/**
 * 是否可以完成从 _Tp　到 _Up 的转换
 * array pair tuple 都被认为是 __tuple_like 的
 * 它们之间是有可能实现相互的转换的
 */
template <class _Tp, class _Up>
struct __tuple_convertible<_Tp, _Up, true, true>
    : public __tuple_convertible_imp<tuple_size<typename remove_reference<_Tp>::type>::value ==
                                     tuple_size<_Up>::value,
             typename __make_tuple_types<_Tp>::type, typename __make_tuple_types<_Up>::type>
{};

// __tuple_constructible

template <bool, class _Tp, class _Up>
struct __tuple_constructible_imp : public false_type {};

template <class _Tp0, class ..._Tp, class _Up0, class ..._Up>
struct __tuple_constructible_imp<true, __tuple_types<_Tp0, _Tp...>, __tuple_types<_Up0, _Up...> >
    : public integral_constant<bool,
                               is_constructible<_Up0, _Tp0>::value &&
                               __tuple_constructible_imp<true, __tuple_types<_Tp...>, __tuple_types<_Up...> >::value> {};

template <>
struct __tuple_constructible_imp<true, __tuple_types<>, __tuple_types<> >
    : public true_type {};

template <class _Tp, class _Up, bool = __tuple_like<typename remove_reference<_Tp>::type>::value,
                                bool = __tuple_like<_Up>::value>
struct __tuple_constructible
    : public false_type {};

template <class _Tp, class _Up>
struct __tuple_constructible<_Tp, _Up, true, true>
    : public __tuple_constructible_imp<tuple_size<typename remove_reference<_Tp>::type>::value ==
                                     tuple_size<_Up>::value,
             typename __make_tuple_types<_Tp>::type, typename __make_tuple_types<_Up>::type>
{};

// __tuple_assignable

template <bool, class _Tp, class _Up>
struct __tuple_assignable_imp : public false_type {};

template <class _Tp0, class ..._Tp, class _Up0, class ..._Up>
struct __tuple_assignable_imp<true, __tuple_types<_Tp0, _Tp...>, __tuple_types<_Up0, _Up...> >
    : public integral_constant<bool,
                               is_assignable<_Up0&, _Tp0>::value &&
                               __tuple_assignable_imp<true, __tuple_types<_Tp...>, __tuple_types<_Up...> >::value> {};

template <>
struct __tuple_assignable_imp<true, __tuple_types<>, __tuple_types<> >
    : public true_type {};

template <class _Tp, class _Up, bool = __tuple_like<typename remove_reference<_Tp>::type>::value,
                                bool = __tuple_like<_Up>::value>
struct __tuple_assignable
    : public false_type {};

template <class _Tp, class _Up>
struct __tuple_assignable<_Tp, _Up, true, true>
    : public __tuple_assignable_imp<tuple_size<typename remove_reference<_Tp>::type>::value ==
                                    tuple_size<_Up>::value,
             typename __make_tuple_types<_Tp>::type, typename __make_tuple_types<_Up>::type>
{};

}
#endif
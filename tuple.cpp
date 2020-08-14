#ifndef _LIBCPP_TUPLE
#define _LIBCPP_TUPLE

#include "__config.cpp"
#include "__tuple.cpp"  //定义了所有的 tuple 类型的基础功能
#include "type_traits.cpp"
#include "__functional_base.cpp"
#include "utility.cpp"  // pair  类所在位置

namespace yjh_def
{
struct  allocator_arg_t { };

constexpr allocator_arg_t allocator_arg = allocator_arg_t();

// uses_allocator

template <class _Tp>
/**
 * 测试 _Tp 是否有 allocator_type 类型数据
 * 这是一种非常经典的实现方法，标准库中这种判断都是使用这种方法进行实现的
 */
struct __has_allocator_type
{
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename _Up::allocator_type* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Tp, class _Alloc, bool = __has_allocator_type<_Tp>::value>
struct __uses_allocator
    : public integral_constant<bool,
        is_convertible<_Alloc, typename _Tp::allocator_type>::value>
{
};

template <class _Tp, class _Alloc>
struct __uses_allocator<_Tp, _Alloc, false>
    : public false_type
{
};

/**
 * 如果 _Tp 类型有 allocator_type 并且 _Alloc 可以转化为 _Tp::allocator_type 类型，
 * 则这个类持有 true_type
 * 否则的话 这个类持有 false_type
 */
template <class _Tp, class _Alloc>
struct uses_allocator
    : public __uses_allocator<_Tp, _Alloc>
{
};

#ifndef _YJH_HAS_NO_VARIADICS
// uses-allocator construction

template <class _Tp, class _Alloc, class ..._Args>
struct __uses_alloc_ctor_imp
{
    /**
     * 如果 _Tp 类型自己拥有 allocator_type 并且 _Alloc 可以转换为 _Tp::allocator_type类型的话
     * __ua 将会拥有 true 值，否则的话，这里的值就是 false 
     */
    static const bool __ua = uses_allocator<_Tp, _Alloc>::value;
    static const bool __ic =
    /**
     * allocator_arg_t  : allocator argument tags : 用于指示参数中使用了分配器
     * 这个类是一个空的类，其自身单独使用并没有任何的意义
     */
        is_constructible<_Tp, allocator_arg_t, _Alloc, _Args...>::value;
    static const int value = __ua ? 2 - __ic : 0;
    /**
     * 这个 value 可能有下面的几种可能的结果值
     * 1. __ua = true;  __ic = true     value = 1
     * 2. __ua = true;  __ic = false    value = 2
     * 3. __ua = false; __ic = true     value = 0
     * 4. __ua = false; __ic = false    value = 0
     */
};
/**
 * _Tp 数据类型
 * _Alloc 分配器
 * _Args 给 _Tp 初始化的参数类型
 */
template <class _Tp, class _Alloc, class ..._Args>
struct __uses_alloc_ctor
    : integral_constant<int, __uses_alloc_ctor_imp<_Tp, _Alloc, _Args...>::value>
    {};

#endif //_YJH_HAS_NO_VARIADICS

#ifndef _YJH_HAS_NO_VARIADICS
// tuple_size

template <class ..._Tp>
class tuple_size<tuple<_Tp...> >
    : public integral_constant<size_t, sizeof...(_Tp)>
{
};

// tuple_element

template <size_t _Ip, class ..._Tp>
class tuple_element<_Ip, tuple<_Tp...> >
{
public:
    typedef typename tuple_element<_Ip, __tuple_types<_Tp...> >::type type;
};

// __tuple_leaf
/** __tuple_leaf 是用来存储 tuple 中每一种数据类型的实际容器
 * _Ip 是 _Hp 的下标值，这里可能的使用方法是
 * __tuple_leaf<0, int>
 * __tuple_leaf<1, double>
 * __tuple_leaf<2, std::string>
 * 通过 __tuple_impl 私有继承这个类，来调用__tuple_leaf
 */
template <size_t _Ip, class _Hp, bool = is_empty<_Hp>::value &&
    !__is_final(_Hp)
>
class __tuple_leaf;

template <size_t _Ip, class _Hp, bool _Ep>
inline
void swap(__tuple_leaf<_Ip, _Hp, _Ep>& __x, __tuple_leaf<_Ip, _Hp, _Ep>& __y)
    noexcept(__is_nothrow_swappable<_Hp>::value)
{
    swap(__x.get(), __y.get());
}
/**
 * _Ip 是 _Hp 的下标值，这里可能的使用方法是
 * __tuple_leaf<0, int>
 * __tuple_leaf<1, double>
 * __tuple_leaf<2, std::string>
 * 通过 __tuple_impl 私有继承这个类，来调用__tuple_leaf
 * bool 值是针对非 final 的空类设计的，如果 bool 值是 true 说明要存储的数据是一个空类
 * 并且这个类不是 final 类
 */
template <size_t _Ip, class _Hp, bool>
class __tuple_leaf
{
    _Hp value;

    __tuple_leaf& operator=(const __tuple_leaf&);
public:
     constexpr __tuple_leaf()
             noexcept(is_nothrow_default_constructible<_Hp>::value) : value()
       {static_assert(!is_reference<_Hp>::value,
              "Attempted to default construct a reference element in a tuple");}
              /**
               * 引用类型是不能进行默认初始化的，引用类型只能指向某一个内存对象，它和 
               * 指针对象不同的地方在于，指针类型可以初始化为 nullptr
               */

    template <class _Alloc>
    /**
     * 这种情况下 ，_Alloc 无法转化为 _Hp 类型的 _Hp::allocator_type[或者 _Hp 不含有 allocator_type]
     * 引起，尽管参数中给了分配器，但是无法在这里进行使用
     */   
    __tuple_leaf(integral_constant<int, 0>, const _Alloc&)
        : value()
    {static_assert(!is_reference<_Hp>::value,
            "Attempted to default construct a reference element in a tuple");}

    template <class _Alloc> 
    /**
     * 这是最好的情况，不但 _Alloc 和 _Hp::allocator_type 兼容，并且构造函数的参数允许接受
     * allocator_arg_t 
     */
        __tuple_leaf(integral_constant<int, 1>, const _Alloc& __a)
            : value(allocator_arg_t(), __a)
            /**
             * allocator_arg_t() 是一个空类，只用来标注，没有任何实际的功能
             * 和 iterator_tag 拥有相似的功能
             */
        {static_assert(!is_reference<_Hp>::value,
              "Attempted to default construct a reference element in a tuple");}
    /**
     * 虽然 _Alloc 可以和 _Hp::allocator_type 兼容，但是构造函数中不接受 allocator_arg_t 
     * 因此直接使用 _Alloc 对象进行初始化
     */
    template <class _Alloc>
        __tuple_leaf(integral_constant<int, 2>, const _Alloc& __a)
            : value(__a)
        {static_assert(!is_reference<_Hp>::value,
              "Attempted to default construct a reference element in a tuple");}

    template <class _Tp,
              class = typename enable_if<is_constructible<_Hp, _Tp>::value>::type>
        explicit __tuple_leaf(_Tp&& __t) noexcept((is_nothrow_constructible<_Hp, _Tp>::value))
            : value(yjh_def::forward<_Tp>(__t))
        {static_assert(!is_reference<_Hp>::value ||
                       (is_lvalue_reference<_Hp>::value &&
                        (is_lvalue_reference<_Tp>::value ||
                         is_same<typename remove_reference<_Tp>::type,
                                 reference_wrapper<
                                    typename remove_reference<_Hp>::type
                                 >
                                >::value)) ||
                        (is_rvalue_reference<_Hp>::value &&
                         !is_lvalue_reference<_Tp>::value),
       "Attempted to construct a reference element in a tuple with an rvalue");}

    template <class _Tp, class _Alloc>
        
        explicit __tuple_leaf(integral_constant<int, 0>, const _Alloc&, _Tp&& __t)
            : value(yjh_def::forward<_Tp>(__t))
        {static_assert(!is_lvalue_reference<_Hp>::value ||
                       (is_lvalue_reference<_Hp>::value &&
                        (is_lvalue_reference<_Tp>::value ||
                         is_same<typename remove_reference<_Tp>::type,
                                 reference_wrapper<
                                    typename remove_reference<_Hp>::type
                                 >
                                >::value)),
       "Attempted to construct a reference element in a tuple with an rvalue");}

    template <class _Tp, class _Alloc>
        
        explicit __tuple_leaf(integral_constant<int, 1>, const _Alloc& __a, _Tp&& __t)
            : value(allocator_arg_t(), __a, yjh_def::forward<_Tp>(__t))
        {static_assert(!is_lvalue_reference<_Hp>::value ||
                       (is_lvalue_reference<_Hp>::value &&
                        (is_lvalue_reference<_Tp>::value ||
                         is_same<typename remove_reference<_Tp>::type,
                                 reference_wrapper<
                                    typename remove_reference<_Hp>::type
                                 >
                                >::value)),
       "Attempted to construct a reference element in a tuple with an rvalue");}

    template <class _Tp, class _Alloc>
        
        explicit __tuple_leaf(integral_constant<int, 2>, const _Alloc& __a, _Tp&& __t)
            : value(yjh_def::forward<_Tp>(__t), __a)
        {static_assert(!is_lvalue_reference<_Hp>::value ||
                       (is_lvalue_reference<_Hp>::value &&
                        (is_lvalue_reference<_Tp>::value ||
                         is_same<typename remove_reference<_Tp>::type,
                                 reference_wrapper<
                                    typename remove_reference<_Hp>::type
                                 >
                                >::value)),
       "Attempted to construct a reference element in a tuple with an rvalue");}

    __tuple_leaf(const __tuple_leaf& __t) noexcept(is_nothrow_copy_constructible<_Hp>::value)
        : value(__t.get())
        {static_assert(!is_rvalue_reference<_Hp>::value, "Can not copy a tuple with rvalue reference member");}

    template <class _Tp>
        
        explicit __tuple_leaf(const __tuple_leaf<_Ip, _Tp>& __t)
                           noexcept((is_nothrow_constructible<_Hp, const _Tp&>::value))
            : value(__t.get()) {}

    template <class _Tp>
    __tuple_leaf&
    operator=(_Tp&& __t) noexcept((is_nothrow_assignable<_Hp&, _Tp>::value))
    {
        value = yjh_def::forward<_Tp>(__t);
        return *this;
    }

    
    int swap(__tuple_leaf& __t) noexcept(__is_nothrow_swappable<__tuple_leaf>::value)
    {
        yjh_def::swap(*this, __t);
        return 0;
    }

    _Hp& get()       _NOEXCEPT {return value;}
    const _Hp& get() const _NOEXCEPT {return value;}
};

/**
 * 对应的情况： _Hp 是一个空类，并且这个类并不是一个 final 类
 */
template <size_t _Ip, class _Hp>
class __tuple_leaf<_Ip, _Hp, true>
    : private _Hp
{
    __tuple_leaf& operator=(const __tuple_leaf&);
public:
    __tuple_leaf()
             _NOEXCEPT(is_nothrow_default_constructible<_Hp>::value) {}

    template <class _Alloc>

        __tuple_leaf(integral_constant<int, 0>, const _Alloc&) {}

    template <class _Alloc>

        __tuple_leaf(integral_constant<int, 1>, const _Alloc& __a)
            : _Hp(allocator_arg_t(), __a) {}

    template <class _Alloc>

        __tuple_leaf(integral_constant<int, 2>, const _Alloc& __a)
            : _Hp(__a) {}

    template <class _Tp,
              class = typename enable_if<is_constructible<_Hp, _Tp>::value>::type>

        explicit __tuple_leaf(_Tp&& __t) _NOEXCEPT((is_nothrow_constructible<_Hp, _Tp>::value))
            : _Hp(yjh_def::forward<_Tp>(__t)) {}

    template <class _Tp, class _Alloc>

        explicit __tuple_leaf(integral_constant<int, 0>, const _Alloc&, _Tp&& __t)
            : _Hp(yjh_def::forward<_Tp>(__t)) {}

    template <class _Tp, class _Alloc>

        explicit __tuple_leaf(integral_constant<int, 1>, const _Alloc& __a, _Tp&& __t)
            : _Hp(allocator_arg_t(), __a, yjh_def::forward<_Tp>(__t)) {}

    template <class _Tp, class _Alloc>

        explicit __tuple_leaf(integral_constant<int, 2>, const _Alloc& __a, _Tp&& __t)
            : _Hp(yjh_def::forward<_Tp>(__t), __a) {}

    template <class _Tp>

        explicit __tuple_leaf(const __tuple_leaf<_Ip, _Tp>& __t)
            _NOEXCEPT((is_nothrow_constructible<_Hp, const _Tp&>::value))
            : _Hp(__t.get()) {}

    template <class _Tp>

        __tuple_leaf&
        operator=(_Tp&& __t) _NOEXCEPT((is_nothrow_assignable<_Hp&, _Tp>::value))
        {
            _Hp::operator=(yjh_def::forward<_Tp>(__t));
            return *this;
        }

    int
    swap(__tuple_leaf& __t) _NOEXCEPT(__is_nothrow_swappable<__tuple_leaf>::value)
    {
        yjh_def::swap(*this, __t);
        return 0;
    }
    /**
     * 子类上转型到自己的父类对象
     */
       _Hp& get()       _NOEXCEPT {return static_cast<_Hp&>(*this);} 
       const _Hp& get() const _NOEXCEPT {return static_cast<const _Hp&>(*this);}
};

template <class ..._Tp>
void __swallow(_Tp&&...) _NOEXCEPT {}
/**
 * 如果参数列表中的所有的条件都是 true 的话，那么这个就返回一个 true 
 * 否则的话，返回 false
 */
template <bool ...> struct __all;

template <>
struct __all<>
{
    static const bool value = true;
};
/**
 * 递归
 */
template <bool _B0, bool ... _Bp>
struct __all<_B0, _Bp...>
{
    static const bool value = _B0 && __all<_Bp...>::value;
};

// __tuple_impl

template<class _Indx, class ..._Tp> struct __tuple_impl;

template<size_t ..._Indx, class ..._Tp>
/**
 * tuple 类中通过 __make_tuple_indices 将 __tuple_indices<0,1,2,3...., sizeof...(_Tp) - 1>
 * 传递到这个函数模板当中
 * 可能的使用方法 : __typle_impl<0,1,2,3,4,... sizeof...(_Tp) - 1, int, double, std::string, ....>
 */
struct __tuple_impl<__tuple_indices<_Indx...>, _Tp...>
    : public __tuple_leaf<_Indx, _Tp>...    //同时继承了多个 __tuple_leaf 类,通过这种方式存储所有的元素
{
    constexpr __tuple_impl()
    /**
     * 如果 _Tp 的所有的类型都有默认构造函数并且是非异常的,那么这里的默认构造函数就不会发生异常
     */
        noexcept(__all<is_nothrow_default_constructible<_Tp>::value...>::value) {}

    template <size_t ..._Uf, class ..._Tf,
              size_t ..._Ul, class ..._Tl, class ..._Up>
        explicit
        __tuple_impl(__tuple_indices<_Uf...>, __tuple_types<_Tf...>,
                     __tuple_indices<_Ul...>, __tuple_types<_Tl...>,
                     _Up&&... __u)
                     noexcept((__all<is_nothrow_constructible<_Tf, _Up>::value...>::value &&
                                 __all<is_nothrow_default_constructible<_Tl>::value...>::value)) :
                                 /**
                                  * 从这个地方大致可以看出来，_Tf 使用 _Up 来进行初始化，_Tl 则进行默认初始化，
                                  * 不提供初始化的值
                                  * 毕竟在构建 tuple 的过程中，未必可以一次性给定所有的数据类型的初始化值
                                  */
            __tuple_leaf<_Uf, _Tf>(yjh_def::forward<_Up>(__u))...,  // 使用给定的值进行初始化
            __tuple_leaf<_Ul, _Tl>()...         // 使用数据类型的默认初始化
            {}

    template <class _Alloc, size_t ..._Uf, class ..._Tf,
              size_t ..._Ul, class ..._Tl, class ..._Up>
        explicit
        __tuple_impl(allocator_arg_t, const _Alloc& __a,
                     __tuple_indices<_Uf...>, __tuple_types<_Tf...>,
                     __tuple_indices<_Ul...>, __tuple_types<_Tl...>,
                     _Up&&... __u) :
            __tuple_leaf<_Uf, _Tf>(__uses_alloc_ctor<_Tf, _Alloc, _Up>(), __a,
            yjh_def::forward<_Up>(__u))...,
            __tuple_leaf<_Ul, _Tl>(__uses_alloc_ctor<_Tl, _Alloc>(), __a)...
            {}

    template <class _Tuple,
              class = typename enable_if
                      <
                         __tuple_convertible<_Tuple, tuple<_Tp...> >::value
                      >::type
             >
        __tuple_impl(_Tuple&& __t) noexcept((__all<is_nothrow_constructible<_Tp, typename tuple_element<_Indx,
                                       typename __make_tuple_types<_Tuple>::type>::type>::value...>::value))
            : __tuple_leaf<_Indx, _Tp>(yjh_def::forward<typename tuple_element<_Indx,
                                       typename __make_tuple_types<_Tuple>::type>::type>(yjh_def::get<_Indx>(__t)))...
            {}

    template <class _Alloc, class _Tuple,
              class = typename enable_if
                      <
                         __tuple_convertible<_Tuple, tuple<_Tp...> >::value
                      >::type
             >
        __tuple_impl(allocator_arg_t, const _Alloc& __a, _Tuple&& __t)
            : __tuple_leaf<_Indx, _Tp>(__uses_alloc_ctor<_Tp, _Alloc, typename tuple_element<_Indx,
                                       typename __make_tuple_types<_Tuple>::type>::type>(), __a,
                                       yjh_def::forward<typename tuple_element<_Indx,
                                       typename __make_tuple_types<_Tuple>::type>::type>(yjh_def::get<_Indx>(__t)))...
            {}

    template <class _Tuple>
        typename enable_if
        <
            __tuple_assignable<_Tuple, tuple<_Tp...> >::value,
            __tuple_impl&
        >::type
        operator=(_Tuple&& __t) noexcept((__all<is_nothrow_assignable<_Tp&, typename tuple_element<_Indx,
                                       typename __make_tuple_types<_Tuple>::type>::type>::value...>::value))
        {
            __swallow(__tuple_leaf<_Indx, _Tp>::operator=(yjh_def::forward<typename tuple_element<_Indx,
                                       typename __make_tuple_types<_Tuple>::type>::type>(yjh_def::get<_Indx>(__t)))...);
            return *this;
        }

        __tuple_impl&
        operator=(const __tuple_impl& __t) noexcept((__all<is_nothrow_copy_assignable<_Tp>::value...>::value))
        {
            __swallow(__tuple_leaf<_Indx, _Tp>::operator=(static_cast<const __tuple_leaf<_Indx, _Tp>&>(__t).get())...);
            return *this;
        }

    void swap(__tuple_impl& __t)
        noexcept(__all<__is_nothrow_swappable<_Tp>::value...>::value)
    {
        __swallow(__tuple_leaf<_Indx, _Tp>::swap(static_cast<__tuple_leaf<_Indx, _Tp>&>(__t))...);
    }
};
// tuple
/**
 * 用法举例 tuple<double, char, std::string> student_imfor;
 */
template <class ..._Tp>
class tuple
{
    /**
     * __make_tuple_indices 默认的开始位置为 _Sp = 0 结束的位置为 sizeof...(_Tp)
     * 在这你 __make_tuple_indices 返回的 type 是 __tuple_indices<0,1,2,3,4,5,.... sizeof...(_Tp) - 1>
     */
    typedef __tuple_impl<typename __make_tuple_indices<sizeof...(_Tp)>::type, _Tp...> base;

    base base_;
    /**
     * 类的 friend 函数可以直接调用类的非public 对象，即可以调用类中的所有的对象
     * 如果 tuple 自身被定义为 const 那么其存储的数据在使用是也要是 const 
     */
    template <size_t _Jp, class ..._Up> friend
        typename tuple_element<_Jp, tuple<_Up...> >::type& get(tuple<_Up...>&) _NOEXCEPT;
    template <size_t _Jp, class ..._Up> friend
        const typename tuple_element<_Jp, tuple<_Up...> >::type& get(const tuple<_Up...>&) _NOEXCEPT;
    template <size_t _Jp, class ..._Up> friend
        typename tuple_element<_Jp, tuple<_Up...> >::type&& get(tuple<_Up...>&&) _NOEXCEPT;
public:

    constexpr tuple()
    /**
     * 使用默认构造函数需要保证所有的数据类型 _Tp 必须是默认构造并且无异常抛出的
     */
        noexcept(__all<is_nothrow_default_constructible<_Tp>::value...>::value) {}

    explicit tuple(const _Tp& ... __t) noexcept((__all<is_nothrow_copy_constructible<_Tp>::value...>::value)) 
        : base_(typename __make_tuple_indices<sizeof...(_Tp)>::type(),      // __tuple_indices<0,1,2,3,4, ...sizeof...(_Tp)>
                typename __make_tuple_types<tuple, sizeof...(_Tp)>::type(), // __tuple_type<_Tp1, _Tp2, _Tp3, _Tp4>
                typename __make_tuple_indices<0>::type(),   //  这里或许返回的是  __tuple_indices<> ? 这里面也是空的
                typename __make_tuple_types<tuple, 0>::type(),  // 这里返回的或许是 __tuple_type<> ? 这里面是空的
                __t...
                /**
                 * 根据 __tuple_impl 的定义可知，make_tuple_indices<sizeof...(_Tp)>::type() 中的所有的类型使用__t 来进行
                 * 初始化。 剩下的没有提供初始化值，那么只能采用默认初始化
                 */
               ) {}

    template <class _Alloc>
    /**
     * 这个构造函数和上面的构造函数中，要存储的数据类型的个数和提供的初始化的值 __t 的个数是相同的，所以所有的数据类型都可以用提供的
     * 初始化值进行正确的初始化
     * 后面的构造函数中，就出现了提供的初始化中的个数少于要存储的数据类型的个数，这时候，部分的数据类型需要使用默认初始化
     */
      tuple(allocator_arg_t, const _Alloc& __a, const _Tp& ... __t)
        : base_(allocator_arg_t(), __a,
                typename __make_tuple_indices<sizeof...(_Tp)>::type(),
                typename __make_tuple_types<tuple, sizeof...(_Tp)>::type(),
                typename __make_tuple_indices<0>::type(),
                typename __make_tuple_types<tuple, 0>::type(),  // 这里传递 tuple 模版参数，_Tp 的内容也会同时传递过去
                // __make_tuple_types<tuple<_Tp...>, 0>
                __t...
               ) {}

    template <class ..._Up,
              typename enable_if
                      <
                         sizeof...(_Up) <= sizeof...(_Tp) &&
                         __tuple_convertible
                         <
                            tuple<_Up...>,  // 第一个参数
                            typename __make_tuple_types<tuple,
                                     sizeof...(_Up) < sizeof...(_Tp) ?
                                        sizeof...(_Up) :
                                        sizeof...(_Tp)>::type
                         >::value,
                         bool
                      >::type = false
                      // 如果 enable_if 中的条件为 true 的话，那么这个enable_if就拥有 type 对象(类型为 bool)，那么使用 enable_if<>::value = false
                      // 就可以成功
                      //如果 enable_if 中的条件是 false 的话，那么就不会有 type 对象，那么这里的赋值就会报错
             >

        tuple(_Up&&... __u)
            noexcept((
                /**
                 * 这个地方没有看懂什么意思
                 */
                is_nothrow_constructible<
                    typename __make_tuple_indices<sizeof...(_Up)>::type,
                    typename __make_tuple_types<tuple, sizeof...(_Up)>::type,
                    typename __make_tuple_indices<sizeof...(_Tp), sizeof...(_Up)>::type,
                    typename __make_tuple_types<tuple, sizeof...(_Tp), sizeof...(_Up)>::type,
                    _Up...
                >::value
            ))
            /**
             * 前面 sizeof...(_Up) 种数据类型使用 __u 来进行初始化，后面剩下的数据类型使用默认初始化
             */
            : base_(typename __make_tuple_indices<sizeof...(_Up)>::type(),
                    typename __make_tuple_types<tuple, sizeof...(_Up)>::type(),
                    typename __make_tuple_indices<sizeof...(_Tp), sizeof...(_Up)>::type(),
                    typename __make_tuple_types<tuple, sizeof...(_Tp), sizeof...(_Up)>::type(),
                    yjh_def::forward<_Up>(__u)...) {}

    template <class ..._Up,
              typename enable_if
                      <
                         sizeof...(_Up) <= sizeof...(_Tp) &&
                         __tuple_constructible
                         <
                            tuple<_Up...>,
                            typename __make_tuple_types<tuple,
                                     sizeof...(_Up) < sizeof...(_Tp) ?
                                        sizeof...(_Up) :
                                        sizeof...(_Tp)>::type
                         >::value &&
                         !__tuple_convertible
                         <
                            tuple<_Up...>,
                            typename __make_tuple_types<tuple,
                                     sizeof...(_Up) < sizeof...(_Tp) ?
                                        sizeof...(_Up) :
                                        sizeof...(_Tp)>::type
                         >::value,
                         bool       //enable_if 的第二个参数
                      >::type =false
             >

        explicit
        tuple(_Up&&... __u)
            noexcept((
                is_nothrow_constructible<
                    typename __make_tuple_indices<sizeof...(_Up)>::type,
                    typename __make_tuple_types<tuple, sizeof...(_Up)>::type,
                    typename __make_tuple_indices<sizeof...(_Tp), sizeof...(_Up)>::type,
                    typename __make_tuple_types<tuple, sizeof...(_Tp), sizeof...(_Up)>::type,
                    _Up...
                >::value
            ))
            : base_(typename __make_tuple_indices<sizeof...(_Up)>::type(),
                    typename __make_tuple_types<tuple, sizeof...(_Up)>::type(),
                    typename __make_tuple_indices<sizeof...(_Tp), sizeof...(_Up)>::type(),
                    typename __make_tuple_types<tuple, sizeof...(_Tp), sizeof...(_Up)>::type(),
                    yjh_def::forward<_Up>(__u)...) {}

    template <class _Alloc, class ..._Up,
              class = typename enable_if
                      <
                         sizeof...(_Up) <= sizeof...(_Tp) &&
                         __tuple_convertible
                         <
                            tuple<_Up...>,
                            typename __make_tuple_types<tuple,
                                     sizeof...(_Up) < sizeof...(_Tp) ?
                                        sizeof...(_Up) :
                                        sizeof...(_Tp)>::type
                         >::value
                      >::type
             >

        tuple(allocator_arg_t, const _Alloc& __a, _Up&&... __u)
            : base_(allocator_arg_t(), __a,
                    typename __make_tuple_indices<sizeof...(_Up)>::type(),
                    typename __make_tuple_types<tuple, sizeof...(_Up)>::type(),
                    typename __make_tuple_indices<sizeof...(_Tp), sizeof...(_Up)>::type(),
                    typename __make_tuple_types<tuple, sizeof...(_Tp), sizeof...(_Up)>::type(),
                    yjh_def::forward<_Up>(__u)...) {}

    template <class _Tuple,
              typename enable_if
                      <
                         __tuple_convertible<_Tuple, tuple>::value,
                         bool
                      >::type = false
             >

        tuple(_Tuple&& __t) noexcept((is_nothrow_constructible<base, _Tuple>::value))
            : base_(yjh_def::forward<_Tuple>(__t)) {}

    template <class _Tuple,
              typename enable_if
                      <
                         __tuple_constructible<_Tuple, tuple>::value &&
                         !__tuple_convertible<_Tuple, tuple>::value,
                         bool
                      >::type = false
             >

        explicit
        tuple(_Tuple&& __t) noexcept((is_nothrow_constructible<base, _Tuple>::value))
            : base_(yjh_def::forward<_Tuple>(__t)) {}

    template <class _Alloc, class _Tuple,
              class = typename enable_if
                      <
                         __tuple_convertible<_Tuple, tuple>::value
                      >::type
             >

        tuple(allocator_arg_t, const _Alloc& __a, _Tuple&& __t)
            : base_(allocator_arg_t(), __a, yjh_def::forward<_Tuple>(__t)) {}

    template <class _Tuple,
              class = typename enable_if
                      <
                         __tuple_assignable<_Tuple, tuple>::value
                      >::type
             >

        tuple&
        operator=(_Tuple&& __t) noexcept((is_nothrow_assignable<base&, _Tuple>::value))
        {
            base_.operator=(yjh_def::forward<_Tuple>(__t));
            return *this;
        }

    void swap(tuple& __t) noexcept(__all<__is_nothrow_swappable<_Tp>::value...>::value)
        {base_.swap(__t.base_);}
};

template <>
class tuple<>
{
public:
    constexpr tuple() _NOEXCEPT {}
    template <class _Alloc>
        tuple(allocator_arg_t, const _Alloc&) _NOEXCEPT {}
    template <class _Alloc>
        tuple(allocator_arg_t, const _Alloc&, const tuple&) _NOEXCEPT {}
    template <class _Up>
        tuple(array<_Up, 0>) _NOEXCEPT {}
    template <class _Alloc, class _Up>
        tuple(allocator_arg_t, const _Alloc&, array<_Up, 0>) _NOEXCEPT {}
    void swap(tuple&) _NOEXCEPT {}
};

template <class ..._Tp>
inline
typename enable_if
<
    __all<__is_swappable<_Tp>::value...>::value,
    void
>::type
swap(tuple<_Tp...>& __t, tuple<_Tp...>& __u)
                 noexcept(__all<__is_nothrow_swappable<_Tp>::value...>::value)
    {__t.swap(__u);}

// get
/**
 * 获取 tuple 的第 _Ip 个元素值，返回其引用
 */
template <size_t _Ip, class ..._Tp>
inline
// 返回类型通过 tuple_element 来获得
typename tuple_element<_Ip, tuple<_Tp...> >::type&
get(tuple<_Tp...>& __t) _NOEXCEPT
{
    typedef typename tuple_element<_Ip, tuple<_Tp...> >::type type;
    /**
     * __t.base_ 是 __tuple_leaf 的子类，进行向上转型将其转化为 __tuple_leaf
     * 的类型，然后调用其 get() 方法，得到其中存储的数据
     */
    return static_cast<__tuple_leaf<_Ip, type>&>(__t.base_).get();
}

template <size_t _Ip, class ..._Tp>
inline
const typename tuple_element<_Ip, tuple<_Tp...> >::type&
get(const tuple<_Tp...>& __t) _NOEXCEPT
{
    typedef typename tuple_element<_Ip, tuple<_Tp...> >::type type;
    return static_cast<const __tuple_leaf<_Ip, type>&>(__t.base_).get();
}

template <size_t _Ip, class ..._Tp>
inline
typename tuple_element<_Ip, tuple<_Tp...> >::type&&
get(tuple<_Tp...>&& __t) _NOEXCEPT
{
    typedef typename tuple_element<_Ip, tuple<_Tp...> >::type type;
    return static_cast<type&&>(
             static_cast<__tuple_leaf<_Ip, type>&&>(__t.base_).get());
}

// tie
template <class ..._Tp>
inline
tuple<_Tp&...>
tie(_Tp&... __t) noexcept
{
    return tuple<_Tp&...>(__t...);
}

/**
 * __ignore_t : ignore type 忽略类型，这个类的所有数据类型的实例之间可以进行相互
 * 赋值
 */

template <class _Up>
struct __ignore_t
{
    template <class _Tp>
        const __ignore_t& operator=(_Tp&&) const {return *this;}
};
/**
 * 一个 ignore 的实例
 */
namespace { const __ignore_t<unsigned char> ignore = __ignore_t<unsigned char>(); }

template <class _Tp> class reference_wrapper;   // 来自于 __functional_base.cpp 的 reference_wrapper

template <class _Tp>
struct ___make_tuple_return
{
    typedef _Tp type;
};

template <class _Tp>
struct ___make_tuple_return<reference_wrapper<_Tp> >
{
    typedef _Tp& type;
};

template <class _Tp>
struct __make_tuple_return
{
    typedef typename ___make_tuple_return<typename decay<_Tp>::type>::type type;
};

template <class... _Tp>
inline
tuple<typename __make_tuple_return<_Tp>::type...>
make_tuple(_Tp&&... __t)
{
    return tuple<typename __make_tuple_return<_Tp>::type...>(yjh_def::forward<_Tp>(__t)...);
}

template <class... _Tp>
inline
tuple<_Tp&&...>
forward_as_tuple(_Tp&&... __t) _NOEXCEPT
{
    return tuple<_Tp&&...>(yjh_def::forward<_Tp>(__t)...);
}

template <size_t _Ip>
// 这里的 _Ip 对应与 tuple 中的下标值 _Ip - 1
struct __tuple_equal
{
    template <class _Tp, class _Up>
    bool operator()(const _Tp& __x, const _Up& __y)
    {
        return __tuple_equal<_Ip - 1>()(__x, __y) && get<_Ip-1>(__x) == get<_Ip-1>(__y);
    }
};

template <>
// _Ip 的值为 0 的时候，两个 tuple 已经比较完了
struct __tuple_equal<0>
{
    template <class _Tp, class _Up>

    bool operator()(const _Tp&, const _Up&)
    {
        return true;
    }
};

template <class ..._Tp, class ..._Up>
inline
bool
operator==(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
{
    return __tuple_equal<sizeof...(_Tp)>()(__x, __y);
}

template <class ..._Tp, class ..._Up>
inline
bool
operator!=(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
{
    return !(__x == __y);
}

template <size_t _Ip>
struct __tuple_less
{
    template <class _Tp, class _Up>
    bool operator()(const _Tp& __x, const _Up& __y)
    {
        return __tuple_less<_Ip-1>()(__x, __y) ||
             (!__tuple_less<_Ip-1>()(__y, __x) && get<_Ip-1>(__x) < get<_Ip-1>(__y));
    }
};

template <>
// _Ip 的值为 0 的时候，两个 tuple 已经比较完了， 所以直接返回 false 值就可以了
struct __tuple_less<0>
{
    template <class _Tp, class _Up>
    bool operator()(const _Tp&, const _Up&)
    {
        return false;
    }
};

template <class ..._Tp, class ..._Up>
inline
bool
operator<(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
{
    return __tuple_less<sizeof...(_Tp)>()(__x, __y);
}

template <class ..._Tp, class ..._Up>
inline
bool
operator>(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
{
    return __y < __x;
}

template <class ..._Tp, class ..._Up>
inline
bool
operator>=(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
{
    return !(__x < __y);
}

template <class ..._Tp, class ..._Up>
inline
bool
operator<=(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
{
    return !(__y < __x);
}

// tuple_cat
// 将两个 tuple 对象进行合并为一个 tuple 对象
template <class _Tp, class _Up> struct __tuple_cat_type;

template <class ..._Ttypes, class ..._Utypes>
//通过合并两个 tuple 对象，获得合并之后的对象的类型
// 第一个参数是　tuple 类型； 第二个类型为 __tuple_types 类型
struct __tuple_cat_type<tuple<_Ttypes...>, __tuple_types<_Utypes...> >
{
    typedef tuple<_Ttypes..., _Utypes...> type;
};

// _Is_Tuple0TupleLike = false 的时候是一个空类
template <class _ResultTuple, bool _Is_Tuple0TupleLike, class ..._Tuples>
struct __tuple_cat_return_1
{
};
/**
 * 结合两个 tuple 类型
 */
template <class ..._Types, class _Tuple0>
struct __tuple_cat_return_1<tuple<_Types...>, true, _Tuple0>
{
    typedef typename __tuple_cat_type<tuple<_Types...>,
            typename __make_tuple_types<typename remove_reference<_Tuple0>::type>::type>::type
                                                                           type;
};

/**
 * 对于将多个 tuple 类型进行合并，递归就完事了
 * 这里的合并将所有的 tuple 的所有的数据类型全部都合并起来
 */
template <class ..._Types, class _Tuple0, class _Tuple1, class ..._Tuples>
struct __tuple_cat_return_1<tuple<_Types...>, true, _Tuple0, _Tuple1, _Tuples...>
    : public __tuple_cat_return_1<
                 typename __tuple_cat_type<
                     tuple<_Types...>,
                     typename __make_tuple_types<typename remove_reference<_Tuple0>::type>::type
                 >::type,
                 __tuple_like<typename remove_reference<_Tuple1>::type>::value, // 查看 _Tuple1 是否是 tuple 类型
                 _Tuple1, _Tuples...>
{
};

template <class ..._Tuples> struct __tuple_cat_return;

template <class _Tuple0, class ..._Tuples>
struct __tuple_cat_return<_Tuple0, _Tuples...>
    : public __tuple_cat_return_1<tuple<>,
         __tuple_like<typename remove_reference<_Tuple0>::type>::value, _Tuple0,
                                                                     _Tuples...>
{
};
/**
 * 没有 tuple 类型输入的时候的特化
 */
template <>
struct __tuple_cat_return<>
{
    typedef tuple<> type;
};

inline
tuple<>
tuple_cat()
{
    return tuple<>();
}

template <class _Rp, class _Indices, class _Tuple0, class ..._Tuples>
struct __tuple_cat_return_ref_imp;

template <class ..._Types, size_t ..._I0, class _Tuple0>
struct __tuple_cat_return_ref_imp<tuple<_Types...>, __tuple_indices<_I0...>, _Tuple0>
{
    typedef typename remove_reference<_Tuple0>::type _T0;
    typedef tuple<_Types..., typename __apply_cv<_Tuple0,
                          typename tuple_element<_I0, _T0>::type>::type&&...> type; // 为什么这里 使用 ::type&& ?
};

/**
 * 递归
 */
template <class ..._Types, size_t ..._I0, class _Tuple0, class _Tuple1, class ..._Tuples>
struct __tuple_cat_return_ref_imp<tuple<_Types...>, __tuple_indices<_I0...>,
                                  _Tuple0, _Tuple1, _Tuples...>
    : public __tuple_cat_return_ref_imp<
         tuple<_Types..., typename __apply_cv<_Tuple0,  // 如果 _Tuple0 含有 cv 限限定符， 那么 type&& 也加上 cv 限定符
               typename tuple_element<_I0,
                  typename remove_reference<_Tuple0>::type>::type>::type&&...>,
                  /**
                   * 如果 type 是左值引用类型，那么 type&& 将还是左值引用类型
                   * 如果 type 是右值引用类型，那么 type&& 将是右值引用类型
                   */
         typename __make_tuple_indices<tuple_size<typename
                                 remove_reference<_Tuple1>::type>::value>::type,
         _Tuple1, _Tuples...>
{
};
/**
 * 所有的数据都是左值类型或者是右值类型？
 */
template <class _Tuple0, class ..._Tuples>
struct __tuple_cat_return_ref
    : public __tuple_cat_return_ref_imp<tuple<>,
               typename __make_tuple_indices<
                        tuple_size<typename remove_reference<_Tuple0>::type>::value
               >::type, _Tuple0, _Tuples...>
{
};

template <class _Types, class _I0, class _J0>
struct __tuple_cat;

/**
 * _IO 是当前的 tuple 的下标的索引，_JO 是 tuple0 的下标的索引
 */
template <class ..._Types, size_t ..._I0, size_t ..._J0>
struct __tuple_cat<tuple<_Types...>, __tuple_indices<_I0...>, __tuple_indices<_J0...> >
{
    template <class _Tuple0>
    typename __tuple_cat_return_ref<tuple<_Types...>&&, _Tuple0&&>::type
    operator()(tuple<_Types...> __t, _Tuple0&& __t0)
    {
        return yjh_def::forward_as_tuple(yjh_def::forward<_Types>(get<_I0>(__t))...,
                                      get<_J0>(yjh_def::forward<_Tuple0>(__t0))...);
    }

    template <class _Tuple0, class _Tuple1, class ..._Tuples>
    typename __tuple_cat_return_ref<tuple<_Types...>&&, _Tuple0&&, _Tuple1&&, _Tuples&&...>::type
    operator()(tuple<_Types...> __t, _Tuple0&& __t0, _Tuple1&& __t1, _Tuples&& ...__tpls)
    {
        typedef typename remove_reference<_Tuple0>::type _T0;
        typedef typename remove_reference<_Tuple1>::type _T1;
        return __tuple_cat<
           tuple<_Types..., typename __apply_cv<_Tuple0, typename tuple_element<_J0, _T0>::type>::type&&...>,
           typename __make_tuple_indices<sizeof ...(_Types) + tuple_size<_T0>::value>::type,
           typename __make_tuple_indices<tuple_size<_T1>::value>::type>()
                           (yjh_def::forward_as_tuple(
                              yjh_def::forward<_Types>(get<_I0>(__t))...,
                              get<_J0>(yjh_def::forward<_Tuple0>(__t0))...
                            ),
                            yjh_def::forward<_Tuple1>(__t1),
                            yjh_def::forward<_Tuples>(__tpls)...);
    }
};

template <class _Tuple0, class... _Tuples>
inline
typename __tuple_cat_return<_Tuple0, _Tuples...>::type
tuple_cat(_Tuple0&& __t0, _Tuples&&... __tpls)
{
    typedef typename remove_reference<_Tuple0>::type _T0;
    return __tuple_cat<tuple<>, __tuple_indices<>,
                  typename __make_tuple_indices<tuple_size<_T0>::value>::type>()
                  (tuple<>(), yjh_def::forward<_Tuple0>(__t0),
                                            yjh_def::forward<_Tuples>(__tpls)...);
}

template <class ..._Tp, class _Alloc>
struct uses_allocator<tuple<_Tp...>, _Alloc>
    : true_type {};

/**
 * 这里的实现？
 * 这里应该是 pair 中那么没有在 utility.cpp 中实现的 private 构造函数，这个构造函数在这个地方进行了实现
 * pair 的 first 和 second 成员在构造时接收了 tuple<_Args1...> 和 tuple<_Args2...>中的所有的数值
 */
template <class _T1, class _T2>
template <class... _Args1, class... _Args2, size_t ..._I1, size_t ..._I2>
inline
pair<_T1, _T2>::pair(piecewise_construct_t,
                     tuple<_Args1...>& __first_args, tuple<_Args2...>& __second_args,
                     __tuple_indices<_I1...>, __tuple_indices<_I2...>)
    :  first(yjh_def::forward<_Args1>(get<_I1>( __first_args))...),
      second(yjh_def::forward<_Args2>(get<_I2>(__second_args))...)
{
}

#endif //_YJH_HAS_NO_VARIADICS

}
#endif
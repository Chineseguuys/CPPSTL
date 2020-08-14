#ifndef _LIBCPP_FUNCTION_BASE
#define _LIBCPP_FUNCTION_BASE

#include "__config.cpp"
#include "type_traits.cpp"
#include "typeinfo"
#include "exception.cpp"



namespace yjh_def
{
/**
 * 对于单个参数的可调用类型，有一个参数的类型和一个返回值的类型
 */
template <class _Arg, class _Result>
struct unary_function
{
    typedef _Arg        argument_type;
    typedef _Result     result_type;            
};
/**
 * 对于两个参数的可调用类型，有两个参数的类型和一个返回值的类型
 */
template <class _Arg1, class _Arg2, class _Result>
struct binary_function
{
    typedef _Arg1   first_argument_type;
    typedef _Arg2   second_argument_type;
    typedef _Result result_type;
};

template <class _Tp>    struct hash;

template <class _Tp>
struct __has_result_type
{
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename _Up::result_type* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

// less
template <class _Tp>
struct less : binary_function<_Tp, _Tp, bool>
{
    bool operator()(const _Tp& __x, const _Tp& __y) const
    { return __x < __y; }
};

#ifndef _YJH_HAS_NO_VARIADICS
// __weak_result_type
template <class _Tp>
/**
 * 查看 _Tp 类型是否是 unary_function 类型或者继承自 unary_function 类型
 */
struct __derives_from_unary_function
{
private:
    struct __two { char __lx; char __lxx; };
    static __two __test(...);
    template <class _Ap, class _Rp>
        static unary_function<_Ap, _Rp>
        __test(const volatile unary_function<_Ap, _Rp>*);
        // 利用的是类的性质，父类指针可以指向子类对象

public:
    static const bool value = !is_same<decltype(__test((_Tp*)0)), __two>::value;
    typedef decltype(__test((_Tp*)0)) type;
};

/**
 * 同理于 __derives_from_unary_function
 */
template <class _Tp>
struct __derives_from_binary_function
{
private:
    struct __two {char __lx; char __lxx;};
    static __two __test(...);
    template <class _A1, class _A2, class _Rp>
        static binary_function<_A1, _A2, _Rp>
        __test(const volatile binary_function<_A1, _A2, _Rp>*);
public:
    static const bool value = !is_same<decltype(__test((_Tp*)0)), __two>::value;
    typedef decltype(__test((_Tp*)0)) type;
};

/**
 * 如果 __derives_from_unary_function<_Tp>::value 是 true 的话，那么 
 * __derives_from_unary_function<_Tp>::type 就是 unary_function<_Ap, _Rp>类型
 * 下面的 __maybe_derive_from_binary_function 也是同理
 */
template <class _Tp, bool = __derives_from_unary_function<_Tp>::value>
struct __maybe_derive_from_unary_function  // bool is true
    : public __derives_from_unary_function<_Tp>::type
{
};

template <class _Tp>
struct __maybe_derive_from_unary_function<_Tp, false>
{
};

template <class _Tp, bool = __derives_from_binary_function<_Tp>::value>
struct __maybe_derive_from_binary_function  // bool is true
    : public __derives_from_binary_function<_Tp>::type
{
};

template <class _Tp>
struct __maybe_derive_from_binary_function<_Tp, false>
{
};

template <class _Tp, bool = __has_result_type<_Tp>::value>
struct __weak_result_type_imp // bool is true
    : public __maybe_derive_from_unary_function<_Tp>,
      public __maybe_derive_from_binary_function<_Tp>
{
    typedef typename _Tp::result_type result_type;
};

/**
 * 之所以称为 __weak 应该是由于 只考虑了 unary_function 和 binary_function 
 */
template <class _Tp>
struct __weak_result_type_imp<_Tp, false>
    : public __maybe_derive_from_unary_function<_Tp>,
      public __maybe_derive_from_binary_function<_Tp>
{
};

template <class _Tp>
struct __weak_result_type
    : public __weak_result_type_imp<_Tp>
{
};

// 下面全部都是__weak_result_type 的特化过程
// 0 argument case
/**
 * 函数类型
 */
template <class _Rp>
struct __weak_result_type<_Rp ()>
{
    typedef _Rp result_type;
};

/**
 * 函数引用类型
 */
template <class _Rp>
struct __weak_result_type<_Rp (&)()>
{
    typedef _Rp result_type;
};

/**
 * 函数指针类型
 */
template <class _Rp>
struct __weak_result_type<_Rp (*)()>
{
    typedef _Rp result_type;
};

// 1 argument case
// 函数类型
template <class _Rp, class _A1>
struct __weak_result_type<_Rp (_A1)>
    : public unary_function<_A1, _Rp>
{
};
// 函数引用
template <class _Rp, class _A1>
struct __weak_result_type<_Rp (&)(_A1)>
    : public unary_function<_A1, _Rp>
{
};
// 函数指针
template <class _Rp, class _A1>
struct __weak_result_type<_Rp (*)(_A1)>
    : public unary_function<_A1, _Rp>
{
};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)()>
    : public unary_function<_Cp*, _Rp>
{
};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)() const>
    : public unary_function<const _Cp*, _Rp>
{
};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)() volatile>
    : public unary_function<volatile _Cp*, _Rp>
{
};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)() const volatile>
    : public unary_function<const volatile _Cp*, _Rp>
{
};

// 2 argument case

template <class _Rp, class _A1, class _A2>
struct __weak_result_type<_Rp (_A1, _A2)>
    : public binary_function<_A1, _A2, _Rp>
{
};

template <class _Rp, class _A1, class _A2>
struct __weak_result_type<_Rp (*)(_A1, _A2)>
    : public binary_function<_A1, _A2, _Rp>
{
};

template <class _Rp, class _A1, class _A2>
struct __weak_result_type<_Rp (&)(_A1, _A2)>
    : public binary_function<_A1, _A2, _Rp>
{
};
/**
 * 指向成员函数的指针
 */
template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1)>
    : public binary_function<_Cp*, _A1, _Rp>
{
};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1) const>
    : public binary_function<const _Cp*, _A1, _Rp>
{
};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1) volatile>
    : public binary_function<volatile _Cp*, _A1, _Rp>
{
};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1) const volatile>
    : public binary_function<const volatile _Cp*, _A1, _Rp>
{
};

// 3 or more arguments

template <class _Rp, class _A1, class _A2, class _A3, class ..._A4>
struct __weak_result_type<_Rp (_A1, _A2, _A3, _A4...)>
{
    typedef _Rp result_type;
};

template <class _Rp, class _A1, class _A2, class _A3, class ..._A4>
struct __weak_result_type<_Rp (&)(_A1, _A2, _A3, _A4...)>
{
    typedef _Rp result_type;
};

template <class _Rp, class _A1, class _A2, class _A3, class ..._A4>
struct __weak_result_type<_Rp (*)(_A1, _A2, _A3, _A4...)>
{
    typedef _Rp result_type;
};

template <class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...)>
{
    typedef _Rp result_type;
};

template <class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...) const>
{
    typedef _Rp result_type;
};

template <class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...) volatile>
{
    typedef _Rp result_type;
};

template <class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...) const volatile>
{
    typedef _Rp result_type;
};

// bullets 1 and 2
// 下面是几个 lambda 函数
template <class _Fp, class _A0, class ..._Args>
inline
auto
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    -> decltype((yjh_def::forward<_A0>(__a0).*__f)(yjh_def::forward<_Args>(__args)...))
{
    return (yjh_def::forward<_A0>(__a0).*__f)(yjh_def::forward<_Args>(__args)...);
}

template <class _Fp, class _A0, class ..._Args>
inline
auto
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    -> decltype(((*yjh_def::forward<_A0>(__a0)).*__f)(yjh_def::forward<_Args>(__args)...))
{
    return ((*yjh_def::forward<_A0>(__a0)).*__f)(yjh_def::forward<_Args>(__args)...);
}

// bullets 3 and 4

template <class _Fp, class _A0>
inline
auto
__invoke(_Fp&& __f, _A0&& __a0)
    -> decltype(yjh_def::forward<_A0>(__a0).*__f)
{
    return yjh_def::forward<_A0>(__a0).*__f;
}

template <class _Fp, class _A0>
inline
auto
__invoke(_Fp&& __f, _A0&& __a0)
    -> decltype((*yjh_def::forward<_A0>(__a0)).*__f)
{
    return (*yjh_def::forward<_A0>(__a0)).*__f;
}

// bullet 5

template <class _Fp, class ..._Args>
inline
auto
__invoke(_Fp&& __f, _Args&& ...__args)
    -> decltype(yjh_def::forward<_Fp>(__f)(yjh_def::forward<_Args>(__args)...))
{
    return yjh_def::forward<_Fp>(__f)(yjh_def::forward<_Args>(__args)...);
}

template <class _Tp, class ..._Args>
struct __invoke_return
{
    typedef decltype(__invoke(yjh_def::declval<_Tp>(), yjh_def::declval<_Args>()...)) type;
};

/**
 * _Tp 可以是基本类型，也可以是函数(可以是基本的函数，也可以是类的成员函数)
 * 可能的使用方法
 * yjh_def::reference_wrapper<int(int, int)> a_reference(some_func);
 * a_reference(100,200)
 */
template <class _Tp>
class reference_wrapper
    : public __weak_result_type<_Tp>
{
public:
    typedef _Tp type;
private:
    type* __f_;  // 如果是函数类型，这里的 __f_ 就是指向函数的指针

public:
    reference_wrapper(type& __f) noexcept : __f_(&__f) {}
private:
    reference_wrapper(type&&);
public:
    operator    type&       () const noexcept { return *__f_; }
                type&    get() const noexcept { return *__f_; }
    
    template <class... _ArgTypes>
    typename __invoke_of<type&, _ArgTypes...>::type // 这里得到 resultType
        operator() (_ArgTypes&&... __args) const
        {
            return __invoke(get(), yjh_def::forward<_ArgTypes>(__args)...);
        }
};

template <class _Tp>    struct ____is_reference_wrapper : public false_type {};
template <class _Tp>    struct ____is_reference_wrapper<reference_wrapper<_Tp> > : public true_type {};
template <class _Tp>    struct __is_reference_wrapper
    : public ____is_reference_wrapper<typename remove_cv<_Tp>::type> {};

template <class _Tp>
inline
reference_wrapper<_Tp>
ref(_Tp& __t) _NOEXCEPT
{
    return reference_wrapper<_Tp>(__t);
}

template <class _Tp>
inline
reference_wrapper<_Tp>
ref(reference_wrapper<_Tp> __t) _NOEXCEPT
{
    return ref(__t.get());
}

template <class _Tp>
inline
reference_wrapper<const _Tp>
cref(const _Tp& __t) _NOEXCEPT
{
    return reference_wrapper<const _Tp>(__t);
}

template <class _Tp>
inline
reference_wrapper<const _Tp>
cref(reference_wrapper<_Tp> __t) _NOEXCEPT
{
    return cref(__t.get());
}

template <class _Tp> void ref(const _Tp&&) = delete;
template <class _Tp> void cref(const _Tp&&) = delete;

#endif
}
#endif
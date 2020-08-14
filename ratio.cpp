#ifndef _LIBCPP_RATIO
#define _LIBCPP_RATIO


#include "__config.cpp"
#include "cstdint.cpp"
#include "climits.cpp"
#include "type_traits.cpp"


#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif


_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"




namespace yjh_def
{
// __static_gcd
/**
 * 计算最大公约数
 */
template <intmax_t _Xp, intmax_t _Yp>
struct __static_gcd
{
    static const intmax_t value = __static_gcd<_Yp, _Xp % _Yp>::value;
};

template <intmax_t _Xp>
struct __static_gcd<_Xp, 0>
{
    static const intmax_t value = _Xp;
};

template <>
struct __static_gcd<0, 0>
{
    static const intmax_t value = 1;
};


// __static_lcm
// 最小公倍数

template <intmax_t _Xp, intmax_t _Yp>
struct __static_lcm
{
    static const intmax_t value = _Xp / __static_gcd<_Xp, _Yp>::value * _Yp;
};

// __static_abs
// 取绝对值
template <intmax_t _Xp>
struct __static_abs
{
    static const intmax_t value = _Xp < 0 ? -_Xp : _Xp;
};

// __static_sign
// 确定 __Xp 的符号，大于零得到 1， 小于零得到 -1，等于零得到0
template <intmax_t _Xp>
struct __static_sign
{
    static const intmax_t value = _Xp == 0 ? 0 : (_Xp < 0 ? -1 : 1);
};

template <intmax_t _Xp, intmax_t _Yp, intmax_t = __static_sign<_Yp>::value>
class __ll_add;

template <intmax_t _Xp, intmax_t _Yp>
class __ll_add<_Xp, _Yp, 1>
{
    static const intmax_t min = (1LL << (sizeof(intmax_t) * CHAR_BIT - 1)) + 1;
    static const intmax_t max = -min;

    static_assert(_Xp <= max - _Yp, "overflow in __ll_add");
public:
    static const intmax_t value = _Xp + _Yp;
};

template <intmax_t _Xp, intmax_t _Yp>
class __ll_add<_Xp, _Yp, 0>
{
public:
    static const intmax_t value = _Xp;
};

template <intmax_t _Xp, intmax_t _Yp>
class __ll_add<_Xp, _Yp, -1>
{
    /**
     * 最小的负数
     * 复数在内存中都是采用原数字的绝对值的二进制编码取反再 + 1 得到的。这种编码形式被称为 补码。补码还原为原码也是采用取反 + 1 就可以了
     * 0x800000001 表示的是负数。 那么它取反码 + 1 得到的就是 0x7ffffffff  
     * 我们来考虑 0x80000000 ，他可以用来表示 -0 ，但是没有这个表示的必要，有 +0 就够了，那么就用 0x800000000 表示 0x80000000001 - 1
     * 因此 0x800000000 是最小的负数 最小的负数的绝对值比最大的正数大 1 (举个例子：char 的范围就是 -128 --- +127)
     */
    static const intmax_t min = (1LL << (sizeof(intmax_t) * CHAR_BIT - 1)) + 1;
    static const intmax_t max = -min;

    static_assert(min - _Yp <= _Xp, "overflow in __ll_add");
public:
    static const intmax_t value = _Xp + _Yp;
};

template <intmax_t _Xp, intmax_t _Yp, intmax_t = __static_sign<_Yp>::value>
class __ll_sub;

template <intmax_t _Xp, intmax_t _Yp>
class __ll_sub<_Xp, _Yp, 1>
{
    static const intmax_t min = (1LL << (sizeof(intmax_t) * CHAR_BIT - 1)) + 1;
    static const intmax_t max = -min;

    static_assert(min + _Yp <= _Xp, "overflow in __ll_sub");
public:
    static const intmax_t value = _Xp - _Yp;
};

template <intmax_t _Xp, intmax_t _Yp>
class __ll_sub<_Xp, _Yp, 0>
{
public:
    static const intmax_t value = _Xp;
};

template <intmax_t _Xp, intmax_t _Yp>
class __ll_sub<_Xp, _Yp, -1>
{
    static const intmax_t min = (1LL << (sizeof(intmax_t) * CHAR_BIT - 1)) + 1;
    static const intmax_t max = -min;

    static_assert(_Xp <= max + _Yp, "overflow in __ll_sub");
public:
    static const intmax_t value = _Xp - _Yp;
};

template <intmax_t _Xp, intmax_t _Yp>
class __ll_mul
{
    static const intmax_t nan = (1LL << (sizeof(intmax_t) * CHAR_BIT - 1));
    static const intmax_t min = nan + 1;
    static const intmax_t max = -min;
    static const intmax_t __a_x = __static_abs<_Xp>::value;
    static const intmax_t __a_y = __static_abs<_Yp>::value;

    static_assert(_Xp != nan && _Yp != nan && __a_x <= max / __a_y, "overflow in __ll_mul");
public:
    static const intmax_t value = _Xp * _Yp;
};

template <intmax_t _Yp>
class __ll_mul<0, _Yp>
{
public:
    static const intmax_t value = 0;
};

template <intmax_t _Xp>
class __ll_mul<_Xp, 0>
{
public:
    static const intmax_t value = 0;
};

template <>
class __ll_mul<0, 0>
{
public:
    static const intmax_t value = 0;
};

// Not actually used but left here in case needed in future maintenance
template <intmax_t _Xp, intmax_t _Yp>
class __ll_div
{
    static const intmax_t nan = (1LL << (sizeof(intmax_t) * CHAR_BIT - 1));
    static const intmax_t min = nan + 1;
    static const intmax_t max = -min;

    static_assert(_Xp != nan && _Yp != nan && _Yp != 0, "overflow in __ll_div");
public:
    static const intmax_t value = _Xp / _Yp;
};

// ratio
/**
 * ratio 用于表示分数
 * 第一个参数是分子，第二个参数是分母
 * 默认的情况下，分母的值为 1 ，即这个分数代表的是一个整数
 * 编译期间给定的分数，分子和分母未必是最简的形式
 */
template <intmax_t _Num, intmax_t _Den = 1>
class ratio
{
    static_assert(__static_abs<_Num>::value >= 0, "ratio numerator is out of range");
    static_assert(_Den != 0, "ratio ddivide by 0");
    static_assert(__static_abs<_Den>::value >  0, "ratio denominator is out of range");
    static _LIBCPP_CONSTEXPR const intmax_t __na = __static_abs<_Num>::value;
    static _LIBCPP_CONSTEXPR const intmax_t __da = __static_abs<_Den>::value;
    static _LIBCPP_CONSTEXPR const intmax_t __s =  \
                __static_sign<_Num>::value * __static_sign<_Den>::value;
    static _LIBCPP_CONSTEXPR const intmax_t __gcd = __static_gcd<__na, __da>::value;
public:
    static _LIBCPP_CONSTEXPR const intmax_t num = __s * __na / __gcd;
    static _LIBCPP_CONSTEXPR const intmax_t den = __da / __gcd;

    typedef ratio<num, den> type;
};

template <intmax_t _Num, intmax_t _Den>
_LIBCPP_CONSTEXPR const intmax_t ratio<_Num, _Den>::num;

template <intmax_t _Num, intmax_t _Den>
_LIBCPP_CONSTEXPR const intmax_t ratio<_Num, _Den>::den;

template <class _Tp>                    struct __is_ratio                     : false_type {};
template <intmax_t _Num, intmax_t _Den> struct __is_ratio<ratio<_Num, _Den> > : true_type  {};


typedef ratio<1LL, 1000000000000000000LL> atto;
typedef ratio<1LL,    1000000000000000LL> femto;
typedef ratio<1LL,       1000000000000LL> pico;
typedef ratio<1LL,          1000000000LL> nano;
typedef ratio<1LL,             1000000LL> micro;
typedef ratio<1LL,                1000LL> milli;
typedef ratio<1LL,                 100LL> centi;
typedef ratio<1LL,                  10LL> deci;
typedef ratio<                 10LL, 1LL> deca;
typedef ratio<                100LL, 1LL> hecto;
typedef ratio<               1000LL, 1LL> kilo;
typedef ratio<            1000000LL, 1LL> mega;
typedef ratio<         1000000000LL, 1LL> giga;
typedef ratio<      1000000000000LL, 1LL> tera;
typedef ratio<   1000000000000000LL, 1LL> peta;
typedef ratio<1000000000000000000LL, 1LL> exa;

/**
 * 执行两个分数的乘法运算，举个例子
 * 5/6 * 24/25
 * 先计算 5 和 25 的最大公约数 5， 6 和 24 的最大公约数 6
 * 那么上面的乘法就可以化简为 1/1 * 4/5
 * 最终的计算结果就是 (1*4) / (1*5)
 */
template <class _R1, class _R2>
struct __ratio_multiply
{
private:
    static const intmax_t __gcd_n1_d2 = __static_gcd<_R1::num, _R2::den>::value;
    static const intmax_t __gcd_d1_n2 = __static_gcd<_R1::den, _R2::num>::value;
public:
    typedef typename ratio
        <
            __ll_mul<_R1::num / __gcd_n1_d2, _R2::num / __gcd_d1_n2>::value,
            __ll_mul<_R2::den / __gcd_n1_d2, _R1::den / __gcd_d1_n2>::value
        >::type type;
};

#ifndef _LIBCPP_CXX03_LANG
template <class _R1, class _R2> using ratio_multiply
                                    = typename __ratio_multiply<_R1, _R2>::type;
#else 
template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_multiply
    : public __ratio_multiply<_R1, _R2>::type {};
#endif

// 出发就是把第二个分数倒过来在执行乘法就可以了
template <class _R1, class _R2>
struct __ratio_divide
{
private:
    static const intmax_t __gcd_n1_n2 = __static_gcd<_R1::num, _R2::num>::value;
    static const intmax_t __gcd_d1_d2 = __static_gcd<_R1::den, _R2::den>::value;
public:
    typedef typename ratio
        <
            __ll_mul<_R1::num / __gcd_n1_n2, _R2::den / __gcd_d1_d2>::value,
            __ll_mul<_R2::num / __gcd_n1_n2, _R1::den / __gcd_d1_d2>::value
        >::type type;
};

#ifndef _LIBCPP_CXX03_LANG

template <class _R1, class _R2> using ratio_divide
                                      = typename __ratio_divide<_R1, _R2>::type;

#else  // _LIBCPP_CXX03_LANG

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_divide
    : public __ratio_divide<_R1, _R2>::type {};

#endif  // _LIBCPP_CXX03_LANG

template <class _R1, class _R2>
struct __ratio_add
{
private:
    static const intmax_t __gcd_n1_n2 = __static_gcd<_R1::num, _R2::num>::value;
    static const intmax_t __gcd_d1_d2 = __static_gcd<_R1::den, _R2::den>::value;
public:
    typedef typename ratio_multiply
        <
            ratio<__gcd_n1_n2, _R1::den / __gcd_d1_d2>,
            ratio
            <
                __ll_add
                <
                    __ll_mul<_R1::num / __gcd_n1_n2, _R2::den / __gcd_d1_d2>::value,
                    __ll_mul<_R2::num / __gcd_n1_n2, _R1::den / __gcd_d1_d2>::value
                >::value,
                _R2::den
            >
        >::type type;
};

#ifndef _LIBCPP_CXX03_LANG

template <class _R1, class _R2> using ratio_add
                                         = typename __ratio_add<_R1, _R2>::type;

#else  // _LIBCPP_CXX03_LANG

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_add
    : public __ratio_add<_R1, _R2>::type {};

#endif  // _LIBCPP_CXX03_LANG

template <class _R1, class _R2>
struct __ratio_subtract
{
private:
    static const intmax_t __gcd_n1_n2 = __static_gcd<_R1::num, _R2::num>::value;
    static const intmax_t __gcd_d1_d2 = __static_gcd<_R1::den, _R2::den>::value;
public:
    typedef typename ratio_multiply
        <
            ratio<__gcd_n1_n2, _R1::den / __gcd_d1_d2>,
            ratio
            <
                __ll_sub
                <
                    __ll_mul<_R1::num / __gcd_n1_n2, _R2::den / __gcd_d1_d2>::value,
                    __ll_mul<_R2::num / __gcd_n1_n2, _R1::den / __gcd_d1_d2>::value
                >::value,
                _R2::den
            >
        >::type type;
};

#ifndef _LIBCPP_CXX03_LANG

template <class _R1, class _R2> using ratio_subtract
                                    = typename __ratio_subtract<_R1, _R2>::type;

#else  // _LIBCPP_CXX03_LANG

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_subtract
    : public __ratio_subtract<_R1, _R2>::type {};

#endif  // _LIBCPP_CXX03_LANG

// ratio_equal

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_equal
    : public _LIBCPP_BOOL_CONSTANT((_R1::num == _R2::num && _R1::den == _R2::den)) {};

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_not_equal
    : public _LIBCPP_BOOL_CONSTANT((!ratio_equal<_R1, _R2>::value)) {};

// ratio_less

template <class _R1, class _R2, bool _Odd = false,
          intmax_t _Q1 = _R1::num / _R1::den, intmax_t _M1 = _R1::num % _R1::den,
          intmax_t _Q2 = _R2::num / _R2::den, intmax_t _M2 = _R2::num % _R2::den>
struct __ratio_less1
{
    static const bool value = _Odd ? _Q2 < _Q1 : _Q1 < _Q2;
};

template <class _R1, class _R2, bool _Odd, intmax_t _Qp>
struct __ratio_less1<_R1, _R2, _Odd, _Qp, 0, _Qp, 0>
{
    static const bool value = false;
};

template <class _R1, class _R2, bool _Odd, intmax_t _Qp, intmax_t _M2>
struct __ratio_less1<_R1, _R2, _Odd, _Qp, 0, _Qp, _M2>
{
    static const bool value = !_Odd;
};

template <class _R1, class _R2, bool _Odd, intmax_t _Qp, intmax_t _M1>
struct __ratio_less1<_R1, _R2, _Odd, _Qp, _M1, _Qp, 0>
{
    static const bool value = _Odd;
};

template <class _R1, class _R2, bool _Odd, intmax_t _Qp, intmax_t _M1,
                                                        intmax_t _M2>
struct __ratio_less1<_R1, _R2, _Odd, _Qp, _M1, _Qp, _M2>
{
    static const bool value = __ratio_less1<ratio<_R1::den, _M1>,
                                            ratio<_R2::den, _M2>, !_Odd>::value;
};

template <class _R1, class _R2, intmax_t _S1 = __static_sign<_R1::num>::value,
                                intmax_t _S2 = __static_sign<_R2::num>::value>
struct __ratio_less
{
    static const bool value = _S1 < _S2;
};

template <class _R1, class _R2>
struct __ratio_less<_R1, _R2, 1LL, 1LL>
{
    static const bool value = __ratio_less1<_R1, _R2>::value;
};

template <class _R1, class _R2>
struct __ratio_less<_R1, _R2, -1LL, -1LL>
{
    static const bool value = __ratio_less1<ratio<-_R2::num, _R2::den>, ratio<-_R1::num, _R1::den> >::value;
};

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_less
    : public _LIBCPP_BOOL_CONSTANT((__ratio_less<_R1, _R2>::value)) {};

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_less_equal
    : public _LIBCPP_BOOL_CONSTANT((!ratio_less<_R2, _R1>::value)) {};

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_greater
    : public _LIBCPP_BOOL_CONSTANT((ratio_less<_R2, _R1>::value)) {};

template <class _R1, class _R2>
struct _LIBCPP_TEMPLATE_VIS ratio_greater_equal
    : public _LIBCPP_BOOL_CONSTANT((!ratio_less<_R1, _R2>::value)) {};

template <class _R1, class _R2>
/**
 * 求两个分数的最小公约数
 */
struct __ratio_gcd
{
    typedef ratio<__static_gcd<_R1::num, _R2::num>::value,
                  __static_lcm<_R1::den, _R2::den>::value> type;
};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _R1, class _R2>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool ratio_equal_v
    = ratio_equal<_R1, _R2>::value;

template <class _R1, class _R2>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool ratio_not_equal_v
    = ratio_not_equal<_R1, _R2>::value;

template <class _R1, class _R2>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool ratio_less_v
    = ratio_less<_R1, _R2>::value;

template <class _R1, class _R2>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool ratio_less_equal_v
    = ratio_less_equal<_R1, _R2>::value;

template <class _R1, class _R2>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool ratio_greater_v
    = ratio_greater<_R1, _R2>::value;

template <class _R1, class _R2>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool ratio_greater_equal_v
    = ratio_greater_equal<_R1, _R2>::value;
#endif



} // end of namespace yjh_def


#endif
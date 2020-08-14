#ifndef _LIBCPP_LIMITS
#define _LIBCPP_LIMITS

#include "__config.cpp"
#include "type_traits.cpp"

#if defined(_LIBCPP_COMPILER_MSVC)          //_MSC_VER
#include "limits_win32.cpp"
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace yjh_def
{

#ifndef __CHAR_BIT__
#define __CHAR_BIT__  8
#endif
/**
std::round_indeterminate 	无法确定舍入风格
std::round_toward_zero 	向零舍入
std::round_to_nearest 	向最近可表示值舍入
std::round_toward_infinity 	向正无穷大舍入
std::round_toward_neg_infinity 	向负无穷大舍入
*/
enum float_round_style
{
    round_indeterminate         = -1,
    round_toward_zero           = 0,
    round_to_nearest            = 1,
    round_toward_infinity       = 2,
    round_toward_neg_infinity   = 3
};

/**
std::denorm_indeterminate 	无法确定是否支持非正规值
std::denorm_absent 	类型不支持非正规值
std::denorm_present 	类型允许非正规值
*/
enum float_denorm_style
{
    denorm_indeterminate = -1,
    denorm_absent = 0,
    denorm_present = 1
};

template <class _Tp, bool = is_arithmetic<_Tp>::value>
class __libcpp_numeric_limits
{
protected:
    typedef _Tp type;

    static const  bool is_specialized = false;	// 查看 _Tp 是否是该类型的特化
    static type min() noexcept {return type();}	//返回给定类型的最小有限值 
    static type max() noexcept {return type();}	
    static type lowest() noexcept {return type();}	//返回给定类型的最低有限值 

    static const int  digits = 0;	//能无更改地表示的 radix 位数 
    static const int  digits10 = 0;	//能无更改地表示的十进制位数 
    static const int  max_digits10 = 0;	//区别所有此类型值所需的十进制位数		
    static const bool is_signed = false;	// 是否是有符号类型
    static const bool is_integer = false;
    static const bool is_exact = false;		//鉴别准确表示的类型 
    static const int  radix = 0;	//给定类型的表示所用的基或整数底
    static type epsilon() noexcept {return type();}		//返回 1.0 与给定类型的下个可表示值的差 
    static type round_error() noexcept {return type();}	//返回给定浮点类型的最大舍入误差

    static const int  min_exponent = 0;	//底的该数次幂是合法正规浮点值的最小负数加一 
    static const int  min_exponent10 = 0;	//10 的该数次幂是合法正规浮点值的最小负数 
    static const int  max_exponent = 0;	//底的该数次幂是合法有限浮点值的最大整数加一 
    static const int  max_exponent10 = 0;	//10 的该数次幂是合法有限浮点值的最大整数 

    static const bool has_infinity = false;		//鉴别能表示特殊值“正无穷大”的浮点类型 
    static const bool has_quiet_NaN = false;	//鉴别能表示特殊值“安静的非数”（ NaN ）的浮点类型 
    static const bool has_signaling_NaN = false;	//鉴别能表示特殊值“发信的非数”（ NaN ）的浮点类型 
    static const float_denorm_style has_denorm = denorm_absent;	//鉴别浮点类型所用的非正规风格
    static const bool has_denorm_loss = false;	//鉴别浮点类型是否检测精度损失为非正规损失，而非不准确结果 
    static type infinity() noexcept {return type();}	//返回给定类型的正无穷大值 
    static type quiet_NaN() noexcept {return type();}	//返回给定浮点类型的安静 NaN 值 
    static type signaling_NaN() noexcept {return type();}	//返回给定浮点类型的发信的 NaN 
    static type denorm_min() noexcept {return type();}	//返回给定浮点类型的最小正非正规值 

    static const bool is_iec559 = false;	// 鉴别 IEC 559/IEEE 754 浮点类型 
    static const bool is_bounded = false;	//鉴别表示有限值集合的类型
    static const bool is_modulo = false;	//鉴别以模算术处理溢出的类型 

    static const bool traps = false;	//鉴别可能导致算术运算出现陷阱的类型 
    static const bool tinyness_before = false;	//鉴别检测舍入前是否非正规的浮点类型 
    static const float_round_style round_style = round_toward_zero;
};

template <class _Tp, int digits, bool is_signed>
struct __libcpp_compute_min
{
	/**
		举个例子，如 int 类型， 二进制位 32 位。最高为 符号位
		那么 int 类型的最小值就是 1 (0x00000001) 进行左移位31位就可以得到 int 类型的最小值 (0x80000000)
	*/
    static const _Tp value = _Tp(_Tp(1) << digits);
};

template <class _Tp, int digits>
struct __libcpp_compute_min<_Tp, digits, false>
{
	/**
		无符号类型的数最小值自然就是 0 
	*/
    static const _Tp value = _Tp(0);
};

/**
* 当 _Tp 数据类型为算术类型的话，使用下面的特化
*/
template <class _Tp>
class __libcpp_numeric_limits<_Tp, true>
{
protected:
    typedef _Tp type;

    static const bool is_specialized = true;	// 这个类是一个局部特化的类

    static const bool is_signed = (type(-1) < type(0));
    static const int  digits = static_cast<int>(sizeof(type) * __CHAR_BIT__ - is_signed); //如果是有符号数，那么其二进制数值不包括最高位符号位
    static const int  digits10 = digits * 3 / 10;	// 这个原理是什么？
    static const int  max_digits10 = 0;
    static const type __min = __libcpp_compute_min<type, digits, is_signed>::value;  // 得到 _Tp 数据类型的最小值
    static const type __max = is_signed ? type(type(~0) ^ __min) : type(~0);	// ^ 异或运算符
    static type min() noexcept {return __min;}
    static type max() noexcept {return __max;}
    static type lowest() noexcept {return min();}	// 和 min() 返回的结果是一样的

    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int  radix = 2;		// 2 进制
    static type epsilon() noexcept {return type(0);}	// 返回 1.0 和指定的类型 和 1.0 最接近的值的差值  epsilon 是 1.0 + epsilon != 1.0 的最小数值
    static type round_error() noexcept {return type(0);}

    static const int  min_exponent = 0;
    static const int  min_exponent10 = 0;
    static const int  max_exponent = 0;
    static const int  max_exponent10 = 0;

    static const bool has_infinity = false;
    static const bool has_quiet_NaN = false;
    static const bool has_signaling_NaN = false;
    static const float_denorm_style has_denorm = denorm_absent;   // 不支持非正规值
    static const bool has_denorm_loss = false;
    static type infinity() noexcept {return type(0);}
    static type quiet_NaN() noexcept {return type(0);}
    static type signaling_NaN() noexcept {return type(0);}
    static type denorm_min() noexcept {return type(0);}

    static const bool is_iec559 = false;
    static const bool is_bounded = true;
    static const bool is_modulo = true;

#if __i386__ || __x86_64__
    static const bool traps = true;
#else
    static const bool traps = false;
#endif
    static const bool tinyness_before = false;
    static const float_round_style round_style = round_toward_zero;  // 向零舍入
};

template <>
/**
 * 对 bool 类型的数值进行的类模板的特化
*/
class __libcpp_numeric_limits<bool, true>
{
protected:
    typedef bool type;

    static const bool is_specialized = true;

    static const bool is_signed = false;
    static const int  digits = 1;
    static const int  digits10 = 0;
    static const int  max_digits10 = 0;
    static const type __min = false;
    static const type __max = true;
    static type min() {return __min;}
    static type max() {return __max;}
    static type lowest() {return min();}

    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int  radix = 2;
    static type epsilon() {return type(0);}
    static type round_error() {return type(0);}

    static const int  min_exponent = 0;
    static const int  min_exponent10 = 0;
    static const int  max_exponent = 0;
    static const int  max_exponent10 = 0;

    static const bool has_infinity = false;
    static const bool has_quiet_NaN = false;
    static const bool has_signaling_NaN = false;
    static const float_denorm_style has_denorm = denorm_absent;
    static const bool has_denorm_loss = false;
    static type infinity() {return type(0);}
    static type quiet_NaN() {return type(0);}
    static type signaling_NaN() {return type(0);}
    static type denorm_min() {return type(0);}

    static const bool is_iec559 = false;
    static const bool is_bounded = true;
    static const bool is_modulo = false;

    static const bool traps = false;
    static const bool tinyness_before = false;
    static const float_round_style round_style = round_toward_zero;
};

template <>
class __libcpp_numeric_limits<float, true>
{
protected:
    typedef float type;

    static const bool is_specialized = true;

    static const bool is_signed = true;
    static const int  digits = __FLT_MANT_DIG__;
    static const int  digits10 = __FLT_DIG__;
    static const int  max_digits10 = 2+(digits * 30103)/100000;
    static type min() {return __FLT_MIN__;}
    static type max() {return __FLT_MAX__;}
    static type lowest() {return -max();}

    static const bool is_integer = false;
    static const bool is_exact = false;
    static const int  radix = __FLT_RADIX__;
    static type epsilon() {return __FLT_EPSILON__;}
    static type round_error() {return 0.5F;}

    static const int  min_exponent = __FLT_MIN_EXP__;
    static const int  min_exponent10 = __FLT_MIN_10_EXP__;
    static const int  max_exponent = __FLT_MAX_EXP__;
    static const int  max_exponent10 = __FLT_MAX_10_EXP__;

    static const bool has_infinity = true;
    static const bool has_quiet_NaN = true;
    static const bool has_signaling_NaN = true;
    static const float_denorm_style has_denorm = denorm_present;
    static const bool has_denorm_loss = false;
    static type infinity() {return __builtin_huge_valf();}
    static type quiet_NaN() {return __builtin_nanf("");}
    static type signaling_NaN() {return __builtin_nansf("");}
    static type denorm_min() {return __FLT_DENORM_MIN__;}

    static const bool is_iec559 = true;
    static const bool is_bounded = true;
    static const bool is_modulo = false;

    static const bool traps = false;
    static const bool tinyness_before = false;
    static const float_round_style round_style = round_to_nearest;
};

template <>
class __libcpp_numeric_limits<double, true>
{
protected:
    typedef double type;

    static const bool is_specialized = true;

    static const bool is_signed = true;
    static const int  digits = __DBL_MANT_DIG__;
    static const int  digits10 = __DBL_DIG__;
    static const int  max_digits10 = 2+(digits * 30103)/100000;
    static type min() {return __DBL_MIN__;}
    static type max() {return __DBL_MAX__;}
    static type lowest() {return -max();}

    static const bool is_integer = false;
    static const bool is_exact = false;
    static const int  radix = __FLT_RADIX__;
    static type epsilon() {return __DBL_EPSILON__;}
    static type round_error() {return 0.5;}

    static const int  min_exponent = __DBL_MIN_EXP__;
    static const int  min_exponent10 = __DBL_MIN_10_EXP__;
    static const int  max_exponent = __DBL_MAX_EXP__;
    static const int  max_exponent10 = __DBL_MAX_10_EXP__;

    static const bool has_infinity = true;
    static const bool has_quiet_NaN = true;
    static const bool has_signaling_NaN = true;
    static const float_denorm_style has_denorm = denorm_present;
    static const bool has_denorm_loss = false;
    static type infinity() {return __builtin_huge_val();}
    static type quiet_NaN() {return __builtin_nan("");}
    static type signaling_NaN() {return __builtin_nans("");}
    static type denorm_min() {return __DBL_DENORM_MIN__;}

    static const bool is_iec559 = true;
    static const bool is_bounded = true;
    static const bool is_modulo = false;

    static const bool traps = false;
    static const bool tinyness_before = false;
    static const float_round_style round_style = round_to_nearest;
};

template <>
class __libcpp_numeric_limits<long double, true>
{
protected:
    typedef long double type;

    static const bool is_specialized = true;

    static const bool is_signed = true;
    static const int  digits = __LDBL_MANT_DIG__;
    static const int  digits10 = __LDBL_DIG__;
    static const int  max_digits10 = 2+(digits * 30103)/100000;
    static type min() {return __LDBL_MIN__;}
    static type max() {return __LDBL_MAX__;}
    static type lowest() {return -max();}

    static const bool is_integer = false;
    static const bool is_exact = false;
    static const int  radix = __FLT_RADIX__;
    static type epsilon() {return __LDBL_EPSILON__;}
    static type round_error() {return 0.5;}

    static const int  min_exponent = __LDBL_MIN_EXP__;
    static const int  min_exponent10 = __LDBL_MIN_10_EXP__;
    static const int  max_exponent = __LDBL_MAX_EXP__;
    static const int  max_exponent10 = __LDBL_MAX_10_EXP__;

    static const bool has_infinity = true;
    static const bool has_quiet_NaN = true;
    static const bool has_signaling_NaN = true;
    static const float_denorm_style has_denorm = denorm_present;
    static const bool has_denorm_loss = false;
    static type infinity() {return __builtin_huge_vall();}
    static type quiet_NaN() {return __builtin_nanl("");}
    static type signaling_NaN() {return __builtin_nansl("");}
    static type denorm_min() {return __LDBL_DENORM_MIN__;}

#if (defined(__ppc__) || defined(__ppc64__))
    static const bool is_iec559 = false;
#else
    static const bool is_iec559 = true;
#endif
    static const bool is_bounded = true;
    static const bool is_modulo = false;

    static const bool traps = false;
    static const bool tinyness_before = false;
    static const float_round_style round_style = round_to_nearest;
};

template <class _Tp>
class numeric_limits
    : private __libcpp_numeric_limits<typename remove_cv<_Tp>::type>
{
    typedef __libcpp_numeric_limits<typename remove_cv<_Tp>::type> __base;
    typedef typename __base::type type;
public:
    static const bool is_specialized = __base::is_specialized;
    static type min() noexcept      {return __base::min();}
    static type max() noexcept      {return __base::max();}
    static type lowest() noexcept   {return __base::lowest();}

	static const int	digits = __base::digits;
	static const int	digits10 = __base::digits10;
	static const int	max_digits10 = __base::max_digits10;
	static const bool	is_signed = __base::is_signed;
	static const bool	is_integer = __base::is_integer;
	static const bool	is_exact = __base::is_exact;
	static const int	radix = __base::radix;
	static type epsilon()		noexcept { return __base::epsilon(); }
	static type round_error()	noexcept { return __base::round_error(); }

	static const int min_exponent = __base::min_exponent;
	static const int min_exponent10 = __base::min_exponent10;
	static const int max_exponent = __base::max_exponent;
	static const int max_exponent10 = __base::max_exponent10;

	static const bool has_infinity = __base::has_infinity;
	static const bool has_quiet_NaN = __base::has_quiet_NaN;
	static const bool has_signaling_NaN = __base::has_signaling_NaN;
	static const float_denorm_style has_denorm = __base::has_denorm;
	static const bool has_denorm_loss = __base::has_denorm_loss;

	static type infinity() noexcept { return __base::infinity(); }
	static type quiet_NaN() noexcept { return __base::quiet_NaN(); }
	static type signaling_NaN() noexcept { return __base::signaling_NaN(); }
	static type denorm_min() noexcept { return __base::denorm_min(); }

	static const bool is_iec559 = __base::is_iec559;
	static const bool is_bounded = __base::is_bounded;
	static const bool is_modulo = __base::is_modulo;

	static const bool traps = __base::traps;
	static const bool tinyness_before = __base::tinyness_before;
	static const float_round_style round_style = __base::round_style;
};

template <class _Tp>
const bool numeric_limits<_Tp>::is_specialized;

template <class _Tp>
const int numeric_limits<_Tp>::digits;

template <class _Tp>
const int numeric_limits<_Tp>::digits10;

template <class _Tp>
const int numeric_limits<_Tp>::max_digits10;

template <class _Tp>
const bool numeric_limits<_Tp>::is_signed;

template <class _Tp>
const bool numeric_limits<_Tp>::is_integer;

template <class _Tp>
const bool numeric_limits<_Tp>::is_exact;

template <class _Tp>
const int numeric_limits<_Tp>::radix;

template <class _Tp>
const int numeric_limits<_Tp>::min_exponent;

template <class _Tp>
const int numeric_limits<_Tp>::min_exponent10;

template <class _Tp>
const int numeric_limits<_Tp>::max_exponent;

template <class _Tp>
const int numeric_limits<_Tp>::max_exponent10;

template <class _Tp>
const bool numeric_limits<_Tp>::has_infinity;

template <class _Tp>
const bool numeric_limits<_Tp>::has_quiet_NaN;

template <class _Tp>
const bool numeric_limits<_Tp>::has_signaling_NaN;

template <class _Tp>
const float_denorm_style numeric_limits<_Tp>::has_denorm;

template <class _Tp>
const bool numeric_limits<_Tp>::has_denorm_loss;

template <class _Tp>
const bool numeric_limits<_Tp>::is_modulo;

template <class _Tp>
const bool numeric_limits<_Tp>::is_iec559;

template <class _Tp>
const bool numeric_limits<_Tp>::is_bounded;

template <class _Tp>
const bool numeric_limits<_Tp>::traps;

template <class _Tp>
const bool numeric_limits<_Tp>::tinyness_before;

template <class _Tp>
const float_round_style numeric_limits<_Tp>::round_style;

template <class _Tp>
class numeric_limits<const _Tp>
	: private numeric_limits<_Tp>
{
	typedef numeric_limits<_Tp> __base;
	typedef _Tp type;
public:
	static const bool is_specialized = __base::is_specialized;
	static type min() noexcept { return __base::min(); }
	static type max() noexcept { return __base::max(); }
	static type lowest() noexcept { return __base::lowest(); }

	static const int	digits = __base::digits;
	static const int	digits10 = __base::digits10;
	static const int	max_digits10 = __base::max_digits10;
	static const bool	is_signed = __base::is_signed;
	static const bool	is_integer = __base::is_integer;
	static const bool	is_exact = __base::is_exact;
	static const int	radix = __base::radix;
	static type epsilon()		noexcept { return __base::epsilon(); }
	static type round_error()	noexcept { return __base::round_error(); }

	static const int min_exponent = __base::min_exponent;
	static const int min_exponent10 = __base::min_exponent10;
	static const int max_exponent = __base::max_exponent;
	static const int max_exponent10 = __base::max_exponent10;

	static const bool has_infinity = __base::has_infinity;
	static const bool has_quiet_NaN = __base::has_quiet_NaN;
	static const bool has_signaling_NaN = __base::has_signaling_NaN;
	static const float_denorm_style has_denorm = __base::has_denorm;
	static const bool has_denorm_loss = __base::has_denorm_loss;

	static type infinity() noexcept { return __base::infinity(); }
	static type quiet_NaN() noexcept { return __base::quiet_NaN(); }
	static type signaling_NaN() noexcept { return __base::signaling_NaN(); }
	static type denorm_min() noexcept { return __base::denorm_min(); }

	static const bool is_iec559 = __base::is_iec559;
	static const bool is_bounded = __base::is_bounded;
	static const bool is_modulo = __base::is_modulo;

	static const bool traps = __base::traps;
	static const bool tinyness_before = __base::tinyness_before;
	static const float_round_style round_style = __base::round_style;
};

template <class _Tp>
const bool numeric_limits<const _Tp>::is_specialized;

template <class _Tp>
const int numeric_limits<const _Tp>::digits;

template <class _Tp>
const int numeric_limits<const _Tp>::digits10;

template <class _Tp>
const int numeric_limits<const _Tp>::max_digits10;

template <class _Tp>
const bool numeric_limits<const _Tp>::is_signed;

template <class _Tp>
const bool numeric_limits<const _Tp>::is_integer;

template <class _Tp>
const bool numeric_limits<const _Tp>::is_exact;

template <class _Tp>
const int numeric_limits<const _Tp>::radix;

template <class _Tp>
const int numeric_limits<const _Tp>::min_exponent;

template <class _Tp>
const int numeric_limits<const _Tp>::min_exponent10;

template <class _Tp>
const int numeric_limits<const _Tp>::max_exponent;

template <class _Tp>
const int numeric_limits<const _Tp>::max_exponent10;

template <class _Tp>
const bool numeric_limits<const _Tp>::has_infinity;

template <class _Tp>
const bool numeric_limits<const _Tp>::has_quiet_NaN;

template <class _Tp>
const bool numeric_limits<const _Tp>::has_signaling_NaN;

template <class _Tp>
const float_denorm_style numeric_limits<const _Tp>::has_denorm;

template <class _Tp>
const bool numeric_limits<const _Tp>::has_denorm_loss;

template <class _Tp>
const bool numeric_limits<const _Tp>::is_modulo;

template <class _Tp>
const bool numeric_limits<const _Tp>::is_iec559;

template <class _Tp>
const bool numeric_limits<const _Tp>::is_bounded;

template <class _Tp>
const bool numeric_limits<const _Tp>::traps;

template <class _Tp>
const bool numeric_limits<const _Tp>::tinyness_before;

template <class _Tp>
const float_round_style numeric_limits<const _Tp>::round_style;


template <class _Tp>
class numeric_limits<volatile _Tp>
	: private numeric_limits<_Tp>
{
	typedef numeric_limits<_Tp> __base;
	typedef _Tp type;
public:
	static const bool is_specialized = __base::is_specialized;
	static type min() noexcept { return __base::min(); }
	static type max() noexcept { return __base::max(); }
	static type lowest() noexcept { return __base::lowest(); }

	static const int	digits = __base::digits;
	static const int	digits10 = __base::digits10;
	static const int	max_digits10 = __base::max_digits10;
	static const bool	is_signed = __base::is_signed;
	static const bool	is_integer = __base::is_integer;
	static const bool	is_exact = __base::is_exact;
	static const int	radix = __base::radix;
	static type epsilon()		noexcept { return __base::epsilon(); }
	static type round_error()	noexcept { return __base::round_error(); }

	static const int min_exponent = __base::min_exponent;
	static const int min_exponent10 = __base::min_exponent10;
	static const int max_exponent = __base::max_exponent;
	static const int max_exponent10 = __base::max_exponent10;

	static const bool has_infinity = __base::has_infinity;
	static const bool has_quiet_NaN = __base::has_quiet_NaN;
	static const bool has_signaling_NaN = __base::has_signaling_NaN;
	static const float_denorm_style has_denorm = __base::has_denorm;
	static const bool has_denorm_loss = __base::has_denorm_loss;

	static type infinity() noexcept { return __base::infinity(); }
	static type quiet_NaN() noexcept { return __base::quiet_NaN(); }
	static type signaling_NaN() noexcept { return __base::signaling_NaN(); }
	static type denorm_min() noexcept { return __base::denorm_min(); }

	static const bool is_iec559 = __base::is_iec559;
	static const bool is_bounded = __base::is_bounded;
	static const bool is_modulo = __base::is_modulo;

	static const bool traps = __base::traps;
	static const bool tinyness_before = __base::tinyness_before;
	static const float_round_style round_style = __base::round_style;
};

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_specialized;

template <class _Tp>
const int numeric_limits<volatile _Tp>::digits;

template <class _Tp>
const int numeric_limits<volatile _Tp>::digits10;

template <class _Tp>
const int numeric_limits<volatile _Tp>::max_digits10;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_signed;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_integer;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_exact;

template <class _Tp>
const int numeric_limits<volatile _Tp>::radix;

template <class _Tp>
const int numeric_limits<volatile _Tp>::min_exponent;

template <class _Tp>
const int numeric_limits<volatile _Tp>::min_exponent10;

template <class _Tp>
const int numeric_limits<volatile _Tp>::max_exponent;

template <class _Tp>
const int numeric_limits<volatile _Tp>::max_exponent10;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::has_infinity;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::has_quiet_NaN;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::has_signaling_NaN;

template <class _Tp>
const float_denorm_style numeric_limits<volatile _Tp>::has_denorm;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::has_denorm_loss;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_modulo;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_iec559;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::is_bounded;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::traps;

template <class _Tp>
const bool numeric_limits<volatile _Tp>::tinyness_before;

template <class _Tp>
const float_round_style numeric_limits<volatile _Tp>::round_style;


template <class _Tp>
class numeric_limits<const volatile _Tp>
	: private numeric_limits<_Tp>
{
	typedef numeric_limits<_Tp> __base;
	typedef _Tp type;
public:
	static const bool is_specialized = __base::is_specialized;
	static type min() noexcept { return __base::min(); }
	static type max() noexcept { return __base::max(); }
	static type lowest() noexcept { return __base::lowest(); }

	static const int	digits = __base::digits;
	static const int	digits10 = __base::digits10;
	static const int	max_digits10 = __base::max_digits10;
	static const bool	is_signed = __base::is_signed;
	static const bool	is_integer = __base::is_integer;
	static const bool	is_exact = __base::is_exact;
	static const int	radix = __base::radix;
	static type epsilon()		noexcept { return __base::epsilon(); }
	static type round_error()	noexcept { return __base::round_error(); }

	static const int min_exponent = __base::min_exponent;
	static const int min_exponent10 = __base::min_exponent10;
	static const int max_exponent = __base::max_exponent;
	static const int max_exponent10 = __base::max_exponent10;

	static const bool has_infinity = __base::has_infinity;
	static const bool has_quiet_NaN = __base::has_quiet_NaN;
	static const bool has_signaling_NaN = __base::has_signaling_NaN;
	static const float_denorm_style has_denorm = __base::has_denorm;
	static const bool has_denorm_loss = __base::has_denorm_loss;

	static type infinity() noexcept { return __base::infinity(); }
	static type quiet_NaN() noexcept { return __base::quiet_NaN(); }
	static type signaling_NaN() noexcept { return __base::signaling_NaN(); }
	static type denorm_min() noexcept { return __base::denorm_min(); }

	static const bool is_iec559 = __base::is_iec559;
	static const bool is_bounded = __base::is_bounded;
	static const bool is_modulo = __base::is_modulo;

	static const bool traps = __base::traps;
	static const bool tinyness_before = __base::tinyness_before;
	static const float_round_style round_style = __base::round_style;
};

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_specialized;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::digits;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::digits10;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::max_digits10;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_signed;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_integer;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_exact;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::radix;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::min_exponent;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::min_exponent10;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::max_exponent;

template <class _Tp>
const int numeric_limits<const volatile _Tp>::max_exponent10;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::has_infinity;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::has_quiet_NaN;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::has_signaling_NaN;

template <class _Tp>
const float_denorm_style numeric_limits<const volatile _Tp>::has_denorm;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::has_denorm_loss;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_modulo;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_iec559;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::is_bounded;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::traps;

template <class _Tp>
const bool numeric_limits<const volatile _Tp>::tinyness_before;

template <class _Tp>
const float_round_style numeric_limits<const volatile _Tp>::round_style;

}
#endif
#ifndef _LIBCPP_BIT
#define _LIBCPP_BIT


#include "__config.cpp"
#include "limits.cpp"
#include "type_traits.cpp"


#if defined(__IBMCPP__)
#include "some_header_file"
#endif

#if defined(_LIBCPP_COMPILER_MSVC)
#include <intrin.h>
#endif

_LIBCPP_PUSH_MACROS // 将 min 和 max 的定义压入栈中
// 然后在 undef min 和 max ,这样方便我们定义自己的 min 和 max 
// 在使用完自己定义的 min 和 max 之后，再使用 pop macros 恢复栈中的 min 和 max 定义
#include "__undef_macros.cpp"

namespace yjh_def
{
#ifndef _LIBCPP_COMPILER_MSVC   // 不是使用 mscv 编译器进行编译程序

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_ctz(unsigned __x)              _NOEXCEPT { return __builtin_ctz(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_ctz(unsigned long __x)      _NOEXCEPT { return __builtin_ctzl(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_ctz(unsigned long long __x) _NOEXCEPT { return __builtin_ctzll(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_clz(unsigned __x)           _NOEXCEPT { return __builtin_clz(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_clz(unsigned long __x)      _NOEXCEPT { return __builtin_clzl(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_clz(unsigned long long __x) _NOEXCEPT { return __builtin_clzll(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_popcount(unsigned __x)           _NOEXCEPT { return __builtin_popcount(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_popcount(unsigned long __x)      _NOEXCEPT { return __builtin_popcountl(__x); }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __libcpp_popcount(unsigned long long __x) _NOEXCEPT { return __builtin_popcountll(__x); }

#else

// 使用这些函数的前提条件是 __x!= 0
// 即要保证 __x 的二进制中至少有一个 1
// ctz : 判断整数数值的尾部有多少个后缀零
// clz : 判断整数数值的头部有多少个前缀零
inline _LIBCPP_INLINE_VISIBILITY
int __libcpp_ctz(unsigned __x)
{
	static_assert(sizeof(unsigned) == sizeof(unsigned long), "");
	static_assert(sizeof(unsigned long) == 4, "");
	unsigned long __where;
	if(_BitScanForward(&__where, __x))      // from <intrin.h>
		return static_cast<int>(__where);
	return 32;
}

inline _LIBCPP_INLINE_VISIBILITY
int __libcpp_ctz(unsigned long __x) {
	static_assert(sizeof(unsigned long) == sizeof(unsigned), "");
	return __libcpp_ctz(static_cast<unsigned>(__x));
}

inline _LIBCPP_INLINE_VISIBILITY
int __libcpp_ctz(unsigned long long __x)
{
	unsigned long __where;
	#if defined(_LIBCPP_HAS_BITSCAN64) && (defined(_M_AMD64) || defined(__x86_64__))
		if(_BitScanForward64(&__where, __x))
			return static_cast<int>(__where);
	#else
		/**
		 * 在 32 位机器上，没有方法可以一次判断 64 为的数值的尾部有多少个 0
		 * 所以先判断 低 32 位尾部有多少个0；如果低 32 位全部都是 0 就把高 32 位
		 * 移动到低 32 位的位置再做判断
		 */
		if(_BitScanForward(&__where, static_cast<unsigned long>(__x)))
			return static_cast<int>(__where);
		if(_BitScanForward(&__where, static_cast<unsigned long>(__x >> 32)))
			return static_cast<int>(__where + 32);
	#endif
	return 64;
}

inline _LIBCPP_INLINE_VISIBILITY
int __libcpp_clz(unsigned __x) {
  static_assert(sizeof(unsigned) == sizeof(unsigned long), "");
  static_assert(sizeof(unsigned long) == 4, "");
  unsigned long __where;
  if (_BitScanReverse(&__where, __x))
	return static_cast<int>(31 - __where);
  return 32; // Undefined Behavior.
}

inline _LIBCPP_INLINE_VISIBILITY
int __libcpp_clz(unsigned long __x) {
	static_assert(sizeof(unsigned) == sizeof(unsigned long), "");
	return __libcpp_clz(static_cast<unsigned>(__x));
}

inline _LIBCPP_INLINE_VISIBILITY
int __libcpp_clz(unsigned long long __x) {
  unsigned long __where;
#if defined(_LIBCPP_HAS_BITSCAN64)
  if (_BitScanReverse64(&__where, __x))
	return static_cast<int>(63 - __where);
#else
  // Win32 doesn't have _BitScanReverse64 so emulate it with two 32 bit calls.
  if (_BitScanReverse(&__where, static_cast<unsigned long>(__x >> 32)))
	return static_cast<int>(63 - (__where + 32));
  if (_BitScanReverse(&__where, static_cast<unsigned long>(__x)))
	return static_cast<int>(63 - __where);
#endif
  return 64; // Undefined Behavior.
}

// 整数数值中的 1 的个数
inline _LIBCPP_INLINE_VISIBILITY 
int __libcpp_popcount(unsigned __x) {
  static_assert(sizeof(unsigned) == 4, "");
  return __popcnt(__x);
}

inline _LIBCPP_INLINE_VISIBILITY int __libcpp_popcount(unsigned long __x) {
  	static_assert(sizeof(unsigned long) == 4, "");
  	return __popcnt(__x);
}

inline _LIBCPP_INLINE_VISIBILITY int __libcpp_popcount(unsigned long long __x) {
  	static_assert(sizeof(unsigned long long) == 8, "");
  	return __popcnt64(__x);
}
#endif

template <class _Tp>
using __bitop_unsigned_integer _LIBCPP_NODEBUG_TYPE = integral_constant<bool,
		is_integral<_Tp>::value &&
		is_unsigned<_Tp>::value &&
		_IsNotSame<typename remove_cv<_Tp>::type, bool>::value &&
		_IsNotSame<typename remove_cv<_Tp>::type, signed char>::value &&
		_IsNotSame<typename remove_cv<_Tp>::type, wchar_t>::value &&
		_IsNotSame<typename remove_cv<_Tp>::type, char16_t>::value &&
		_IsNotSame<typename remove_cv<_Tp>::type, char32_t>::value
		>;

/**
 * 绕某一个轴进行旋转
 */
template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp __rotl(_Tp __t, unsigned int __cnt) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__rotl requires unsigned");
	const unsigned int __dig = numeric_limits<_Tp>::digits;
    if ((__cnt % __dig) == 0)
        return __t;
    return (__t << (__cnt % __dig)) | (__t >> (__dig - (__cnt % __dig)));
}

template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp __rotr(_Tp __t, unsigned int __cnt) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__rotr requires unsigned");
    const unsigned int __dig = numeric_limits<_Tp>::digits;
    if ((__cnt % __dig) == 0)
        return __t;
    return (__t >> (__cnt % __dig)) | (__t << (__dig - (__cnt % __dig)));
}

template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
int __countr_zero(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__countr_zero requires unsigned");
    if (__t == 0)
        return numeric_limits<_Tp>::digits;

    if      (sizeof(_Tp) <= sizeof(unsigned int))
        return __libcpp_ctz(static_cast<unsigned int>(__t));
    else if (sizeof(_Tp) <= sizeof(unsigned long))
        return __libcpp_ctz(static_cast<unsigned long>(__t));
    else if (sizeof(_Tp) <= sizeof(unsigned long long))
        return __libcpp_ctz(static_cast<unsigned long long>(__t));
    else
    {
        int __ret = 0;
        int __iter = 0;
        const unsigned int __ulldigits = numeric_limits<unsigned long long>::digits;
        while ((__iter = __libcpp_ctz(static_cast<unsigned long long>(__t))) == __ulldigits)
        {
            __ret += __iter;
            __t >>= __ulldigits;
        }
        return __ret + __iter;
    }
}

template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
int __countl_zero(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__countl_zero requires unsigned");
    if (__t == 0)
        return numeric_limits<_Tp>::digits;

    if      (sizeof(_Tp) <= sizeof(unsigned int))
        return __libcpp_clz(static_cast<unsigned int>(__t))
              - (numeric_limits<unsigned int>::digits - numeric_limits<_Tp>::digits);
    else if (sizeof(_Tp) <= sizeof(unsigned long))
        return __libcpp_clz(static_cast<unsigned long>(__t))
              - (numeric_limits<unsigned long>::digits - numeric_limits<_Tp>::digits);
    else if (sizeof(_Tp) <= sizeof(unsigned long long))
        return __libcpp_clz(static_cast<unsigned long long>(__t))
              - (numeric_limits<unsigned long long>::digits - numeric_limits<_Tp>::digits);
    else
    {
        int __ret = 0;
        int __iter = 0;
        const unsigned int __ulldigits = numeric_limits<unsigned long long>::digits;
        while (true) {
            __t = __rotr(__t, __ulldigits);
            if ((__iter = __countl_zero(static_cast<unsigned long long>(__t))) != __ulldigits)
                break;
            __ret += __iter;
            }
        return __ret + __iter;
    }
}

template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
int __countl_one(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__countl_one requires unsigned");
    return __t != numeric_limits<_Tp>::max()
        ? __countl_zero(static_cast<_Tp>(~__t))
        : numeric_limits<_Tp>::digits;
}


template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
int __countr_one(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__countr_one requires unsigned");
    return __t != numeric_limits<_Tp>::max()
        ? __countr_zero(static_cast<_Tp>(~__t))
        : numeric_limits<_Tp>::digits;
}


template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
int
__popcount(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__libcpp_popcount requires unsigned");
    if      (sizeof(_Tp) <= sizeof(unsigned int))
        return __libcpp_popcount(static_cast<unsigned int>(__t));
    else if (sizeof(_Tp) <= sizeof(unsigned long))
        return __libcpp_popcount(static_cast<unsigned long>(__t));
    else if (sizeof(_Tp) <= sizeof(unsigned long long))
        return __libcpp_popcount(static_cast<unsigned long long>(__t));
    else
    {
        int __ret = 0;
        while (__t != 0)
        {
            __ret += __libcpp_popcount(static_cast<unsigned long long>(__t));
            __t >>= numeric_limits<unsigned long long>::digits;
        }
        return __ret;
    }
}


// integral log base 2
template<class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
unsigned __bit_log2(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__bit_log2 requires unsigned");
    return std::numeric_limits<_Tp>::digits - 1 - __countl_zero(__t);
}

template <class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
/**
 * 如果一个数是二的指数，那么整个数的二进制当中只会有一个 1 
 * 这个数减去 1 之后，当前1 的位置一定会变成 0。
 */
bool __ispow2(_Tp __t) _NOEXCEPT
{
    static_assert(__bitop_unsigned_integer<_Tp>::value, "__ispow2 requires unsigned");
	return __t != 0 && (((__t & (__t - 1)) == 0)); 
}

}   // namespace yjh_def



#endif
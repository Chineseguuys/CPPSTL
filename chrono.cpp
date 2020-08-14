#ifndef _LIBCPP_CHRONO
#define _LIBCPP_CHRONO

#include "__config.cpp"
#include "ctime.cpp"
#include "type_traits.cpp"
#include "ratio.cpp"
#include "limits.cpp"


#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"

#ifndef _LIBCPP_CXX03_LANG
namespace filesystem
{
struct _FilesystemClock;
}
#endif

namespace yjh_def
{
namespace chrono
{

template <class _Rep, class _Period = ratio<1> > class _LIBCPP_TEMPLATE_VIS duration;

template <class _Tp>
struct __is_duration : false_type {};

template <class _Rep, class _Period>
struct __is_duration<duration<_Rep, _Period> > : true_type  {};

template <class _Rep, class _Period>
struct __is_duration<const duration<_Rep, _Period> > : true_type  {};

template <class _Rep, class _Period>
struct __is_duration<volatile duration<_Rep, _Period> > : true_type  {};

template <class _Rep, class _Period>
struct __is_duration<const volatile duration<_Rep, _Period> > : true_type  {};

} // namespace chrono

// type_traits.cpp 中的 common_type<_T1, _T2> 的特化
template <class _Rep1, class _Period1, class _Rep2, class _Period2>
struct _LIBCPP_TEMPLATE_VIS common_type<chrono::duration<_Rep1, _Period1>,
                                         chrono::duration<_Rep2, _Period2> >
{
    /**
     * 输入两个 duration 对象，它们各自的一个计数的时间间隔 preoid 不相同，common_type 返回的 
     * duration 的计数时间间隔取值他们两个的时间间隔的最小公约数
     * e.g
     * period1 = 3/4  period2 = 1/6  那么新的 period = 1/12
     */
    typedef chrono::duration<typename common_type<_Rep1, _Rep2>::type,
                             typename __ratio_gcd<_Period1, _Period2>::type> type;
};

namespace chrono
{
// duration_cast
template <class _FromDuration, class _ToDuration,
          class _Period = typename ratio_divide<typename _FromDuration::period, typename _ToDuration::period>::type,
          bool = _Period::num == 1,
          bool = _Period::den == 1>
/**
 * _Preiod::num = 1 说明了 _ToDuration::period 是 _FromDuration::preiod 的整数倍
 * 反之， _FromDuration::preiod 是 _ToDuration::period 的整数倍
 * 两个都等于 1 说明了这两者相等
 */
struct __duration_cast;

template <class _FromDuration, class _ToDuration, class _Period>
struct __duration_cast<_FromDuration, _ToDuration, _Period, true, true>
/**
 * _FromDuration的每次计数的时间间隔 和 _ToDuration 的是相等的
 */
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    _ToDuration operator()(const _FromDuration& __fd) const
    {
        return _ToDuration(static_cast<typename _ToDuration::rep>(__fd.count()));
    }
};

template <class _FromDuration, class _ToDuration, class _Period>
/**
 * _Toduration的每次计数的时间间隔 是 _FromDuration 的整数倍  _Period::den 的值代表了倍数
 * 因此为了两个 Dutation 中的数据代表了相同的时间长度，所以 _ToDuration 的计数个数是 _FromDuration 
 * 的 1/ _Period::den
 */
struct __duration_cast<_FromDuration, _ToDuration, _Period, true, false>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    _ToDuration operator()(const _FromDuration& __fd) const
    {
        typedef typename common_type<typename _ToDuration::rep, typename _FromDuration::rep, intmax_t>::type _Ct;
        return _ToDuration(static_cast<typename _ToDuration::rep>(
                           static_cast<_Ct>(__fd.count()) / static_cast<_Ct>(_Period::den)));
    }
};

template <class _FromDuration, class _ToDuration, class _Period>
struct __duration_cast<_FromDuration, _ToDuration, _Period, false, true>
/**
 * _FromDuration 的每次计数的时间间隔 是 _ToDuration 的整数倍  _Period::num 的值代表了倍数
 * 因此为了两个 Dutation 代表相同的时间长度，所以 _ToDuration 的计数个数是 _FromDuration 
 * 的 _Period::num 倍
 */
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    _ToDuration operator()(const _FromDuration& __fd) const
    {
        typedef typename common_type<typename _ToDuration::rep, typename _FromDuration::rep, intmax_t>::type _Ct;
        return _ToDuration(static_cast<typename _ToDuration::rep>(
                           static_cast<_Ct>(__fd.count()) * static_cast<_Ct>(_Period::num)));
    }
};

template <class _FromDuration, class _ToDuration, class _Period>
struct __duration_cast<_FromDuration, _ToDuration, _Period, false, false>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    _ToDuration operator()(const _FromDuration& __fd) const
    {
        typedef typename common_type<typename _ToDuration::rep, typename _FromDuration::rep, intmax_t>::type _Ct;
        return _ToDuration(static_cast<typename _ToDuration::rep>(
                           static_cast<_Ct>(__fd.count()) * static_cast<_Ct>(_Period::num)
                                                          / static_cast<_Ct>(_Period::den)));
    }
};

template <class _ToDuration, class _Rep, class _Period>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename enable_if
<
    __is_duration<_ToDuration>::value,
    _ToDuration
>::type
duration_cast(const duration<_Rep, _Period>& __fd)
{
    return __duration_cast<duration<_Rep, _Period>, _ToDuration>()(__fd);
}

template <class _Rep>
struct _LIBCPP_TEMPLATE_VIS treat_as_floating_point : is_floating_point<_Rep> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Rep>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool treat_as_floating_point_v
    = treat_as_floating_point<_Rep>::value;
#endif

// duration_values
template <class _Rep>
struct _LIBCPP_TEMPLATE_VIS duration_values
{
public:
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR _Rep zero() _NOEXCEPT {return _Rep(0);}
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR _Rep max()  _NOEXCEPT {return numeric_limits<_Rep>::max();}
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR _Rep min()  _NOEXCEPT {return numeric_limits<_Rep>::lowest();}
};

#if _LIBCPP_STD_VER > 14
template <class _ToDuration, class _Rep, class _Period>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
typename enable_if
<
    __is_duration<_ToDuration>::value,
    _ToDuration
>::type
floor(const duration<_Rep, _Period>& __d)
{
    _ToDuration __t = duration_cast<_ToDuration>(__d);
    if (__t > __d)
        __t = __t - _ToDuration{1};
    return __t;
}

template <class _ToDuration, class _Rep, class _Period>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
typename enable_if
<
    __is_duration<_ToDuration>::value,
    _ToDuration
>::type
ceil(const duration<_Rep, _Period>& __d)
{
    _ToDuration __t = duration_cast<_ToDuration>(__d);
    if (__t < __d)
        __t = __t + _ToDuration{1};
    return __t;
}

template <class _ToDuration, class _Rep, class _Period>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
typename enable_if
<
    __is_duration<_ToDuration>::value,
    _ToDuration
>::type
round(const duration<_Rep, _Period>& __d)
{
    _ToDuration __lower = floor<_ToDuration>(__d);
    _ToDuration __upper = __lower + _ToDuration{1};
    auto __lowerDiff = __d - __lower;
    auto __upperDiff = __upper - __d;
    if (__lowerDiff < __upperDiff)
        return __lower;
    if (__lowerDiff > __upperDiff)
        return __upper;
    return __lower.count() & 1 ? __upper : __lower;
}
#endif



// duration

template <class _Rep, class _Preiod>
/**
 * _Preiod 代表了一次计数所需要的时间间隔
 * _Rep 进行计数， 计数值 * 时间间隔 就代表了一段时间
 */
class duration
{
    static_assert(!__is_duration<_Rep>::value, "A duration representation can not be a duration");
    static_assert(__is_ratio<_Period>::value, "Second template parameter of duration must be a std::ratio");
    static_assert(_Period::num > 0, "duration period must be positive");

    template <class _R1, class _R2>
    /**
     * 有溢出的检测，执行的是除法  _R1 / _R2
     */
    struct __no_overflow
    {
    private:
        static const intmax_t __gcd_n1_n2 = __static_gcd<_R1::num, _R2::num>::value;
        static const intmax_t __gcd_d1_d2 = __static_gcd<_R1::den, _R2::den>::value;
        static const intmax_t __n1 = _R1::num / __gcd_n1_n2;
        static const intmax_t __d1 = _R1::den / __gcd_d1_d2;
        static const intmax_t __n2 = _R2::num / __gcd_n1_n2;
        static const intmax_t __d2 = _R2::den / __gcd_d1_d2;
        static const intmax_t max = -((intmax_t(1) << (sizeof(intmax_t) * CHAR_BIT - 1)) + 1);
        // intmax_t 可以表示的最大的数值

        template <intmax_t _Xp, intmax_t _Yp, bool __overflow>
        struct __mul    // __overflow == false
        {
            static const intmax_t value = _Xp * _Yp;
        };

        template <intmax_t _Xp, intmax_t _Yp>
        struct __mul<_Xp, _Yp, true>
        {
            static const intmax_t value = 1;
        };

    public:
        static const bool value = (__n1 <= max / __d2) && (__n2 <= max / __d1);
        typedef ratio<__mul<__n1, __d2, !value>::value,
                      __mul<__n2, __d1, !value>::value> type;
    };

public:
    typedef _Rep rep;
    typedef typename _Period::type period;
private:
    rep __rep_;
public:
#ifndef _LIBCPP_CXX03_LANG
    duration() = default;
#else
    duration() {}
#endif    

    template <class _Rep2>
        _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
        explicit duration(const _Rep2& __r,
            typename enable_if
            <
               is_convertible<_Rep2, rep>::value &&     
               // 保证精度的话，就要杜绝从 浮点数型向整数型的转换
               (treat_as_floating_point<rep>::value ||  // rep 是浮点类型或者 _Rep2 不是浮点类型
               !treat_as_floating_point<_Rep2>::value)
            >::type* = 0)
                : __rep_(__r) {}

    // conversions
    template <class _Rep2, class _Period2>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    duration(const duration<_Rep2, _Period2>& __d,
            typename enable_if
            <
            /**
             * peried2 / period 不能溢出 并且
             * rep 是浮点数，或者 peried2 / period 是一个整数(分母为 1)
             * 并且 _Rep2 不可以是浮点数
             */
                __no_overflow<_Period2, period>::value && (
                treat_as_floating_point<rep>::value ||
                (__no_overflow<_Period2, period>::type::den == 1 &&
                 !treat_as_floating_point<_Rep2>::value))
            >::type* = 0)
                : __rep_(yjh_def::chrono::duration_cast<duration>(__d).count()) {}
    
    // observer
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR rep count() const {return __rep_;}

    // arithmetic
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR typename common_type<duration>::type operator+() const 
                    {return typename common_type<duration>::type(*this);}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR typename common_type<duration>::type operator-() const 
                    {return typename common_type<duration>::type(-__rep_);}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator++()      {++__rep_; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration  operator++(int)   {return duration(__rep_++);}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator--()      {--__rep_; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration  operator--(int)   {return duration(__rep_--);}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator+=(const duration& __d) {__rep_ += __d.count(); return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator-=(const duration& __d) {__rep_ -= __d.count(); return *this;}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator*=(const rep& rhs) {__rep_ *= rhs; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator/=(const rep& rhs) {__rep_ /= rhs; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator%=(const rep& rhs) {__rep_ %= rhs; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 duration& operator%=(const duration& rhs) {__rep_ %= rhs.count(); return *this;}

    // special values

    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR duration zero() _NOEXCEPT 
                    {return duration(duration_values<rep>::zero());}
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR duration min()  _NOEXCEPT 
                    {return duration(duration_values<rep>::min());}
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR duration max()  _NOEXCEPT 
                    {return duration(duration_values<rep>::max());}
};

typedef duration<long long,         nano> nanoseconds;
typedef duration<long long,        micro> microseconds;
typedef duration<long long,        milli> milliseconds;
typedef duration<long long              > seconds;
typedef duration<     long, ratio<  60> > minutes;
typedef duration<     long, ratio<3600> > hours;
#if _LIBCPP_STD_VER > 17
typedef duration<     int, ratio_multiply<ratio<24>, hours::period>>         days;
typedef duration<     int, ratio_multiply<ratio<7>,   days::period>>         weeks;
typedef duration<     int, ratio_multiply<ratio<146097, 400>, days::period>> years;
typedef duration<     int, ratio_divide<years::period, ratio<12>>>           months;
#endif

template <class _LhsDuration, class _RhsDuration>
/**
 * 两个 duration 代表的时间长度是否相同
 */
struct __duration_eq
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    bool operator()(const _LhsDuration& __lhs, const _RhsDuration& __rhs) const
        {
            typedef typename common_type<_LhsDuration, _RhsDuration>::type _Ct;
            return _Ct(__lhs).count() == _Ct(__rhs).count();
        }
};

template <class _LhsDuration>
struct __duration_eq<_LhsDuration, _LhsDuration>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    bool operator()(const _LhsDuration& __lhs, const _LhsDuration& __rhs) const
        {return __lhs.count() == __rhs.count();}
};

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
bool
operator==(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    return __duration_eq<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >()(__lhs, __rhs);
}

// Duration !=

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
bool
operator!=(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    return !(__lhs == __rhs);
}

// Duration <

template <class _LhsDuration, class _RhsDuration>
struct __duration_lt
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    bool operator()(const _LhsDuration& __lhs, const _RhsDuration& __rhs) const
        {
            typedef typename common_type<_LhsDuration, _RhsDuration>::type _Ct;
            return _Ct(__lhs).count() < _Ct(__rhs).count();
        }
};

template <class _LhsDuration>
struct __duration_lt<_LhsDuration, _LhsDuration>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    bool operator()(const _LhsDuration& __lhs, const _LhsDuration& __rhs) const
        {return __lhs.count() < __rhs.count();}
};

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
bool
operator< (const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    return __duration_lt<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >()(__lhs, __rhs);
}

// Duration >

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
bool
operator> (const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    return __rhs < __lhs;
}

// Duration <=

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
bool
operator<=(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    return !(__rhs < __lhs);
}

// Duration >=

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
bool
operator>=(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    return !(__lhs < __rhs);
}

// Duration +
/**
 * 将两个 duration 的时间长度相加，得到一个新的 duration 
 * 由于两个 duration 的单位时间间隔是不一样的，所以新的 duration 需要使用两个  duration 的
 * 单位时间间隔的最大公约数作为新的单位时间间隔，并重新计算 __rep_ 的值
 */
template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type
operator+(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    typedef typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type _Cd;
    return _Cd(_Cd(__lhs).count() + _Cd(__rhs).count());
}

// Duration -

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type
operator-(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    typedef typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type _Cd;
    return _Cd(_Cd(__lhs).count() - _Cd(__rhs).count());
}

// Duration *
/**
 * 把当前的时间长度乘以一个固定的数值
 */
template <class _Rep1, class _Period, class _Rep2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename enable_if
<
    is_convertible<_Rep2, typename common_type<_Rep1, _Rep2>::type>::value,
    duration<typename common_type<_Rep1, _Rep2>::type, _Period>
>::type
operator*(const duration<_Rep1, _Period>& __d, const _Rep2& __s)
{
    typedef typename common_type<_Rep1, _Rep2>::type _Cr;
    typedef duration<_Cr, _Period> _Cd;
    return _Cd(_Cd(__d).count() * static_cast<_Cr>(__s));
}

template <class _Rep1, class _Period, class _Rep2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename enable_if
<
    is_convertible<_Rep1, typename common_type<_Rep1, _Rep2>::type>::value,
    duration<typename common_type<_Rep1, _Rep2>::type, _Period>
>::type
operator*(const _Rep1& __s, const duration<_Rep2, _Period>& __d)
{
    return __d * __s;
}

// Duration /

template <class _Rep1, class _Period, class _Rep2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename enable_if
<
    !__is_duration<_Rep2>::value &&
      is_convertible<_Rep2, typename common_type<_Rep1, _Rep2>::type>::value,
    duration<typename common_type<_Rep1, _Rep2>::type, _Period>
>::type
operator/(const duration<_Rep1, _Period>& __d, const _Rep2& __s)
{
    typedef typename common_type<_Rep1, _Rep2>::type _Cr;
    typedef duration<_Cr, _Period> _Cd;
    return _Cd(_Cd(__d).count() / static_cast<_Cr>(__s));
}

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename common_type<_Rep1, _Rep2>::type
operator/(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    typedef typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type _Ct;
    return _Ct(__lhs).count() / _Ct(__rhs).count();
}


// Duration %

template <class _Rep1, class _Period, class _Rep2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename enable_if
<
    !__is_duration<_Rep2>::value &&
      is_convertible<_Rep2, typename common_type<_Rep1, _Rep2>::type>::value,
    duration<typename common_type<_Rep1, _Rep2>::type, _Period>
>::type
operator%(const duration<_Rep1, _Period>& __d, const _Rep2& __s)
{
    typedef typename common_type<_Rep1, _Rep2>::type _Cr;
    typedef duration<_Cr, _Period> _Cd;
    return _Cd(_Cd(__d).count() % static_cast<_Cr>(__s));
}

template <class _Rep1, class _Period1, class _Rep2, class _Period2>
inline _LIBCPP_INLINE_VISIBILITY
_LIBCPP_CONSTEXPR
typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type
operator%(const duration<_Rep1, _Period1>& __lhs, const duration<_Rep2, _Period2>& __rhs)
{
    typedef typename common_type<_Rep1, _Rep2>::type _Cr;
    typedef typename common_type<duration<_Rep1, _Period1>, duration<_Rep2, _Period2> >::type _Cd;
    return _Cd(static_cast<_Cr>(_Cd(__lhs).count()) % static_cast<_Cr>(_Cd(__rhs).count()));
}

//////////////////////////////////////////////////////////
///////////////////// time_point /////////////////////////
//////////////////////////////////////////////////////////

template <class _Clock, class _Duration = typename _Clock::duration>
class time_point
{
    static_assert(__is_duration<_Duration>::value,
                "Second template parameter of time_point must be a std::chrono::duration");
public:
    typedef _Clock                      clock;
    typedef _Duration                   duration;
    typedef typename duration::rep      rep;
    typedef typename duration::period   period;

private:
    duration __d_;

public:
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11 time_point() 
                : __d_(duration::zero()) {}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11 
    explicit time_point(const duration& __d) 
        : __d_(__d) {}

    // conversions
    template <class _Duration2>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    time_point(const time_point<clock, _Duration2>& t,
        typename enable_if
        <
            is_convertible<_Duration2, duration>::value
        >::type* = 0)
            : __d_(t.time_since_epoch()) {}

    // observer
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11 duration time_since_epoch() const {return __d_;}

    // arithmetic
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 time_point& 
        operator+=(const duration& __d) {__d_ += __d; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14 time_point& 
        operator-=(const duration& __d) {__d_ -= __d; return *this;}
    
    // special values
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR
    time_point min() _NOEXCEPT {return time_point(duration::min());}
    _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR 
    time_point max() _NOEXCEPT {return time_point(duration::max());}
};

}   // chrono

/**
 * 对于 type_traits.cpp 中的 common_type 的一个特化
 */
template <class _Clock, class _Duration1, class _Duration2>
struct _LIBCPP_TEMPLATE_VIS common_type<chrono::time_point<_Clock, _Duration1>,
                                         chrono::time_point<_Clock, _Duration2> >
{
    typedef chrono::time_point<_Clock, typename common_type<_Duration1, _Duration2>::type> type;
};


namespace chrono
{

template <class _ToDuration, class _Clock, class _Duration>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
time_point<_Clock, _ToDuration>
time_point_cast(const time_point<_Clock, _Duration>& __t)
{
    return time_point<_Clock, _ToDuration>(yjh_def::chrono::duration_cast<_ToDuration>(__t.time_since_epoch()));
}



} // namespace chrono



} // namespace yjh_def


#endif
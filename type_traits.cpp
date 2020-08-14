#ifndef _LIBCPP_TYPE_TRAITS	// 防止头文件的重复
#define _LIBCPP_TYPE_TRAITS

#include <stddef.h>
#include "__config.cpp"



namespace yjh_def{
//typedef long long ptrdiff_t;
using ::size_t;
using ::ptrdiff_t;
typedef long double max_align_t;
/**
 * __any 类有一个可以接收任何数据类型输入的构造函数
 */
struct __any
{
	__any(...);
};

struct nullptr_t
{
	void* __lx;
	struct __nat {int __for_bool_;};
	nullptr_t() : __lx(0) {}
	nullptr_t(int __nat::*) : __lx(0) {}

	operator int __nat::*() const {return 0;}

	template <class _Tp>
		operator _Tp* () const {return 0;}

	template <class _Tp, class _Up>
		operator _Tp _Up::* () const {return 0;}

	friend bool operator == (nullptr_t, nullptr_t) {return true;}
	friend bool operator != (nullptr_t, nullptr_t) {return false;}
	friend bool operator < (nullptr_t, nullptr_t) {return false;}
	friend bool operator <= (nullptr_t, nullptr_t) {return true;}
	friend bool operator > (nullptr_t, nullptr_t) {return false;}
	friend bool operator >= (nullptr_t, nullptr_t) {return true;}
};

inline nullptr_t __get_nullptr_t() {return nullptr_t(0);}

//typedef decltype(nullptr) nullptr_t;

template <bool _Bp, class _If, class _Then>
	struct conditional {typedef _If type;};
template <class _If, class _Then>
	struct conditional<false, _If, _Then> {typedef _Then type;};

template <bool, class _Tp = void>	struct enable_if {};
template <class _Tp>	struct enable_if<true, _Tp> {typedef _Tp type;};

template <class _Tp, _Tp __v>
struct integral_constant
{
    static const _Tp 	value = __v;
	typedef _Tp 		value_type;
	typedef integral_constant type;
	operator value_type() const {return value;};
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

#if _LIBCPP_STD_VER > 14
template <bool __b>
using bool_constant = integral_constant<bool, __b>;
#define _LIBCPP_BOOL_CONSTANT(__b) bool_constant<(__b)>
#else 
#define _LIBCPP_BOOL_CONSTANT(__b) integral_constant<bool, (__b)>
#endif


//is_const
template <class _Tp> struct is_const            : public false_type{};
template <class _Tp> struct is_const<_Tp const> : public true_type{};

// is_volatile
template <class _Tp>	struct is_volatile					: public false_type {};
template <class _Tp>	struct is_volatile<_Tp volatile>	: public true_type {};


//remove_const
template <class _Tp> struct remove_const            {typedef _Tp type;};
template <class _Tp> struct remove_const<const _Tp> {typedef _Tp type;};

//remove_volatile
template <class _Tp> struct remove_volatile                 {typedef _Tp type;};
template <class _Tp> struct remove_volatile<volatile _Tp>   {typedef _Tp type;};

//remove_cv
template <class _Tp> struct remove_cv
{
    typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;
};

//is_void

template <class _Tp> struct __is_void					: public false_type {};
template <>			 struct __is_void<void>				: public true_type {};

template <class _Tp> struct is_void
	: public __is_void<typename remove_cv<_Tp>::type> {};

// __is_nullptr_t
template <class _Tp>	struct ____is_nullptr_t				: public false_type {};
template <>				struct ____is_nullptr_t<nullptr_t>	: public true_type {};

template <class _Tp>	struct __is_nullptr_t
	: public ____is_nullptr_t<typename remove_cv<_Tp>::type> {};

//is_integral
template <class _Tp> struct __is_integral                   : public false_type {};
//模板的特化，下面的这些具体的数据类型都是整数类型，除了下面这些情况以外的都不是整数类型
template<>           struct __is_integral<bool>             : public true_type {};
template<>           struct __is_integral<char>             : public true_type {};
template<>           struct __is_integral<signed char>      : public true_type {};
template<>			 struct __is_integral<unsigned char>	: public true_type {};

template<>           struct __is_integral<short>            : public true_type {};
template<>			 struct __is_integral<unsigned short>	: public true_type {};
template<>			 struct __is_integral<int>				: public true_type {};
template<>			 struct __is_integral<unsigned int>		: public true_type {};
template<>			 struct __is_integral<long>				: public true_type {};
template<>			 struct __is_integral<unsigned long>	: public true_type {};
template<>			 struct __is_integral<unsigned long long> : public true_type {};

template <class _Tp> struct is_integral
    : public __is_integral<typename remove_cv<_Tp>::type> {};

//is_floating_point

template <class _Tp> struct __is_floating_point						: public false_type {};
//模板的特化，只有下面的三种具体的数据类型是浮点数数据类型，其他的数据类型都不是浮点数数据类型
template<> 			struct __is_floating_point<float>				: public true_type {};
template<>			struct __is_floating_point<double>				: public true_type {};
template<>			struct __is_floating_point<long double>			: public true_type {};

//具体的数据类型可能带 const volatile 限定词
//考虑一下 const volatile 等限定词在 模板参数中的地位
//以及 *  &  在模板参数中的地位
template <class _Tp> struct is_floating_point
	: public __is_floating_point<typename remove_cv<_Tp>::type> {};

//is_array

template <class _Tp> struct is_array
	: public false_type {};
template <class _Tp> struct is_array<_Tp[]>
	: public true_type {};
template <class _Tp, int _Np> struct is_array<_Tp[_Np]>
	: public true_type {};

//is_pointer

template <class _Tp> struct __is_pointer			: public false_type {};
template <class _Tp> struct __is_pointer<_Tp*>		: public true_type {}; // 这个模版包含了 _Tp* _Tp**, .....
//template <class _Tp> struct __is_pointer<_Tp**>		: public false_type {}; //如果这样写的话，那么 int** 就不会被认为是 pointer 类型

template <class _Tp> struct is_pointer
	: public __is_pointer<typename remove_cv<_Tp>::type> {};

//is_reference
template <class _Tp> struct is_lvalue_reference				: public false_type {};
template <class _Tp> struct is_lvalue_reference<_Tp&>		: public true_type {};
template <class _Tp> struct is_rvalue_reference				: public false_type {};
template <class _Tp> struct is_rvalue_reference<_Tp&&>		: public true_type {};

//这里的实现没有考虑 const volatile 等限定符，也没有必要在判定之前除去这些限定符，这样做的原因可以结合上面的 is_integal 的实现对比得出结论
template <class _Tp> struct is_reference			: public false_type {};
template <class _Tp> struct is_reference<_Tp&>		: public true_type {}; 	//& 和 && 是具有完全不同的含义的，不同于 * 与 ** 甚至于与 ***
template <class _Tp> struct is_reference<_Tp&&>		: public true_type {};

//is_union
/** 错误的实现方法
 * 这里的实现方法是错误的
 */
//template <class _Tp> struct __libcpp_union : public false_type {};
//template <class _Tp> struct is_union
//	: public __libcpp_union<typename remove_cv<_Tp>::type> {};

template <class _Tp> struct is_union
    : public integral_constant<bool, __is_union(_Tp)> {};

//is_class

struct __two {char __lx[2];};
namespace __is_class_imp
{
	template <class _Tp> char __test(int _Tp::*);   
	template <class _Tp> __two __test(...);
	/**
	 * 这里的技巧就是，如果 _Tp 是一个类的话，那么调用 __test<_Tp>(0) 会优先调用第一个函数模板的实化
	 * 如果 _Tp 不是一个类的话，那么调用 __test<_Tp>(0) 就会优先调用第二个函数模板
	 * 这两个函数模板一大不同之处，就是返回值的大小上面， char 类型的 sizeof 是 1 ；而 __two 类型的 sizeof 是 2
	 */
}
template <class _Tp> struct is_class
	: public integral_constant<bool, sizeof(__is_class_imp::__test<_Tp>(0)) == 1 && !is_union<_Tp>::value> {};

//is_same

template <class _Tp, class _Up>	struct is_same				: public false_type {};
template <class _Tp>			struct is_same<_Tp, _Tp>	: public true_type {};


template <class _Tp, class _Up>
using _IsSame = integral_constant<
	bool, 
	#ifdef __clang_
		__is_same(_Tp, _Up)
	#else
		yjh_def::is_same<_Tp, _Up>::value
	#endif
>;

template <class _Tp, class _Up>
using _IsNotSame = integral_constant<
		bool,
		#ifdef __clang__
			!__is_same(_Tp, _Up)
		#else
			!yjh_def::is_same<_Tp, _Up>::value
		#endif	
	>;

// addressof
#ifndef _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF

template <class _Tp>
inline _LIBCPP_CONSTEXPR_AFTER_CXX14
_LIBCPP_NO_CFI _LIBCPP_INLINE_VISIBILITY
_Tp*
addressof(_Tp& __x) _NOEXCEPT
{
    return __builtin_addressof(__x);
}

#else

template <class _Tp>
inline _LIBCPP_NO_CFI _LIBCPP_INLINE_VISIBILITY
_Tp*
addressof(_Tp& __x) _NOEXCEPT
{
  return reinterpret_cast<_Tp *>(
      const_cast<char *>(&reinterpret_cast<const volatile char &>(__x)));
}

#endif // _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF

#if defined(_LIBCPP_HAS_OBJC_ARC) && !defined(_LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF)
// Objective-C++ Automatic Reference Counting uses qualified pointers
// that require special addressof() signatures. When
// _LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF is defined, the compiler
// itself is providing these definitions. Otherwise, we provide them.
template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__strong _Tp*
addressof(__strong _Tp& __x) _NOEXCEPT
{
  return &__x;
}

#ifdef _LIBCPP_HAS_OBJC_ARC_WEAK
template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__weak _Tp*
addressof(__weak _Tp& __x) _NOEXCEPT
{
  return &__x;
}
#endif

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__autoreleasing _Tp*
addressof(__autoreleasing _Tp& __x) _NOEXCEPT
{
  return &__x;
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__unsafe_unretained _Tp*
addressof(__unsafe_unretained _Tp& __x) _NOEXCEPT
{
  return &__x;
}
#endif

#if !defined(_LIBCPP_CXX03_LANG)
template <class _Tp> _Tp* addressof(const _Tp&&) noexcept = delete;
#endif

//is_function
namespace __is_function_imp
{
	template <class _Tp> char 	__test(_Tp*);
	template <class _Tp> __two	__test(...);
	template <class _Tp> _Tp&	__source();
}

template <class _Tp, bool = is_class<_Tp>::value ||
							is_union<_Tp>::value ||
							is_void<_Tp>::value ||
							is_reference<_Tp>::value ||
							is_same<_Tp, nullptr_t>::value >
struct ___is_function
	: public integral_constant<bool, sizeof(__is_function_imp::__test<_Tp>(__is_function_imp::__source<_Tp>())) == 1> {};
template <class _Tp> struct ___is_function<_Tp, true> : public false_type {};
/**
 * 值得注意的是函数类型和函数指针类型之间的区别：
 * 举个简单的例子就可以看的出来：
 *          int(int, double)  是一个函数类型
 *          int(*)(int, double) 是一个函数指针类型
 *          yjh_def::add_pointer(int(int, double)) = int(*)(int, double) 将函数类型转化为函数指针类型
 * 这样就可以非常明确的看出了 函数类型和函数指针类型之间的区别
 */
template <class _Tp> struct is_function
	: public ___is_function<_Tp> {};

// is_memeber_pointer
/**
 * 如果 T 为指向非静态成员对象或者非静态成员函数的指针，则这个模板类返回 true
 * 否则的话，返回 false
 */
template <class _Tp>			struct __is_member_pointer				: public false_type {};
template <class _Tp, class _Up>	struct __is_member_pointer<_Tp _Up::*>	: public true_type {};
 
template <class _Tp> struct	is_member_pointer
	: public __is_member_pointer<typename remove_cv<_Tp>::type> {};


// __void_t
template <class> struct __void_t {typedef void type;};

// is_enum
// 直接使用 C 语言的内建函数 __is_enum(_Tp)
template <class _Tp> struct is_enum
	: public integral_constant<bool, __is_enum(_Tp)> {};

// is_arithmetic
/**
 * 可以用于数学计算的只有整数或者是浮点数
 */
template <class _Tp> struct is_arithmetic
	: public integral_constant<bool,	is_integral<_Tp>::value	||
										is_floating_point<_Tp>::value> {};


// is_scalar
template <class _Tp> struct is_scalar
	: public integral_constant<bool,	is_arithmetic<_Tp>::value		||
										is_member_pointer<_Tp>::value	||
										is_pointer<_Tp>::value			||
										__is_nullptr_t<_Tp>::value		||
										is_enum<_Tp>::value				> {};

template <> struct is_scalar<nullptr_t> : public true_type {};

// add_const
template <class _Tp, bool =	is_reference<_Tp>::value ||
							is_function<_Tp>::value ||
							is_const<_Tp>::value	>
struct __add_const				{typedef _Tp type;};

template <class _Tp>
struct __add_const<_Tp, false> {typedef _Tp type;};

template <class _Tp>	struct add_const
	{typedef typename __add_const<_Tp>::type type;};

// add_volatile
template <class _Tp, bool =	is_reference<_Tp>::value ||
							is_function<_Tp>::value ||
							is_volatile<_Tp>::value	>
struct __add_volatile			{typedef _Tp type;};

template <class _Tp>
struct __add_volatile<_Tp, false> {typedef volatile _Tp type;};

template <class _Tp>	struct add_volatile
	{typedef typename __add_volatile<_Tp>::type type;};

// add_cv     const volatile
template <class _Tp>	struct add_cv
	{typedef typename add_const<typename add_volatile<_Tp>::type>::type type;};

// is_abstract

namespace __is_abstract_imp
{
	template <class _Tp> char	__test(_Tp (*)[1]);   //这里从语法上如何解释
	template <class _Tp> __two	__test(...);
}
template <class _Tp, bool = is_class<_Tp>::value>
struct __libcpp_abstract : public integral_constant<bool, sizeof(__is_abstract_imp::__test<_Tp>(0)) != 1> {};

template <class _Tp> struct __libcpp_abstract<_Tp, false> : public false_type {};

template <class _Tp> struct is_abstract : public __libcpp_abstract<_Tp> {};

// is_base_of
template <class _Bp, class _Dp>
struct is_base_of
	: public integral_constant<bool, __is_base_of(_Bp, _Dp)> {};

// remove_reference
template <class _Tp> struct remove_reference			{typedef _Tp type;};
template <class _Tp> struct remove_reference<_Tp&>		{typedef _Tp type;};
template <class _Tp> struct remove_reference<_Tp&&>		{typedef _Tp type;};

// add_lvalue_reference
template <class _Tp>	struct	add_lvalue_reference						{typedef _Tp& type;};
template <class _Tp>	struct	add_lvalue_reference<_Tp&>					{typedef _Tp& type;};
template <>				struct	add_lvalue_reference<void>					{typedef void type;};
template <>				struct	add_lvalue_reference<const void>			{typedef const void type;};
template <>				struct	add_lvalue_reference<volatile void>			{typedef volatile void type;};
template <>				struct	add_lvalue_reference<const volatile void>	{typedef const volatile void type;};

// add_rvalue_reference
template <class _Tp>	struct add_rvalue_reference							{typedef _Tp&& type;};
template <>				struct add_rvalue_reference<void>					{typedef void type;};
template <>				struct add_rvalue_reference<const void>				{typedef const void type;};
template <>				struct add_rvalue_reference<volatile void>			{typedef volatile void type;};
template <>				struct add_rvalue_reference<const volatile void>	{typedef const volatile void type;};

// declval()
template <class _Tp>
typename add_rvalue_reference<_Tp>::type
declval();

// remove_pointer
template <class _Tp>	struct remove_pointer							{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp*>						{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp* const>				{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp* const volatile>		{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp* volatile>			{typedef _Tp type;};

// add_pointer
template <class _Tp>	struct add_pointer
	{typedef typename remove_reference<_Tp>::type* type;};


// aligned_storage
template <yjh_def::size_t _Len>
struct __aligned_storage_msa
{
	/**
	 * 这里的 char 究竟占用多少个字节是未知的，为了对其内存，方便数据的拷贝，使用 __aligned__
	 * 将数据对其到系统默认的字节长度
	 */
	union __type
	{
		unsigned char __data[_Len];
		struct __attribute__((__aligned__)){ } __align;	// ?????? 完全不懂这个东西
	};
};

template <yjh_def::size_t _Len, yjh_def::size_t _Align = 
	__alignof__(typename __aligned_storage_msa<_Len>::__type)>
struct aligned_storage
{
	union type
	{
		unsigned char __data[_Len];
		struct __attribute__((__aligned__((_Align)))) { } __align;
	};
};

// is_signed
/**
 * 只有整型的数据才需要考虑是否是 unsigned 或者是 signed
 * 浮点数一定是 signed 的
 */
template <class _Tp, bool = is_integral<_Tp>::value>
struct ___is_signed : public integral_constant<bool, _Tp(-1) < _Tp(0)> {};

/**
 * 浮点数
 */
template <class _Tp>
struct ___is_signed<_Tp, false> : public true_type {};

/**
 * 算术类型的数据才有资格测试是否是 signed 类型
 */
template <class _Tp, bool = is_arithmetic<_Tp>::value>
struct __is_signed : public ___is_signed<_Tp> {};

template <class _Tp>
struct __is_signed<_Tp, false> : public false_type {};

/**
 * 判断一个数据类型是否是 signed 的最终类
 */
template <class _Tp>	struct is_signed : public __is_signed<_Tp> {};

// is_unsigned
template <class _Tp, bool = is_integral<_Tp>::value>
struct ___is_unsigned : public integral_constant<bool, _Tp(0) < _Tp(-1)> {};

template <class _Tp>
struct ___is_unsigned<_Tp, false> : public false_type {};

template <class _Tp, bool = is_arithmetic<_Tp>::value>
struct __is_unsigned : public ___is_unsigned<_Tp> {};

template <class _Tp>	struct __is_unsigned<_Tp, false> : public false_type {};

/**
 * 判断一个数据是不是 unsigned 的最终类型
 */
template <class _Tp>	struct is_unsigned : public __is_unsigned<_Tp> {};

// rank
/**
 * 如果给 rank 提供的是一个数组类型，那么 rank 可以获取 数组的维度
 * 对于其他的任何的数据类型，返回值都是 0；
 * rank 的实现采用了 递归的结构
 * 使用例子：
 * std::rank<int[5]>
 * std::rank<int[][5]>
 * std::rank<int[][5][5]>
 */
template <class _Tp> struct rank
	: public integral_constant<int, 0> {};

template <class _Tp> struct rank<_Tp[]>
	: public integral_constant<int, rank<_Tp>::value + 1> {};

template <class _Tp, int _Np> struct rank<_Tp[_Np]>
	: public integral_constant<int, rank<_Tp>::value + 1> {};

// extent
/**
 * 如果 _Tp 是数组类型，则给出 _Tp 在第 N 维度的元素的个数
 */
template <class _Tp, unsigned _IP = 0> struct extent
	: public integral_constant<int, 0> {};
template <class _Tp> struct extent<_Tp[], 0>
	: public integral_constant<int, 0> {};
template <class _Tp, unsigned _Ip> struct extent<_Tp[], _Ip>
	: public integral_constant<int, extent<_Tp, _Ip-1>::value> {};
template <class _Tp, unsigned _Np> struct extent<_Tp[_Np], 0>
	: public integral_constant<int, _Np> {};
template <class _Tp, unsigned _Np, unsigned _Ip> struct extent<_Tp[_Np], _Ip>
	: public integral_constant<int, extent<_Tp, _Ip - 1>::value> {};

// remove_extent
template <class _Tp> struct remove_extent
	{typedef _Tp type;};
template <class _Tp> struct remove_extent<_Tp[]>
	{typedef _Tp type;};
template <class _Tp, unsigned _Np> struct remove_extent<_Tp[_Np]>
	{typedef _Tp type;};

// remove_all_extent
template <class _Tp> struct remove_all_extent
	{typedef _Tp type;};
template <class _Tp> struct remove_all_extent<_Tp[]>
	{typedef typename remove_all_extent<_Tp>::type type;};
template <class _Tp, unsigned _Np> struct remove_all_extent<_Tp[_Np]>
	{typedef typename remove_all_extent<_Tp>::type type;};

// decay
/**
 * 数组类型转化为指针
 * 函数 类型转化为 函数指针类型
 * 移除所有类型 的 const volatile 限定修饰符
 */
template <class _Tp>
struct decay
{
private:
	typedef typename remove_reference<_Tp>::type _Up;
public:
	typedef typename yjh_def::conditional
						<
							is_array<_Up>::value,
							typename remove_extent<_Up>::type*,   // change type_name[] ==> type_name*
							typename yjh_def::conditional
							<
								is_function<_Up>::value,
								typename add_pointer<_Up>::type,
								typename remove_cv<_Up>::type
							>::type
						>::type type;
};

// move
/**
 * 不要被 move 函数的名称所迷惑， move 函数自身不做任何实际的移动过程，move 做的仅仅是将输入的
 * 变量转换为右值类型[即可以被移动的类型]
 * 至于返回的右值类型是否被移到，要看被返回的右值类型如何被使用。一个变量被转换为右值类型，其也未必可以成功的被移动
 */
template <class _Tp>
typename remove_reference<_Tp>::type&&
move(_Tp&& __t)
{
	typedef typename remove_reference<_Tp>::type _Up;
	return static_cast<_Up&&>(__t);
}

// forward 
/**
 * why
 * 这个地方没有弄懂是什么意思
 */
template <class _Tp>
_Tp&&
forward(typename remove_reference<_Tp>::type& __t) noexcept
{
	//std::cout << "forward(&)" << '\n';
	return static_cast<_Tp&&>(__t);
}

template <class _Tp>
inline _Tp&&
forward(typename remove_reference<_Tp>::type&& __t) noexcept
{
	//std::cout << "forward(&&)" << '\n';
	static_assert(!is_lvalue_reference<_Tp>::value,
					"Can not forward an rvalue as a lvalue.");	 // 不可以讲一个左值转化为右值
	return static_cast<_Tp&&>(__t);
}

// for_each
template <class _InputIterator, class _Function>
inline
_Function for_each(_InputIterator __first, _InputIterator __last, _Function __f)
{
	for (; __first != __last; ++__first)
		__f(*__first);
	return move(__f);
}


// is_convertible 的实现

namespace __is_convertible_imp
{
template <class _Tp>    char    __test(_Tp);
template <class _Tp>    __two   __test(...);
template <class _Tp>    _Tp&&   __source();

/**
 * 测试 _Tp 是否是下面的三种类型中的一种
 * array
 * function
 * void
 */
template <class _Tp,    bool _IsArray =         is_array<_Tp>::value,
                        bool _IsFunction =      is_function<_Tp>::value,
                        bool _IsVoid =          is_void<_Tp>::value >
                        struct __is_array_function_or_void                              {enum {value = 0};};
template <class _Tp>    struct __is_array_function_or_void<_Tp, true, false, false>     {enum {value = 1};};
template <class _Tp>    struct __is_array_function_or_void<_Tp, false, true, false>     {enum {value = 2};};
template <class _Tp>    struct __is_array_function_or_void<_Tp, false, false, true>     {enum {value = 3};};
}

template <class _Tp,
        unsigned = __is_convertible_imp::__is_array_function_or_void<typename remove_reference<_Tp>::type>::value>
struct __is_convertible_check
{
    static const unsigned __v = 0;
};

template <class _Tp>
struct __is_convertible_check<_Tp, 0>
{
    static const unsigned __v = sizeof(_Tp);
};

template <class _T1, class _T2,
    unsigned _T1_is_array_function_or_void = __is_convertible_imp::__is_array_function_or_void<_T1>::value,
    unsigned _T2_is_array_function_or_void = __is_convertible_imp::__is_array_function_or_void<_T2>::value>
struct __is_convertible
    : public integral_constant< bool,
            sizeof(__is_convertible_imp::__test<_T2>(__is_convertible_imp::__source<_T1>())) == 1 >
{};
/**
 * 下面的几个是上面的模板类的一系列的偏特化
 * 用于说明一些比较特殊的情况
 */
//如果 T1 和 T2 是两种不同的数据类型，并且 T1 是一个数组的话，那么 T1 和 T2 之间必然不可能互相转换
//下面的几种情况都是 T1 是数组类型的情况
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 0> : false_type {};
template <class _T1> struct __is_convertible<_T1, const _T1&, 1, 0> : true_type {};
template <class _T1> struct __is_convertible<_T1, _T1&&, 1, 0> : true_type {};
template <class _T1> struct __is_convertible<_T1, const _T1&&, 1, 0> : true_type {};
template <class _T1> struct __is_convertible<_T1, volatile _T1&&, 1, 0> : true_type {};
template <class _T1> struct __is_convertible<_T1, const volatile _T1&&, 1, 0> : true_type {};
/**
 * 数组是否可以转化为指针？
 */
template <class _T1, class _T2> struct __is_convertible<_T1, _T2*, 1, 0>
    : public integral_constant<bool, __is_convertible<typename remove_all_extent<_T1>::type*, _T2*>::value> {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2* const, 1, 0>
    : public integral_constant<bool, __is_convertible<typename remove_all_extent<_T1>::type*, _T2* const>::value> {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2* volatile, 1, 0>
    : public integral_constant<bool, __is_convertible<typename remove_all_extent<_T1>::type*, _T2* volatile>::value> {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2* const volatile, 1, 0>
    : public integral_constant<bool, __is_convertible<typename remove_all_extent<_T1>::type*, _T2*const volatile>::value> {};

//下面的几种情况都是 T1 是 function 的情况
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 0>                         : public false_type {};
template <class _T1>            struct __is_convertible<_T1, _T1&&, 2, 0>                       : public true_type {};
template <class _T1>            struct __is_convertible<_T1, _T1&, 2, 0>                        : public true_type {};
template <class _T1>            struct __is_convertible<_T1, _T1*, 2, 0>                        : public true_type {};
template <class _T1>            struct __is_convertible<_T1, _T1* const, 2, 0>                  : public true_type {};
template <class _T1>            struct __is_convertible<_T1, _T1* volatile, 2, 0>               : public true_type {};
template <class _T1>            struct __is_convertible<_T1, _T1* const volatile, 2, 0>         : public true_type {};

// T1 是 void 类型是
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 0>                         : public false_type {};

// T2 是 array 类型的情况
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 1>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 1>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 1>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 1>                         : public false_type {};
// T2 是 function 类型的情况
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 2>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 2>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 2>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 2>                         : public false_type {};
// T2 是 void 类型的情况
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 3>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 3>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 3>                         : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 3>                         : public true_type {};

/**
 * is_convertible 的总的接口
 */
template <class _T1, class _T2> struct is_convertible
    : public __is_convertible<_T1, _T2>
{
    static const unsigned __complete_check1 = __is_convertible_check<_T1>::__v;
    static const unsigned __complete_check2 = __is_convertible_check<_T2>::__v;
};

// is_empty
#ifdef _HAS_IS_EMPTY_
template <class _Tp>
struct is_empty
	: public integral_constant<bool, __is_empty(_Tp)> {}
#else
template <class _Tp>
struct __is_empty1
	: public _Tp
{
	double __lx;
};

struct __is_empty2
{
	double __lx;
};
/**
 * 查看一个类是否是一个空类的实现非常的巧妙：
 * __is_empty1 和 __is_empty2 都只有一个double类型的成员，唯一的不同是，
 * __is_empty1 类还继承了 待测试的类 _Tp
 * 如果这个时候 __is_empty1 和 __is_empty2 类大小还是相同的话，那么就说明了
 * _Tp 类是一个空类，没有包含任何的数据
 * 
 * 在进行大小的比较之前，先使用 is_class 测试 _Tp 是否是一个类
 */
template <class _Tp, bool = is_class<_Tp>::value>
struct __libcpp_empty 
	: public integral_constant<bool, sizeof(__is_empty1<_Tp>) == sizeof(__is_empty2)> {};

template <class _Tp> struct __libcpp_empty<_Tp, false> : public false_type {};

template <class _Tp> struct is_empty : public __libcpp_empty<_Tp> {};
#endif

// is_polymorphic
#ifdef __HAS_IS_POLYMORPHIC_
template <class _Tp>
struct is_polymorphic
	: public integral_constant<bool, __is_polymorphic(_Tp)> {}

#else
/**
 * 一个类中具有虚函数，那么这个类就需要保存一个指向虚函数的虚基表的指针来存储这个虚基表的地址，会占用一个指针类型的空间
 * 从这里可以看出，如果 _Tp 中有虚函数[即有多态特性] 那么 __is_polymorohic1 就需要虚基表，类的内部需要存储虚基表的指针
 * __is_polumorihic2 类是一定要建立虚基表的
 * 这个时候如果 __is_polymorohic1 和 __is_polumorihic2 大小相同，说明 _Tp 中有虚函数
 * 
 * 在进行比较之前，需要确定 _Tp 是否是一个 class 类型
 */
template <class _Tp> struct __is_polymorphic1 : public _Tp {};
template <class _Tp> struct __is_polymorphic2 : public _Tp {virtual ~__is_polymorphic2() throw();};
template <class _Tp, bool = is_class<_Tp>::value>
struct __libcpp_polymorphic
	: public integral_constant<bool, sizeof(__is_polymorphic1<_Tp>) == sizeof(__is_polymorphic2<_Tp>)>
	{};

template <class _Tp>
struct __libcpp_polymorphic<_Tp, false>
	: public false_type {};

template <class _Tp>
struct is_polymorphic
	: public __libcpp_polymorphic<_Tp> {};

#endif

// __type_list
template <class _Hp, class _Tp>
struct __type_list
{
	typedef _Hp		_Head;
	typedef _Tp		_Tail;
};

// __nat
struct __nat
{
	__nat() 						= delete;
	__nat(const __nat&) 			= delete;
	__nat& operator=(const __nat&)	= delete;
	~__nat()						= delete;
};


// make_signed  / make_unsigned
typedef
	__type_list<signed char,
	__type_list<signed short,
	__type_list<signed int,
	__type_list<signed long,
	__type_list<signed long long,
	__nat
	> > > > > __signed_types;

typedef
	__type_list<unsigned char,
	__type_list<unsigned short,
	__type_list<unsigned int,
	__type_list<unsigned long,
	__type_list<unsigned long long,
	__nat
	> > > > > __unsigned_types;

// __find_first
template <class _TypeList, size_t _Size, bool = _Size < sizeof(typename _TypeList::_Head) >struct __find_first;
/**
 * 这个局部特化值得仔细看一看
 * __signed_type 中包含了所有的 singned 类型
 * __unsigned_type 中包含了所有的 unsigned 类型
*/
template <class _Hp, class _Tp, size_t _Size>
struct __find_first<__type_list<_Hp, _Tp>, _Size, true>
{
	typedef _Hp type;
};

template <class _Hp, class _Tp, size_t _Size>
struct __find_first<__type_list<_Hp, _Tp>, _Size, false>
{
	typedef typename __find_first<_Tp, _Size>::type type;
};
/**
 * 这个类很有意思，如果 _Tp 带 cv 限定符的话，那么 _Up 也带上相同的 cv 限定符
 */
template <class _Tp, class _Up,		bool = is_const<typename remove_reference<_Tp>::type>::value,
									bool = is_volatile<typename remove_reference<_Tp>::type>::value>
struct __apply_cv
{
	typedef _Up type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp, _Up, true, false>
{
	typedef const _Up type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp, _Up, true, true>
{
	typedef const volatile _Up type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp, _Up, false, true>
{
	typedef volatile _Up type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp&, _Up, false, false>
{
	typedef _Up& type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp&, _Up, true, false>
{
	typedef const _Up& type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp&, _Up, false, true>
{
	typedef volatile _Up& type;
};

template <class _Tp, class _Up>
struct __apply_cv<_Tp&, _Up, true, true>
{
	typedef const volatile _Up& type;
};


template <class _Tp, bool = is_integral<_Tp>::value || is_enum<_Tp>::value>
struct __make_signed {};

template <class _Tp>
struct __make_signed<_Tp, true>
{
	/**
	 * 这里 make signed 的方法就是通过 将 _Tp 类型和 __signed_type 中的每一个类型进行 sizeof 的比较，如果它们的 sizeof 
	 * 的大小是相同的，那么相对应的 __signed_type 中的类型，就是我们需要的 signed 的类型
	*/
	typedef typename __find_first<__signed_types, sizeof(_Tp)>::type type;
};
/**
 * 下面是  __make_signed 的针对所有的整数数值类型的特化
 */
template <>	struct __make_signed<bool, true>									{};
template <>	struct __make_signed<unsigned short, true>							{ typedef short type; };
template <>	struct __make_signed<signed short, true>							{ typedef short type; };
template <>	struct __make_signed<unsigned int, true>							{ typedef short type; };
template <>	struct __make_signed<signed int, true>								{ typedef int type; };
template <> struct __make_signed<signed long, true>								{ typedef long type; };
template <> struct __make_signed<unsigned long, true>							{ typedef long type; };
template <> struct __make_signed<signed long long, true>						{ typedef long long type; };
template <> struct __make_signed<unsigned long long, true>						{ typedef long long type; };

template <class _Tp>
struct make_signed
{
	typedef typename __apply_cv<_Tp, typename __make_signed<typename remove_cv<_Tp>::type>::type>::type type;
};

template <class _Tp, bool = is_integral<_Tp>::value || is_enum<_Tp>::value>
struct __make_unsigned {};

template <class _Tp>
struct __make_unsigned<_Tp, true>
{
	/**
	* 这里 make signed 的方法就是通过 将 _Tp 类型和 __signed_type 中的每一个类型进行 sizeof 的比较，如果它们的 sizeof
	* 的大小是相同的，那么相对应的 __signed_type 中的类型，就是我们需要的 signed 的类型
	*/
	typedef typename __find_first<__unsigned_types, sizeof(_Tp)>::type type;
};

template <> struct __make_unsigned<bool, true>					{};
template <> struct __make_unsigned<  signed short, true>		{ typedef unsigned short     type; };
template <> struct __make_unsigned<unsigned short, true>		{ typedef unsigned short     type; };
template <> struct __make_unsigned<  signed int, true>			{ typedef unsigned int       type; };
template <> struct __make_unsigned<unsigned int, true>			{ typedef unsigned int       type; };
template <> struct __make_unsigned<  signed long, true>			{ typedef unsigned long      type; };
template <> struct __make_unsigned<unsigned long, true>			{ typedef unsigned long      type; };
template <> struct __make_unsigned<  signed long long, true>	{ typedef unsigned long long type; };
template <> struct __make_unsigned<unsigned long long, true>	{ typedef unsigned long long type; };

template <class _Tp>
struct make_unsigned
{
	typedef typename __apply_cv<_Tp, typename __make_unsigned<typename remove_cv<_Tp>::type>::type>::type type;
};

// result_of
template <class _Callable> class result_of;
#ifdef _LIBCPP_HAS_NO_VARIADICS
// something about result_of
#endif


// common_type
/**
 * 确定最多三个数据类型的公共数据类型
 */
#ifdef _LIBCPP_HAS_NO_VARIADICS

template <class _Tp, class _Up = void, class V = void>
struct common_type
{
	typedef typename common_type<typename common_type<_Tp, _Up>::type, V>::type type;
};

template <class _Tp>
struct common_type<_Tp, void, void>
{
	typedef _Tp type;
};

template <class _Tp, class _Up>
struct common_type<_Tp, _Up, void>
{
private:
	static _Tp&& __t();
	static _Up&& __u();
public:
	typedef typename remove_reference<decltype(true ? __t() : __u())>::type type;
	/**
	 * 这里使用了一个技巧：
	 * true ? __t() : __u() 涉及到了 ? 运算符的一个特性
	 * ? 运算符中如何 ? 前面的表达式是 true ，那么返回第一个，否则的话，返回第二个
	 * 那么返回值的数据类型如何定义，? 表达式的返回值类型为 :两端的数据的公共类型
	 * 举个例子：
	 * int integer = 100;
	 * double floating = 12.34;
	 * auto temp = (条件表达式 ? integer : floating);
	 * 这里的 temp 数据类型为 double 类型
	 */
};

#else 
template <class ..._Tp> struct common_type;

template <class _Tp>
struct common_type<_Tp>
{
	typedef _Tp type;
};

template <class _Tp, class _Up>
struct common_type<_Tp, _Up>
{
private:
	static _Tp&& __t();
	static _Up&& __u();
	static bool __f();
public:
	typedef typename remove_reference<decltype(__f() ? __t() : __u())>::type type;
	/**
	 * 这里使用了一个技巧：
	 * true ? __t() : __u() 涉及到了 ? 运算符的一个特性
	 * ? 运算符中如何 ? 前面的表达式是 true ，那么返回第一个，否则的话，返回第二个
	 * 那么返回值的数据类型如何定义，? 表达式的返回值类型为 :两端的数据的公共类型
	 * 举个例子：
	 * int integer = 100;
	 * double floating = 12.34;
	 * auto temp = (条件表达式 ? integer : floating);
	 * 这里的 temp 数据类型为 double 类型
	 */
};

template <class _Tp, class _Up, class ..._Vp>
struct common_type<_Tp, _Up, _Vp...>
{
	typedef typename common_type<typename common_type<_Tp, _Up>::type, _Vp...>::type type;
};

#endif

// template <class T> struct is_constructible0

// main is_constructible0 test

#ifdef _LIBCPP_HAS_NO_VARIADICS
template <class _Tp>
decltype((_Tp(), true_type()))
__is_constructible0_test(_Tp&);

false_type
__is_constructible0_test(__any);

template <class _Tp, class _A0>
decltype((_Tp(declval<_A0>()), true_type()))
__is_constructible1_test(_Tp&, _A0&);

template <class _A0>
false_type
__is_constructible1_test(__any, _A0&);

template <class _Tp, class _A0, class _A1>
decltype( (_Tp(declval<_A0>(), declval<_A1>()), true_type()) )
__is_constructible2_test(_Tp&, _A0&, _A1&);

template <class _A0, class _A1>
false_type
__is_constructible2_test(__any, _A0&, _A1&);

template <bool, class _Tp>
struct __is_constructible0_imp
	: public common_type
			<
				decltype(__is_constructible0_test(declval<_Tp&>()))
			>::type
{};

template <bool, class _Tp, class _A0>
struct __is_constructible1_imp
	: public common_type
			<
			decltype(__is_constructible1_test(declval<_Tp&>(), declval<_A0&>()))
			>::type
{};

template <bool, class _Tp, class _A0, class _A1>
struct __is_constructible2_imp
	: public common_type
		<
		decltype(__is_constructible2_test(declval<_Tp&>(), declval<_A0>(), declval<_A1>()))
		>::type {};

template <class _Tp>
struct __is_constructible0_imp<true, _Tp>
	: public is_scalar<_Tp>
	{};

template <class _Tp, class _A0>
struct __is_constructible1_imp<true, _Tp, _A0>
	: public is_convertible<_A0, _Tp>
	{};

template <class _Tp, class _A0, class _A1>
struct __is_constructible2_imp<true, _Tp, _A0, _A1>
	: public false_type
	{};

template <bool, class _Tp>
struct __is_constructible0_void_check
	: public __is_constructible0_imp<is_scalar<_Tp>::value || is_reference<_Tp>::value,
										_Tp>
	{};

template <bool, class _Tp, class _A0>
struct __is_constructible1_void_check
	: public __is_constructible1_imp<is_scalar<_Tp>::value || is_reference<_Tp>::value,
										_Tp, _A0>
	{};

template <bool, class _Tp, class _A0, class _A1>
struct __is_constructible2_void_check
	: public __is_constructible2_imp<is_scalar<_Tp>::value || is_reference<_Tp>::value,
										_Tp, _A0, _A1>
	{};

/**
 * 下面这三种 true 的情况的出现，说明了 _Tp 是void 或者 abstract 或者 function 类型
 * 这些类型自然是无法进行构造的
 */
template <class _Tp>
struct __is_constructible0_void_check<true, _Tp>
	: public false_type {};

template <class _Tp, class _A0>
struct __is_constructible1_void_check<true, _Tp, _A0>
	: public false_type {};

template <class _Tp, class _A0, class _A1>
struct __is_constructible2_void_check<true, _Tp, _A0, _A1>
	: public false_type {};

// is_constructible 入口
namespace __is_construct
{
struct __nat {};
};

template <class _Tp,	class _A0 = __is_construct::__nat,
						class _A1 = __is_construct::__nat>
/**
 * 如何 _Tp 是 void 或者抽象类型或者是函数类型，如果_A0 或者 _A1 是 void 类型
 * 那么 _Tp 就是不可构造的类型
 */
struct is_constructible
	: public __is_constructible2_void_check<is_void<_Tp>::value
										|| is_abstract<_Tp>::value
										|| is_function<_Tp>::value
										|| is_void<_A0>::value
										|| is_void<_A1>::value,
										_Tp, _A0, _A1>
	{};

template <class _Tp>
struct is_constructible<_Tp, __is_construct::__nat, __is_construct::__nat>
	: public __is_constructible0_void_check<is_void<_Tp>::value
										|| is_abstract<_Tp>::value
										|| is_function<_Tp>::value,
										_Tp	>
	{};

template <class _Tp, class _A0>
struct is_constructible<_Tp, _A0, __is_construct::__nat>
	: public __is_constructible1_void_check<is_void<_Tp>::value
										|| is_abstract<_Tp>::value
										|| is_function<_Tp>::value
										|| is_void<_A0>::value,
											_Tp, _A0>
	{};

//数组类型如果其存储的元素的类型是可以构造的，那么这个数组类型就是可以构造的
template <class _Ap, unsigned _Np>
struct __is_constructible0_imp<false, _Ap[_Np]>
	: public is_constructible<typename remove_all_extent<_Ap>::type>
	{};

template <class _Ap, unsigned _Np, class _A0>
struct __is_constructible1_imp<false, _Ap[_Np], _A0>
	: public false_type {};

template <class _Ap, unsigned _Np, class _A0, class _A1>
struct __is_constructible2_imp<false, _Ap[_Np], _A0, _A1>
	: public false_type {};

//非完整声明的数组类型是无法进行构造的
template <class _Ap>
struct __is_constructible0_imp<false, _Ap[]>
	: public false_type {};

template <class _Ap, class _A0, class _A1>
struct __is_constructible2_imp<false, _Ap[], _A0, _A1>
	: public false_type {};

template <class _Ap, class _A0>
struct __is_constructible1_imp<false, _Ap[], _A0>
	: public false_type {};

#else 
template <typename, typename T> struct __select_2nd {	typedef T type; };

template <class _Tp, class ..._Args>
/**
 * 如果 _Tp(declval<_Args>()...)可以解析成功的话，说明了 _Tp 可以使用 _Args 进行初始化
 * 这个函数自然返回的类型为 true_type
 */
typename __select_2nd<decltype(yjh_def::move(_Tp(declval<_Args>()...))), true_type>::type
___is_constructible_test(_Tp&&, _Args&& ...);
/**
 * 如果上面的_Tp(declval<_Args>()...)解析失败的话，那么下面的这个函数模板将会被执行
 * __any 类是一个可以接受任何数据类型进行初始化的类
 */
template <class ..._Args>
false_type
___is_constructible_test(__any, _Args&& ...);

/**
 * 下面的类中 bool 为 true 时，说明 _Tp 类型是 scalar 或者 reference 
 * 为 false 的时候，说明了 _Tp 是 Array 类型的
 */
template <bool, class _Tp, class... _Args>
struct ___is_constructible   // false, _Tp is not a scalar
	: public common_type
		<
			decltype(___is_constructible_test(declval<_Tp>(), declval<_Args>() ...))
		>::type
	{};

// function types are not constructible
// 函数类型是不能进行构建的

template <class _Rp, class... _A1, class... _A2>
struct ___is_constructible<false, _Rp(_A1...), _A2...>
	: public false_type
	{};

//		handle scalars and reference types

//		scalars are default constructible, reference are not
template <class _Tp>
struct ___is_constructible<true, _Tp>
	: public is_scalar<_Tp>
	{};

//      Scalars and references are constructible from one arg if that arg is
//          implicitly convertible to the scalar or reference.
template <class _Tp>
struct ___is_constructible_ref
{
	true_type static __lxx(_Tp);
	false_type static __lxx(...);
};
// _A0 是否可以隐式进行转化 为 _Tp 类型
template <class _Tp, class _A0>
struct ___is_constructible<true, _Tp, _A0>
	: public common_type
		<
			decltype(___is_constructible_ref<_Tp>::__lxx(declval<_A0>()))
		>::type
	{};

//      Scalars and references are not constructible from multiple args.
//	标量值类型无法使用多个参数进行初始化，自然 reference 类型也不可以使用多个参数值
//	进行初始化
template <class _Tp, class _A0, class ..._Args>
struct ___is_constructible<true, _Tp, _A0, _Args...>
	: public false_type {};

//      Treat scalars and reference types separately
// 如果 模板参数的第一个参数 bool 是 true ，说明 _Tp 是一个 void 类型
template <bool, class _Tp, class... _Args>
struct ___is_constructible_void_check
	: public ___is_constructible<is_scalar<_Tp>::value || is_reference<_Tp>::value,
						_Tp, _Args...>
	{};

//      If any of T or Args is void, is_constructible should be false
template <class _Tp, class... _Args>
struct ___is_constructible_void_check<true, _Tp, _Args...>
	: public false_type
	{};

template <class ..._Args>	struct __contains_void;

template <>	struct __contains_void<> : false_type {};

template <class _A0, class ..._Args>
struct __contains_void<_A0, _Args...>
{
	static const bool value = is_void<_A0>::value ||
							__contains_void<_Args...>::value;
};

//      is_constructible entry point
//		is_constructible 入口点

template <class _Tp, class... _Args>
struct is_constructible
	/**
	 * 如果 _Tp, 或者其参数中存在 void 类型，那么这个 _Tp 就不是可构造的
	 * 如果 _Tp 是 一个抽象类，同样的，这个 _Tp 也是没有办法进行构造的
	 */
	: public ___is_constructible_void_check<__contains_void<_Tp, _Args...>::value ||
										is_abstract<_Tp>::value,
										_Tp, _Args...>
	{};

//      Array types are default constructible if their element type
//      is default constructible
//		数组类型被认为是可以构造的，当且仅当其存储的数据类型是可以构造的

template <class _Ap, size_t _Np>
struct ___is_constructible<false, _Ap[_Np]>
	: public is_constructible<typename remove_all_extent<_Ap>::type>
	{};

//      Incomplete array types are not constructible
template <class _Ap, class ..._Args>
struct ___is_constructible<false, _Ap[], _Args...>
	: public false_type
	{};


#endif

// is_default_constructible
template <class _Tp>
struct is_default_constructible
	: public is_constructible<_Tp> {};

// is_copy_constructible
template <class _Tp>
struct is_copy_constructible
	: public is_constructible<_Tp, typename add_lvalue_reference<_Tp>::type> {};

// is_move_constructible
template <class _Tp>
struct is_move_constructible
	: public is_constructible<_Tp, typename add_rvalue_reference<_Tp>::type> {};

// is_trivially_constructible
/**
 * 这里先解释一下什么叫做 trivial ,什么叫 non-trivial 什么叫 POD
 * trivial 和 non-trivial 针对下面的几种函数来说的
 *      构造函数
 *      复制构造函数
 *      赋值函数
 *      析构函数
 * 如果这一些函数至少满足了下面的几条中的一条
 *      显示定义了这四个函数
 *      类里面有非静态的和非POD的数据成员 【POD : plain old data 就是 C++的内建类型或者 C 的结构体类型，这些类型只由一些基本的数据结构构成】
 *      有基类
 * 那么这个函数就是 non-trivial 的
 * trivial 类型的数据在进行拷贝、赋值的时候可以进行优化，因为可以采用直接复制内存中的二进制数据进行赋值，速度快，十分高效
 * non-trivial 类型在进行拷贝、赋值的时候需要调用上述的几种函数，进行相应的操作，效率要比直接的内存的复制慢一些
 * 举个例子：
 * struct data
 * {int a;
 *  int b;}
 * 这个类中只有两个基本的数据类型，没有定义构造、拷贝、析构函数，也没有基类。
 * 所有这个类的实例在进行拷贝的时候，就可以直接进行内存中二进制数据的拷贝就可以了，效率非常的高
 * 
 */
#ifdef _LIBCPP_HAS_NO_VARIADICS
template <class _Tp, 	class _A0 = __is_construct::__nat,
						class _A1 = __is_construct::__nat>
struct is_trivially_constructible
	: false_type {};

template <class _Tp>
struct is_trivially_constructible<_Tp, 	__is_construct::__nat,
										__is_construct::__nat>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_constructible<_Tp, _Tp, __is_construct::__nat>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_constructible<_Tp, _Tp&, __is_construct::__nat>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_constructible<_Tp, const _Tp&, __is_construct::__nat>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

#else

template <class _Tp, class... _Args>
struct is_trivially_constructible
	: integral_constant<bool, __is_trivially_constructible(_Tp, _Args...)>
	{};

#endif

// is_trivially_default_constructible
template <class _Tp>
struct is_trivially_default_constructible
	: public is_trivially_constructible<_Tp>
	{};

// is_trivially_copy_constructible
template <class _Tp>	struct is_trivially_copy_constructible
	: public is_trivially_constructible<_Tp, const typename add_lvalue_reference<_Tp>::value>
	{};

// is_trivially_move_constructible
template <class _Tp>	struct is_trivially_move_constructible
	: public is_trivially_constructible<_Tp, typename add_rvalue_reference<_Tp>::value>
	{};

#if __has_feature(is_trivially_assignable) || _GNUC_VER >=501 //GNUC 的gcc 版本高于 5.0.1
/**
 * 使用编译器的 builtin function 
 */
template <class _Tp, class _Arg>
struct is_trivially_assignable
	: integral_constant<bool, __is_trivially_assignable(_Tp, _Arg)>
{};

#else
// is_trivially_assignable
/**
 * 是否具有平凡的赋值函数
 */
template <class _Tp, class _Arg>
struct is_trivially_assignable
	: public false_type {};

template <class _Tp>
struct is_trivially_assignable<_Tp&, _Tp>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_assignable<_Tp&, _Tp&>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_assignable<_Tp&, const _Tp&>
	: integral_constant<bool, is_scalar<_Tp>::value> {};

template <class _Tp>
struct is_trivially_assignable<_Tp&, _Tp&&>
	: integral_constant<bool, is_scalar<_Tp>::value> {};
#endif


// is_trivially_copy_assignable
template <class _Tp>	struct is_trivially_copy_assignable
	: public is_trivially_assignable<typename add_lvalue_reference<_Tp>::type,
									const typename add_lvalue_reference<_Tp>::value>
	{};

// is_trivially_move_assignable
template <class _Tp>	struct is_trivially_move_assignable
	: public is_trivially_assignable<typename add_lvalue_reference<_Tp>::type,
									typename add_rvalue_reference<_Tp>::type>
	{};

// is_trivially_move_assignable
/**
 * 是否有平凡的析构函数
 */
template <class _Tp>	struct __libcpp_trivial_destructor
	: public integral_constant<bool,	is_scalar<_Tp>::value ||
										is_reference<_Tp>::value> {};

template <class _Tp>	struct is_trivially_destructible
	: public __libcpp_trivial_destructor<typename remove_all_extent<_Tp>::type>
	{};

// is_nothrow_constructible
#ifndef _LIBCPP_HAS_NO_VARIADICS
/**
 * 尚不清楚，问么这里的模板类会报错
 * 使用这种特性的还包括 is_constructible 类
 */
template <bool, class _Tp, class... _Args>	struct ___is_nothrow_constructible;

template <class _Tp, class... _Args>
struct ___is_nothrow_constructible<true, _Tp, _Args...>
	: public integral_constant<bool, noexcept(_Tp(declval<_Args>()...))>
{};

template <class _Tp, class... _Args>
struct ___is_nothrow_constructible<false, _Tp, _Args...>
	: public false_type {};

template <class _Tp, class... _Args>
struct is_nothrow_constructible
	: ___is_nothrow_constructible<is_constructible<_Tp, _Args...>::value, _Tp, _Args...>
	{};


#else
template <class _Tp,	class _A0 = __is_construct::__nat,
						class _A1 = __is_construct::__nat>
struct is_nothrow_constructible
	: false_type {};

template <class _Tp>
struct is_nothrow_constructible<_Tp, __is_construct::__nat,
									__is_construct::__nat>
	: integral_constant<bool, __has_nothrow_constructor(_Tp)>
	{};

template <class _Tp>
struct is_nothrow_constructible<_Tp, _Tp, __is_construct::__nat>
	: integral_constant<bool, __has_nothrow_copy(_Tp)> {};

template <class _Tp>
struct is_nothrow_constructible<_Tp, const _Tp&,
									__is_construct::__nat>
	: integral_constant<bool, __has_nothrow_copy(_Tp)> {};

template <class _Tp>
struct is_nothrow_constructible<_Tp, _Tp&,
									__is_construct::__nat>
	: integral_constant<bool, __has_nothrow_copy(_Tp)> {};

template <class _Tp>
struct is_nothrow_constructible<_Tp, _Tp&&,
									__is_construct::__nat>
	: integral_constant<bool, __has_nothrow_copy(_Tp)> {};

#endif

// is_nothrow_default_constructible
template <class _Tp>	struct is_nothrow_default_constructible
	: public is_nothrow_constructible<_Tp> {};

// is_nothrow_copy_constructible
template <class _Tp>	struct is_nothrow_copy_constructible
	: public is_nothrow_constructible<_Tp, const typename add_lvalue_reference<_Tp>::type>
	{};

// is_nothrow_move_constructible
template <class _Tp>	struct is_nothrow_move_constructible
	: public is_nothrow_constructible<_Tp, typename add_rvalue_reference<_Tp>::type>
	{};


// is_assignable
/**
 * why
 * 为什么可以这样进行实现
 */
template <class _Tp, class _Arg>
decltype((declval<_Tp>() = declval<_Arg>(), true_type()))
__is_assignable_test(_Tp&&, _Arg&&);

template <class _Arg>
false_type
__is_assignable_test(__any, _Arg&&);

template <class _Tp, class _Arg, bool = is_void<_Tp>::value || is_void<_Arg>::value>
struct __is_assignable_imp
	: public common_type<
		decltype(__is_assignable_test(declval<_Tp>(), declval<_Arg>()))
		>::type {};

template <class _Tp, class _Arg>
struct __is_assignable_imp<_Tp, _Arg, true>
	: public false_type {};

template <class _Tp, class _Arg>
struct is_assignable
	: public __is_assignable_imp<_Tp, _Arg> {};

// is_copy_assignable
template <class _Tp>	struct is_copy_assignable
	: public is_assignable<typename add_lvalue_reference<_Tp>::type,
							const typename add_lvalue_reference<_Tp>::type>
	{};

// is_move_assignable
template <class _Tp>	struct is_move_assignable
	: public is_assignable<typename add_lvalue_reference<_Tp>::type,
						const typename add_rvalue_reference<_Tp>::type> {};

// is_nothrow_assignable
template <bool, class _Tp, class _Arg>	struct ___is_nothrow_assignable;

template <class _Tp, class _Arg>
struct ___is_nothrow_assignable<false, _Tp, _Arg>
	: public false_type
	{};

template <class _Tp, class _Arg>
struct ___is_nothrow_assignable<true, _Tp, _Arg>
	: public integral_constant<bool, noexcept(yjh_def::declval<_Tp>() = yjh_def::declval<_Arg>()) >
	{};

template <class _Tp, class _Arg>
struct is_nothrow_assignable
	/**
	 * 先查看 _Tp 是否可以使用 _Arg 进行赋值，如果可以的话，再考虑这个赋值函数是否是无异常的
	 */
	: public ___is_nothrow_assignable<is_assignable<_Tp, _Arg>::value, _Tp, _Arg>
	{};

// is_nothrow_copy_assignable
template <class _Tp>	struct is_nothrow_copy_assignable
	: public is_nothrow_assignable<	typename add_lvalue_reference<_Tp>::type,
									typename add_lvalue_reference<_Tp>::type
								>
	{};

// is_nothrow_move_assignable
template <class _Tp>	struct is_nothrow_move_assignable
	: public is_nothrow_assignable<	typename add_lvalue_reference<_Tp>::type,
									typename add_rvalue_reference<_Tp>::type
								>
	{};



// is_destructible
template <class _Tp>
struct __destructible_test
{
	_Tp __t;
};

template <class _Tp>
/**
 * 调用 __destructible_test的析构函数，就会调用其成员 __t 的析构函数
 * 如何手动调用 ~__destructible_test<_Tp>() 如果可以成功调用 说明 _Tp
 * 的析构函数可以完成调用
 */
decltype((declval<__destructible_test<_Tp> >().~__destructible_test<_Tp>(), true_type()))
__is_destructible_test(_Tp&&);

false_type
__is_destructible_test(__any);

/**
 * 如果 _Tp 类型是 void 或者是 一个抽象类 那么自然无法进行析构
 */
template <class _Tp, bool = is_void<_Tp>::value || is_abstract<_Tp>::value>
struct __destructible_imp
	: public common_type
		<
			decltype(__is_destructible_test(declval<_Tp>()))
		>::type {};

template <class _Tp>
struct __destructible_imp<_Tp, true>
	: public false_type {};

template <class _Tp>
struct is_destructible
	: public __destructible_imp<_Tp> {};

// swap
template <class _Tp>
inline
typename enable_if
<
	is_move_constructible<_Tp>::value &&
	is_move_assignable<_Tp>::value
>::type
swap(_Tp& __x, _Tp& __y) noexcept(	is_nothrow_constructible<_Tp>::value &&
										is_nothrow_move_assignable<_Tp>::value)
{
	_Tp		__t(yjh_def::move(__x));
	__x = 	yjh_def::move(__y);
	__y = 	yjh_def::move(__t);
}

template <class _ForwardIterator1, class _ForwardIterator2>
inline
void
iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
		noexcept(noexcept(swap(*declval<_ForwardIterator1>(), *declval<_ForwardIterator2>())))
{
	swap(*__a, *__b);
}

// __swappable
namespace __detail
{
using yjh_def::swap;
__nat swap(__any, __any);

template <class _Tp>
struct __swappable
{
	typedef decltype(swap(declval<_Tp&>(), declval<_Tp&>())) type;
	static const bool value = !is_same<type, __nat>::value;
};

} //__detail

template <class _Tp>
struct __is_swappable
	: public integral_constant<bool, __detail::__swappable<_Tp>::value>
	{};

template <bool, class _Tp>
struct __is_nothrow_swappable_imp
	: public integral_constant<bool, noexcept(swap(yjh_def::declval<_Tp&>(),
													yjh_def::declval<_Tp&>()))>
	{};

template <class _Tp>
struct __is_nothrow_swappable_imp<false, _Tp>
	: public false_type {};

template <class _Tp>
struct __is_nothrow_swappable
	: public __is_nothrow_swappable_imp<__is_swappable<_Tp>::value, _Tp>
	{};

#ifndef _LIBCPP_HAS_NO_VARIADICS

// check for complete types

template <class ..._Tp>	struct __check_complete;

/**
 * 没有给任何数据类型，那么就不需要判断完整性
 * __check_complete 只提供编译器中数据类型完整性的判定，这个类不进行实际的使用，其没有任何
 * 可以使用的成员变量 或者是函数
 */
template <>
struct __check_complete<>
{};

/**
 * 对于多个参数，则一一检测它们的完整性，这里巧妙的使用继承的方法进行递归式的判断
 */
template <class _Hp, class _T0, class ..._Tp>
struct __check_complete<_Hp, _T0, _Tp...>
	: 	private	__check_complete<_Hp>,
		private __check_complete<_T0, _Tp...>
{};

template <class _Hp>
struct __check_complete<_Hp, _Hp>
	: private __check_complete<_Hp>
{};

/**
 * 对于一个单一的数据类型，其sizeof 如果不大于 0  的话，那么就会认为其不是一个完整的类型
 * static_assert 将会在编译期间报错
 */
template <class _Tp>
struct __check_complete<_Tp>
{
	static_assert(sizeof(_Tp) > 0, "Type must be complete.");
};
/**
 * 引用类型的完整性和其基本类型的完整性是一样的
 */
template <class _Tp>
struct __check_complete<_Tp&>
    : private __check_complete<_Tp>
{
};

template <class _Tp>
struct __check_complete<_Tp&&>
    : private __check_complete<_Tp>
{
};
/**
 * 函数类型，函数指针类型，检查函数的返回值的完整性
 */
template <class _Rp, class ..._Param>
struct __check_complete<_Rp (*)(_Param...)>
    : private __check_complete<_Rp>
{
};

template <class _Rp, class ..._Param>
struct __check_complete<_Rp (_Param...)>
    : private __check_complete<_Rp>
{
};
/**
 * 类的成员函数 的完整性通过检查类的完整性完成
 */
template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...)>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) const>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) volatile>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) const volatile>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) &>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) const&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) volatile&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) const volatile&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) &&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) const&&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) volatile&&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class, class ..._Param>
struct __check_complete<_Rp (_Class::*)(_Param...) const volatile&&>
    : private __check_complete<_Class>
{
};

template <class _Rp, class _Class>
struct __check_complete<_Rp _Class::*>
    : private __check_complete<_Class>
{
};

// __invoke forward declarations
// fall back - none of the bullets

template <class ..._Args>
auto
/**
 * 所有无法正常完成调用的，将会调用这个lambda，返回值的类型是 __nat
 */
__invoke(__any, _Args&& ...__args)
	-> __nat;

// bullets 1 and 2

template <class _Fp, class _A0, class ..._Args>
auto
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    -> decltype((yjh_def::forward<_A0>(__a0).*__f)(yjh_def::forward<_Args>(__args)...));

template <class _Fp, class _A0, class ..._Args>
auto
__invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
    -> decltype(((*yjh_def::forward<_A0>(__a0)).*__f)(yjh_def::forward<_Args>(__args)...));

// bullets 3 and 4

template <class _Fp, class _A0>
auto
__invoke(_Fp&& __f, _A0&& __a0)
    -> decltype(yjh_def::forward<_A0>(__a0).*__f);

template <class _Fp, class _A0>
auto
__invoke(_Fp&& __f, _A0&& __a0)
    -> decltype((*yjh_def::forward<_A0>(__a0)).*__f);

// bullet 5

template <class _Fp, class ..._Args>
auto
__invoke(_Fp&& __f, _Args&& ...__args)
    -> decltype(yjh_def::forward<_Fp>(__f)(yjh_def::forward<_Args>(__args)...));

// __invokable

template <class _Fp, class ..._Args>
struct __invokable_imp
    : private __check_complete<_Fp>
{
    typedef decltype(
            __invoke(yjh_def::declval<_Fp>(), yjh_def::declval<_Args>()...)
                    ) type;	// 该调用的返回值类型	如果无法完成调用，那么这里的type = __nat 类型
    static const bool value = !is_same<type, __nat>::value;	
};

template <class _Fp, class ..._Args>
struct __invokable
    : public integral_constant<bool,
          __invokable_imp<_Fp, _Args...>::value>
{
};

// __invoke_of

/**
 * 如果 _Fp 是不可被调用的，不是一个函数，函数指针或者内的成员函数，那么
 * 我们将没有办法获取其返回值类型
 * 这里构建一个空的类
 */
template <bool _Invokable, class _Fp, class ..._Args>
struct __invoke_of_imp  // false
{
};
/**
 * 如果 _Fp 是可以被调用的，这里的 type 指定调用的返回值类型
 */
template <class _Fp, class ..._Args>
struct __invoke_of_imp<true, _Fp, _Args...>
{
    typedef typename __invokable_imp<_Fp, _Args...>::type type;
};
/**
 * 如果 _Fp 类型不可以使用 _Args 参数进行调用的话，那么编译时期将会抛出异常
 * 可以调用的情况下 type 成员为 _Fp 的返回数据类型
 */
template <class _Fp, class ..._Args>
struct __invoke_of
    : public __invoke_of_imp<__invokable<_Fp, _Args...>::value, _Fp, _Args...>
{
};

template <class _Fp, class ..._Args>
class result_of<_Fp(_Args...)>
    : public __invoke_of<_Fp, _Args...>
{
};

#endif  //_LIBCPP_HAS_NO_VARIADICS

// underlying type
template <class _Tp, bool = is_enum<_Tp>::value> struct __underlying_type_impl;

template <class _Tp>
struct __underlying_type_impl<_Tp, false> {};

template <class _Tp>
struct __underlying_type_impl<_Tp, true>
{
	typedef __underlying_type(_Tp) type;
};

template <class _Tp>
struct underlying_type : __underlying_type_impl<_Tp, is_enum<_Tp>::value> {};

#if _LIBCPP_STD_VER > 11
template <class _Tp> using underlying_type_t = typename underlying_type<_Tp>::type;
#endif


template <class _Tp, bool = is_enum<_Tp>::value>
struct __sfinae_underlying_type
{
    typedef typename underlying_type<_Tp>::type type;
    typedef decltype(((type)1) + 0) __promoted_type;
};

template <class _Tp>
struct __sfinae_underlying_type<_Tp, false> {};

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
int __convert_to_integral(int __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
unsigned __convert_to_integral(unsigned __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
long __convert_to_integral(long __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
unsigned long __convert_to_integral(unsigned long __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
long long __convert_to_integral(long long __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
unsigned long long __convert_to_integral(unsigned long long __val) {return __val; }

template<typename _Fp>
/**
 * 浮点数被转换为 long long 类型的数据
 */
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
typename enable_if<is_floating_point<_Fp>::value, long long>::type
 __convert_to_integral(_Fp __val) { return __val; }

#ifndef _LIBCPP_HAS_NO_INT128
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
__int128_t __convert_to_integral(__int128_t __val) { return __val; }

inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
__uint128_t __convert_to_integral(__uint128_t __val) { return __val; }
#endif

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
typename __sfinae_underlying_type<_Tp>::__promoted_type
__convert_to_integral(_Tp __val) { return __val; }

}
#endif
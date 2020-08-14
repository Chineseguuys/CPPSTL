#include <iostream>

namespace yjh_std{

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


//is_const
template <class _Tp> struct is_const            : public false_type{};
template <class _Tp> struct is_const<_Tp const> : public true_type{};

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
//这里的实现没有考虑 const volatile 等限定符，也没有必要在判定之前除去这些限定符，这样做的原因可以结合上面的 is_integal 的实现对比得出结论
template <class _Tp> struct is_reference			: public false_type {};
template <class _Tp> struct is_reference<_Tp&>		: public true_type {}; 	//& 和 && 是具有完全不同的含义的，不同于 * 与 ** 甚至于与 ***
template <class _Tp> struct is_reference<_Tp&&>		: public true_type {};

//is_class

template <class _Tp> struct __libcpp_union : public false_type {};
template <class _Tp> struct is_union
	: public __libcpp_union<typename remove_cv<_Tp>::type> {};

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
struct __is_function
	: public integral_constant<bool, sizeof(__is_function_imp::__test<_Tp>(__is_function_imp::__source<_Tp>())) == 1> {};
template <class _Tp> struct __is_function<_Tp, true> : public false_type {};

template <class _Tp> struct is_function
	: public __is_function<_Tp> {};

// is_memeber_pointer
template <class _Tp>			struct __is_member_pointer				: public false_type {};
template <class _Tp, class _Up>	struct __is_member_pointer<_Tp _Up::*>	: public true_type {};
 
template <class _Tp> struct	is_member_pointer
	: public __is_member_pointer<typename remove_cv<_Tp>::type> {};

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

// remove_pointer
template <class _Tp>	struct remove_pointer							{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp*>						{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp* const>				{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp* const volatile>		{typedef _Tp type;};
template <class _Tp>	struct remove_pointer<_Tp* volatile>			{typedef _Tp type;};

// add_pointer
template <class _Tp>	struct add_pointer
	{typedef typename remove_reference<_Tp>::type* type;};

// is_arithmetic
/**
 * 可以用于数学计算的只有整数或者是浮点数
 */
template <class _Tp> struct is_arithmetic
	: public integral_constant<bool,	is_integral<_Tp>::value	||
										is_floating_point<_Tp>::value> {};

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
 * 如何 _Tp 是数组类型，则给出 _Tp 在第 N 维度的元素的个数
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

// move
/**
 * 为什么 move 函数要这样进行设计
 */
template <class _Tp>
typename remove_reference<_Tp>::type&&
move(_Tp&& __t)
{
	typedef typename remove_reference<_Tp>::type _Up;
	return static_cast<_Up&&>(__t);
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

//find
template <class _InputIterator, class _Tp>
inline _InputIterator
find(_InputIterator __first, _InputIterator __last, const _Tp& __value_)
{
	for (; __first != __last; ++__first)
		if (*__first == __value_)
			break;
	return __first;
}

// find_if
template <class _InputIterator, class _Predicate>
inline _InputIterator
find_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
{
	for (; __first != __last; ++__first)
		if (__pred(*__first))
			break;
	return __first;
}

// find_if_not
template <class _InputIterator, class _Predicate>
inline _InputIterator find_if_not(_InputIterator __first, _InputIterator __last, _Predicate __pred)
{
	for (; __first != __last; ++__first)
		if(!__pred(*__first))
			break;
	return __first;
}

}


using namespace std;
struct A{};
class B{};
enum class C{};
/** enum class 和 enum
 * enum 具有非常多的局限性，比如，两个 enum 中不能够有相同名字变量，不能存在其他变量名和 enum 中的变量名重复
 * e.g
 * enum Color1{Red, Black, Green};
 * enum Color2{Red, Blue, Peek};
 * 上面的情况是不被允许的，因为 Red 重复定义
 * e.g
 * enum Color{Red, Black, Green};
 * int Green = 12;
 * 上面的情况也不行，因为 Green 重复定义
 * ** 出现上面的原因主要是因为 enum 并不能限定它里面的变量的作用域，并且其变量被设定为 int 类型，所以会和外面的变量冲突
 * 
 * 解决方案： enum class C++ 推荐使用 新的 enum class 关键字，使用 enum class 声明的 enum 对象，具有和 class 相似的作用域
 * 即 enum class 里面的变量对外面不可见，也不允许 enum 变量隐性转换为 int 类型，也不能进行不同的 enum class 之间的比较
 * e.g
 * enum class Color1 {Red, Black, Green};
 * enum class Color2 {Red, Black, Green};
 * int Green = 100;
 * 上面不会发成任何冲突
 * Color1 c1 = Color1::Red;
 * Color2 c2 = Color2::Red;
 * c1 == c2  是不可以直接进行比较的，这样的比较是错误的
 * 
 * note: enum class 不是 class
 */
union S
{
	std::int32_t n;
	std::uint16_t s[2];
	std::uint8_t c;
};

double a_function_example(int _integer, double _floating)
{
	return _floating;
}

class Abstract_Class
{
	virtual void test() = 0;
	virtual ~Abstract_Class() = 0;
};

#define cmd_out std::cout
#include <typeinfo>

int main()
{	
	/*
    yjh_std::integral_constant<int, 100> const_integer1;
    yjh_std::integral_constant<int, 12334> const_integer2;
    cout<<int(const_integer1)<<endl;
    cout<<int(const_integer2)<<endl;

	cout<<std::boolalpha;
    cout<<yjh_std::is_const<int>::value<<endl;  //false
    cout<<yjh_std::is_const<const int>::value<<endl;    //true
    cout<<yjh_std::is_const<const int*>::value<<endl;   //false
    cout<<yjh_std::is_const<int* const>::value<<endl;   //true
    cout<<yjh_std::is_const<const int&>::value<<endl;   //false

	cout<<yjh_std::is_integral<const unsigned int>::value<<endl;	//true
	cout<<yjh_std::is_integral<const double>::value<<endl;		//false

	cout<<yjh_std::is_floating_point<const double>::value<<endl;	//true
	cout<<yjh_std::is_floating_point<const unsigned int*>::value<<endl;		//false

	cout<<yjh_std::is_pointer<const int*>::value<<endl;		//true
	cout<<yjh_std::is_pointer<const int**>::value<<endl;	//true
	cout<<yjh_std::is_pointer<double***>::value<<endl;		//true
	cout<<yjh_std::is_pointer<int>::value<<endl;		//false

	cout<<yjh_std::is_reference<int&>::value<<endl;		//true
	cout<<yjh_std::is_reference<double&&>::value<<endl;		//true
	cout<<yjh_std::is_reference<const int&>::value<<endl;	//true

	cout<<yjh_std::is_class<A>::value<<endl;	//ture
	cout<<yjh_std::is_array<C>::value<<endl;	//false
	cout<<yjh_std::is_class<int>::value<<endl;	//false

	cout<<yjh_std::is_same<const int, const int>::value<<endl;	//true
	cout<<yjh_std::is_same<const int*, int*>::value<<endl;	//false

	cout<<yjh_std::is_function<double(double, int)>::value<<endl;
	cout<<yjh_std::is_function<const int*>::value<<endl;

	cout<<yjh_std::is_abstract<Abstract_Class>::value<<endl;
	cout<<yjh_std::is_abstract<A>::value<<endl;
	*/
	/**
	int integer_a = 2233;
	yjh_std::add_lvalue_reference<const int>::type integer_ref = integer_a;	 //const int& 类型
	cmd_out << typeid(integer_ref).name() << '\n';
	//integer_ref = 2323;
	cmd_out << integer_ref << '\n';
	const std::type_info& type_name = typeid(integer_ref);
	cmd_out << type_name.name() << '\n';
	const std::type_info& type_name_info = typeid(yjh_std::add_pointer<const int*&>::type);
	cmd_out << type_name_info.name() << '\n';
	*/
	/**
	cmd_out << yjh_std::rank<int[10]>::value << "\n";
	cmd_out << yjh_std::rank<int[][5][5]>::value << '\n';
	cmd_out << yjh_std::rank<int[]>::value << '\n';
	*/
	/**
	cmd_out << yjh_std::extent<int[5][10][15], 0>::value << '\n';
	cmd_out << yjh_std::extent<int[5][10][15], 1>::value << '\n';
	cmd_out << yjh_std::extent<int[5][10][15], 2>::value << '\n';
	cmd_out << yjh_std::extent<int[5][10][15], 3>::value << '\n';
	cmd_out << yjh_std::extent<int[][100], 1>::value << '\n';
	*/
	int a[10] {1,2,3,4,5,6,7,8,9,0};
	auto func = yjh_std::for_each(a, a + 10, [](const int& num)->void{cmd_out << num << ' ';});
	cmd_out << '\n';
	func(100);
    return 0;
}
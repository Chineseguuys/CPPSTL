#include <iostream>
#include <type_traits>



template<typename _Tp>
void the_func(_Tp& __p)
{
	typename std::remove_reference_t<_Tp> temp = __p;
	temp = 111;
	std::cout << temp << '\n';
}

template <typename _Tp>
void the_func(_Tp&& __p)
{
	std::cout << "-*-2-*- "<< '\n';
	typename std::remove_reference_t<_Tp> temp = std::move(__p);
	temp = 11111;
	std::cout << temp << '\n';
}

template <typename _Tp>
void is_const_1(typename std::add_lvalue_reference<_Tp>::type __p)
{
	std::cout << std::boolalpha;
	std::cout << "_Tp is const ? " << std::is_const<_Tp>::value << '\n';
	std::cout << "_Tp is reference ? " << std::is_reference<_Tp>::value << '\n';
}

template <typename _Tp>
void is_const(_Tp& __p)
{
	std::cout << std::boolalpha;
	std::cout << "_Tp is const ? " << std::is_const<_Tp>::value << '\n';
	std::cout << "_Tp is reference ? " << std::is_reference<_Tp>::value << '\n';
}
/*
int main()
{
	int integer_1 = 123;
	const int integer_2 = 1314;
	is_const(integer_2);
	is_const_1<const int>(integer_2);
	return 0;
}
*/
#include <typeinfo>
/*
int main(int argc, char** argv)
{
	int num = 100;
	int& num_ref = num;
	int&& rref_num = static_cast<int&&>(num_ref);
	num = 200;
	std::cout << num_ref << '\n';
	std::cout << rref_num << '\n';
	std::cout << typeid(num_ref).name() << '\n';
	std::cout << typeid(rref_num).name() << '\n';
	return 0;
}
*/
//引用转发
template <class _Tp>
void func_forward(_Tp&& x)	// 引用转发不可以有 cv 限定符号
{
	//
}

template <class _Tp>
void g(const _Tp&& x)	//	x 不是转发引⽤：const T 不是⽆ cv 限定的
{}

template<class T> struct A {
template<class U>
A(T&& x, U&& y, int* p); // x 不是转发引⽤：T 不是构造函数的类型模板形参[他是类的模板参数]
// 但 y 是转发引⽤
};
/*
auto&& vec = foo(); // foo() 可以是左值或右值，vec 是转发引⽤
auto i = std::begin(vec); // 也可以
(*i)++; // 也可以
g(std::forward<decltype(vec)>(vec)); // 转发，保持值类别
for (auto&& x: f()) {
// x 是转发引⽤；这是使⽤范围 for 循环的最安全⽅式
}
auto&& z = {1, 2, 3}; // *不是*转发引⽤（初始化器列表的特殊情形）

int main()
{
	int i = 100;
	func_forward(i);
	func_forward(10);
	return 0;
}
*/
//尽管引⽤⼀旦初始化，就始终指代⼀个有效的对象或函数，但有可能创建⼀个程序，被指代对象的⽣存期结束，但引⽤仍保持可访问（悬垂
//（dangling））。访问这种引⽤是未定义⾏为。 ⼀个常见例⼦是返回⾃动变量的引⽤的函数：
std::string& f()
{
std::string s = "Example";
return s; // 退出 s 的作⽤域:
// 调⽤其析构函数并解分配其存储
}
#include <string>
int main()
{
	std::string& r = f(); // 悬垂引⽤
	std::cout << r; // 未定义⾏为：从悬垂引⽤读取
	std::string s = f(); // 未定义⾏为：从悬垂引⽤复制初始化
	return 0;
}
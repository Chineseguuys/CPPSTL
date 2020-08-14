#ifndef _LIBCPP_TYPEINFO
#define _LIBCPP_TYPEINFO

#include "__config.cpp"
#include "exception.cpp"
#include "type_traits.cpp"

namespace yjh_def
{
	/**
	* C++ 关键字 typeid(__x) 会构造这个类， 通过 .name() 成员函数可以得到 __x 的类型的名称
	* 在 gcc 中 type_info 的构造函数被设置为 protected 类型，而在 msvc 中 拷贝构造函数和 operator=(const type_info&) 被设置为 delete
	* 因此这个类无法进行手动构造，只能由  typeid 进行构造，并且是 const type_info 类型；
	* 使用方法：
	* const type_info& type_name_info = typeid(__x);
	* 关键性的问题在于    typeid(__x) 操作符和 sizeof 的性质是一样的，他并不是一个函数
	* 往往自己编写的 type_info 类并不能完成 typeid() 操作符产生的 type_info 到 自己编写的 type_info 的转化
	* 发生这样的错误的类还有 initializer_list : 从 {e1, e2, e3} 到 initializer_list 的转化中
	*/
	class type_info
	{
		type_info& operator=(const type_info&);
		type_info(const type_info&);
	protected:
		const char* __type_name;

			explicit type_info(const char* __n)
			: __type_name(__n) {}

	public:
		virtual ~type_info();

			const char* name() const noexcept { return __type_name; }

			bool before(const type_info& __arg) const noexcept
		{
			return __type_name < __arg.__type_name;
		}


			size_t hash_code() const noexcept
		{
			return *reinterpret_cast<const size_t*>(&__type_name);
		}

			bool operator==(const type_info& __arg) const noexcept
		{
			return __type_name == __arg.__type_name;
		}
			bool operator!=(const type_info& __arg) const noexcept
		{
			return !operator==(__arg);
		}

	};

	class bad_cast
		: public exception
	{
	public:
		bad_cast() noexcept;
		virtual ~bad_cast() noexcept;
		virtual const char* what() const noexcept;
	};

	class bad_typeid
		: public exception
	{
	public:
		bad_typeid() noexcept;
		virtual ~bad_typeid() noexcept;
		virtual const char* what() const noexcept;
	};

}





#endif // !_YJH_TYPEINFO

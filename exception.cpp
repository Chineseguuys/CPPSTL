#ifndef _LIBCPP_EXCEPTION
#define _LIBCPP_EXCEPTION

#include "type_traits.cpp"

namespace yjh_def
{
class exception
{
public:
	exception() noexcept {}
	virtual ~exception() noexcept;
	virtual const char* what() const noexcept;
};

class bad_exception
	: public exception
{
	bad_exception() noexcept {}
	virtual ~bad_exception() noexcept;
	virtual const char* what() const noexcept;
};

typedef void (*unexpected_handler)();
unexpected_handler set_unexpected(unexpected_handler) noexcept;
unexpected_handler get_unexpected() noexcept;
void unexpected();

typedef void (*terminate_handler)();
terminate_handler set_terminate(terminate_handler) noexcept;
terminate_handler get_terminate() noexcept;
void terminate() noexcept;

bool uncaught_exception() noexcept;

class exception_ptr;

exception_ptr current_exception() noexcept;
void rethrow_exception(exception_ptr);

class exception_ptr
{
	void* __ptr_;
public:
	/**
	 * 大部分的函数都没有进行实现
	 */
	exception_ptr() noexcept : __ptr_() {}
	exception_ptr(nullptr_t) noexcept : __ptr_() {}
	exception_ptr(const exception_ptr&) noexcept;
	exception_ptr& operator=(const exception_ptr&) noexcept;
	~exception_ptr() noexcept;

	explicit operator bool() noexcept {return __ptr_ != nullptr;}
	friend bool operator==(const exception_ptr& __x, const exception_ptr& __y) noexcept
		{return __x.__ptr_ == __y.__ptr_;}
	friend bool operator!=(const exception_ptr& __x, const exception_ptr& __y) noexcept
		{return !(__x == __y);}
	
	friend exception_ptr current_exception() noexcept;
	friend void rethrow_exception(exception_ptr);
};

template <class _Ep>
exception_ptr
make_exception_ptr(_Ep __e) noexcept
{
	try
	{
		throw __e;
	}
	catch(...)
	{
		return current_exception();
	}
}

// nested_exception
/**
 * std::nested_exception 是一个多态混入类，可以捕获并存储当前异常，令任意类型的异常彼此间内嵌可行。 
 */
class nested_exception
{
	exception_ptr __ptr_;
public:
	nested_exception() noexcept;
	virtual ~nested_exception() noexcept;

	void rethrow_nested() const;
	exception_ptr nested_ptr() const noexcept {return __ptr_;}
};

template <class _Tp>
struct __nested
	:	public _Tp,
		public nested_exception
{
	explicit __nested(const _Tp& __t) : _Tp(__t) {}
};

template <class _Tp>
void
/**
 * 如果 __t 是一个类的话，并且没有继承 nested_exception 的话，那么调用这个函数
 */ 
throw_with_nested(_Tp&& __t, typename enable_if<
				  is_class<typename remove_reference<_Tp>::type>::value &&
				  !is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
				  >::type* = 0)
{
	throw __nested<typename remove_reference<_Tp>::type>(forward<_Tp>(__t));
}

template <class _Tp>
void
/**
 * 如果 __t 是一个 class 的话，并且其为 nested_exception 的子类的话，那么调用这个函数
 */
throw_with_nested(_Tp&& __t, typename enable_if<
					!is_class<typename remove_reference<_Tp>::type>::value ||
					is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
					>::type* = 0)
{
	throw forward<_Tp>(__t);
}

//rethrow_if_nested
template <class _Ep>
inline void
rethrow_if_nested(const _Ep& __e, typename enable_if<
					is_polymorphic<_Ep>::value
					>::type* = 0)
{
	const nested_exception* __nep = dynamic_cast<const nested_exception*>(&__e);
	if(__nep)
		__nep->rethrow_nested();
}

template <class _Ep>
inline void
rethrow_if_nested(const _Ep&, typename enable_if<
					!is_polymorphic<_Ep>::value
					>::type* = 0)
{}

}



#endif
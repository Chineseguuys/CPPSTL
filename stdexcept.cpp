#ifndef _LIBCPP_STDEXCEPT
#define _LIBCPP_STDEXCEPT

#include "__config.cpp"
#include "exception.cpp"
#include "iosfwd.cpp"       // for string forward decl  string 定义在这个地方

namespace yjh_def
{
/**
 * 逻辑错误
 */
class logic_error
	: public exception
{
private:
	void* __imp_;
public:
	explicit logic_error(const string&);
	explicit logic_error(const char*);

	logic_error(const logic_error&) noexcept;
	logic_error& operator= (const logic_error&) noexcept;

	virtual ~logic_error() noexcept;
	virtual const char* what() const noexcept;
};

/**
 * 运行期间错误
 */
class runtime_error
	: public exception
{
private:
	void* __imp_;
public:
	explicit runtime_error(const string&);
	explicit runtime_error(const char*);

	runtime_error(const runtime_error&) noexcept;
	runtime_error& operator= (const runtime_error&) noexcept;

	virtual ~runtime_error() noexcept;
	virtual const char* what() const noexcept;
};

/** 继承结构
 * exception <== logic_error <== domain_error
 */
class domain_error
	: public logic_error
{
public:
	explicit domain_error(const string& __s) 	: logic_error(__s) {}
	explicit domain_error(const char* __s) 		: logic_error(__s) {}

	virtual ~domain_error() noexcept;
};

/** 继承结构
 * exception <== logic_error <== invalid_argument
 */
class invalid_argument
	: public logic_error
{
public:
	explicit invalid_argument(const string& __s)		: logic_error(__s) {}
	explicit invalid_argument(const char* __s)			: logic_error(__s) {}

	virtual ~invalid_argument() noexcept;
};

/** 继承结构
 * exception <== logic_error <== length_error
 */
class length_error
	: public logic_error
{
public:
	explicit length_error(const string& __s)		: logic_error(__s) {}
	explicit length_error(const char* __s)			: logic_error(__s) {}

	virtual ~length_error() noexcept;
};

/** 继承结构
 * exception <== logic_error <== out_of_range
 */
class out_of_range
	: public logic_error
{
public:
	explicit out_of_range(const string& __s)		: logic_error(__s) {}
	explicit out_of_range(const char* __s)			: logic_error(__s) {}

	virtual ~out_of_range() noexcept;
};


_LIBCPP_NORETURN inline _LIBCPP_INLINE_VISIBILITY
void __throw_length_error(const char* __msg)
{
	#ifndef _LIBCPP_NO_EXCEPTIONS
		throw length_error(__msg);
	#else
		((void)__msg);
		yjh_def::abort();
	#endif
}

_LIBCPP_NORETURN inline _LIBCPP_INLINE_VISIBILITY
void __throw_out_of_range(const char* __msg)
{
	#ifndef _LIBCPP_NO_EXCEPTIONS
		throw out_of_range(__msg);
	#else
		((void)__msg);
		yjh_def::abort();
	#endif
}



}









#endif  //_YJH_STDEXCEPT
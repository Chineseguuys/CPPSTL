#ifndef _YJH_INITIALIZER_LIST
#define _YJH_INITIALIZER_LIST

#include "__config.cpp"

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

namespace yjh_def
{
template <class _Ep>
class initializer_list
{
	const _Ep* __begin_;
	unsigned __size_;

	
	initializer_list(const _Ep* __b, unsigned __s) noexcept
		:	__begin_(__b),
			__size_(__s)
		{}
public:
	typedef _Ep					value_type;
	typedef const _Ep&			reference;
	typedef const _Ep&			const_reference;
	typedef unsigned			size_type;

	typedef const _Ep*			iterator;
	typedef const _Ep*			const_iterator;

	initializer_list() noexcept : __begin_(NULL), __size_(0) {}
	unsigned size() const noexcept {return __size_;}
	const_iterator begin() const noexcept {return __begin_;}
	const_iterator end() const noexcept {return __begin_ + __size_;}
};

template <class _Ep>
inline 
const _Ep* begin(initializer_list<_Ep> __il) noexcept
{
	return __il.begin();
}

template <class _Ep>
inline
const _Ep* end(initializer_list<_Ep> __il) noexcept
{
	return __il.end();
}

}



#endif
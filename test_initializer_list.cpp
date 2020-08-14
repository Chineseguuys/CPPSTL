#include <iostream>
#include <initializer_list>
namespace yjh_def
{
template <class _Ep>
class initializer_list
{
	const _Ep*		__begin_;
	size_t			__size_;

	initializer_list(const _Ep* __b, size_t __s)
		:	__begin_(__b),
			__size_(__s)
		{}
public:
	typedef _Ep						value_type;
	typedef const _Ep&				reference;
	typedef const _Ep&				const_reference;
	typedef size_t					size_type;
	typedef const _Ep*				iterator;
	typedef const _Ep*				const_iterator;

	initializer_list() : __begin_(NULL), __size_(0) {}
	size_t			size() const {return __size_;}
	const _Ep*		begin() const {return __begin_;}
	const _Ep*		end() const {return __begin_ + __size_;}
};

template <class _Ep>
const _Ep*
begin(initializer_list<_Ep> __il)
{
	return __il.begin();
}

template <class _Ep>
const _Ep*
end(initializer_list<_Ep> __il)
{
	return __il.end();
}
}

namespace mscv_std
{
template <class _Elem>
class initializer_list
{
public:
	typedef _Elem				value_type;
	typedef const _Elem&		reference;
	typedef const _Elem&		const_reference;
	typedef size_t				size_type;

	typedef const _Elem*		iterator;
	typedef const _Elem*		const_iterator;

	initializer_list() : _First(0), _Last(0) {}

	initializer_list(const _Elem* _First_arg, const _Elem* _Last_arg)
		: _First(_First_arg), _Last(_Last_arg)
	{}

	const _Elem*	begin() const {return (_First);}
	const _Elem*	end() const {return (_Last);}

	size_t			size() {return ((size_t)(_Last - _First));}
private:
	const _Elem* _First;
	const _Elem* _Last;
};

template <class _Elem>
const _Elem* begin(initializer_list<_Elem> _Ilist)
{
	return (_Ilist.begin());
}

template <class _Elem>
const _Elem* end(initializer_list<_Elem> _Ilist)
{
	return (_Ilist.end());
}
}


void test_yjh(yjh_def::initializer_list<int> il)
{
	for(yjh_def::initializer_list<int>::iterator it = il.begin(); it != il.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<< '\n';
}

void test_mscv(mscv_std::initializer_list<int> il)
{
	for(mscv_std::initializer_list<int>::iterator it = il.begin(); it != il.end(); ++it)
		std::cout<<*it<< " ";
	std::cout<< '\n';
}

void test_std(std::initializer_list<int> il)
{
	for(std::initializer_list<int>::iterator it = il.begin(); it != il.end(); ++it)
		std::cout<< *it << " ";
	std::cout<< '\n';
}


int main()
{
	test_std({1,2,3,4,5,6});
	//test_yjh({1,2,3,4,5,6}); 报错，无法实现
	test_mscv({1,2,3,4,5,6});
	return 0;
}
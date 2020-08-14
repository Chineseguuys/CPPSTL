#ifndef _LIBCPP_ALGORITHM
#define _LIBCPP_ALGORITHM

#include "iterator.cpp"
#include "cstring.cpp"

namespace yjh_def
{
template <class _T1, class _T2 = _T1>
struct __equal_to
{
	bool operator()(const _T1& __x, const _T1& __y) const {return __x ==__y;}
	bool operator()(const _T1& __x, const _T2& __y) const {return __x == __y;}
	bool operator()(const _T2& __x, const _T1& __y) const {return __x == __y;}
	bool operator()(const _T2& __x, const _T2& __y) const {return __x == __y;}
};

template <class _T1>
struct __equal_to<_T1, _T1>
{
	bool operator()(const _T1& __x, const _T1& __y) const {return __x == __y;}
};

template <class _T1>
struct __equal_to<const _T1, _T1>
{
	bool operator()(const _T1& __x, const _T1& __y) const {return __x == __y;}
};

template <class _T1>
struct __equal_to<_T1, const _T1>
{
	bool operator()(const _T1& __x, const _T1& __y) const {return __x == __y;}
};

template <class _Predicate>
class __negate
{
private:
	_Predicate __P_;
public:
	__negate() {}
	__negate(_Predicate __p) : __P_(__p) {}
	
	template <class _T1>
	bool operator()(const _T1& __x) {return !__P_(__x);}

	template <class _T1, class _T2>
	bool operator()(const _T1& __x, const _T2& __y) {return !__P_(__x, __y);}
};

/**
 * 这里给一个 all_of 的可能的使用的实例：
 * std::vector<int> v(10,2);
 * bool all_even = std::all_of(v.begin(), v.end(), [](int& i)->bool {return i % 2 == 0;})
 */
template <class _InputIterator, class _Predicate>
inline bool all_of(_InputIterator __First, _InputIterator __Last, _Predicate __pred)
{
	for(; __First != __Last; ++__First)
		if (!__pred(*__First))
			return false;
	return true;
}

// any_of
template <class _InputIterator, class _Predicate>
inline bool any_of(_InputIterator __First, _InputIterator __Last, _Predicate __Pred)
{
	for (; __First != __Last; ++__First)
		if (__Pred(*__First))
			return true;
	return false;
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

// count
template <class _InputIterator, class _Tp>
inline typename yjh_def::iterator_traits<_InputIterator>::difference_type
count(_InputIterator __first, _InputIterator __last, const _Tp& __value_)
{
	typename yjh_def::iterator_traits<_InputIterator>::difference_type __r(0);
	for (; __first != __last; ++__first)
		if (*__first == __value_)
			++__r;
	return __r;
}

// count_if
template <class _InputIterator, class _Predicate>
inline typename yjh_def::iterator_traits<_InputIterator>::difference_type
count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
{
	typename yjh_def::iterator_traits<_InputIterator>::difference_type __r(0);
	for (; __first != __last; ++__first)
		if (__pred(*__first))
			++__r;
	return __r;
}

//equal
template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
inline bool
equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __pred)
{
	for (; __first1 != __last1; ++__first1, ++__first2)
		if (!__pred(*__first1, *__first2))
			return false;
	return true;
}

template <class _InputIterator1, class _InputIterator2>
inline bool
equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
{
	typedef typename yjh_def::iterator_traits<_InputIterator1>::value_type __v1;
	typedef typename yjh_def::iterator_traits<_InputIterator2>::value_type __v2;
	return equal(__first1, __last1, __first2, __equal_to<__v1, __v2>());
}

// __less
template <class _T1, class _T2 = _T1>
struct __less
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T1& __x, const _T1& __y) const {return __x < __y;}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T1& __x, const _T2& __y) const {return __x < __y;}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T2& __x, const _T1& __y) const {return __x < __y;}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T2& __x, const _T2& __y) const {return __x < __y;}
};

template <class _T1>
struct __less<_T1, _T1>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T1& __x, const _T1& __y) const {return __x < __y;}
};

template <class _T1>
struct __less<const _T1, _T1>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T1& __x, const _T1& __y) const {return __x < __y;}
};

template <class _T1>
struct __less<_T1, const _T1>
{
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    bool operator()(const _T1& __x, const _T1& __y) const {return __x < __y;}
};


// min_element
template <class _ForwardIterator, class _Compare>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
_ForwardIterator
min_element(_ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    static_assert(__is_forward_iterator<_ForwardIterator>::value,
        "std::min_element requires a ForwardIterator");
    if (__first != __last)
    {
        _ForwardIterator __i = __first;
        while (++__i != __last)
            if (__comp(*__i, *__first))
                __first = __i;
    }
    return __first;
}

template <class _ForwardIterator>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
_ForwardIterator
min_element(_ForwardIterator __first, _ForwardIterator __last)
{
    return yjh_def::min_element(__first, __last,
              __less<typename iterator_traits<_ForwardIterator>::value_type>());
}


// min
template <class _Tp, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
const _Tp&
min(const _Tp& __a, const _Tp& __b, _Compare __comp)
{
	return __comp(__b, __a) ? __b : __a;
}

template <class _Tp>
inline
_LIBCPP_INLINE_VISIBILITY
const _Tp&
min (const _Tp& __a, const _Tp& __b)
{
	return yjh_def::min(__a, __b, __less<_Tp>());
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Compare>
inline
_LIBCPP_INLINE_VISIBILITY
_Tp 
min(initializer_list<_Tp> __t, _Compare __comp)
{
	return yjh_def::min_element(__t.begin(), __t.end(), __comp);
}


template<class _Tp>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp
min(initializer_list<_Tp> __t)
{
    return *yjh_def::min_element(__t.begin(), __t.end(), __less<_Tp>());
}


#endif




// max
template <class _Tp, class _Compare>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
const _Tp&
max(const _Tp& __a, const _Tp& __b, _Compare _comp)
{
	return _comp(__a, __b) ? __b : __a;
}

template <class _Tp, class _Compare>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
const _Tp&
max(const _Tp& __a, const _Tp& __b)
{
	return yjh_def::max(__a, __b, __less<_Tp>());
}


// copy
// _unwrap_iter
/**
 * 最一般的情况，后面都是特化的情况
 */
template <class _Iter>
_Iter
__unwrap_iter(_Iter __i)
{
	return __i;
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
typename enable_if
	<
		is_trivially_copy_assignable<_Tp>::value,
		// 为什么要求 _Tp 类型具有平凡的拷贝构造函数呢？
		_Tp*
	>::type
__unwrap_iter(move_iterator<_Tp*> __i)
{
	return __i.base();
}

#if _LIBCPP_DEBUG_LEVEL < 2

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
typename enable_if
	<
		is_trivially_copy_assignable<_Tp>::value,
		_Tp*
	>::type
__unwrap_iter(__wrap_iter<_Tp*> __i)
{
	return __i.base();
}


template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
typename enable_if
	<
		is_trivially_copy_assignable<_Tp>::value,
		const _Tp*
	>::type
__unwrap_iter(__wrap_iter<const _Tp*> __i)
{
	return __i.base();
}

#else

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
typename enable_if
<
    is_trivially_copy_assignable<_Tp>::value,
    __wrap_iter<_Tp*>
>::type
__unwrap_iter(__wrap_iter<_Tp*> __i)
{
    return __i;
}

#endif

// copy
template <class _InputIterator, class _OutputIterator>
inline _LIBCPP_INLINE_VISIBILITY
_OutputIterator
__copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
	for (; __first != __last; ++__first, (void)++__result)
		*__result = *__first;
	return __result;
}

template <class _Tp, class _Up>
inline _LIBCPP_INLINE_VISIBILITY
typename enable_if
	<
		/**
		 * 第一个参数_Tp* 是被复制的对象，所以它有可能是 const 修饰的，但是第二个参数是
		 * 接受的对象，所以其不能是 const
		 * 对象由指针指向的数据结构的赋值，需要_Tp 和 _Up 是完全一样的，这样可以直接进行内存的拷贝
		 */
		is_same<typename remove_const<_Tp>::type, _Up>::value &&
		is_trivially_copy_assignable<_Up>::value,	// 平凡的拷贝构造函数说明，_Up 数据的拷贝可以进行直接的内存拷贝来完成
		// 不会出现一些可能的依赖问题
		_Up*
	>::type
__copy(_Tp* __first, _Tp* __last, _Up* __result)
{
	const size_t __n = static_cast<size_t>(__last - __first);
	if(__n > 0 )
		yjh_def::memmove(__result, __first, __n * sizeof(_Up));
	return __result + __n;	// 返回指向数据的末尾的指针
}

template <class _InputIterator, class _OutputIterator>
inline _LIBCPP_INLINE_VISIBILITY
_OutputIterator
copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
	return yjh_def::__copy(__unwrap_iter(__first), __unwrap_iter(__last),
				__unwrap_iter(__result));
}


// move
template <class _InputIterator, class _OutputIterator>
inline _LIBCPP_INLINE_VISIBILITY
_OutputIterator
__move(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    for (; __first != __last; ++__first, (void) ++__result)
        *__result = yjh_def::move(*__first);
    return __result;
}

template <class _Tp, class _Up>
inline _LIBCPP_INLINE_VISIBILITY
typename enable_if
<
    is_same<typename remove_const<_Tp>::type, _Up>::value &&
    is_trivially_copy_assignable<_Up>::value,
    _Up*
>::type
__move(_Tp* __first, _Tp* __last, _Up* __result)
{
    const size_t __n = static_cast<size_t>(__last - __first);
    if (__n > 0)
        yjh_def::memmove(__result, __first, __n * sizeof(_Up));	// C 的函数，将一段内存复制到另一段内存
    return __result + __n; // 返回尾部的指针
}

template <class _InputIterator, class _OutputIterator>
inline _LIBCPP_INLINE_VISIBILITY
_OutputIterator
move(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    return yjh_def::__move(__unwrap_iter(__first), __unwrap_iter(__last), __unwrap_iter(__result));
}

// move_backward
template <class _InputIterator, class _OutputIterator>
inline _LIBCPP_INLINE_VISIBILITY
_OutputIterator 
/**
 * 反向移动赋值
 */
__move_backward(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
	while(__first != __last)
		*--__result = yjh_def::move(*--__last);
	return __result;
}

template <class _Tp, class _Up>
inline _LIBCPP_INLINE_VISIBILITY
typename enable_if
<
    is_same<typename remove_const<_Tp>::type, _Up>::value &&
    is_trivially_copy_assignable<_Up>::value,
    _Up*
>::type
__move_backward(_Tp* __first, _Tp* __last, _Up* __result)
{
    const size_t __n = static_cast<size_t>(__last - __first);
    if (__n > 0)
    {
        __result -= __n;
        yjh_def::memmove(__result, __first, __n * sizeof(_Up));
    }
    return __result;
}

template <class _BidirectionalIterator1, class _BidirectionalIterator2>
inline _LIBCPP_INLINE_VISIBILITY
_BidirectionalIterator2
move_backward(_BidirectionalIterator1 __first, _BidirectionalIterator1 __last,
              _BidirectionalIterator2 __result)
{
    return yjh_def::__move_backward(__unwrap_iter(__first), 
			__unwrap_iter(__last), 
			__unwrap_iter(__result)
		);
}

// fill_n 
template <class _OutputIterator, class _Size, class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
_OutputIterator
__fill_n(_OutputIterator __first, _Size __n, const _Tp& __value_)
{
    for (; __n > 0; ++__first, (void) --__n)
        *__first = __value_;
    return __first;
}

template <class _OutputIterator, class _Size, class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
_OutputIterator
fill_n(_OutputIterator __first, _Size __n, const _Tp& __value_)
{
   return yjh_def::__fill_n(__first, __convert_to_integral(__n), __value_);
}

// fill 
/**
 * fill 对 不同的迭代器分开进行处理
 * 前向迭代器由于无法使用 - 直接计算元素的个数，
 * 随机迭代器可以是用 + - 运算符，可以直接计算出需要拷贝的元素的个数
 */
template <class _ForwardIterator, class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
void
__fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value_, forward_iterator_tag)
{
    for (; __first != __last; ++__first)
        *__first = __value_;
}

template <class _RandomAccessIterator, class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
void
__fill(_RandomAccessIterator __first, _RandomAccessIterator __last, const _Tp& __value_, random_access_iterator_tag)
{
    yjh_def::fill_n(__first, __last - __first, __value_);
}

template <class _ForwardIterator, class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
void
fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value_)
{
    yjh_def::__fill(__first, __last, __value_, typename iterator_traits<_ForwardIterator>::iterator_category());
}

// __comp_ref_type  
template <class _Comp>
struct __comp_ref_type
{
	#ifndef _LIBCPP_DEBUG
		typedef typename add_lvalue_reference<_Comp>::type type;
	#else
		// something else
	#endif
};

// lexicographical_compare
template <class _Compare, class _InputIterator1, class _InputIterator2>
_LIBCPP_CONSTEXPR_AFTER_CXX17 bool 
__lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
					_InputIterator2 __first2, _InputIterator2 __last2,
					_Compare __comp)
{
	for (; __first2 != __last2; ++__first1, (void)++__first2)
	{
		if (__first1 == __last1 || __comp(*__first1, * __first2))
			return true;
		if (__comp(*__first2, *__first1))
			return false;
	}
	return false;
}

template <class _InputIterator1, class _InputIterator2, class _Compare>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
bool
lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                        _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
{
    typedef typename __comp_ref_type<_Compare>::type _Comp_ref;
    return __lexicographical_compare<_Comp_ref>(__first1, __last1, __first2, __last2, __comp);
}

template <class _InputIterator1, class _InputIterator2>
_LIBCPP_NODISCARD_EXT inline
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
bool
lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                        _InputIterator2 __first2, _InputIterator2 __last2)
{
    return yjh_def::lexicographical_compare(__first1, __last1, __first2, __last2,
                                         __less<typename iterator_traits<_InputIterator1>::value_type,
                                                typename iterator_traits<_InputIterator2>::value_type>());
}

} // namespace yjh_def


#endif
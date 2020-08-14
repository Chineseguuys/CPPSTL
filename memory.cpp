#ifndef _LIBCPP_MEMORY
#define _LIBCPP_MEMORY

#include "__config.cpp"
#include "type_traits.cpp"
#include <typeinfo>	// 配合 typeid() 使用 	
// error : must #include <typeinfo> before using typeid
#include "cstdint.cpp"
#include "new.cpp"
#include "utility.cpp"
#include "limits.cpp"
#include "iterator.cpp"
#include "iosfwd.cpp"
#include "cstring.cpp"
#include "__functional_base.cpp"
#include "tuple.cpp"

#ifdef min
#undef min
#endif // min

#ifdef max
#undef max
#endif // max

/**
 * 这里目前定义了下面这些：
 * pointer_tratis : 指针的一个统一的接口
 * allocator 内存分配器
 * 
*/
namespace yjh_def
{

/**
template <class _Tp>
inline
_Tp*
addressof(_Tp& __x) noexcept
{
	return (_Tp*)&(char&)__x;
}
*/

// allocator
template <class _Tp> class allocator;

template <>
class allocator<void>
{
public:
	typedef void*			pointer;
	typedef const void*		const_pointer;
	typedef void			value_type;

	template <class _Up> struct rebind { typedef allocator<_Up> other; };
};

template <>
class allocator<const void>
{
public:
	typedef const void*				pointer;
	typedef const void*				const_pointer;
	typedef const void				value_type;

	template <class _Up>	struct rebind { typedef allocator<_Up> other; };
};

// pointer_traits
template <class _Tp>
/**
 * 查看一个类是否有 element_type 这个成员变量
*/
struct __has_element_type
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up>	__two __test(...);
	template <class _Up>	static char __test(typename _Up::element_type* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Ptr, bool = __has_element_type<_Ptr>::value>
struct __pointer_traits_element_type;

template <class _Ptr>
struct __pointer_traits_element_type<_Ptr, true>
{
	typedef typename _Ptr::element_type type;
};

#ifndef _YJH_HAS_NO_VARIADICS
/**
 * 对于多参数的 class 要返回 element_type 使用这个类
*/
template <template <class, class...> class _Sp, class _Tp, class ..._Args>
struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, true>
{
	typedef typename _Sp<_Tp, _Args...>::element_type type;
};

template <template <class, class...> class _Sp, class _Tp, class ..._Args>
struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, false>
{
	typedef _Tp type;
};



#else

// 这里的不会被编译

#endif // !_YJH_HAS_NO_VARIADICS

// __has_difference_type
template <class _Tp>
struct __has_difference_type
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up>	static __two __test(...);
	template <class _Up>	static char __test(typename _Up::difference_type* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

// __pointer_traits_difference_type
/**
 * 如果 _Ptr 拥有自己的 difference_type 的话，那么这个类的 type 就是这个类型
 * 否则的话 将 ptrdiff_t 指定为 type
 */
template <class _Ptr, bool = __has_difference_type<_Ptr>::value>
struct __pointer_traits_difference_type
{
	typedef yjh_def::ptrdiff_t type;
};

template <class _Ptr>
struct __pointer_traits_difference_type<_Ptr, true>
{
	typedef typename _Ptr::difference_type type;
};

template <class _Tp, class _Up>
struct __has_rebind
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Xp> static __two __test(...);
	/**
	 * 注意这里的写法，rebind<> 是模板类中的模板类，使用 _Xp::template 说明其为模板类 _Xp 中的 一个模板类
	 * 当然也可以用来指代模板函数
	*/
	template <class _Xp> static char __test(typename _Xp::template rebind<_Up>* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Tp, class _Up, bool = __has_rebind<_Tp, _Up>::value>
struct __pointer_traits_rebind
{
	typedef typename _Tp::template rebind<_Up>::other type;
	/**
	 * _Tp::template rebind<_Up> 表示的意思是
	 *  调用 _Tp 类中带模版参数的成员函数或者 成员变量 rebind<_Up>
	*/
};

#ifndef _YJH_HAS_NO_VARIADICS
/**
 * 模版参数的嵌套
 * 这个模板类是上面的模板类的一个特化
*/
template <template <class, class...> class _Sp, class _Tp, class ..._Args, class _Up>
struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, true>
{
	typedef typename _Sp<_Tp, _Args...>::template rebind<_Up>::other type;
};

/**
 * 如果 _Sp 类型没有 rebind 那么 type 设定为自身
*/
template <template <class, class...> class _Sp, class _Tp, class ..._Args, class _Up>
struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, false>
{
	typedef _Sp<_Tp, _Args...> type;
};

#else
// 这里的内容不会被编译

#endif // !_YJH_HAS_NO_VARIADICS

// pointer_traits
template <class _Ptr>
struct pointer_traits
{
	typedef _Ptr														pointer;
	typedef typename __pointer_traits_element_type<pointer>::type		element_type;
	typedef typename __pointer_traits_difference_type<pointer>::type	difference_type;

	template <class _Up>	struct rebind
	{
		typedef typename __pointer_traits_rebind<pointer, _Up>::type other;
	};

private:
	struct __nat {};
public:
	static pointer pointer_to(typename conditional<is_void<element_type>::value,
										__nat, element_type>::type& __r)
	{
		return pointer::pointer_to(__r);
	}
};

/**
 * pointer_traits 对于指针类型的特化
 */
template <class _Tp>
struct pointer_traits<_Tp*>
{
	typedef _Tp*				pointer;
	typedef _Tp					element_type;
	typedef yjh_def::ptrdiff_t	difference_type;

	template <class _Up>	struct rebind { typedef _Up* other; };

private:
	struct __nat {};
public:
	static pointer pointer_to (typename conditional< is_void<element_type>::value,
										__nat, element_type>::type& __r) noexcept
	{
		return yjh_def::addressof(__r);
	}
};

template <class _From, class _To>
struct __rebind_pointer
{
    typedef typename pointer_traits<_From>::template rebind<_To>::other type;
};


// allocator_traits

namespace __has_pointer_type_imp
{
	/**
	* 查看一个类是否有 pointer 这个成员
	*/
	template <class _Up> static __two test(...);
	template <class _Up> static char test(typename _Up::pointer* = 0);
}

template <class _Tp>
struct __has_pointer_type
	: public integral_constant<bool, sizeof(__has_pointer_type_imp::test<_Tp>(0)) == 1>
{};

namespace __pointer_type_imp
{
template <class _Tp, class _Dp, bool = __has_pointer_type<_Dp>::value>
struct __pointer_type
{
	typedef typename _Dp::pointer type;
};

template <class _Tp, class _Dp>
struct __pointer_type<_Tp, _Dp, false>
{
	typedef _Tp* type;
};

}  // __pointer_type_imp

template <class _Tp, class _Up>
struct __pointer_type
{
	typedef typename __pointer_type_imp::__pointer_type<_Tp, typename remove_reference<_Up>::type>::type type;
};

template <class _Tp>
/**
* 查看类中是否有 const_pointer 成员
*/
struct __has_const_pointer
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::const_pointer* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Tp, class _Ptr, class _Alloc, bool = __has_const_pointer<_Alloc>::value>
struct __const_pointer
{
	typedef typename _Alloc::const_pointer type;
};

template <class _Tp, class _Ptr, class _Alloc>
struct __const_pointer<_Tp, _Ptr, _Alloc, false>
{
	typedef typename pointer_traits<_Ptr>::template rebind<const _Tp>::other type;
};

// __has_void_pointer
template <class _Tp>
struct __has_void_pointer
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::void_pointer* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};


template <class _Ptr, class _Alloc, bool = __has_void_pointer<_Alloc>::value>
struct __void_pointer
{
	typedef typename _Alloc::void_pointer type;
};

template <class _Ptr, class _Alloc>
struct __void_pointer<_Ptr, _Alloc, false>
{
	typedef typename pointer_traits<_Ptr>::template rebind<void>::other type;
};

// __has_const_void_pointer
template <class _Tp>
struct __has_const_void_pointer
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::const_void_pointer* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Ptr, class _Alloc, bool = __has_const_void_pointer<_Alloc>::value>
struct __const_void_pointer
{
	typedef typename _Alloc::const_void_pointer type;
};

template <class _Ptr, class _Alloc>
struct __const_void_pointer<_Ptr, _Alloc, false>
{
	typedef typename pointer_traits<_Ptr>::template rebind<const void>::other type;
};

template <class _Tp>
inline
_Tp* __to_raw_pointer(_Tp* __p) noexcept
{
	return __p;
}

template <class _Pointer>
typename pointer_traits<_Pointer>::element_type*
/**
* 获取 _Pointer 类型的原始的指针类型数据
*/
__to_raw_pointer(_Pointer __p)
{
	return yjh_def::__to_raw_pointer(__p.operator->());
}

// __has_size_type
template <class _Tp>
/**
* 和上面的 __has_element_type 以及 _has_difference_type 的实现是同样的原理
*/
struct __has_size_type
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::size_type* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Alloc, class _DiffType, bool = __has_size_type<_Alloc>::value>
struct __size_type
{
	/**
	 * 从 unsigned char/short/int/long/long long/ 中找到 和 _DiffType 相对应的数据类型
	 * 下面的这一行代码会在 __has_size_typ<_Alloc> 为 false 的时候执行
	*/
	typedef typename make_unsigned<_DiffType>::type type;
};

template <class _Alloc, class _DiffType>
struct __size_type<_Alloc, _DiffType, true>
{
	typedef typename _Alloc::size_type type;
};

// __has_propagate_on_container_copy_assignment
template <class _Tp>
struct __has_propagate_on_container_copy_assignment
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::propagate_on_container_copy_assignment* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Alloc, bool = __has_propagate_on_container_copy_assignment<_Alloc>::value>
struct __propagate_on_container_copy_assignment
{
	typedef false_type type;
};

template <class _Alloc>
struct __propagate_on_container_copy_assignment<_Alloc, true>
{
	typedef typename _Alloc::propagate_on_container_copy_assignment type;
};

// __has_propagate_on_container_move_assignment
template <class _Tp>
struct __has_propagate_on_container_move_assignment
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::propagate_on_container_move_assignment* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Alloc, bool = __has_propagate_on_container_move_assignment<_Alloc>::value>
struct __propagate_on_container_move_assignment
{
	typedef false_type type;
};

template <class _Alloc>
struct __propagate_on_container_move_assignment<_Alloc, true>
{
	typedef typename _Alloc::propagate_on_container_move_assignment type;
};

// __has_propagate_on_container_swap
template <class _Tp>
struct __has_propagate_on_container_swap
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Up> static __two __test(...);
	template <class _Up> static char __test(typename _Up::propagate_on_container_swap* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Alloc, bool = __has_propagate_on_container_swap<_Alloc>::value>
struct __propagate_on_container_swap
{
	typedef false_type type;
};

template <class _Alloc>
struct __propagate_on_container_swap<_Alloc, true>
{
	typedef typename _Alloc::propagate_on_container_swap type;
};

// __is_always_equal  
template<class _Tp, class = void>
struct __has_is_always_equal : false_type {};

template <class _Tp>
struct __has_is_always_equal<_Tp,
			typename __void_t<typename _Tp::is_always_equal>::type>
	: true_type {};

template <class _Alloc, bool = __has_is_always_equal<_Alloc>::value>
struct __is_always_equal
{
	typedef _LIBCPP_NODEBUG_TYPE typename yjh_def::is_empty<_Alloc>::type type;
};

template <class _Alloc>
struct __is_always_equal<_Alloc, true>
{
	typedef typename _Alloc::is_always_equal type;
};

// __has_rebind_other
template <class _Tp, class _Up, bool = __has_rebind<_Tp, _Up>::value>
struct __has_rebind_other
{
private:
	struct __two { char __lx; char __lxx; };
	template <class _Xp> static __two __test(...);
	template <class _Xp> static char __test(typename _Xp::template rebind<_Up>::other* = 0);
public:
	static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Tp, class _Up>
struct __has_rebind_other<_Tp, _Up, false>
{
	static const bool value = false;
};

template <class _Tp, class _Up, bool = __has_rebind_other<_Tp, _Up>::value>
struct __allocator_traits_rebind
{
	typedef typename _Tp::template rebind<_Up>::other type;
};

#ifndef _YJH_HAS_NO_VARIADICS

template <template <class, class...> class _Alloc, class _Tp, class ..._Args, class _Up>
struct __allocator_traits_rebind<_Alloc<_Tp, _Args...>, _Up, true>
{
	typedef typename _Alloc<_Tp, _Args...>::template rebind<_Up>::other type;
};

template <template <class, class...> class _Alloc, class _Tp, class ..._Args, class _Up>
struct __allocator_traits_rebind<_Alloc<_Tp, _Args...>, _Up, false>
{
	typedef _Alloc<_Up, _Args...> type;
};
#endif // !_YJH_HAS_NO_VARIADICS

#ifndef _YJH_HAS_NO_ADVANCED_SFINAE
/**
* auto lambda_func(int __a, int __b) -> int { return __a * __b; }
* 这是 定义 lambda 表达式的一种方法
* 另一种方法就是：
* auto lambda_func = [](int __a, int __b) ->int { return __a * __b;};   //注意这里的 ; 不可以省略
* 注意无处不在的引用转发
*/
template <class _Alloc, class _SizeType, class _ConstVoidPtr>
auto
__has_allocate_hint_test(_Alloc&& __a, _SizeType&& __sz, _ConstVoidPtr&& __p)
-> decltype(__a.allocate(__sz, __p), true_type());

template <class _Alloc, class _SizeType, class _ConstVoidPtr>
auto
__has_allocate_hint_test(const _Alloc& __a, _SizeType&& __sz, _ConstVoidPtr&& __p)
->false_type;

template <class _Alloc, class _SizeType, class _ConstVoidPtr>
struct __has_allocate_hint
	: integral_constant<bool,
	is_same<
	decltype(__has_allocate_hint_test(declval<_Alloc>(),
		declval<_SizeType>(),
		declval<_ConstVoidPtr>())),
	true_type>::value>
{
};

#endif // !_YJH_HAS_NO_ADVANCED_SFINAE
/**
 * 为什么这里使用 _Tp* 下面使用 _Pointer

*/
template <class _Alloc, class _Tp, class ..._Args>
decltype(yjh_def::declval<_Alloc>().construct(	yjh_def::declval<_Tp*>(),
												yjh_def::declval<_Args>()...),
												true_type())
__has_construct_test(_Alloc&& __a, _Tp* __p, _Args&& ..._args);

template <class _Alloc, class _Pointer, class ..._Args>
false_type
/**
* 如果上面的 decltype 里面的内容编译器解析失败，那么下面的这个函数会被执行
*/
__has_construct_test(const _Alloc& __a, _Pointer&& __p, _Args&& ...__args);

template <class _Alloc, class _Pointer, class ..._Args>
struct __has_construct
	: integral_constant<bool,
	is_same<
	decltype(__has_construct_test(declval<_Alloc>(), declval<_Pointer>(), declval<_Args>()...)), true_type>::value>
{};

template <class _Alloc, class _Pointer>
auto
__has_destroy_test(const _Alloc& __a, _Pointer&& __p)
-> decltype(__a.destroy(__p), true_type());

template <class _Alloc, class _Pointer>
auto
__has_destroy_test(const _Alloc& __a, _Pointer&& __p)
->false_type;

template <class _Alloc, class _Pointer>
struct __has_destroy
	: integral_constant<bool,
	is_same<
	decltype(__has_destroy_test(declval<_Alloc>(),
		declval<_Pointer>())),
	true_type>::value>
{};

template <class _Alloc>
auto
__has_max_size_test(_Alloc&& __a)
-> decltype(__a.max_size(), true_type());

template <class _Alloc>
auto
__has_max_size_test(const volatile _Alloc& __a)
->false_type;

template <class _Alloc>
struct __has_max_size
	: integral_constant<bool,
	is_same<
	decltype(__has_max_size_test(declval<_Alloc&>())),
	true_type>::value>
{
};

template <class _Alloc>
auto
/**
 * 如果 __a 没有 select_on_container_copy_construction() 这个函数，这个 lambda 函数
 * 就会解析失败，那么将要执行后面的一个函数模板
*/
__has_select_on_container_copy_construction_test(_Alloc&& __a)
-> decltype(__a.select_on_container_copy_construction(), true_type());

template <class _Alloc>
auto
__has_select_on_container_copy_construction_test(const volatile _Alloc& __a)
->false_type;

template <class _Alloc>
/**
 * 测试 _Alloc 是否有 select_on_constainer_copy_construction 函数
*/
struct __has_select_on_container_copy_construction
	: integral_constant<bool,
	is_same<
	decltype(__has_select_on_container_copy_construction_test(declval<_Alloc&>())),
	true_type>::value>
{
};

template <class _Alloc, class _Ptr, bool = __has_difference_type<_Alloc>::value>
struct __alloc_traits_difference_type
{
	typedef typename pointer_traits<_Ptr>::difference_type type;
};

template <class _Alloc, class _Ptr>
struct __alloc_traits_difference_type<_Alloc, _Ptr, true>
{
	typedef typename _Alloc::difference_type type;
};

template <class _Tp>
struct __is_default_allocator : false_type {};

template <class _Tp>
struct __is_default_allocator<yjh_def::allocator<_Tp> > : true_type {};


// allocator_traits
template <class _Alloc>
struct allocator_traits
{
	typedef _Alloc									allocator_type;
	typedef typename allocator_type::value_type		value_type;
	/**
	 * 如果 _Alloc 具有类型 pointer ， 那么这里的  pointer 就是 _Alloc.pointer
	 * 如果 _Alloc 没有类型 pointer , 那么这里的 pointer 被定义为 value_type* 类型
	*/
	typedef typename __pointer_type<value_type, allocator_type>::type			pointer;
	typedef typename __const_pointer<value_type, pointer, allocator_type>::type	const_pointer;
	typedef typename __void_pointer<pointer, allocator_type>::type				void_pointer;
	typedef typename __const_void_pointer<pointer, allocator_type>::type		const_void_pointer;
	
	typedef typename __alloc_traits_difference_type<allocator_type, pointer>::type		difference_type;
	typedef typename __size_type<allocator_type, difference_type>::type					size_type;
	
	typedef typename __propagate_on_container_copy_assignment<allocator_type>::type
		propagate_on_container_copy_assignment;
	typedef typename __propagate_on_container_move_assignment<allocator_type>::type
		propagate_on_container_move_assignment;
	typedef typename __propagate_on_container_swap<allocator_type>::type
		propagate_on_container_swap;
	/**
	 * template<> using 的用法	
	*/
	template <class _Tp> using rebind_alloc =
			typename __allocator_traits_rebind<allocator_type, _Tp>::type;
	template <class _Tp> using rebind_traits = allocator_traits<rebind_alloc<_Tp>>;

	typedef typename __is_always_equal<allocator_type>::type	is_always_equal;

	/**
	 * 使用分配器分配未初始化的内存
	 * 如果 allocator_type 有自己的 allocate 函数
	*/
	static pointer allocate(allocator_type& __a, size_type __n)
	{
		return __a.allocate(__n);
	}

	static pointer allocate(allocator_type& __a, size_type __n, const_void_pointer __hint)
	{
		return allocate(__a, __n, __hint, __has_allocate_hint<allocator_type, size_type, const_void_pointer>());
	}

	static void deallocate(allocator_type& __a, pointer __p, size_type __n)
	{
		__a.deallocator(__p, __n);
	}

	/**
	 * 使用 __args 的这些参数对 __p 进行初始化
	*/
	template <class _Tp, class ..._Args>
	static void construct(allocator_type& __a, _Tp* __p, _Args&&... __args)
	{
		__construct(__has_construct<allocator_type, pointer, _Args...>(),
			__a, __p, forward<_Args>(__args)...);
	}

	template <class _Tp>
	static void destroy(allocator_type& __a, _Tp* __p)
	{
		__destroy(__has_destroy<allocator_type, _Tp*>(), __a, __p);
	}

	static allocator_type
		select_on_container_copy_construction(const allocator_type& __a)
	{
		return select_on_container_copy_construction(
			__has_select_on_container_copy_construction<const allocator_type>(),
			__a
		);
	}

    template <class _Ptr>
    _LIBCPP_INLINE_VISIBILITY
    static
    void
    __construct_forward_with_exception_guarantees(allocator_type& __a, _Ptr __begin1, _Ptr __end1, _Ptr& __begin2)
    {
        //static_assert(__is_cpp17_move_insertable<allocator_type>::value,
          //"The specified type does not meet the requirements of Cpp17MoveInsertible");
        for (; __begin1 != __end1; ++__begin1, (void) ++__begin2)
            construct(__a, yjh_def::__to_raw_pointer(__begin2),
#ifdef _LIBCPP_NO_EXCEPTIONS
            yjh_def::move(*__begin1)
#else
            yjh_def::move_if_noexcept(*__begin1)
#endif
        	);
        }

    template <class _Tp>
    _LIBCPP_INLINE_VISIBILITY
    static
    typename enable_if
        <
            (__is_default_allocator<allocator_type>::value
            || !__has_construct<allocator_type, _Tp*, _Tp>::value) &&
            is_trivially_move_constructible<_Tp>::value,
            void
        >::type
    __construct_forward_with_exception_guarantees(allocator_type&, _Tp* __begin1, _Tp* __end1, _Tp*& __begin2)
    {
        ptrdiff_t _Np = __end1 - __begin1;
        if (_Np > 0)
        {
            yjh_def::memcpy(__begin2, __begin1, _Np * sizeof(_Tp));
            __begin2 += _Np;
        }
    }



	template <class _Ptr>
	_LIBCPP_INLINE_VISIBILITY
	static void
	__construct_backward_with_exception_guarantees(allocator_type& __a,
				_Ptr __begin1, _Ptr __end1,
				_Ptr& __end2)
	{
		while (__end1 != __begin1)
		{
			construct(__a, yjh_def::__to_raw_pointer(__end2 - 1),
		#ifdef _LIBCPP_NO_EXCEPTIONS
			yjh_def::move(*--__end1);
		#else
			yjh_def::move_if_noexcept(*--__end1)
		#endif
			);
			--__end2;
		}
	}

    template <class _Tp>
    _LIBCPP_INLINE_VISIBILITY
    static
    typename enable_if
        <
            (__is_default_allocator<allocator_type>::value
                || !__has_construct<allocator_type, _Tp*, _Tp>::value) &&
             is_trivially_move_constructible<_Tp>::value,
            void
        >::type
    __construct_backward_with_exception_guarantees(allocator_type&, _Tp* __begin1, _Tp* __end1, _Tp*& __end2)
    {
        ptrdiff_t _Np = __end1 - __begin1;
        __end2 -= _Np;
        if (_Np > 0)
            yjh_def::memcpy(__end2, __begin1, _Np * sizeof(_Tp));
    }


	template <class _Ptr>
	static void
	/**
	 * 拷贝构造
	*/
		__construct_forward(allocator_type& __a, _Ptr __begin1, _Ptr __end1, _Ptr __begin2)
	{
		for (; __begin1 != __end1; ++__begin1, ++__begin2)
		{
			construct(__a, yjh_def::__to_raw_pointer(__begin2), yjh_def::move_if_noexcept(*__begin1));
		}
	}

	template <class _Tp>
	static
		typename enable_if
		<
			(is_same<allocator_type, allocator<_Tp> >::value
				|| !__has_construct<allocator_type, _Tp*, _Tp>::value) &&
			is_trivially_move_constructible<_Tp>::value,
			void
		>::type 

		__construct_forward(allocator_type& __a, _Tp* __begin1, _Tp* __end1, _Tp*& __begin2)
	{
		/**
		 * 从 _begin1 的位置开始，拷贝_Np*sizeof(_Tp)个字节的内存内容到 _begin2 开始的内存空间当中
		 */
		ptrdiff_t _Np = __end1 - __begin1;
		yjh_def::memcpy(__begin2, __begin1, _Np * sizeof(_Tp));
	}

	static size_type max_size(const allocator_type& __a)
	{
		return __max_size(__has_max_size<const allocator_type>(), __a);
	}

private:
	static pointer allocate(allocator_type& __a, size_type __n,
		const_void_pointer __hint, true_type)
	{
		return __a.allocate(__n, __hint);
	}

	static pointer allocate(allocator_type& __a, size_type __n,
		const_void_pointer, false_type)
	{
		return __a.allocate(__n);
	}

#ifndef _YJH_HAS_NO_VARIADICS
	template <class _Tp, class ..._Args>
	static void __construct(true_type, allocator_type& __a, _Tp* __p, _Args&&... __args)
	{
		__a.construct(__p, yjh_def::forward<_Args>(__args)...);
	}
	/**
	 * 说明了 __a 没有 construct,那么就使用 new 运算符进行手动的构造
	 * __p 是一块原始的没有经过构造的内存
	*/
	template <class _Tp, class ..._Args>
	static void __construct(false_type, allocator_type& __a, _Tp* __p, _Args&&... __args)
	{
		::new ((void*)__p) _Tp(yjh_def::forward<_Args>(__args)...);
	}

#endif // _YJH_HAS_NO_VARIADICS
	template <class _Tp>
	static void __destroy(true_type, allocator_type& __a, _Tp* __p)
	{
		__a.destroy(__p);
	}
	/**
	 * 如果 allocator_type 没有 destroy 就需要手都进行析构
	*/
	template <class _Tp>
	static void __destroy(false_type, allocator_type&, _Tp* __p)
	{
		__p->~_Tp();
	}

	static size_type __max_size(true_type, const allocator_type& __a)
	{
		return __a.max_size();
	}

	static size_type __max_size(false_type, const allocator_type&)
	{
		return numeric_limits<size_type>::max();
	}

	static allocator_type 
		select_on_container_copy_construction(true_type, const allocator_type& __a)
	{
		return __a.select_on_container_copy_construction();
	}

	static allocator_type
		select_on_container_copy_construction(false_type, const allocator_type& __a)
	{
		return __a;
	}
};

// __rebind_alloc_helper
template <class _Traits, class _Tp>
struct __rebind_alloc_helper
{
	typedef typename _Traits::template rebind_alloc<_Tp>::other type;
};


// allocator
/**
 * 举个使用的例子 : string* p = allocator<string>().allocate(5);
*/
template <class _Tp>
class allocator
{
public:
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
	typedef _Tp*			pointer;
	typedef const _Tp*		const_pointer;
	typedef _Tp&			reference;
	typedef const _Tp&		const_reference;
	typedef _Tp				value_type;
	/**
	* 若在使用 A 类型的分配器的容器被移动赋值时需要移动该分配器，则为 true。
	* 若此成员是 false 且源和目标容器的分配器比较不相等，则移动赋值不能夺取源内存的所有权，而必须逐个进行元素的移动赋值或移动构造，
	* 按需调整其自身内存的大小
	*
	* 这个是一个可选的选项，未必要提供这个变量
	*/
	typedef true_type	propagate_on_container_move_assignment;

	template <class _Up> struct rebind { typedef allocator<_Up> other; };

	allocator() noexcept {}

	template <class _Up>
	allocator(const allocator<_Up>&) noexcept {}

	pointer address(reference __x) noexcept
	{
		return yjh_def::addressof(__x);
	}

	pointer address(const_reference __x) noexcept
	{
		return yjh_def::addressof(__x);
	}

	pointer allocate(size_type __n, allocator<void>::const_pointer = 0)
	{
		/**
		 * operator new () 运算符返回一段空的内存，不进行任何的初始化
		*/
		return static_cast<pointer>(::operator new(__n * sizeof(_Tp)));
	}

	void deallocate(pointer __p, size_type) noexcept
	{
		::operator delete((void*)__p);
	}

	size_type max_size() const noexcept	 // 可以传递给 allocate() 函数的 __n 参数的最大值
	{
		return size_type(~0) / sizeof(_Tp);			// 0 = 0x000000000  ~0 = 0xffffffff
	}

	template <class _Up, class..._Args>
	void
		construct(_Up* __p, _Args&&... __args)
	{
		::new((void*)__p) _Up(yjh_def::forward<_Args>(__args)...);
	}
	/**
	 * 使用 operator new 开辟的 原始内存，需要显式调用其中存储的类的析构函数进行析构
	*/
	void destroy(pointer __p) { __p->~_Tp(); }
};


template <class _Tp>
/**
 * allocator 负责分配和回收原始内存，它并不关注分配的内存用于什么数据形式
 */
class allocator<const _Tp>
{
public:
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef const _Tp*			pointer;
	typedef const _Tp*			const_pointer;
	typedef const _Tp&			reference;
	typedef const _Tp&			const_reference;

	typedef true_type		propagate_on_container_move_assignment;
	allocator() noexcept {}
	
	template <class _Up>
	allocator(const allocator<_Up>&) noexcept {}

	const_pointer address(const_reference __x) const noexcept
	{
		return yjh_def::addressof(__x);
	}

	pointer allocate(size_type __n, allocator<void>::const_pointer = 0)
	{
		return static_cast<pointer>(::operator new(__n * sizeof(_Tp)));
	}

	void deallocate(pointer __p, size_type) noexcept
	{
		::operator delete((void*)__p);
	}

	size_type max_size() const noexcept
	{
		return size_type(~0) / sizeof(_Tp);
	}

	template <class _Up, class ..._Args>
	void
	construct(_Up* __p, _Args&&... __args)
	{
		::new((void*)__p) _Up(yjh_def::forward<_Args>(__args)...);
	}

	void destroy(pointer __p) { __p->~_Tp(); }
};

/**
 * 为什么这你要设置为 true 呢
*/
template <class _Tp, class _Up>
inline
bool operator == (const allocator<_Tp>&, const allocator<_Up>&) noexcept
{
	return true;
}

template <class _Tp, class _Up>
inline
bool operator != (const allocator<_Tp>&, const allocator<_Up>&) noexcept
{
	return false;
}

template <class _OutputIterator, class _Tp>
class raw_storage_iterator
	: public iterator
	<
		output_iterator_tag,
		_Tp,
		ptrdiff_t,
		_Tp*,
		raw_storage_iterator<_OutputIterator, _Tp>&
	>
{
private:
	_OutputIterator __x_;
public:
	raw_storage_iterator(_OutputIterator __x) : __x_(__x) {}
	raw_storage_iterator& operator*() { return *this; }
	raw_storage_iterator& operator=(const _Tp& __element)
	{
		::new(&*__x_) _Tp(__element);
		return *this;
	}

	raw_storage_iterator& operator++() { ++__x_; return *this; }	//前置 ++
	raw_storage_iterator operator++(int)		// 后置 ++
	{
		raw_storage_iterator __t(*this);
		++__x_;
		return __t;
	}
};

template <class _Tp>
pair<_Tp*, ptrdiff_t>
get_temporary_buffer(ptrdiff_t __n) noexcept
{
	pair<_Tp*, ptrdiff_t> __r(0, 0);
	/**
	 * 下令这个式子的意义是什么？
	 * ~ptrdiff_t(0) = 0xffffffff
	 * ptrdiff_t(1) = 0x00000001
	 * ptrdiff_t(1) << (sizeof(ptrdiff_t) * __CHAR_BIT__ -1) = 0x80000000
	 * ~ptrdiff_t(0) ^ (ptrdiff_t(1) << (sizeof(ptrdiff_t) * __CHAR_BIT__ -1)) = 0xffffffff ^ 0x80000000 = 0x7fffffff
	 * 这个值正好是 ptrdiff_t 的正数值的最大值
	 * operator new() 中接受的参数不可以大于这个数值，所以_Tp 的个数不能超过 0x7fffffff / sizeof(_Tp)
	 */
	const ptrdiff_t __m = (~ptrdiff_t(0) ^
		ptrdiff_t(ptrdiff_t(1) << (sizeof(ptrdiff_t) * __CHAR_BIT__ - 1)))
		/ sizeof(_Tp);
	
	if (__n > __m)
		__n = __m;
	while (__n > 0)
	{
		__r.first = static_cast<_Tp*>(::operator new(__n * sizeof(_Tp), nothrow));	// 这里的 onthrow 定义在何处
		if (__r.first)
		{
			__r.second = __n;
			break;
		}
		__n /= 2;	// 如果内存的分配失败了，可能是因为 __n 实在太大了，系统无法开辟这么大的内存空间，这个时候尝试将申请的空间
		//减小一半
		// 因为有这个机制在，所以上面的 operator new() 不允许以抛出异常的形式返回
	}
	return __r;
}

template <class _Tp>
inline
void return_temporary_buffer(_Tp* __p) noexcept { ::operator delete(__p); }

template <class _Tp>
struct auto_ptr_ref
{
	_Tp* __ptr_;
};

// 智能指针  smart pointer
// auto_ptr
template <class _Tp>
/**
 * 现在 auto_ptr 用的很少，现在用的比较多的是 shared_ptr, unique_ptr
 * auto_ptr 在向另一个 auto_ptr 进行赋值或者拷贝的时候，会释放自身所持有的指针，并把指针交出
*/
class auto_ptr
{
private:
	_Tp* __ptr_;
public:
	typedef _Tp element_type;

	explicit auto_ptr(_Tp* __p = 0) throw() : __ptr_(__p) {}	// __p 是使用 new 进行分配的内存
	auto_ptr(auto_ptr& __p) throw() : __ptr_(__p.release()) {}
	template <class _Up>
	auto_ptr(auto_ptr<_Up>& __p) throw()
		: __ptr_(__p.release()) {}

	auto_ptr& operator=(auto_ptr& __p) throw()
	{
		reset(__p.release());
		return *this;
	}

	template <class _Up>
	auto_ptr& operator=(auto_ptr<_Up>& __p) throw()
	{
		reset(__p.release());
		return *this;
	}

	auto_ptr& operator=(auto_ptr_ref<_Tp> __p) throw()
	{
		reset(__p.__ptr_);
		return *this;
	}

	~auto_ptr() throw() { delete __ptr_; }
	_Tp*	operator*() const throw() { return *__ptr_; }
	_Tp*	operator->() const throw() { return __ptr_; }
	_Tp*	get()	const throw() { return __ptr_; }
	_Tp*	release() throw()	// 交出对指针的控制权
	{
		_Tp* __t = __ptr_;
		__ptr_ = 0;
		return __t;
	}
	/**
	 * 释放当前的指针
	 * 并接收新的指针
	 */
	void reset(_Tp* __p = 0) throw()
	{
		if (__ptr_ != __p)
			delete __ptr_;
		__ptr_ = __p;
	}

	auto_ptr(auto_ptr_ref<_Tp> __p) throw() : __ptr_(__p.__ptr_) {}
	template <class _Up>
	/**
	 * 重载类型转换运算符
	 * auto_ptr ans(new int(10));
	 * auto_ptr_ref<int> res = auto_ptr_ref<int>(ans);
	 * 查看 test_operator_type.cpp 详情
	*/
	operator auto_ptr_ref<_Up>() throw()
	{
		auto_ptr_ref<_Up> __t;
		__t.__ptr_ = release();
		return __t;
	}

	template <class _Up>
	operator auto_ptr<_Up>() throw()
	{
		return auto_ptr<_Up>(release());
	}
};

template <>
class auto_ptr<void>
{
public:
	typedef void element_type;
};

template <	class _T1, class _T2,
			bool = is_same<typename remove_cv<_T1>::type,
			typename remove_cv<_T2>::type>::value,
			bool = is_empty<_T1>::value,
			bool = is_empty<_T2>::value
>
struct __libcpp_compressed_pair_switch;

template <class _T1, class _T2, bool IsSame>
struct __libcpp_compressed_pair_switch<_T1, _T2, IsSame, false, false> { enum { value = 0 }; };

template <class _T1, class _T2, bool IsSame>
struct __libcpp_compressed_pair_switch<_T1, _T2, IsSame, true, false> { enum { value = 1 }; };

template <class _T1, class _T2, bool IsSame>
struct __libcpp_compressed_pair_switch<_T1, _T2, IsSame, false, true> { enum { value = 2 }; };

template <class _T1, class _T2>
struct __libcpp_compressed_pair_switch<_T1, _T2, false, true, true> { enum { value = 3 }; };

template <class _T1, class _T2>
struct __libcpp_compressed_pair_switch<_T1, _T2, true, true, true> { enum { value = 1 }; };

template <	class _T1, class _T2,
			unsigned = __libcpp_compressed_pair_switch<_T1, _T2>::value
>
class __libcpp_compressed_pair_imp;

template <class _T1, class _T2>
/**
 * _T1 和 _T2 都不是空类
 * 但是 _T1 和 _T2 不一定是相同的类型
*/
class __libcpp_compressed_pair_imp<_T1, _T2, 0>
{
private:
	_T1 __first_;
	_T2 __second_;
public:
	typedef _T1 _T1_param;
	typedef _T2 _T2_param;

	typedef typename remove_reference<_T1>::type& _T1_reference;
	typedef typename remove_reference<_T2>::type& _T2_reference;

	typedef const typename remove_reference<_T1>::type& _T1_const_reference;
	typedef const typename remove_reference<_T2>::type& _T2_const_reference;

	__libcpp_compressed_pair_imp() {}
	explicit __libcpp_compressed_pair_imp(_T1_param __t1)
		: __first_(yjh_def::forward<_T1_param>(__t1)) {}
	explicit __libcpp_compressed_pair_imp(_T2_param __t1)
		: __second_(yjh_def::forward<_T2_param>(__t1)) {}

	explicit __libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
		:	__first_(yjh_def::forward<_T1_param>(__t1)),
			__second_(yjh_def::forward<_T2_param>(__t2)){}

#ifdef _YJH_HAS_NO_DEFAULTED_FUNCTIONS

		__libcpp_compressed_pair_imp(const __libcpp_compressed_pair_imp& __p)
		noexcept(is_nothrow_copy_constructible<_T1>::value &&
			is_nothrow_copy_constructible<_T2>::value)
		: __first_(__p.first()),
		__second_(__p.second()) {}

		__libcpp_compressed_pair_imp& operator=(const __libcpp_compressed_pair_imp& __p)
		noexcept(is_nothrow_copy_assignable<_T1>::value &&
			is_nothrow_copy_assignable<_T2>::value)
	{
		__first_ = __p.first();
		__second_ = __p.second();
		return *this;
	}

#ifndef _YJH_HAS_NO_RVALUE_REFERENCES

		__libcpp_compressed_pair_imp(__libcpp_compressed_pair_imp&& __p)
		noexcept(is_nothrow_move_constructible<_T1>::value &&
			is_nothrow_move_constructible<_T2>::value)
		: __first_(yjh_def::forward<_T1>(__p.first())),
		__second_(yjh_def::forward<_T2>(__p.second())) {}

			__libcpp_compressed_pair_imp& operator=(__libcpp_compressed_pair_imp&& __p)
		noexcept(is_nothrow_move_assignable<_T1>::value &&
			is_nothrow_move_assignable<_T2>::value)
	{
		__first_ = yjh_def::forward<_T1>(__p.first());
		__second_ = yjh_def::forward<_T2>(__p.second());
		return *this;
	}

#ifndef _LIBCPP_HAS_NO_VARIADICS

	template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
		__libcpp_compressed_pair_imp(piecewise_construct_t __pc,
			tuple<_Args1...> __first_args,
			tuple<_Args2...> __second_args,
			__tuple_indices<_I1...>,
			__tuple_indices<_I2...>)
		: __first_(yjh_def::forward<_Args1>(get<_I1>(__first_args))...),
		__second_(yjh_def::forward<_Args2>(get<_I2>(__second_args))...)
	{}

#endif  // _YJH_HAS_NO_VARIADICS

#endif  // _YJH_HAS_NO_RVALUE_REFERENCES

#endif  // _YJH_HAS_NO_DEFAULTED_FUNCTIONS

	_T1_reference			first() noexcept		{ return __first_; }
	_T1_const_reference		first() const noexcept	{ return __first_; }
	_T2_reference			second() noexcept		{ return __second_; }
	_T2_const_reference		second() const noexcept { return __second_; }


	void swap(__libcpp_compressed_pair_imp& __x)
		noexcept(	__is_nothrow_swappable<_T1>::value &&
					__is_nothrow_swappable<_T2>::value)
	{
		using yjh_def::swap;
		swap(__first_, __x.__first_);
		swap(__second_, __x.__second_);
	}
};

template <class _T1, class _T2>
/**
 * _T1 是空类， _T2 是非空类
 * 或者两个都是空类，并且是同一个类
*/
class __libcpp_compressed_pair_imp<_T1, _T2, 1>
	: private _T1
{
private:
	_T2 __second_;
public:
	typedef _T1 _T1_param;
	typedef _T2 _T2_param;

	typedef _T1&											_T1_reference;
	typedef typename remove_reference<_T2>::type&			_T2_reference;
	typedef const _T1&										_T1_const_reference;
	typedef const typename remove_reference<_T2>::type&		_T2_const_reference;

	__libcpp_compressed_pair_imp() {}
	explicit __libcpp_compressed_pair_imp(_T1_param __t1)
		: _T1(yjh_def::forward<_T1_param>(__t1)) {}

	explicit __libcpp_compressed_pair_imp(_T2_param __t2)
		: __second_(yjh_def::forward<_T2_param>(__t2)) {}

	__libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
		: _T1(yjh_def::forward<_T1_param>(__t1)),
		__second_(yjh_def::forward<_T2_param>(__t2)) {}


	_T1_reference				first() noexcept			{ return *this; }
	_T1_const_reference			first() const noexcept		{ return *this; }

	_T2_reference				second() noexcept			{ return __second_; }
	_T2_const_reference			second() const noexcept		{ return __second_; }

	void swap(__libcpp_compressed_pair_imp& __x)
		noexcept(__is_nothrow_swappable<_T1>::value &&
			__is_nothrow_swappable<_T2>::value)
	{
		using yjh_def::swap;
		swap(__second_, __x.__second_);
	}

};

template <class _T1, class _T2>
/**
 * _T1 不是一个空类，但是 _T2 是一个空类
*/
class __libcpp_compressed_pair_imp<_T1, _T2, 2>
	: private _T2
{
private:
	_T1 __first_;
public:
	typedef _T1 _T1_param;
	typedef _T2 _T2_param;

	typedef typename remove_reference<_T1>::type&		_T1_reference;
	typedef _T2&                                        _T2_reference;

	typedef const typename remove_reference<_T1>::type&			_T1_const_reference;
	typedef const _T2&											_T2_const_reference;

	__libcpp_compressed_pair_imp() {}
	explicit __libcpp_compressed_pair_imp(_T1_param __t1)
		: __first_(yjh_def::forward<_T1_param>(__t1)) {}
	explicit __libcpp_compressed_pair_imp(_T2_param __t2)
		: _T2(yjh_def::forward<_T2_param>(__t2)) {}
	__libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
		noexcept(is_nothrow_move_constructible<_T1>::value &&
			is_nothrow_move_constructible<_T2>::value)
		: _T2(yjh_def::forward<_T2_param>(__t2)), __first_(yjh_def::forward<_T1_param>(__t1)) {}


	_T1_reference       first() noexcept { return __first_; }
	_T1_const_reference first() const noexcept { return __first_; }

	_T2_reference       second() noexcept { return *this; }
	_T2_const_reference second() const noexcept { return *this; }

	void swap(__libcpp_compressed_pair_imp& __x)
		noexcept(__is_nothrow_swappable<_T1>::value &&
			__is_nothrow_swappable<_T1>::value)
	{
		using yjh_def::swap;
		swap(__first_, __x.__first_);
	}
};

template <class _T1, class _T2>
/**
 * _T1 和 _T2 都是 空类
*/
class __libcpp_compressed_pair_imp<_T1, _T2, 3>
	:	private _T1,
		private _T2
{
public:
	typedef _T1 _T1_param;
	typedef _T2 _T2_param;

	typedef _T1&	_T1_reference;
	typedef _T2&	_T2_reference;

	typedef const _T1&		_T1_const_reference;
	typedef const _T2&		_T2_const_reference;

	__libcpp_compressed_pair_imp() {}
	explicit __libcpp_compressed_pair_imp(_T1_param __t1)
		: _T1(yjh_def::forward<_T1_param>(__t1)) {}
	explicit __libcpp_compressed_pair_imp(_T2_param __t2)
		: _T2(yjh_def::forward<_T2_param>(__t2)) {}
	__libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
		: _T1(yjh_def::forward<_T1_param>(__t1)), _T2(yjh_def::forward<_T2_param>(__t2)) {}


	 _T1_reference       first() noexcept { return *this; }
	 _T1_const_reference first() const noexcept { return *this; }

	 _T2_reference       second() noexcept { return *this; }
	 _T2_const_reference second() const noexcept { return *this; }

	 void swap(__libcpp_compressed_pair_imp&)
		noexcept(__is_nothrow_swappable<_T1>::value &&
			__is_nothrow_swappable<_T1>::value)
	{
	}
};

// __compressed_pair
template <class _T1, class _T2>
class __compressed_pair
	: private __libcpp_compressed_pair_imp<_T1, _T2>
{
	typedef __libcpp_compressed_pair_imp<_T1, _T2> base;
public:
	typedef typename base::_T1_param _T1_param;
	typedef typename base::_T2_param _T2_param;

	typedef typename base::_T1_reference _T1_reference;
	typedef typename base::_T2_reference _T2_reference;

	typedef typename base::_T1_const_reference _T1_const_reference;
	typedef typename base::_T2_const_reference _T2_const_reference;

	__compressed_pair() {}
	explicit __compressed_pair(_T1_param __t1)
		: base(yjh_def::forward<_T1_param>(__t1)) {}
	explicit __compressed_pair(_T2_param __t2)
		: base(yjh_def::forward<_T2_param>(__t2)) {}
	__compressed_pair(_T1_param __t1, _T2_param __t2)
		: base(yjh_def::forward<_T1_param>(__t1), yjh_def::forward<_T2_param>(__t2)) {}

#ifdef _YJH_HAS_NO_DEFAULTED_FUNCTIONS

		__compressed_pair(const __compressed_pair& __p)
		noexcept(is_nothrow_copy_constructible<_T1>::value &&
			is_nothrow_copy_constructible<_T2>::value)
		: base(__p) {}

		__compressed_pair& operator=(const __compressed_pair& __p)
		noexcept(is_nothrow_copy_assignable<_T1>::value &&
			is_nothrow_copy_assignable<_T2>::value)
	{
		base::operator=(__p);
		return *this;
	}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
		__compressed_pair(__compressed_pair&& __p)
		noexcept(is_nothrow_move_constructible<_T1>::value &&
			is_nothrow_move_constructible<_T2>::value)
		: base(yjh_def::move(__p)) {}

		__compressed_pair& operator=(__compressed_pair&& __p)
		noexcept(is_nothrow_move_assignable<_T1>::value &&
			is_nothrow_move_assignable<_T2>::value)
	{
		base::operator=(yjh_def::move(__p));
		return *this;
	}

#ifndef _LIBCPP_HAS_NO_VARIADICS

	template <class... _Args1, class... _Args2>
		__compressed_pair(piecewise_construct_t __pc, tuple<_Args1...> __first_args,
			tuple<_Args2...> __second_args)
		: base(__pc, yjh_def::move(__first_args), yjh_def::move(__second_args),
			typename __make_tuple_indices<sizeof...(_Args1)>::type(),
			typename __make_tuple_indices<sizeof...(_Args2) >::type())
	{}

#endif  // _LIBCPP_HAS_NO_VARIADICS

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

#endif  // _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

	_T1_reference       first() noexcept { return base::first(); }
	_T1_const_reference first() const noexcept { return base::first(); }

	_T2_reference       second() noexcept { return base::second(); }
	_T2_const_reference second() const noexcept { return base::second(); }

	void swap(__compressed_pair& __x)
		noexcept(	__is_nothrow_swappable<_T1>::value &&
					__is_nothrow_swappable<_T2>::value)
	{
		base::swap(__x);
	}
};

template <class _T1, class _T2>
inline
void swap(__compressed_pair<_T1, _T2>& __x, __compressed_pair<_T1, _T2>& __y)
noexcept(
		__is_nothrow_swappable<_T1>::value &&
		__is_nothrow_swappable<_T2>::value
		)
{
	__x.swap(__y);
}

// __same_or_less_cv_qualified

template <class _Ptr1, class _Ptr2,
	bool = is_same<
		typename remove_cv<typename pointer_traits<_Ptr1>::element_type>::type,
		typename remove_cv<typename pointer_traits<_Ptr2>::element_type>::type
	>::value
>
struct __same_or_less_cv_qualified_imp
	/**
	 * 相同的类型不一定可以进行转化，比如 const int 不能简单转化为 int
	 * 被 cv 限定符限定的类型，不可以之间转化为 没有被限定的类型
	 * 但是 int* const 可以转化为 int
	*/
	/**
	 * 只有当两个类是同一个类，并且没有 cv 限定符的限制
	*/
	: is_convertible<_Ptr1, _Ptr2> {};

template <class _Ptr1, class _Ptr2>
struct __same_or_less_cv_qualified_imp<_Ptr1, _Ptr2, false>
	: false_type {};

template <class _Ptr1, class _Ptr2, bool = is_scalar<_Ptr1>::value &&
	!is_pointer<_Ptr1>::value
>
struct __same_or_less_cv_qualified
	: __same_or_less_cv_qualified_imp<_Ptr1, _Ptr2> {};

template <class _Ptr1, class _Ptr2>
struct __same_or_less_cv_qualified<_Ptr1, _Ptr2, true>
	: false_type {};

// default delete
/**
 * 删除器的功能十分的简单，就是释放指针的内存
 */
template <class _Tp>
struct default_delete
{
#ifndef YJH_HAS_NO_DEFAULT_FUNCTIONS
	default_delete() noexcept = default;
#else
	default_delete() noexcept {}
#endif // !YJH_HAS_NO_DEFAULT_FUNCTIONS

template <class _Up>
default_delete(const default_delete<_Up>&,
	typename enable_if<is_convertible<_Up*, _Tp*>::value>::type* = 0) noexcept {}

void operator() (_Tp* __ptr) const noexcept
{
	static_assert(sizeof(_Tp) > 0, "default_delete can not delete incomplete type");
	delete __ptr;
}
};

template <class _Tp>
struct default_delete<_Tp[]>
{
public:
#ifndef YJH_HAS_NO_DEFAULT_FUNCTIONS
	default_delete() noexcept = default;
#else
	default_delete() noexcept {}
#endif // !YJH_HAS_NO_DEFAULT_FUNCTIONS

template <class _Up>
default_delete(const default_delete<_Up[]>&,
	typename enable_if<__same_or_less_cv_qualified<_Up*, _Tp*>::value>::type* = 0)
	noexcept
{}

template <class _Up>
void operator() (_Up* __ptr,
	typename enable_if<__same_or_less_cv_qualified<_Up*, _Tp*>::value>::type* = 0)
	const noexcept
{
	static_assert(sizeof(_Tp) > 0, "default_delete can not delete incomplete type");
	delete[] __ptr;
}
};

// unique_ptr
// 这里针对的是  operator new 操作符
// 紧接这个类后面的是一个针对 operator new[] 的特化版本
template <class _Tp, class _Dp = default_delete<_Tp> >
/**
 * 默认的删除器，对智能指针管理的内存进行释放，
 * 可以自定义删除器，可以是一个函数指针，也可以是一个类
 * e.g 
 * void close_file(std::FILE* fp){std::fclose(fp);}
 * std::unique_ptr<std::FILE, void(*)(std::FILE*)> fp(std::fopen('a.txt'), close_file);
 * 上面的例子就是使用函数作为 删除器
 * 当然这里的代码自身使用的删除器使用 default_delete 类作为删除器，使用的时候，调用类的 operator() 函数实现
*/
class unique_ptr
{
public:
	typedef _Tp element_type;
	typedef _Dp deleter_type;
	/**
	 * default_delete 类中没有 pointer 成员，那么 _Tp* 将会被指派为 pointer
	*/
	typedef typename __pointer_type<_Tp, deleter_type>::type pointer;	// pointer  = _Tp* 
	// 存储的原始指针， 例如 存储 int 类型，这里的 pointer 就是 int* 
private:
	__compressed_pair<pointer, deleter_type> __ptr_;

	struct __nat { int __for_bool_; };

	typedef				typename remove_reference<deleter_type>::type& _Dp_reference;
	typedef const		typename remove_reference<deleter_type>::type& _Dp_const_reference;

public:
	unique_ptr() noexcept
		: __ptr_(pointer())
	{
		static_assert(!is_pointer<deleter_type>::value,
			"unique_ptr constructed with null function pointer deleter");
	}
	unique_ptr(nullptr_t) noexcept
		: __ptr_(pointer())
	{
		static_assert(!is_pointer<deleter_type>::value,
			"unique_ptr constructed with null function pointer deleter");
	}
	explicit unique_ptr(pointer __p) noexcept
		: __ptr_(yjh_def::move(__p))
	{
		static_assert(!is_pointer<deleter_type>::value,
			"unique_ptr constructed with null function pointer deleter");
	}

	unique_ptr(pointer __p, typename conditional<
										is_reference<deleter_type>::value,
										deleter_type,
										typename add_lvalue_reference<const deleter_type>::type
									>::type __d)
		: __ptr_(__p, __d) {}

	unique_ptr(pointer __p, typename remove_reference<deleter_type>::type&& __d)
		noexcept
		: __ptr_(__p, yjh_def::move(__d))
	{
		static_assert(!is_reference<deleter_type>::value, "rvalue deleter bound to reference");
	}

	unique_ptr(unique_ptr&& __u) noexcept
		: __ptr_(__u.release(), yjh_def::forward<deleter_type>(__u.get_deleter())) {}

	template <class _Up, class _Ep>
	unique_ptr(	unique_ptr<_Up, _Ep>&& __u,
				typename enable_if
						<
							!is_array<_Up>::value &&
							is_convertible<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
							is_convertible<_Ep, deleter_type>::value &&
							(
								!is_reference<deleter_type>::value ||
								is_same<deleter_type, _Ep>::value
							),
							__nat
						>::type = __nat()) noexcept
		: __ptr_(__u.release(), yjh_def::forward<_Ep>(__u.get_deleter())) {}

	template <class _Up>
	unique_ptr(auto_ptr<_Up>&& __p,
		typename enable_if<
			is_convertible<_Up*, _Tp*>::value &&
			is_same<_Dp, default_delete<_Tp> >::value,
			__nat
			>::type = __nat()) noexcept
		: __ptr_(__p.release()) {}

	unique_ptr&		operator=(unique_ptr&& __u) noexcept
	{
		reset(__u.release());
		__ptr_.second() = yjh_def::forward<deleter_type>(__u.get_deleter());
		return *this;
	}

	template <class _Up, class _Ep>
	typename enable_if
		<
			!is_array<_Up>::value &&
			is_convertible<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
			is_assignable<deleter_type&, _Ep&&>::value,
			unique_ptr&
		>::type
		operator= (unique_ptr<_Up, _Ep>&& __u) noexcept
	{
		reset(__u.release());
		__ptr_.second() = yjh_def::forward<_Ep>(__u.get_deleter());
		return *this;
	}

	~unique_ptr() { reset(); }

	typename add_lvalue_reference<_Tp>::type operator*() const
	{
		return *__ptr_.first();
	}

	pointer operator ->() const noexcept { return __ptr_.first(); }
	pointer get() const noexcept { return __ptr_.first(); }
	_Dp_reference	get_deleter() noexcept { return __ptr_.second(); }
	_Dp_const_reference get_deleter() const noexcept { return __ptr_.second(); }

	operator bool() const noexcept
	/**
	 * 用于类型转化 bool(unique_ptr) 或者 static_cast<bool>(unique_ptr)
	 */
	{
		return __ptr_.first() != nullptr;
	}

	pointer release() noexcept
	{
		pointer __t = __ptr_.first();
		__ptr_.first() = pointer();	//将自身的指针值重置为默认值，返回原始指针
		return __t;
	}

	void reset(pointer __p = pointer()) noexcept
	{
		pointer __temp = __ptr_.first();
		__ptr_.first() = __p;
		if (__temp)
			__ptr_.second()(__temp);
	}

	void swap(unique_ptr& __u) noexcept
	{
		__ptr_.swap(__u.__ptr_);
	}
};

template <class _Tp, class _Dp>
class unique_ptr<_Tp[], _Dp>
{
public:
	typedef _Tp element_type;
	typedef _Dp deleter_type;
	typedef typename __pointer_type<_Tp, deleter_type>::type pointer;

private:
	__compressed_pair<pointer, deleter_type>  __ptr_;

	struct __nat { int __for_bool_; };

	typedef			typename remove_reference<deleter_type>::type& _Dp_reference;
	typedef const	typename remove_reference<deleter_type>::type& _Dp_const_reference;
public:
	unique_ptr() noexcept
		: __ptr_(pointer())
	{
		static_assert(!is_pointer<deleter_type>::value,
			"unique_ptr constructed with null function pointer deleter");
	}

	unique_ptr(nullptr_t) noexcept
		: __ptr_(pointer())
	{
		static_assert(!is_pointer<deleter_type>::value,
			"unique_ptr constructed with null function pointer deleter");
	}

	template <	class _Pp,
				class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
	>
		explicit unique_ptr(_Pp __p) noexcept
		:__ptr_(__p)
	{
		static_assert(!is_pointer<deleter_type>::value,
			"unique_ptr constructed with null function pointer deleter");
	}

	template <	class _Pp,
		class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
	>
		unique_ptr(_Pp __p, typename conditional<
			is_reference<deleter_type>::value,
			deleter_type,
			typename add_lvalue_reference<const deleter_type>::type>::type __d)
		noexcept
		: __ptr_(__p, __d) {}


	unique_ptr(nullptr_t, typename conditional<
					is_reference<deleter_type>::value,
					deleter_type,
					typename add_lvalue_reference<const deleter_type>::type>::type __d)
		noexcept
		: __ptr_(pointer(), __d) {}

	template <	class _Pp,
		class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
	>
		unique_ptr(_Pp __p, typename remove_reference<deleter_type>::type&& __d)
		noexcept
		: __ptr_(__p, yjh_def::move(__d))
	{
		static_assert(!is_reference<deleter_type>::value, "rvalue deleter bound to reference");
	}

	unique_ptr(nullptr_t, typename remove_reference<deleter_type>::type&& __d)
		noexcept
		: __ptr_(pointer(), yjh_def::move(__d))
	{
		static_assert(!is_reference<deleter_type>::value, "rvalue deleter bound to reference");
	}

	unique_ptr(unique_ptr&& __u) noexcept
		: __ptr_(__u.release(), yjh_def::forward<deleter_type>(__u.get_deleter())) {}

	unique_ptr&		operator = (unique_ptr&& __u) noexcept
	{
		reset(__u.release());
		__ptr_.second() = yjh_def::forward<deleter_type>(__u.get_deleter());
		return *this;
	}

	template <class _Up, class _Ep>
	unique_ptr(unique_ptr<_Up, _Ep>&& __u,
		typename enable_if<
		is_array<_Up>::value &&
		__same_or_less_cv_qualified<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
		(
			!is_reference<deleter_type>::value ||
			is_same<deleter_type, _Ep>::value
			),
		__nat
		>::type = __nat()
	)noexcept
		:__ptr_(__u.release(), yjh_def::forward<deleter_type>(__u.get_deleter())) {}

	template <class _Up, class _Ep>
	typename enable_if
	<
		is_array<_Up>::value &&
		__same_or_less_cv_qualified<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
		is_assignable<deleter_type&, _Ep&&>::value,
		unique_ptr&
	>::type
	operator = (unique_ptr<_Up, _Ep>&& __u) noexcept
	{
		reset(__u.release());
		__ptr_.second() = yjh_def::forward<_Ep>(__u.get_deleter());
		return *this;
	}

	~unique_ptr() { reset(); }

	unique_ptr& operator=(nullptr_t) noexcept
	{
		reset();
		return *this;
	}

	typename add_lvalue_reference<_Tp>::type operator[] (size_t __i) const
	{
		return __ptr_.first()[__i];
	}

	pointer get() const noexcept { return __ptr_.first(); }

	_Dp_reference get_deleter() noexcept { return __ptr_.second(); }

	_Dp_const_reference get_deleter() const noexcept { return __ptr_.first(); }

	operator bool() const noexcept
	{
		return __ptr_.first() != nullptr;
	}

	pointer release() noexcept
	{
		pointer __t = __ptr_.first();
		__ptr_.first() = pointer();
		return __t;
	}

	template <class _Pp,
				class  = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type>
		void reset(_Pp __p) noexcept
	{
		pointer temp = __ptr_.first();
		__ptr_.first() = __p;
		if (temp)
			__ptr_.second()(temp);  // 调用 deleter 的 operator() 函数对内存进行释放
	}

	void reset(nullptr_t) noexcept
	{
		pointer __temp = __ptr_.first();
		__ptr_.first() = nullptr;
		if(__temp)
			__ptr_.second()(__temp);
	}

	void reser() noexcept
	{
		pointer __temp = __ptr_.first();
		__ptr_.first() = nullptr;
		if(__temp)
			__ptr_.second()(__temp);
	}

	void swap(unique_ptr& __u) noexcept
	{
		__ptr_.swap(__u.__ptr_);
	}

};

template <class _Tp, class _Dp>
inline
void
swap(unique_ptr<_Tp, _Dp>& __x, unique_ptr<_Tp, _Dp>& __y) noexcept {__x.swap(__y);}

template <class _T1, class _D1, class _T2, class _D2>
inline 
bool
operator==(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return __x.get() == __y.get();}

template <class _T1, class _D1, class _T2, class _D2>
inline 
bool
operator!=(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return !(__x == __y);}

template <class _T1, class _D1, class _T2, class _D2>
inline 
bool
operator< (const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
{
	/**
	 * 不同的 unique_ptr 可能持有不同类型的数据的指针，那么在进行大小的比较的时候，/
	 * 需要将这些指针转化为它们的公共类型 /
	 * 不然的话，没有办法进行直接的比较
	 */
    typedef typename unique_ptr<_T1, _D1>::pointer _P1;
    typedef typename unique_ptr<_T2, _D2>::pointer _P2;
    typedef typename common_type<_P1, _P2>::type _V;
    return less<_V>()(__x.get(), __y.get());
}

template <class _T1, class _D1, class _T2, class _D2>
inline 
bool
operator> (const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return __y < __x;}

template <class _T1, class _D1, class _T2, class _D2>
inline 
bool
operator<=(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return !(__y < __x);}

template <class _T1, class _D1, class _T2, class _D2>
inline 
bool
operator>=(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return !(__x < __y);}

template <class _T1, class _D1>
inline
bool
operator==(const unique_ptr<_T1, _D1>& __x, nullptr_t) noexcept
{
	/**
	 * ! 运算符会对 __x 进行隐式的转换 bool(__x)
	 */
    return !__x;
}

template <class _T1, class _D1>
inline
bool
operator==(nullptr_t, const unique_ptr<_T1, _D1>& __x) noexcept
{
    return !__x;
}

template <class _T1, class _D1>
inline
bool
operator!=(const unique_ptr<_T1, _D1>& __x, nullptr_t) noexcept
{
    return static_cast<bool>(__x);
}

template <class _T1, class _D1>
inline
bool
operator!=(nullptr_t, const unique_ptr<_T1, _D1>& __x) noexcept
{
    return static_cast<bool>(__x);
}

template <class _T1, class _D1>
inline
bool
operator<(const unique_ptr<_T1, _D1>& __x, nullptr_t)
{
    typedef typename unique_ptr<_T1, _D1>::pointer _P1;
    return less<_P1>()(__x.get(), nullptr);
}

template <class _T1, class _D1>
inline
bool
operator<(nullptr_t, const unique_ptr<_T1, _D1>& __x)
{
    typedef typename unique_ptr<_T1, _D1>::pointer _P1;
    return less<_P1>()(nullptr, __x.get());
}

template <class _T1, class _D1>
inline
bool
operator>(const unique_ptr<_T1, _D1>& __x, nullptr_t)
{
    return nullptr < __x;
}

template <class _T1, class _D1>
inline
bool
operator>(nullptr_t, const unique_ptr<_T1, _D1>& __x)
{
    return __x < nullptr;
}

template <class _T1, class _D1>
inline
bool
operator<=(const unique_ptr<_T1, _D1>& __x, nullptr_t)
{
    return !(nullptr < __x);
}

template <class _T1, class _D1>
inline
bool
operator<=(nullptr_t, const unique_ptr<_T1, _D1>& __x)
{
    return !(__x < nullptr);
}

template <class _T1, class _D1>
inline
bool
operator>=(const unique_ptr<_T1, _D1>& __x, nullptr_t)
{
    return !(__x < nullptr);
}

template <class _T1, class _D1>
inline
bool
operator>=(nullptr_t, const unique_ptr<_T1, _D1>& __x)
{
    return !(nullptr < __x);
}

// hash
template <class _Tp>	struct hash;
// We use murmur2 when size_t is 32 bits, and cityhash64 when size_t
// is 64 bits.  This is because cityhash64 uses 64bit x 64bit
// multiplication, which can be very slow on 32-bit systems.
template <class _Size, size_t = sizeof(_Size)*__CHAR_BIT__>
struct __murmur2_or_cityhash;

template <class _Size>
struct __murmur2_or_cityhash<_Size, 32>
{
	_Size operator() (const void* __key, _Size __len);
};

// murmur2
template <class _Size>
_Size
__murmur2_or_cityhash<_Size, 32>::operator() (const void* __key, _Size __len)
{
	const _Size __m = 0x5bd1e995;
	const _Size __r = 24;
	_Size __h = __len;
	const unsigned char* __data = static_cast<const unsigned char*>(__key);
	for (; __len >= 4; __data += 4, __len -= 4)
	{
		_Size __k = *(const _Size*)__data;
		__k *= __m;
		__k ^= __k >> __r;
		__k *= __m;
		__h *= __m;
		__h ^= __k;
	}
	switch (__len)
	{
		case 3:
			__h ^= __data[2] << 16;
		case 2:
			__h ^= __data[1] << 8;
		case 1:
			__h ^= __data[0];
			__h *= __m;
	}
    __h ^= __h >> 13;
    __h *= __m;
    __h ^= __h >> 15;
    return __h;
}

template <class _Size>
struct __murmur2_or_cityhash<_Size, 64>
{
    _Size operator()(const void* __key, _Size __len);

 private:
  // 在 2^63 and 2^64. 之间的一些质数
  static const _Size __k0 = 0xc3a5c85c97cb3127ULL;
  static const _Size __k1 = 0xb492b66fbe98f273ULL;
  static const _Size __k2 = 0x9ae16a3b2f90404fULL;
  static const _Size __k3 = 0xc949d7c7509e6557ULL;

  /**
   * 从第 __shift 位开始对所有的比特进行翻转
   */
  static _Size __rotate(_Size __val, int __shift) {
    return __shift == 0 ? __val : ((__val >> __shift) | (__val << (64 - __shift)));
  }

  static _Size __rotate_by_at_least_1(_Size __val, int __shift) {
    return (__val >> __shift) | (__val << (64 - __shift));
  }

  static _Size __shift_mix(_Size __val) {
    return __val ^ (__val >> 47);	// 按位 异或
  }

  static _Size __hash_len_16(_Size __u, _Size __v) {
    const _Size __mul = 0x9ddfea08eb382d69ULL;
    _Size __a = (__u ^ __v) * __mul;
    __a ^= (__a >> 47);
    _Size __b = (__v ^ __a) * __mul;
    __b ^= (__b >> 47);
    __b *= __mul;
    return __b;
  }

  static _Size __hash_len_0_to_16(const char* __s, _Size __len) {
    if (__len > 8) {
      const _Size __a = *(const _Size*)__s;
      const _Size __b = *(const _Size*)(__s + __len - 8);
      return __hash_len_16(__a, __rotate_by_at_least_1(__b + __len, __len)) ^ __b;
    }
    if (__len >= 4) {
      const uint32_t __a = *(const uint32_t*)(__s);
      const uint32_t __b = *(const uint32_t*)(__s + __len - 4);
      return __hash_len_16(__len + (__a << 3), __b);
    }
    if (__len > 0) {
      const unsigned char __a = __s[0];
      const unsigned char __b = __s[__len >> 1];
      const unsigned char __c = __s[__len - 1];
      const uint32_t __y = static_cast<uint32_t>(__a) +
                           (static_cast<uint32_t>(__b) << 8);
      const uint32_t __z = __len + (static_cast<uint32_t>(__c) << 2);
      return __shift_mix(__y * __k2 ^ __z * __k3) * __k2;
    }
    return __k2;   // if (__len == 0)
  }

  static _Size __hash_len_17_to_32(const char *__s, _Size __len) {
    const _Size __a = *(const _Size*)(__s) * __k1;
    const _Size __b = *(const _Size*)(__s + 8);
    const _Size __c = *(const _Size*)(__s + __len - 8) * __k2;
    const _Size __d = *(const _Size*)(__s + __len - 16) * __k0;
    return __hash_len_16(__rotate(__a - __b, 43) + __rotate(__c, 30) + __d,
                         __a + __rotate(__b ^ __k3, 20) - __c + __len);
  }

  // Return a 16-byte hash for 48 bytes.  Quick and dirty.
  // Callers do best to use "random-looking" values for a and b.
  static pair<_Size, _Size> __weak_hash_len_32_with_seeds(
      _Size __w, _Size __x, _Size __y, _Size __z, _Size __a, _Size __b) {
    __a += __w;
    __b = __rotate(__b + __a + __z, 21);
    const _Size __c = __a;
    __a += __x;
    __a += __y;
    __b += __rotate(__a, 44);
    return pair<_Size, _Size>(__a + __z, __b + __c);
  }

  // Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
  static pair<_Size, _Size> __weak_hash_len_32_with_seeds(
      const char* __s, _Size __a, _Size __b) {
    return __weak_hash_len_32_with_seeds(*(const _Size*)(__s),
                                         *(const _Size*)(__s + 8),
                                         *(const _Size*)(__s + 16),
                                         *(const _Size*)(__s + 24),
                                         __a,
                                         __b);
  }

  // Return an 8-byte hash for 33 to 64 bytes.
  static _Size __hash_len_33_to_64(const char *__s, size_t __len) {
    _Size __z = *(const _Size*)(__s + 24);
    _Size __a = *(const _Size*)(__s) +
                (__len + *(const _Size*)(__s + __len - 16)) * __k0;
    _Size __b = __rotate(__a + __z, 52);
    _Size __c = __rotate(__a, 37);
    __a += *(const _Size*)(__s + 8);
    __c += __rotate(__a, 7);
    __a += *(const _Size*)(__s + 16);
    _Size __vf = __a + __z;
    _Size __vs = __b + __rotate(__a, 31) + __c;
    __a = *(const _Size*)(__s + 16) + *(const _Size*)(__s + __len - 32);
    __z += *(const _Size*)(__s + __len - 8);
    __b = __rotate(__a + __z, 52);
    __c = __rotate(__a, 37);
    __a += *(const _Size*)(__s + __len - 24);
    __c += __rotate(__a, 7);
    __a += *(const _Size*)(__s + __len - 16);
    _Size __wf = __a + __z;
    _Size __ws = __b + __rotate(__a, 31) + __c;
    _Size __r = __shift_mix((__vf + __ws) * __k2 + (__wf + __vs) * __k0);
    return __shift_mix(__r * __k0 + __vs) * __k2;
  }
};

// cityhash64
template <class _Size>
_Size
__murmur2_or_cityhash<_Size, 64>::operator()(const void* __key, _Size __len)
{
  const char* __s = static_cast<const char*>(__key);
  if (__len <= 32) {
    if (__len <= 16) {
      return __hash_len_0_to_16(__s, __len);
    } else {
      return __hash_len_17_to_32(__s, __len);
    }
  } else if (__len <= 64) {
    return __hash_len_33_to_64(__s, __len);
  }

  // For strings over 64 bytes we hash the end first, and then as we
  // loop we keep 56 bytes of state: v, w, x, y, and z.
  _Size __x = *(const _Size*)(__s + __len - 40);
  _Size __y = *(const _Size*)(__s + __len - 16) +
              *(const _Size*)(__s + __len - 56);
  _Size __z = __hash_len_16(*(const _Size*)(__s + __len - 48) + __len,
                          *(const _Size*)(__s + __len - 24));
  pair<_Size, _Size> __v = __weak_hash_len_32_with_seeds(__s + __len - 64, __len, __z);
  pair<_Size, _Size> __w = __weak_hash_len_32_with_seeds(__s + __len - 32, __y + __k1, __x);
  __x = __x * __k1 + *(const _Size*)(__s);

  // Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
  __len = (__len - 1) & ~static_cast<_Size>(63);
  do {
    __x = __rotate(__x + __y + __v.first + *(const _Size*)(__s + 8), 37) * __k1;
    __y = __rotate(__y + __v.second + *(const _Size*)(__s + 48), 42) * __k1;
    __x ^= __w.second;
    __y += __v.first + *(const _Size*)(__s + 40);
    __z = __rotate(__z + __w.first, 33) * __k1;
    __v = __weak_hash_len_32_with_seeds(__s, __v.second * __k1, __x + __w.first);
    __w = __weak_hash_len_32_with_seeds(__s + 32, __z + __w.second,
                                        __y + *(const _Size*)(__s + 16));
    yjh_def::swap(__z, __x);
    __s += 64;
    __len -= 64;
  } while (__len != 0);
  return __hash_len_16(
      __hash_len_16(__v.first, __w.first) + __shift_mix(__y) * __k1 + __z,
      __hash_len_16(__v.second, __w.second) + __x);
}

// __scalar_hash
template <class _Tp, size_t = sizeof(_Tp) / sizeof(size_t)>
struct __scalar_hash;

template <class _Tp>
/**
 * sizof(_Tp) < sizeof(size_t)
 */
struct __scalar_hash<_Tp, 0>
	: public unary_function<_Tp, size_t>
{
	size_t operator()(_Tp __v) const noexcept
	{
		union
		{
			_Tp 	__t;
			size_t	__a;
		} __u;
		__u.__a = 0;
		__u.__t = __v;
		return __u.__a;
	}
};

template <class _Tp>
/**
 * sizof(_Tp) = sizeof(size_t)
 */
struct __scalar_hash<_Tp, 1>
	: public unary_function<_Tp, size_t>
{
	size_t operator() (_Tp __v) const noexcept
	{
		union 
		{
			_Tp 	__t;
			size_t	__a;
		} __u;
		__u.__t = __v;
		return __u.__a;
	}
};

template <class _Tp>
struct __scalar_hash<_Tp, 2>
/**
 * 3 * sizeof(size_t) > sizeof(_Tp) >= 2 * sizeof(size_t)
 *返回的 hash 要是 size_t 的类型，因此就需要压缩了
 */
    : public unary_function<_Tp, size_t>
{
    size_t operator()(_Tp __v) const noexcept
    {
        union
        {
            _Tp __t;
            struct
            {
                size_t __a;
                size_t __b;
            };
        } __u;
        __u.__t = __v;
        return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
    }
};

template <class _Tp>
struct __scalar_hash<_Tp, 3>
	: public unary_function<_Tp, size_t>
{
	size_t operator() (_Tp __v) const noexcept
	{
		union 
		{
			_Tp __t;
			struct
			{
				size_t __a;
				size_t __b;
				size_t __c;
			};
		} __u;
		__u.__t = __v;
		return __murmur2_or_cityhash<size_t>() (&__u, sizeof(__u));
	}
};

template <class _Tp>
struct __scalar_hash<_Tp, 4>
    : public unary_function<_Tp, size_t>
{
    size_t operator()(_Tp __v) const noexcept
    {
        union
        {
            _Tp __t;
            struct
            {
                size_t __a;
                size_t __b;
                size_t __c;
                size_t __d;
            };
        } __u;
        __u.__t = __v;
        return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
    }
};

template <class _Tp>
struct hash<_Tp*>
	/**
	 * hash 函数关于对于指针类型的特化
	 */
	: public unary_function<_Tp*, size_t>
{
	size_t operator() (_Tp* __v) const noexcept
	{
		union 
		{
			_Tp* __t;
			size_t __a;
		} __u;
		__u.__t = __v;
		return __murmur2_or_cityhash<size_t>() (&__u, sizeof(__u));
	}
};

template <class _Tp, class _Dp>
/**
 * hash 函数关于 unique_ptr 的特化
 */
struct hash<unique_ptr<_Tp, _Dp> >
{
	typedef unique_ptr<_Tp, _Dp>		argument_type;
	typedef size_t						result_type;

	result_type  operator() (const argument_type& __ptr) const noexcept
	{
		typedef typename argument_type::pointer pointer;
		return hash<pointer>()(__ptr.get());
	}
};

/**
 * trivially 的析构函数说明了这个类没有需要手动进行释放的资源，在进行内存回收的时候，直接回收内存地址即可 \
 * 这对应于下面这个类中的 true_type
 * 
 * 如果待释放的资源有手动声明的析构函数，则说明该资源持有需要手动进行释放的资源，对应于下面的类中的 false_type
 */
struct __destruct_n
{
private:
    size_t size;

    template <class _Tp>
    void __process(_Tp* __p, false_type) _NOEXCEPT
        {for (size_t __i = 0; __i < size; ++__i, ++__p) __p->~_Tp();}

    template <class _Tp>
    void __process(_Tp*, true_type) _NOEXCEPT
        {}

    void __incr(false_type) _NOEXCEPT
        {++size;}
    void __incr(true_type) _NOEXCEPT
        {}

    void __set(size_t __s, false_type) _NOEXCEPT
        {size = __s;}
    void __set(size_t, true_type) _NOEXCEPT
        {}
public:
    explicit __destruct_n(size_t __s) _NOEXCEPT
        : size(__s) {}

    template <class _Tp>
    void __incr(_Tp*) _NOEXCEPT
        {__incr(integral_constant<bool, is_trivially_destructible<_Tp>::value>());}

    template <class _Tp>
    void __set(size_t __s, _Tp*) _NOEXCEPT
        {__set(__s, integral_constant<bool, is_trivially_destructible<_Tp>::value>());}

    template <class _Tp>
    void operator()(_Tp* __p) _NOEXCEPT
        {__process(__p, integral_constant<bool, is_trivially_destructible<_Tp>::value>());}
};

template <class _Alloc>
class __allocator_destructor
{
    typedef allocator_traits<_Alloc> __alloc_traits;
public:
    typedef typename __alloc_traits::pointer pointer;
    typedef typename __alloc_traits::size_type size_type;
private:
    _Alloc& __alloc_;
    size_type __s_;
public:
    __allocator_destructor(_Alloc& __a, size_type __s)
             _NOEXCEPT
        : __alloc_(__a), __s_(__s) {}

    void operator()(pointer __p) _NOEXCEPT
        {__alloc_traits::deallocate(__alloc_, __p, __s_);}
};

template <class _InputIterator, class _ForwardIterator>
_ForwardIterator
/**
 * 复制来自范围 [__F, __l) 的元素到始于 d_first 的未初始化内存
 * 出现异常，需要销毁已构造的对象
 */
uninitialized_copy(_InputIterator __f, _InputIterator __l, _ForwardIterator __r)
{
    typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
    _ForwardIterator __s = __r;
    try
    {
#endif
        for (; __f != __l; ++__f, ++__r)
            ::new(&*__r) value_type(*__f);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
	/**
	 * 如果 try 中的 new 在某一次 for 循环中出现了异常，那么前面的循环当中分配的内存 \
	 * 空间应当马上进行回收
	 * 不然的话就会发生内存的泄露
	 * 不管发生的异常的类型是什么
	 */
    catch (...)
    {
        for (; __s != __r; ++__s)
            __s->~value_type();
        throw;
    }
#endif
    return __r;
}


/**
 * 从始于 __f 的范围复制 __n 个元素到始于 __r 的未初始化内存区域
 * 如果出现了异常，则销毁已经构造的对象
 */
template <class _InputIterator, class _Size, class _ForwardIterator>
_ForwardIterator
uninitialized_copy_n(_InputIterator __f, _Size __n, _ForwardIterator __r)
{
    typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
    _ForwardIterator __s = __r;
    try
    {
#endif
        for (; __n > 0; ++__f, ++__r, --__n)
            ::new(&*__r) value_type(*__f);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        for (; __s != __r; ++__s)
            __s->~value_type();
        throw;
    }
#endif
    return __r;
}

/**
 * 使用一个对象值 __x 初始化所有的对象
 * 如果发生异常，则销毁所有的已构造的对象
 */
template <class _ForwardIterator, class _Tp>
void
uninitialized_fill(_ForwardIterator __f, _ForwardIterator __l, const _Tp& __x)
{
    typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
    _ForwardIterator __s = __f;
    try
    {
#endif
        for (; __f != __l; ++__f)
            ::new(&*__f) value_type(__x);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        for (; __s != __f; ++__s)
            __s->~value_type();
        throw;
    }
#endif
}

template <class _ForwardIterator, class _Size, class _Tp>
_ForwardIterator
uninitialized_fill_n(_ForwardIterator __f, _Size __n, const _Tp& __x)
{
    typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
    _ForwardIterator __s = __f;
    try
    {
#endif
        for (; __n > 0; ++__f, --__n)
            ::new(&*__f) value_type(__x);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        for (; __s != __f; ++__s)
            __s->~value_type();
        throw;
    }
#endif
    return __f;
}

class bad_weak_ptr
	: public yjh_def::exception
{
public:
	virtual ~bad_weak_ptr() noexcept;
	virtual const char* what() const noexcept;
};

template <class _Tp>	class weak_ptr;

// shared_ptr
// __shared_count
/**
 * share_count 是一个抽象类
 */
class __shared_count
{
	__shared_count(const __shared_count&);
	__shared_count&	operator=(const __shared_count&);
protected:
	long __shared_owners_;
	virtual ~__shared_count();
private:
	virtual void __on_zero_shared() noexcept = 0;	// 纯虚函数指明这个类不可以进行实现，必须有类继承它来实现接口的功能

public:
	explicit __shared_count(long __refs = 0) noexcept
		: __shared_owners_(__refs) {}
	
	void __add_shared() noexcept;
	bool __release_shared() noexcept;
	long use_count() const noexcept {return __shared_owners_ + 1; }	// 这里为什么要 + 1
};

// __shared_weak_count
// shared_ptr 将这个类作为自己的成员
class __shared_weak_count
	: private __shared_count
{
	long __shared_weak_owners_;
public:
	explicit __shared_weak_count(long __refs = 0) noexcept
		: __shared_count(__refs),
		  __shared_weak_owners_(__refs) {}

protected:
	virtual ~__shared_weak_count();

public:
	void __add_shared() noexcept;
	void __add_weak() noexcept;
	void __release_shared() noexcept;
	void __release_weak() noexcept;
	long use_count() const noexcept {return __shared_count::use_count();}
	__shared_weak_count* lock() noexcept;

	virtual const void* __get_deleter(const std::type_info&) const noexcept;
	/**
	 * type_info 只能由 typeid() 操作符产生，标准库中的 type_info 不允许用户自己构造该类型的实例
	 */

private:
	virtual void __on_zero_shared_weak() noexcept = 0;
};

// __shared_weak_count
template <class _Tp, class _Dp, class _Alloc>
class __shared_ptr_pointer
	: public __shared_weak_count
{
	__compressed_pair<__compressed_pair<_Tp, _Dp>, _Alloc> __data_;
public:
	__shared_ptr_pointer(_Tp __p, _Dp __d, _Alloc __a)
		: __data_(__compressed_pair<_Tp, _Dp>(__p, yjh_def::move(__d)), yjh_def::move(__a)) {}
	
#ifndef _YJH_NO_RTTI
	virtual const void* __get_deleter(const std::type_info&) const noexcept;
#endif

private:
	virtual void __on_zero_shared() noexcept;
	virtual void __on_zero_shared_weak() noexcept;
};

#ifndef _YJH_NO_RTTI
template <class _Tp, class _Dp, class _Alloc>
const void*
__shared_ptr_pointer<_Tp, _Dp, _Alloc>::__get_deleter(const std::type_info& __t) const noexcept
{
	return __t == typeid(_Dp) ? &__data_.first().second() : 0;
}
#endif  // _YJH_NO_RTTI

template <class _Tp, class _Dp, class _Alloc>
void
__shared_ptr_pointer<_Tp, _Dp, _Alloc>::__on_zero_shared() noexcept
{
	__data_.first().second()(__data_.first().first()); //调用 deleter 销毁 _Tp 内存
	__data_.first().second().~_Dp();	// 销毁 deleter 对象
}

template <class _Tp, class _Dp, class _Alloc>
void
__shared_ptr_pointer<_Tp, _Dp, _Alloc>::__on_zero_shared_weak() noexcept
{
	typename _Alloc::template rebind<__shared_ptr_pointer>::other __a(__data_.second());
	// __data_.second() 是一个 allocator 对象
	__data_.second().~_Alloc();
	__a.deallocate(this, 1);
}

template <class _Tp, class _Alloc>
class __shared_ptr_emplace
	: public __shared_weak_count
{
	__compressed_pair<_Alloc, _Tp> __data_;
public:
#ifndef __YJH_HAS_NO_VARIADICS
	__shared_ptr_emplace(_Alloc __a)
		: __data_(yjh_def::move(__a)) {}
	
	template <class ..._Args>
	__shared_ptr_emplace(_Alloc __a, _Args&& ...__args)
		: __data_(piecewise_construct, yjh_def::forward_as_tuple(__a),
			yjh_def::forward_as_tuple(yjh_def::forward<_Args>(__args)...)
		) {}
	
#endif

private:
	virtual void __on_zero_shared() _NOEXCEPT;
	virtual void __on_zero_shared_weak() _NOEXCEPT;
public:
	_Tp* get() _NOEXCEPT { return &__data_.second(); }
};

template <class _Tp, class _Alloc>
void
__shared_ptr_emplace<_Tp, _Alloc>::__on_zero_shared() _NOEXCEPT
{
	__data_.second().~_Tp();
}

template <class _Tp, class _Alloc>
void
__shared_ptr_emplace<_Tp, _Alloc>::__on_zero_shared_weak() _NOEXCEPT
{
    typename _Alloc::template rebind<__shared_ptr_emplace>::other __a(__data_.first());
    __data_.first().~_Alloc();
    __a.deallocate(this, 1);
}

template<class _Tp> class enable_shared_from_this;

/**
 * shared_ptr 可以在多个对象中共享一个指针，并且将会保留这些指针的引用次数
 * 并在没有人使用该指针时自动释放该指针的内存
 */
// shared_ptr
template <class _Tp>
class shared_ptr
{
public:
	typedef _Tp element_type;
private:
	element_type*			__ptr_;
	__shared_weak_count*	__cntrl_;

	struct __nat {int __for_bool_;};
public:
	shared_ptr() noexcept;
	shared_ptr(nullptr_t) noexcept;
	template <	class _Yp,
				class = typename enable_if<
					is_convertible<_Yp*, element_type*>::value
					>::type
			 >
	explicit shared_ptr(_Yp* __p);

	template <	class _Yp, class _Dp,
				class = typename enable_if
					<
						is_convertible<_Yp*, element_type*>::value
					>::type
			>
	shared_ptr(_Yp* __p, _Dp __d);

	template <	class _Yp, class _Dp, class _Alloc,
				class = typename enable_if
					<
						is_convertible<_Yp*, element_type*>::value
					>::type
			>
	shared_ptr(_Yp* __p, _Dp __d, _Alloc __a);

	template <class _Dp>				shared_ptr(nullptr_t, _Dp __d);
	template <class _Dp, class _Alloc> 	shared_ptr(nullptr_t, _Dp __d, _Alloc __a);
	template <class _Yp> shared_ptr(const shared_ptr<_Yp>& __r, element_type* __p) noexcept;
	shared_ptr(const shared_ptr& __r) noexcept;

	template <class _Yp>
	shared_ptr(const shared_ptr<_Yp>& __r,
				typename enable_if
					<	is_convertible<_Yp*, _Tp*>::value, 
						__nat
					>::type = __nat()
				) noexcept;

#ifndef _YJH_HAS_NO_RVALUE_REFERENCES

	shared_ptr(shared_ptr&& __r) noexcept;

	template <class _Yp>
	shared_ptr(shared_ptr<_Yp>&& __r,
				typename enable_if
					<
						is_convertible<_Yp*, _Tp*>::value,
						__nat
					>::type = __nat()) noexcept;

	template <	class _Yp,
				class  = typename enable_if
					<
						is_convertible<_Yp*, element_type*>::value
					>::type
			>
	shared_ptr(auto_ptr<_Yp>&& __r);
#else
	// have nothing
#endif

	template <class _Yp>
	explicit shared_ptr(const weak_ptr<_Yp>& __r,
					typename enable_if
						<
							is_convertible<_Yp*, _Tp*>::value,
							__nat
						>::type = __nat());
	
#ifndef _YJH_HAS_NO_RVALUE_REFERENCES


	/**
	 * 为什么将 deleter 是否是左值类型分别进行处理
	 */
	template <class _Yp, class _Dp,
				class = typename enable_if
					<
						!is_array<_Yp>::value &&
						is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value
					>::type
			>
	shared_ptr(unique_ptr<_Yp, _Dp>&& __r,
				typename enable_if<!is_lvalue_reference<_Dp>::value, __nat>::type = __nat());

	template <class _Yp, class _Dp,
				class = typename enable_if
					<
						!is_array<_Yp>::value &&
						is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value
					>::type
			>
	shared_ptr(unique_ptr<_Yp, _Dp>&&,
				typename enable_if<is_lvalue_reference<_Dp>::value, __nat>::type = __nat());
#else
	// have nothing
#endif

	~shared_ptr();

	shared_ptr&	operator=(const shared_ptr& __r) noexcept;

	template <class _Yp>
	typename enable_if
			<
				is_convertible<_Yp*, element_type*>::value,
				shared_ptr&
			>::type
	operator=(const shared_ptr<_Yp>& __r) noexcept;

#ifndef _YJH_HAS_NO_RVALUE_REFERENCES
    shared_ptr& operator=(shared_ptr&& __r) _NOEXCEPT;

    template<class _Yp>
    typename enable_if
        	<
            	is_convertible<_Yp*, element_type*>::value,
            	shared_ptr<_Tp>&
        	>::type
    operator=(shared_ptr<_Yp>&& __r);

    template<class _Yp>
    typename enable_if
        	<
            	!is_array<_Yp>::value &&
            	is_convertible<_Yp*, element_type*>::value,
            	shared_ptr&
        	>::type
    operator=(auto_ptr<_Yp>&& __r);
#else
	// have nothing
#endif
    template <class _Yp, class _Dp>
    typename enable_if
        	<
            	!is_array<_Yp>::value &&
            	is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value,
            	shared_ptr&
        	>::type
	operator=(unique_ptr<_Yp, _Dp>&& __r);

    void swap(shared_ptr& __r) _NOEXCEPT;

    void reset() _NOEXCEPT;

    template<class _Yp>
        typename enable_if
        	<
            	is_convertible<_Yp*, element_type*>::value,
            	void
        	>::type
    reset(_Yp* __p);

    template<class _Yp, class _Dp>
        typename enable_if
        	<
            	is_convertible<_Yp*, element_type*>::value,
            	void
        	>::type
    reset(_Yp* __p, _Dp __d);

    template<class _Yp, class _Dp, class _Alloc>
        typename enable_if
        	<
            	is_convertible<_Yp*, element_type*>::value,
            	void
        	>::type
    reset(_Yp* __p, _Dp __d, _Alloc __a);

    element_type* get() const _NOEXCEPT {return __ptr_;}

    typename add_lvalue_reference<element_type>::type operator*() const _NOEXCEPT
        {return *__ptr_;}

    element_type* operator->() const _NOEXCEPT {return __ptr_;}

    long use_count() const _NOEXCEPT {return __cntrl_ ? __cntrl_->use_count() : 0;}

    bool unique() const _NOEXCEPT {return use_count() == 1;}

    operator bool() const _NOEXCEPT {return get() != 0;}

    template <class _Up>
    bool owner_before(shared_ptr<_Up> const& __p) const
    {return __cntrl_ < __p.__cntrl_;}

    template <class _Up>
    bool owner_before(weak_ptr<_Up> const& __p) const
    {return __cntrl_ < __p.__cntrl_;}

    bool
    __owner_equivalent(const shared_ptr& __p) const
    {return __cntrl_ == __p.__cntrl_;}

    template <class _Dp>
    _Dp* __get_deleter() const _NOEXCEPT
    {return (_Dp*)(__cntrl_ ? __cntrl_->__get_deleter(typeid(_Dp)) : 0);}

#ifndef _YJH_HAS_NO_VARIADICS

    template<class ..._Args>
    static shared_ptr<_Tp>
        make_shared(_Args&& ...__args);

    template<class _Alloc, class ..._Args>
    static shared_ptr<_Tp>
    	allocate_shared(const _Alloc& __a, _Args&& ...__args);
#endif

private:

    template <class _Yp>
    void
    __enable_weak_this(const enable_shared_from_this<_Yp>* __e) _NOEXCEPT
    {
        if (__e)
            __e->__weak_this_ = *this;
    }

    void __enable_weak_this(const void*) _NOEXCEPT {}

    template <class _Up> friend class shared_ptr;
    template <class _Up> friend class weak_ptr;
};

template <class _Tp>
shared_ptr<_Tp>::shared_ptr() noexcept
	:	__ptr_(0),
		__cntrl_(0)
{}

template <class _Tp>
shared_ptr<_Tp>::shared_ptr(nullptr_t) noexcept
	:	__ptr_(0),
		__cntrl_(0)
{}

template <class _Tp>
template <class _Yp, class>
/**
 * # 注意这个地方的的的定义
	template <	class _Yp,
				class = typename enable_if<
					is_convertible<_Yp*, element_type*>::value
					>::type
			 >
	省略掉了 enable_if 的部分，只留下了一个 class
 */
shared_ptr<_Tp>::shared_ptr(_Yp* __p)
	:	__ptr_(__p)
{
	unique_ptr<_Yp> __hold(__p);
	typedef __shared_ptr_pointer<_Yp*, default_delete<_Yp>, allocator<_Yp> > _CntrlBlk;
	__cntrl_ = new _CntrlBlk(__p, default_delete<_Yp>(), allocator<_Yp>());
	__hold.release();
	__enable_weak_this(__p);
}

template <class _Tp>
template <class _Yp, class _Dp, class>
shared_ptr<_Tp>::shared_ptr(_Yp* __p, _Dp __d)
	:	__ptr_(__p)
{
	try
	{
		typedef __shared_ptr_pointer<_Yp*, _Dp, allocator<_Yp> > _CntrlBlk;
		__cntrl_ = new _CntrlBlk(__p, __d, allocator<_Yp>());
		__enable_weak_this(__p);
	}
	catch(...)
	{
		__d(__p);
		throw;
	}
}

template <class _Tp>
template <class _Dp>
shared_ptr<_Tp>::shared_ptr(nullptr_t __p, _Dp __d)
	:	__ptr_(0)
{
	try
	{
		typedef __shared_ptr_pointer<nullptr_t*, _Dp, allocator<_Tp> > _CntrlBlk;
		__cntrl_ = new _CntrlBlk(__p, __d, allocator<_Tp>());
		__enable_weak_this(__p);
	}
	catch(...)
	{
		__d(__p);
		throw;
	}
}

template <class _Tp>
template <class _Yp, class _Dp, class _Alloc, class>
shared_ptr<_Tp>::shared_ptr(_Yp* __p, _Dp __d, _Alloc __a)
	:	__ptr_(__p)
{
	try
	{
		typedef __shared_ptr_pointer<_Yp*, _Dp, _Alloc> _CntrlBlk;
		typedef typename _Alloc::template rebind<_CntrlBlk>::other _A2;	// allocator<_CntrlBlk>
		typedef __allocator_destructor<_A2> _D2;
		_A2 _a2(__a);	// _A2 是一个 CntrlBlk 的内存分配器
		unique_ptr<_CntrlBlk, _D2> __hold2(_a2.allocate(1), _D2(_a2, 1));
		//这里的  unique_ptr 在进行析构的时候会自动调用 __allocator_destructor<_A2>的 operator() 函数
		// operator(pointer) 自动调用 allocator 的 deallocator 函数释放内存
		::new(__hold2.get())  _CntrlBlk(__p, __d, __a);	// unique_ptr 中存的是一段没有初始化的原始内存
		__cntrl_ = __hold2.release();
		__enable_weak_this(__p);
	}
	catch(...)
	{
		__d(__p);
		throw;
	}
}

template <class _Tp>
template <class _Dp, class _Alloc>
shared_ptr<_Tp>::shared_ptr(nullptr_t __p, _Dp __d, _Alloc __a)
	: __ptr_(0)
{
    try
    {
        typedef __shared_ptr_pointer<nullptr_t, _Dp, _Alloc> _CntrlBlk;
        typedef typename _Alloc::template rebind<_CntrlBlk>::other _A2;
        typedef __allocator_destructor<_A2> _D2;
        _A2 __a2(__a);
        unique_ptr<_CntrlBlk, _D2> __hold2(__a2.allocate(1), _D2(__a2, 1));
        ::new(__hold2.get()) _CntrlBlk(__p, __d, __a);
        __cntrl_ = __hold2.release();
    }
    catch (...)
    {
        __d(__p);
        throw;
    }
}

template<class _Tp>
template<class _Yp>
inline
shared_ptr<_Tp>::shared_ptr(const shared_ptr<_Yp>& __r, element_type *__p) _NOEXCEPT
    : __ptr_(__p),
      __cntrl_(__r.__cntrl_)
{
    if (__cntrl_)
        __cntrl_->__add_shared();	/*这个 __add_shared() 怎么实现的，没有写*/
}

template<class _Tp>
inline
shared_ptr<_Tp>::shared_ptr(const shared_ptr& __r) _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    if (__cntrl_)
        __cntrl_->__add_shared();
}

template<class _Tp>
template<class _Yp>
inline
shared_ptr<_Tp>::shared_ptr(const shared_ptr<_Yp>& __r,
                            typename enable_if
								<
									is_convertible<_Yp*, _Tp*>::value, 
									__nat
								>::type
							)
         _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    if (__cntrl_)
        __cntrl_->__add_shared();
}

template<class _Tp>
inline
/**
 * 进行指针所有权的转移
 */
shared_ptr<_Tp>::shared_ptr(shared_ptr&& __r) _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    __r.__ptr_ = 0;
    __r.__cntrl_ = 0;
}

template<class _Tp>
template<class _Yp>
inline
shared_ptr<_Tp>::shared_ptr(shared_ptr<_Yp>&& __r,
                            typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type)
         _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    __r.__ptr_ = 0;
    __r.__cntrl_ = 0;
}

template<class _Tp>
template<class _Yp, class>
shared_ptr<_Tp>::shared_ptr(auto_ptr<_Yp>&& __r)
    : __ptr_(__r.get())
{
    typedef __shared_ptr_pointer<_Yp*, default_delete<_Yp>, allocator<_Yp> > _CntrlBlk;
    __cntrl_ = new _CntrlBlk(__r.get(), default_delete<_Yp>(), allocator<_Yp>());
    __enable_weak_this(__r.get());
    __r.release();	/*交出指针的拥有权*/
}

template<class _Tp>
template <class _Yp, class _Dp, class>
shared_ptr<_Tp>::shared_ptr(unique_ptr<_Yp, _Dp>&& __r,
           typename enable_if<!is_lvalue_reference<_Dp>::value, __nat>::type)
    : __ptr_(__r.get())
{
    typedef __shared_ptr_pointer<_Yp*, _Dp, allocator<_Yp> > _CntrlBlk;
    __cntrl_ = new _CntrlBlk(__r.get(), __r.get_deleter(), allocator<_Yp>());
    __enable_weak_this(__r.get());
    __r.release();
}

template<class _Tp>
template <class _Yp, class _Dp, class>
shared_ptr<_Tp>::shared_ptr(unique_ptr<_Yp, _Dp>&& __r,
           typename enable_if<is_lvalue_reference<_Dp>::value, __nat>::type)
    : __ptr_(__r.get())
{
    typedef __shared_ptr_pointer<_Yp*,
                                 reference_wrapper<typename remove_reference<_Dp>::type>,
                                 allocator<_Yp> > _CntrlBlk;
    __cntrl_ = new _CntrlBlk(__r.get(), ref(__r.get_deleter()), allocator<_Yp>());
    __enable_weak_this(__r.get());
    __r.release();
}

#ifndef _YJH_HAS_NO_VARIADICS

template<class _Tp>
template<class ..._Args>
shared_ptr<_Tp>
shared_ptr<_Tp>::make_shared(_Args&& ...__args)
{
    typedef __shared_ptr_emplace<_Tp, allocator<_Tp> > _CntrlBlk;
    typedef allocator<_CntrlBlk> _A2;
    typedef __allocator_destructor<_A2> _D2;
    _A2 __a2;
    unique_ptr<_CntrlBlk, _D2> __hold2(__a2.allocate(1), _D2(__a2, 1));
    ::new(__hold2.get()) _CntrlBlk(__a2, yjh_def::forward<_Args>(__args)...);
    shared_ptr<_Tp> __r;
    __r.__ptr_ = __hold2.get()->get();
    __r.__cntrl_ = __hold2.release();
    __r.__enable_weak_this(__r.__ptr_);
    return __r;
}

#endif
























// weak_ptr
template<class _Tp>
class weak_ptr
{
public:
    typedef _Tp element_type;
private:
    element_type*        __ptr_;
    __shared_weak_count* __cntrl_;

public:
    weak_ptr() _NOEXCEPT;
    template<class _Yp> weak_ptr(shared_ptr<_Yp> const& __r,
                   typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type = 0)
                        _NOEXCEPT;

    weak_ptr(weak_ptr const& __r) _NOEXCEPT;

    template<class _Yp> weak_ptr(weak_ptr<_Yp> const& __r,
                   typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type = 0)
                         _NOEXCEPT;

#ifndef _YJH_HAS_NO_RVALUE_REFERENCES
    weak_ptr(weak_ptr&& __r) _NOEXCEPT;
    template<class _Yp> weak_ptr(weak_ptr<_Yp>&& __r,
                   typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type = 0)
                         _NOEXCEPT;
#endif  // _YJH_HAS_NO_RVALUE_REFERENCES
    ~weak_ptr();

    weak_ptr& operator=(weak_ptr const& __r) _NOEXCEPT;

    template<class _Yp>
        typename enable_if
        <
            is_convertible<_Yp*, element_type*>::value,
            weak_ptr&
        >::type
        operator=(weak_ptr<_Yp> const& __r) _NOEXCEPT;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    weak_ptr& operator=(weak_ptr&& __r) _NOEXCEPT;

    template<class _Yp>
        typename enable_if
        <
            is_convertible<_Yp*, element_type*>::value,
            weak_ptr&
        >::type
        operator=(weak_ptr<_Yp>&& __r) _NOEXCEPT;

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Yp>
        typename enable_if
        <
            is_convertible<_Yp*, element_type*>::value,
            weak_ptr&
        >::type
        operator=(shared_ptr<_Yp> const& __r) _NOEXCEPT;

    void swap(weak_ptr& __r) _NOEXCEPT;

    void reset() _NOEXCEPT;

    long use_count() const _NOEXCEPT
	/**
	 * 字面理解，当前有多少个对象持有该指针
	 */
        {return __cntrl_ ? __cntrl_->use_count() : 0;}

    bool expired() const _NOEXCEPT
	/**
	 * 指针是否已经过期，已经没人使用
	 */
        {return __cntrl_ == 0 || __cntrl_->use_count() == 0;}

    shared_ptr<_Tp> lock() const _NOEXCEPT;

    template<class _Up>
        bool owner_before(const shared_ptr<_Up>& __r) const
        {return __cntrl_ < __r.__cntrl_;}

    template<class _Up>
        bool owner_before(const weak_ptr<_Up>& __r) const
        {return __cntrl_ < __r.__cntrl_;}

    template <class _Up> friend class weak_ptr;
    template <class _Up> friend class shared_ptr;
};

template<class _Tp>
inline
weak_ptr<_Tp>::weak_ptr() _NOEXCEPT
    : __ptr_(0),
      __cntrl_(0)
{
}

template<class _Tp>
inline
/**
 * 拷贝过程
 */
weak_ptr<_Tp>::weak_ptr(weak_ptr const& __r) _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    if (__cntrl_)
        __cntrl_->__add_weak();
}

template<class _Tp>
template<class _Yp>
inline
weak_ptr<_Tp>::weak_ptr(shared_ptr<_Yp> const& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
                         _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    if (__cntrl_)
        __cntrl_->__add_weak();
}

template<class _Tp>
template<class _Yp>
inline
weak_ptr<_Tp>::weak_ptr(weak_ptr<_Yp> const& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
         _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    if (__cntrl_)
        __cntrl_->__add_weak();
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
inline
weak_ptr<_Tp>::weak_ptr(weak_ptr&& __r) _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    __r.__ptr_ = 0;
    __r.__cntrl_ = 0;
}

template<class _Tp>
template<class _Yp>
inline
weak_ptr<_Tp>::weak_ptr(weak_ptr<_Yp>&& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
         _NOEXCEPT
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_)
{
    __r.__ptr_ = 0;
    __r.__cntrl_ = 0;
}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
weak_ptr<_Tp>::~weak_ptr()
{
    if (__cntrl_)
        __cntrl_->__release_weak();
}

template<class _Tp>
inline
weak_ptr<_Tp>&
weak_ptr<_Tp>::operator=(weak_ptr const& __r) _NOEXCEPT
{
    weak_ptr(__r).swap(*this);	
	/**
	 * weak_ptr(__r) 是一个临时对象 当前的 weak_ptr 中的内容被存储到这个临时对象当中
	 * 在函数结束的时候自动被销毁掉
	 */
    return *this;
}

template<class _Tp>
template<class _Yp>
inline
typename enable_if
<
    is_convertible<_Yp*, _Tp*>::value,
    weak_ptr<_Tp>&
>::type
weak_ptr<_Tp>::operator=(weak_ptr<_Yp> const& __r) _NOEXCEPT
{
    weak_ptr(__r).swap(*this);
    return *this;
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
inline
weak_ptr<_Tp>&
weak_ptr<_Tp>::operator=(weak_ptr&& __r) _NOEXCEPT
{
    weak_ptr(yjh_def::move(__r)).swap(*this);
    return *this;
}

template<class _Tp>
template<class _Yp>
inline
typename enable_if
<
    is_convertible<_Yp*, _Tp*>::value,
    weak_ptr<_Tp>&
>::type
weak_ptr<_Tp>::operator=(weak_ptr<_Yp>&& __r) _NOEXCEPT
{
    weak_ptr(yjh_def::move(__r)).swap(*this);
    return *this;
}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
template<class _Yp>
inline
typename enable_if
<
    is_convertible<_Yp*, _Tp*>::value,
    weak_ptr<_Tp>&
>::type
weak_ptr<_Tp>::operator=(shared_ptr<_Yp> const& __r) _NOEXCEPT
{
    weak_ptr(__r).swap(*this);
    return *this;
}

template<class _Tp>
inline
void
weak_ptr<_Tp>::swap(weak_ptr& __r) _NOEXCEPT
{
    yjh_def::swap(__ptr_, __r.__ptr_);
    yjh_def::swap(__cntrl_, __r.__cntrl_);
}

template<class _Tp>
inline
void
swap(weak_ptr<_Tp>& __x, weak_ptr<_Tp>& __y) _NOEXCEPT
{
    __x.swap(__y);
}

template<class _Tp>
inline
void
weak_ptr<_Tp>::reset() _NOEXCEPT
{
    weak_ptr().swap(*this);
}

template<class _Tp>
template<class _Yp>
shared_ptr<_Tp>::shared_ptr(const weak_ptr<_Yp>& __r,
                            typename enable_if
								<
									is_convertible<_Yp*, _Tp*>::value, 
									__nat
								>::type
							)
    : __ptr_(__r.__ptr_),
      __cntrl_(__r.__cntrl_ ? __r.__cntrl_->lock() : __r.__cntrl_)
{
    if (__cntrl_ == 0)
#ifndef _YJH_NO_EXCEPTIONS
        throw bad_weak_ptr();
#else
        assert(!"bad_weak_ptr");
#endif
}

template<class _Tp>
shared_ptr<_Tp>
weak_ptr<_Tp>::lock() const _NOEXCEPT
{
    shared_ptr<_Tp> __r;
    __r.__cntrl_ = __cntrl_ ? __cntrl_->lock() : __cntrl_;
    if (__r.__cntrl_)
        __r.__ptr_ = __ptr_;
    return __r;
}


template <class _Tp> struct owner_less;

template <class _Tp>
struct owner_less<shared_ptr<_Tp> >
    : binary_function<shared_ptr<_Tp>, shared_ptr<_Tp>, bool>
{
    typedef bool result_type;
    bool operator()(shared_ptr<_Tp> const& __x, shared_ptr<_Tp> const& __y) const
        {return __x.owner_before(__y);}

    bool operator()(shared_ptr<_Tp> const& __x,   weak_ptr<_Tp> const& __y) const
        {return __x.owner_before(__y);}

    bool operator()(  weak_ptr<_Tp> const& __x, shared_ptr<_Tp> const& __y) const
        {return __x.owner_before(__y);}
};

template <class _Tp>
struct owner_less<weak_ptr<_Tp> >
    : binary_function<weak_ptr<_Tp>, weak_ptr<_Tp>, bool>
{
    typedef bool result_type;
    bool operator()(  weak_ptr<_Tp> const& __x,   weak_ptr<_Tp> const& __y) const
        {return __x.owner_before(__y);}

    bool operator()(shared_ptr<_Tp> const& __x,   weak_ptr<_Tp> const& __y) const
        {return __x.owner_before(__y);}

    bool operator()(  weak_ptr<_Tp> const& __x, shared_ptr<_Tp> const& __y) const
        {return __x.owner_before(__y);}
};

template<class _Tp>
class enable_shared_from_this
{
    mutable weak_ptr<_Tp> __weak_this_;
protected:
    enable_shared_from_this() _NOEXCEPT {}

    enable_shared_from_this(enable_shared_from_this const&) _NOEXCEPT {}

    enable_shared_from_this& operator=(enable_shared_from_this const&) _NOEXCEPT
        {return *this;}

    ~enable_shared_from_this() {}
public:

    shared_ptr<_Tp> shared_from_this()
        {return shared_ptr<_Tp>(__weak_this_);}

    shared_ptr<_Tp const> shared_from_this() const
        {return shared_ptr<const _Tp>(__weak_this_);}

    template <class _Up> friend class shared_ptr;
};


// --helper for container swap --
template <typename _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void __swap_allocator(_Alloc & __a1, _Alloc & __a2)
	#if _LIBCPP_STD_VER >= 14
		_NOEXCEPT
	#else
		_NOEXCEPT_(__is_nothrow_swappable<_Alloc>::value)
	#endif
{
	__swap_allocator(__a1, __a2,
			integral_constant<bool, yjh_def::allocator_traits<_Alloc>::propagate_on_container_swap::value>());
}

template <class _Alloc>
_LIBCPP_INLINE_VISIBILITY
void __swap_allocator(_Alloc & __a1, _Alloc & __a2, true_type)
	#if _LIBCPP_STD_VER >= 14
		_NOEXCEPT
	#else
		_NOEXCEPT_(__is_nothrow_swappable<_Alloc>::value)
	#endif
{
	using yjh_def::swap;
	swap(__a1, __a2);
}

template <class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void __swap_allocator(_Alloc&, _Alloc&, false_type) _NOEXCEPT {}





// __temp_value
template <class _Tp, class _Alloc>
struct __temp_value
{
	typedef allocator_traits<_Alloc> _Traits;

	/**
	 * aligned_storage::type [其实是一个结构体] 中至少有 sizeof(_Tp) 字节的空间，但是为了内存对齐，这个空间的
	 * 大小可能大于这个数值，使用这些存储空间存储 _Tp 的实例
	 * 比方说，数据有9个字节大小，但是内存对齐之后占用 16 个字节
	 */
	typename aligned_storage<sizeof(_Tp), alignof(_Tp)>::type __v;

	_Alloc& __a;

	_Tp* __addr() { return reinterpret_cast<_Tp*>(addressof(__v)); }

	_Tp& 	get() { return *__addr(); }

	template <class... _Args>
	__temp_value(_Alloc& __alloc, _Args&& ... _args) : __a(__alloc)
	{
		_Traits::construct(__a, reinterpret_cast<_Tp*>(addressof(__v)),
					yjh_def::forward<_Args>(_args)...);
	}

	~__temp_value() { _Traits::destroy(__a, __addr()); }
};


}
#endif // !_YJH_MEMORY


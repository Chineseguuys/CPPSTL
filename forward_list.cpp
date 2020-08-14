#ifndef _LIBCPP_FORWARD_LIST
#define _LIBCPP_FORWARD_LIST



#include "__config.cpp"
#include "initializer_list.cpp"
#include "memory.cpp"
#include "limits.cpp"
#include "iterator.cpp"
#include "algorithm.cpp"


#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"

namespace yjh_def
{

template <class _Tp, class _VoidPtr> struct __forward_list_node;
template <class _NodePtr> struct __forward_begin_node;


template <class>
struct __forward_list_node_value_type;

template <class _Tp, class _VoidPtr>
struct __forward_list_node_value_type<__forward_list_node<_Tp, _VoidPtr> > {
  typedef _Tp type;
};


template <class _NodePtr>
struct __forward_node_traits
{
	typedef typename remove_cv<typename pointer_traits<_NodePtr>::element_type>::type   __node;
	typedef typename __forward_list_node_value_type<__node>::type    __node_value_type;
	typedef _NodePtr        __node_pointer;
	typedef __forward_begin_node<_NodePtr>      __begin_node;
	typedef typename __rebind_pointer<_NodePtr, __begin_node>::type
																__begin_node_pointer;   //__begin_node*
	typedef typename __rebind_pointer<_NodePtr, void>::type     __void_pointer;         // void*
	
	#if defined(_LIBCPP_ABI_FORWARD_LIST_REMOVE_NODE_POINTER_UB)
		typedef __begin_node_pointer __iter_node_pointer;
	#else
		typedef typename conditional<
				is_pointer<__void_pointer>::value,
				__begin_node_pointer,   // __forward_begin_node*
				__node_pointer          // __forward_list_node*
			>::type __iter_node_pointer;
	#endif
	typedef typename conditional<
		is_same<__iter_node_pointer, __node_pointer>::value,
		__begin_node_pointer,
		__node_pointer
		>::type __non_iter_node_pointer;

	_LIBCPP_INLINE_VISIBILITY
	static __iter_node_pointer __as_iter_node(__iter_node_pointer __p) {
		return __p;
	}

	_LIBCPP_INLINE_VISIBILITY
	static __iter_node_pointer __as_iter_node(__non_iter_node_pointer __p) {
		return static_cast<__iter_node_pointer>(static_cast<__void_pointer>(__p));
	}
};

// __forward_begin_node
template <class _NodePtr>
struct __forward_begin_node
{
    typedef _NodePtr pointer;
    typedef typename __rebind_pointer<_NodePtr, __forward_begin_node>::type __begin_node_pointer;

    pointer __next_;    // __forward_list_node<_Tp, _VoidPtr>*

    _LIBCPP_INLINE_VISIBILITY __forward_begin_node() : __next_(nullptr) {}

    _LIBCPP_INLINE_VISIBILITY
    __begin_node_pointer __next_as_begin() const {
        return static_cast<__begin_node_pointer>(__next_);
        // 这里是上转型， __forward_list_node* ==> __forward_begin_node* 
    }
};

// __begin_node_of
template <class _Tp, class _VoidPtr>
struct _LIBCPP_HIDDEN __begin_node_of
{
    typedef __forward_begin_node<
        typename __rebind_pointer<_VoidPtr, __forward_list_node<_Tp, _VoidPtr> >::type  // __forward_list_node<_Tp, _VoidPtr>*
    > type;
};

// __forward_list_node
template <class _Tp, class _VoidPtr>
struct __forward_list_node
    : public __begin_node_of<_Tp, _VoidPtr>::type   
        //: public  __forward_begin_node<__forward_list_node<_Tp, _VoidPtr>>
{
    typedef _Tp value_type;

    value_type __value_;
};

template <class _Tp, class _Alloc = allocator<_Tp> > class forward_list;
template <class _NodeConstPtr> class __forward_list_const_iterator;

template <class _NodePtr>
class __forward_list_iterator
{
	typedef __forward_node_traits<_NodePtr>         __traits;
    typedef typename __traits::__node_pointer       __node_pointer;
    typedef typename __traits::__begin_node_pointer __begin_node_pointer;
    typedef typename __traits::__iter_node_pointer  __iter_node_pointer;    //
    typedef typename __traits::__void_pointer       __void_pointer;

	__iter_node_pointer __ptr_;

	__begin_node_pointer __get_begin() const 
	{
		return static_cast<__begin_node_pointer>(
			static_cast<__void_pointer>(__ptr_)
		);
	}

	__node_pointer __get_unsafe_node_pointer() const    // 为什么这叫 unsafe
    // 如果 __ptr_ 是  _forward_begin_node* 类型的，那么这里的强制转换就是从父类的指针向子类的
    // 指针的转换，当然这是不安全的
	{
        return static_cast<__node_pointer>(
                static_cast<__void_pointer>(__ptr_));
	}

_LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_iterator(nullptr_t) _NOEXCEPT : __ptr_(nullptr) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_iterator(__begin_node_pointer __p) _NOEXCEPT    // __forward_begin_node*
        : __ptr_(__traits::__as_iter_node(__p)) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_iterator(__node_pointer __p) _NOEXCEPT  // __forward_list_node*
        : __ptr_(__traits::__as_iter_node(__p)) {}

    template<class, class> friend class _LIBCPP_TEMPLATE_VIS forward_list;

    template<class> friend class _LIBCPP_TEMPLATE_VIS __forward_list_const_iterator;

public:
    typedef forward_iterator_tag                              iterator_category;
	// 迭代器的类型为前向迭代器，即只能依此向前，不能向后
    typedef typename __traits::__node_value_type              value_type;
    typedef value_type&                                       reference;
    typedef typename pointer_traits<__node_pointer>::difference_type
                                                              difference_type;
    typedef typename __rebind_pointer<__node_pointer, value_type>::type pointer;	// value_type*

    _LIBCPP_INLINE_VISIBILITY
    __forward_list_iterator() _NOEXCEPT : __ptr_(nullptr) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __get_unsafe_node_pointer()->__value_;}
    // __value_ 是 __forward_list_node 的成员
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {
        return pointer_traits<pointer>::pointer_to(__get_unsafe_node_pointer()->__value_);
    }

    _LIBCPP_INLINE_VISIBILITY
    __forward_list_iterator& operator++()
    {
        __ptr_ = __traits::__as_iter_node(__ptr_->__next_);
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY
    __forward_list_iterator operator++(int)
    {
        __forward_list_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __forward_list_iterator& __x,
                    const __forward_list_iterator& __y)
        {return __x.__ptr_ == __y.__ptr_;}
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __forward_list_iterator& __x,
                    const __forward_list_iterator& __y)
        {return !(__x == __y);}
};

template <class _NodeConstPtr>
class _LIBCPP_TEMPLATE_VIS __forward_list_const_iterator
{
    static_assert((!is_const<typename pointer_traits<_NodeConstPtr>::element_type>::value), "");
    typedef _NodeConstPtr _NodePtr;

    typedef __forward_node_traits<_NodePtr>         __traits;
    typedef typename __traits::__node               __node;
    typedef typename __traits::__node_pointer       __node_pointer;
    typedef typename __traits::__begin_node_pointer __begin_node_pointer;
    typedef typename __traits::__iter_node_pointer  __iter_node_pointer;
    typedef typename __traits::__void_pointer       __void_pointer;

    __iter_node_pointer __ptr_;

    __begin_node_pointer __get_begin() const {
        return static_cast<__begin_node_pointer>(
                static_cast<__void_pointer>(__ptr_));
    }
    __node_pointer __get_unsafe_node_pointer() const {
        return static_cast<__node_pointer>(
                static_cast<__void_pointer>(__ptr_));
    }

    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_const_iterator(nullptr_t) _NOEXCEPT
        : __ptr_(nullptr) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_const_iterator(__begin_node_pointer __p) _NOEXCEPT
        : __ptr_(__traits::__as_iter_node(__p)) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_const_iterator(__node_pointer __p) _NOEXCEPT
        : __ptr_(__traits::__as_iter_node(__p)) {}


    template<class, class> friend class forward_list;

public:
    typedef forward_iterator_tag                              iterator_category;
    typedef typename __traits::__node_value_type              value_type;
    typedef const value_type&                                 reference;
    typedef typename pointer_traits<__node_pointer>::difference_type
                                                              difference_type;
    typedef typename __rebind_pointer<__node_pointer, const value_type>::type
                                                              pointer;

    _LIBCPP_INLINE_VISIBILITY
    __forward_list_const_iterator() _NOEXCEPT : __ptr_(nullptr) {}
    _LIBCPP_INLINE_VISIBILITY
    __forward_list_const_iterator(__forward_list_iterator<__node_pointer> __p) _NOEXCEPT
        : __ptr_(__p.__ptr_) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __get_unsafe_node_pointer()->__value_;}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(
                __get_unsafe_node_pointer()->__value_);}

    _LIBCPP_INLINE_VISIBILITY
    __forward_list_const_iterator& operator++()
    {
        __ptr_ = __traits::__as_iter_node(__ptr_->__next_);
        return *this;
    }

    _LIBCPP_INLINE_VISIBILITY
    __forward_list_const_iterator operator++(int)
    {
        __forward_list_const_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __forward_list_const_iterator& __x,
                    const __forward_list_const_iterator& __y)
        {return __x.__ptr_ == __y.__ptr_;}
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __forward_list_const_iterator& __x,
                           const __forward_list_const_iterator& __y)
        {return !(__x == __y);}
};

// __forward_list_base
template <class _Tp, class _Alloc>
/**
 * _Tp 是节点需要存储的数据类型
 * _Alloc 是数据的分配器
 */
class __forward_list_base
{
protected:
    typedef _Tp         value_type;
    typedef _Alloc      allocator_type;

    typedef typename allocator_traits<allocator_type>::void_pointer     void_pointer;   // void*
    typedef __forward_list_node<value_type, void_pointer>               __node;
    typedef typename __begin_node_of<value_type, void_pointer>::type    __begin_node;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>, __node>::type __node_allocator;
    typedef allocator_traits<__node_allocator>        __node_traits;
    typedef typename __node_traits::pointer           __node_pointer;

    typedef typename __rebind_alloc_helper<
        allocator_traits<allocator_type>, __begin_node
    >::type                                           __begin_node_allocator;
    typedef typename allocator_traits<__begin_node_allocator>::pointer
                                                      __begin_node_pointer;

    static_assert((!is_same<allocator_type, __node_allocator>::value),
                  "internal allocator type must differ from user-specified "
                  "type; otherwise overload resolution breaks");

    __compressed_pair<__begin_node, __node_allocator> __before_begin_;
    // __begin_node 即链表的开始节点，不存储任何数据的节点，不是使用 new 进行分配的
    // 数据节点 __forward_list_node == __node 是使用 new 进行动态分配的

    _LIBCPP_INLINE_VISIBILITY
    __begin_node_pointer        __before_begin() _NOEXCEPT
        {return pointer_traits<__begin_node_pointer>::pointer_to(__before_begin_.first());}
    _LIBCPP_INLINE_VISIBILITY
    __begin_node_pointer __before_begin() const _NOEXCEPT
        {return pointer_traits<__begin_node_pointer>::pointer_to(const_cast<__begin_node&>(__before_begin_.first()));}

    _LIBCPP_INLINE_VISIBILITY
          __node_allocator& __alloc() _NOEXCEPT
            {return __before_begin_.second();}
    _LIBCPP_INLINE_VISIBILITY
    const __node_allocator& __alloc() const _NOEXCEPT
        {return __before_begin_.second();}

    // iterator
    typedef __forward_list_iterator<__node_pointer>             iterator;
    typedef __forward_list_const_iterator<__node_pointer>       const_iterator;

    _LIBCPP_INLINE_VISIBILITY
    __forward_list_base()
        _NOEXCEPT_(is_nothrow_default_constructible<__node_allocator>::value)
        : __before_begin_(__begin_node()) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_base(const allocator_type& __a)
        : __before_begin_(__begin_node(), __node_allocator(__a)) {}
    _LIBCPP_INLINE_VISIBILITY
    explicit __forward_list_base(const __node_allocator& __a)
        : __before_begin_(__begin_node(), __a) {}
#ifndef _LIBCPP_CXX03_LANG
public:
    _LIBCPP_INLINE_VISIBILITY
    __forward_list_base(__forward_list_base&& __x)
        _NOEXCEPT_(is_nothrow_move_constructible<__node_allocator>::value);
    _LIBCPP_INLINE_VISIBILITY
    __forward_list_base(__forward_list_base&& __x, const allocator_type& __a);
#endif  // _LIBCPP_CXX03_LANG

private:
    __forward_list_base(const __forward_list_base&);
    __forward_list_base& operator=(const __forward_list_base&);

public:
    ~__forward_list_base();

protected:
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __forward_list_base& __x)
        {__copy_assign_alloc(__x, integral_constant<bool,
              __node_traits::propagate_on_container_copy_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__forward_list_base& __x)
        _NOEXCEPT_(!__node_traits::propagate_on_container_move_assignment::value ||
                   is_nothrow_move_assignable<__node_allocator>::value)
        {__move_assign_alloc(__x, integral_constant<bool,
              __node_traits::propagate_on_container_move_assignment::value>());}

public:
    _LIBCPP_INLINE_VISIBILITY
    void swap(__forward_list_base& __x)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(!__node_traits::propagate_on_container_move_assignment::value ||
                    __is_nothrow_swappable<__node_allocator>::value);
#endif
protected:
    void clear() _NOEXCEPT;

private:
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __forward_list_base&, false_type) {}
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __forward_list_base& __x, true_type)
    {
        if (__alloc() != __x.__alloc())
            clear();
        __alloc() = __x.__alloc();
    }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__forward_list_base&, false_type) _NOEXCEPT
        {}
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__forward_list_base& __x, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<__node_allocator>::value)
        {__alloc() = yjh_def::move(__x.__alloc());}
};

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Alloc>
inline
__forward_list_base<_Tp, _Alloc>::__forward_list_base(__forward_list_base&& __x)
        _NOEXCEPT_(is_nothrow_move_constructible<__node_allocator>::value)
    : __before_begin_(yjh_def::move(__x.__before_begin_))
{
    __x.__before_begin()->__next_ = nullptr;
}

template <class _Tp, class _Alloc>
inline
__forward_list_base<_Tp, _Alloc>::__forward_list_base(__forward_list_base&& __x,
                                                      const allocator_type& __a)
    : __before_begin_(__begin_node(), __node_allocator(__a))
{
    if (__alloc() == __x.__alloc())
    {
        __before_begin()->__next_ = __x.__before_begin()->__next_;
        __x.__before_begin()->__next_ = nullptr;
    }
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Alloc>
__forward_list_base<_Tp, _Alloc>::~__forward_list_base()
{
    clear();
}

template <class _Tp, class _Alloc>
inline
void
__forward_list_base<_Tp, _Alloc>::swap(__forward_list_base& __x)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT
#else
        _NOEXCEPT_(!__node_traits::propagate_on_container_move_assignment::value ||
                    __is_nothrow_swappable<__node_allocator>::value)
#endif
{
    __swap_allocator(__alloc(), __x.__alloc(),
            integral_constant<bool, __node_traits::propagate_on_container_swap::value>());
    using yjh_def::swap;
    swap(__before_begin()->__next_, __x.__before_begin()->__next_);
}

template <class _Tp, class _Alloc>
void
__forward_list_base<_Tp, _Alloc>::clear() _NOEXCEPT
{
    __node_allocator& __a = __alloc();
    for (__node_pointer __p = __before_begin()->__next_; __p != nullptr;)
    {
        __node_pointer __next = __p->__next_;
        __node_traits::destroy(__a, yjh_def::addressof(__p->__value_));
        __node_traits::deallocate(__a, __p, 1);
        __p = __next;
    }
    __before_begin()->__next_ = nullptr;
}

template <class _Tp, class _Alloc>
class forward_list
	: private __forward_list_base<_Tp, _Alloc>
{
	typedef __forward_list_base<_Tp, _Alloc> base;
    typedef typename base::__node_allocator  	__node_allocator;
    typedef typename base::__node               __node;
    typedef typename base::__node_traits        __node_traits;
    typedef typename base::__node_pointer       __node_pointer;
    typedef typename base::__begin_node_pointer __begin_node_pointer;

public:
	typedef _Tp    value_type;
    typedef _Alloc allocator_type;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");
	
	typedef value_type&                                                reference;
    typedef const value_type&                                          const_reference;
    typedef typename allocator_traits<allocator_type>::pointer         pointer;
    typedef typename allocator_traits<allocator_type>::const_pointer   const_pointer;
    typedef typename allocator_traits<allocator_type>::size_type       size_type;
    typedef typename allocator_traits<allocator_type>::difference_type difference_type;

	typedef typename base::iterator			iterator;
	typedef typename base::const_iterator 	const_iterator;

	#if _LIBCPP_STD_VER > 17
    	typedef size_type                                __remove_return_type;
	#else
    	typedef void                                     __remove_return_type;
	#endif

	forward_list()
		noexcept(is_nothrow_default_constructible<__node_allocator>::value)
	{}

// constructor
    _LIBCPP_INLINE_VISIBILITY
    explicit forward_list(const allocator_type& __a);
    explicit forward_list(size_type __n);
#if _LIBCPP_STD_VER > 11
    explicit forward_list(size_type __n, const allocator_type& __a);
#endif
    forward_list(size_type __n, const value_type& __v);
    forward_list(size_type __n, const value_type& __v, const allocator_type& __a);
    template <class _InputIterator>
        forward_list(_InputIterator __f, _InputIterator __l,
                     typename enable_if<
                       __is_input_iterator<_InputIterator>::value
                     >::type* = nullptr);
    template <class _InputIterator>
        forward_list(_InputIterator __f, _InputIterator __l,
                     const allocator_type& __a,
                     typename enable_if<
                       __is_input_iterator<_InputIterator>::value
                     >::type* = nullptr);
    forward_list(const forward_list& __x);
    forward_list(const forward_list& __x, const allocator_type& __a);

// copy assignment 
    forward_list& operator=(const forward_list& __x);

// move constructor
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    forward_list(forward_list&& __x)
        _NOEXCEPT_(is_nothrow_move_constructible<base>::value)
        : base(yjh_def::move(__x)) {}
    forward_list(forward_list&& __x, const allocator_type& __a);

    forward_list(initializer_list<value_type> __il);
    forward_list(initializer_list<value_type> __il, const allocator_type& __a);


// move assignment
    _LIBCPP_INLINE_VISIBILITY
    forward_list& operator=(forward_list&& __x)
        _NOEXCEPT_(
             __node_traits::propagate_on_container_move_assignment::value &&
             is_nothrow_move_assignable<allocator_type>::value);

    _LIBCPP_INLINE_VISIBILITY
    forward_list& operator=(initializer_list<value_type> __il);

    _LIBCPP_INLINE_VISIBILITY
    void assign(initializer_list<value_type> __il);
#endif  // _LIBCPP_CXX03_LANG

// assign
    template <class _InputIterator>
        typename enable_if
        <
            __is_input_iterator<_InputIterator>::value,
            void
        >::type
        assign(_InputIterator __f, _InputIterator __l);
    void assign(size_type __n, const value_type& __v);

// alloc()
    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT
        {return allocator_type(base::__alloc());}

// iterator
    _LIBCPP_INLINE_VISIBILITY
    iterator       begin() _NOEXCEPT
        {return       iterator(base::__before_begin()->__next_);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT
        {return const_iterator(base::__before_begin()->__next_);}
    _LIBCPP_INLINE_VISIBILITY
    iterator       end() _NOEXCEPT
        {return       iterator(nullptr);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end() const _NOEXCEPT
        {return const_iterator(nullptr);}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin() const _NOEXCEPT
        {return const_iterator(base::__before_begin()->__next_);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend() const _NOEXCEPT
        {return const_iterator(nullptr);}

    _LIBCPP_INLINE_VISIBILITY
    iterator       before_begin() _NOEXCEPT
        {return       iterator(base::__before_begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator before_begin() const _NOEXCEPT
        {return const_iterator(base::__before_begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbefore_begin() const _NOEXCEPT
        {return const_iterator(base::__before_begin());}
	
// found
    _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT
        {return base::__before_begin()->__next_ == nullptr;}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT {
        return std::min<size_type>(
            __node_traits::max_size(base::__alloc()),
            numeric_limits<difference_type>::max());
    }

    _LIBCPP_INLINE_VISIBILITY
    reference       front()       {return base::__before_begin()->__next_->__value_;}
    _LIBCPP_INLINE_VISIBILITY
    const_reference front() const {return base::__before_begin()->__next_->__value_;}

// modify
#ifndef _LIBCPP_CXX03_LANG
#if _LIBCPP_STD_VER > 14
    template <class... _Args> reference emplace_front(_Args&&... __args);
#else
    template <class... _Args> void      emplace_front(_Args&&... __args);
#endif
    void push_front(value_type&& __v);
#endif  // _LIBCPP_CXX03_LANG
    void push_front(const value_type& __v);

    void pop_front();

#ifndef _LIBCPP_CXX03_LANG
    template <class... _Args>
        iterator emplace_after(const_iterator __p, _Args&&... __args);

    iterator insert_after(const_iterator __p, value_type&& __v);
    iterator insert_after(const_iterator __p, initializer_list<value_type> __il)
        {return insert_after(__p, __il.begin(), __il.end());}
#endif  // _LIBCPP_CXX03_LANG
    iterator insert_after(const_iterator __p, const value_type& __v);
    iterator insert_after(const_iterator __p, size_type __n, const value_type& __v);
    template <class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        typename enable_if
        <
            __is_input_iterator<_InputIterator>::value,
            iterator
        >::type
        insert_after(const_iterator __p, _InputIterator __f, _InputIterator __l);

    iterator erase_after(const_iterator __p);
    iterator erase_after(const_iterator __f, const_iterator __l);

    _LIBCPP_INLINE_VISIBILITY
    void swap(forward_list& __x)
    /**
     * forward_list 中只定义了一系列的函数，所有的数据都存储在 __forward_base 类中
     * 所以交换的操作只进行基类的交换操作就可以了
     */
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT
#else
        _NOEXCEPT_(!__node_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<__node_allocator>::value)
#endif
        {base::swap(__x);}

    void resize(size_type __n);
    void resize(size_type __n, const value_type& __v);
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {base::clear();}

    _LIBCPP_INLINE_VISIBILITY
    void splice_after(const_iterator __p, forward_list&& __x);
    _LIBCPP_INLINE_VISIBILITY
    void splice_after(const_iterator __p, forward_list&& __x, const_iterator __i);
    _LIBCPP_INLINE_VISIBILITY
    void splice_after(const_iterator __p, forward_list&& __x,
                      const_iterator __f, const_iterator __l);
    void splice_after(const_iterator __p, forward_list& __x);
    void splice_after(const_iterator __p, forward_list& __x, const_iterator __i);
    void splice_after(const_iterator __p, forward_list& __x,
                      const_iterator __f, const_iterator __l);
    __remove_return_type remove(const value_type& __v);
    template <class _Predicate> __remove_return_type remove_if(_Predicate __pred);
    _LIBCPP_INLINE_VISIBILITY
    __remove_return_type unique() {return unique(__equal_to<value_type>());}
    template <class _BinaryPredicate> __remove_return_type unique(_BinaryPredicate __binary_pred);
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void merge(forward_list&& __x) {merge(__x, __less<value_type>());}
    template <class _Compare>
        _LIBCPP_INLINE_VISIBILITY
        void merge(forward_list&& __x, _Compare __comp)
        {merge(__x, yjh_def::move(__comp));}
#endif  // _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void merge(forward_list& __x) {merge(__x, __less<value_type>());}
    template <class _Compare> void merge(forward_list& __x, _Compare __comp);
    _LIBCPP_INLINE_VISIBILITY
    void sort() {sort(__less<value_type>());}
    template <class _Compare> _LIBCPP_INLINE_VISIBILITY void sort(_Compare __comp);
    void reverse() _NOEXCEPT;

private:

#ifndef _LIBCPP_CXX03_LANG
    void __move_assign(forward_list& __x, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);
    void __move_assign(forward_list& __x, false_type);
#endif  // _LIBCPP_CXX03_LANG

    template <class _Compare>
        static
        __node_pointer
        __merge(__node_pointer __f1, __node_pointer __f2, _Compare& __comp);

    template <class _Compare>
        static
        __node_pointer
        __sort(__node_pointer __f, difference_type __sz, _Compare& __comp);
};  // end of  forward_list

// constructor 
template <class _Tp, class _Alloc>
inline
forward_list<_Tp, _Alloc>::forward_list(const allocator_type& __a)
    : base(__a)
{
    // __forward_begin_node(nullptr)
}

template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(size_type __n)
{
	if (__n > 0)
	{
		__node_allocator& __a = base::__alloc();
		typedef __allocator_destructor<__node_allocator> _Dp;   // _Dp 只有一个 operator() 函数，调用
            // __node_allocator 的 deallocate
		unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));	
		// __node : forward_list_node : public forward_begin_node
		// base::__before_begin() 中存储的元素指向第一个存储数据的节点，自身并不存储数据
		for (__begin_node_pointer __p = base::__before_begin();
					__n > 0; --n, __p = __p->__next_as_begin())
		{
			__h.reset(__node_traits::allocate(__a, 1));		// 新建了一个 node
			__node_traits::construct(__a, yjh_def::addressof(__h->__value_));	
            // __value_ 是 value_type
			__h->__next_ = nullptr;
			__p->__next_ = __h.release();	// 返回的是 forward_list_node 的指针
		}
	}
}

#if _LIBCPP_STD_VER > 11
template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(size_type __n,
                                        const allocator_type& __base_alloc)
    : base ( __base_alloc )
{
    if (__n > 0)
    {
        __node_allocator& __a = base::__alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));
        for (__begin_node_pointer __p = base::__before_begin(); __n > 0; --__n,
                                                             __p = __p->__next_as_begin())
        {
            __h.reset(__node_traits::allocate(__a, 1));
            __node_traits::construct(__a, yjh_def::addressof(__h->__value_));
            __h->__next_ = nullptr;
            __p->__next_ = __h.release();
        }
    }
}
#endif

template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(size_type __n, const value_type& __v)
{
    insert_after(cbefore_begin(), __n, __v);
}

template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(size_type __n, const value_type& __v,
                                        const allocator_type& __a)
    : base(__a)
{
    insert_after(cbefore_begin(), __n, __v);
}

template <class _Tp, class _Alloc>
template <class _InputIterator>
forward_list<_Tp, _Alloc>::forward_list(_InputIterator __f, _InputIterator __l,
                        typename enable_if
                            <
                                __is_input_iterator<_InputIterator>::value
                            >::type*)
{
    insert_after(cbefore_begin(), __f, __l);
}

template <class _Tp, class _Alloc>
template <class _InputIterator>
forward_list<_Tp, _Alloc>::forward_list(_InputIterator __f, _InputIterator __l,
                        const allocator_type& __a,
                        typename enable_if
                                <
                                    __is_input_iterator<_InputIterator>::value
                                >::type*)
    : base(__a)
{
    insert_after(cbefore_begin(), __f, __l);
}

template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(const forward_list& __x)
    : base(
          __node_traits::select_on_container_copy_construction(__x.__alloc())) {
  insert_after(cbefore_begin(), __x.begin(), __x.end());
}

template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(const forward_list& __x,
                                        const allocator_type& __a)
    : base(__a)
{
    insert_after(cbefore_begin(), __x.begin(), __x.end());
}

// operator=
template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>&
forward_list<_Tp, _Alloc>::operator=(const forward_list& __x)
{
    if (this != &__x)
    {
        base::__copy_assign_alloc(__x);
        assign(__x.begin(), __x.end());
    }
    return *this;
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Alloc>
inline
forward_list<_Tp, _Alloc>&
forward_list<_Tp, _Alloc>::operator=(forward_list&& __x)
    _NOEXCEPT_(
             __node_traits::propagate_on_container_move_assignment::value &&
             is_nothrow_move_assignable<allocator_type>::value)
{
    __move_assign(__x, integral_constant<bool,
          __node_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Tp, class _Alloc>
inline
forward_list<_Tp, _Alloc>&
forward_list<_Tp, _Alloc>::operator=(initializer_list<value_type> __il)
{
    assign(__il.begin(), __il.end());
    return *this;
}
#endif

// __move_assign
template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::__move_assign(forward_list& __x, true_type)
    _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
    /**
     * 先清除自己的链表，然后直接将 __x 的链表拿过来
     */
{
    clear();
    base::__move_assign_alloc(__x);
    base::__before_begin()->__next_ = __x.__before_begin()->__next_;
    __x.__before_begin()->__next_ = nullptr;
}

template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::__move_assign(forward_list& __x, false_type)
{
    if (base::__alloc() == __x.__alloc())
        __move_assign(__x, true_type());
    else
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__x.begin()), _Ip(__x.end()));
    }
}

#ifndef _LIBCPP_CXX03_LANG
// insert_after
template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, value_type&& __v)
{
    __begin_node_pointer const __r = __p.__get_begin();
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp>     __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_), 
                                yjh_def::move(__v));
    __h->__next_ = __r->__next_;
    __r->__next_ = __h.release();
    return iterator(__r->__next_);
}
#endif

template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, const value_type& __v)
{
    __begin_node_pointer const __r = __p.__get_begin();
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_), __v);
    __h->__next_ = __r->__next_;
    __r->__next_ = __h.release();
    return iterator(__r->__next_);
}

template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, size_type __n,
                                        const value_type& __v)
{
    __begin_node_pointer __r = __p.__get_begin();
    if (__n > 0)
    {
        __node_allocator& __a = base::__alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
        __node_traits::construct(__a, yjh_def::addressof(__h->__value_), __v);
        __node_pointer __first = __h.release();
        __node_pointer __last = __first;
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (--__n; __n != 0; --__n, __last = __last->__next_)
            // 先把这 __n 个 node 串成一条链 __first 是链的开始， __last 是链的末尾
            {
                __h.reset(__node_traits::allocate(__a, 1));
                __node_traits::construct(__a, yjh_def::addressof(__h->__value_), __v);
                __last->__next_ = __h.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            // 如果在创建链的过程中发生异常的话，要回收空间
            while (__first != nullptr)
            {
                __node_pointer __next = __first->__next_;
                __node_traits::destroy(__a, yjh_def::addressof(__first->__value_));
                __node_traits::deallocate(__a, __first, 1);
                __first = __next;
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        // 把上面的那一条链插入到待插入的位置
        __last->__next_ = __r->__next_;
        __r->__next_ = __first;
        __r = static_cast<__begin_node_pointer>(__last);
    }
    return iterator(__r);
}

template <class _Tp, class _Alloc>
template <class _InputIterator>
typename enable_if
<
    __is_input_iterator<_InputIterator>::value,
    typename forward_list<_Tp, _Alloc>::iterator
>::type
forward_list<_Tp, _Alloc>::insert_after(const_iterator __p,
                                        _InputIterator __f, _InputIterator __l)
{
    __begin_node_pointer __r = __p.__get_begin();
    if (__f != __l)
    {
        __node_allocator& __a = base::__alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
        __node_traits::construct(__a, yjh_def::addressof(__h->__value_), *__f);
        __node_pointer __first = __h.release();
        __node_pointer __last = __first;
        /**
         * 和上面的过程是一样的，先串成链，再插入
         */
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (++__f; __f != __l; ++__f, ((void)(__last = __last->__next_)))
            {
                __h.reset(__node_traits::allocate(__a, 1)); // 分配新的 node 节点的内存
                __node_traits::construct(__a, yjh_def::addressof(__h->__value_), *__f);
                __last->__next_ = __h.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            while (__first != nullptr)
            {
                __node_pointer __next = __first->__next_;
                __node_traits::destroy(__a, yjh_def::addressof(__first->__value_));
                __node_traits::deallocate(__a, __first, 1);
                __first = __next;
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        /**
         * 最后把上面生成的链插入到待插入的位置就可以了
         */
        __last->__next_ = __r->__next_;
        __r->__next_ = __first;
        __r = static_cast<__begin_node_pointer>(__last);    
        //_node_pointer -> __begin_node_pointer
        // 这里为什么要进行上转型
    }
    return iterator(__r);
}

// erase_after
template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::erase_after(const_iterator __f)
{
    __begin_node_pointer __p = __f.__get_begin();
    __node_pointer __n = __p->__next_;
    __p->__next_ = __n->__next_;
    __node_allocator& __a = base::__alloc();
    __node_traits::destroy(__a, yjh_def::addressof(__n->__value_));
    __node_traits::deallocate(__a, __n, 1);
    return iterator(__p->__next_);
}


template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::erase_after(const_iterator __f, const_iterator __l)
{
    /**
     * 删除从 __f 开始到 __l 结束的所有的数据
     * 不包括 __f, 不包括 __l
     */
    __node_pointer __e = __l.__get_unsafe_node_pointer();
    if (__f != __l)
    {
        __begin_node_pointer __bp = __f.__get_begin();

        __node_pointer __n = __bp->__next_;
        if (__n != __e)
        {
            __bp->__next_ = __e;
            __node_allocator& __a = base::__alloc();
            do
            {
                __node_pointer __tmp = __n->__next_;
                __node_traits::destroy(__a, yjh_def::addressof(__n->__value_));
                /**
                 * 现对 _Tp 对象进行析构，之后在回收内存空间
                 */
                __node_traits::deallocate(__a, __n, 1);
                __n = __tmp;
            } while (__n != __e);
        }
    }
    return iterator(__e);
}

// push_front
#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::push_front(value_type&& __v)
{
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_), 
                        yjh_def::move(__v));
    __h->__next_ = base::__before_begin()->__next_;
    base::__before_begin() -> __next_ = __h.release();
}

#endif

template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::push_front(const value_type& __v)
{  
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<_node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_), __v);
    __h->__next_ = base::__before_begin()->__next_;
    base::__before_begin()->__next_ = __h.release();
}

// pop_front
template <class _Tp, class _Alloc>
void 
forward_list<_Tp, _Alloc>::pop_front()
{
    __node_allocator& __a = base::__alloc();
    /**
     * 这里难道不会出问题吗？
     * 如果当前的链表之中没有任何数据的话，那么 __p == nullptr
     * 下面的代码就会发生异常
     */
    __node_pointer __p = base::__before_begin()->__next_;
    base::before_begin()->__next_ = __p->__next_;
    __node_traits::destroy(__a, yjh_def::addressof(__p->__value_));
    __node_traits::deallocate(__a, __p, 1);
}

// emplace_front
template <class _Tp, class _Alloc>
template <class... _Args>
#if _LIBCPP_STD_VER > 14
typename forward_list<_Tp, _Alloc>::reference
#else
void
#endif
forward_list<_Tp, _Alloc>::emplace_front(_Args&&... __args)
{
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_),
                            yjh_def::forward<_Args>(__args)...);
    __h->__next_ = base::__before_begin()->__next_;
    base::__before_begin()->__next_ = __h.release();
#if _LIBCPP_STD_VER > 14
    return base::__before_begin()->__next_->__value_;
#endif
}

// emplace_after
#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Alloc>
template <class... _Args>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::emplace_after(const_iterator __p, _Args&&... __args)
{
    __begin_node_pointer const __r = __p.__get_begin();
    // __r 指向的是一个 _node 对象，这里赋值的过程采用了上转型，__r 只能方位节点的
    // __next_ 字段，无法访问 __value_ 字段
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    // 使用 unique_ptr 可以保证在发生异常的时候，可以顺利的释放已经开辟的内存空间
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_),
                                  yjh_def::forward<_Args>(__args)...);
    __h->__next_ = __r->__next_;
    __r->__next_ = __h.release();
    return iterator(__r->__next_);
}


// insert_after
template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, value_type&& __v)
{
    __begin_node_pointer const __r = __p.__get_begin();
    __node_allocator& __a = base::__alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
    __node_traits::construct(__a, yjh_def::addressof(__h->__value_), yjh_def::move(__v));
    __h->__next_ = __r->__next_;
    __r->__next_ = __h.release();
    return iterator(__r->__next_);
}
#endif

template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::iterator
forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, size_type __n,
                                        const value_type& __v)
{
    __begin_node_pointer __r = __p.__get_begin();
    if (__n > 0)
    // __n 代表插入的个数，如果小于 0  就没有任何的意义
    {
        __node_allocator& __a = base::__alloc();
        /**
         * __node_allocator 为 __node(__forward_list_node) 类型分配空间,
         * 为 __node::__value_ 进行构造
         */
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
        __node_traits::construct(__a, yjh_def::addressof(__h->__value_), __v);
        __node_pointer __first = __h.release();
        __node_pointer __last = __first;
        /**
         * 先将 __n 个节点连接成为一个串，串的开始指针为 __first, 串的结束节点是 __last 
         * 开始和结束节点都包含数据
         */
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (--__n; __n != 0; --__n, __last = __last->__next_)
            {
                __h.reset(__node_traits::allocate(__a, 1));
                __node_traits::construct(__a, yjh_def::addressof(__h->__value_), __v);
                __last->__next_ = __h.release();
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            while (__first != nullptr)
            {
                __node_pointer __next = __first->__next_;
                __node_traits::destroy(__a, yjh_def::addressof(__first->__value_));
                __node_traits::deallocate(__a, __first, 1);
                __first = __next;
            }
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        __last->__next_ = __r->__next_;
        __r->__next_ = __first;
        __r = static_cast<__begin_node_pointer>(__last);
    }
    return iterator(__r);
}

// resize 
/**
 * 重新将 链表设置为指定的大小，里面的数据存 _Tp 的默认值
 */
template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::resize(size_type __n)
{
    size_type __sz = 0;
    iterator __p = before_begin();
    iterator __i = begin();
    iterator __e = end();
    for (; __i != __e && __sz < __n; ++__p, ++__i, ++__sz)
        ;
    if (__i != __e)
    /**
     * 链表的长度很长，长度大于 __n 的长度，因此，对于超出的部分，全部进行回收
     */
        erase_after(__p, __e);
    else
    {
        /**
         * 链表的长度很短，没有达到 resize 的要求，要在后面进行添加
         */
        __n -= __sz;
        // __n 代表需要额外添加的元素的个数
        if (__n > 0)
        {
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));
            for (__begin_node_pointer __ptr = __p.__get_begin(); __n > 0; --__n,
                                                         __ptr = __ptr->__next_as_begin())
            // __p 指向链表的最后一个元素
            {
                /**
                 * __h 中存储的 __forward_list_node 指针只分配了内存，但是没有进行构造
                 * 但是却对 __forward_list_node 中的元素 __next_ 进行了赋值
                 * 对其中的 __value_ 进行了构造
                 * 这种使用方法非常的神奇
                 */
                __h.reset(__node_traits::allocate(__a, 1));
                __node_traits::construct(__a, yjh_def::addressof(__h->__value_));
                __h->__next_ = nullptr;
                __ptr->__next_ = __h.release();
            }
        }
    }
}

// merge
template <class _Tp, class _Alloc>
template <class _Compare>
void
forward_list<_Tp, _Alloc>::merge(forward_list& __x, _Compare __comp)
{
    if (this != &__x) // 不可能将自己和自己进行合并
    {
        base::__before_begin()->__next_ = __merge(base::__before_begin()->__next_,
                                __x.__before_begin()->__next_,
                                __comp);
        __x.__before_begin()->__next_ = nullptr;
        // 被合并的链表自身变成了一个空的链表
    }
}

// __merge
template <class _Tp, class _Alloc>
template <class _Compare>
typename forward_list<_Tp, _Alloc>::__node_pointer
/**
 * 根据特定的规则，合并两个列表为一个列表
 */
forward_list<_Tp, _Alloc>::__merge(__node_pointer __f1, __node_pointer __f2,
                                   _Compare& __comp)
/**
 * __merge 的过程会打乱两张链表
 */
{
    // 其中的任意一个链表如果是空的话，那么就返回另外一张链表
    if (__f1 == nullptr)
        return __f2;
    if (__f2 == nullptr)
        return __f1;
    __node_pointer __r;
    if (__comp(__f2->__value_, __f1->__value_))
    {
        __node_pointer __t = __f2;
        while (__t->__next_ != nullptr &&
                             __comp(__t->__next_->__value_, __f1->__value_))
            __t = __t->__next_;
        __r = __f2; 
        __f2 = __t->__next_;
        __t->__next_ = __f1;
    }
    else
        __r = __f1;
    __node_pointer __p = __f1;
    __f1 = __f1->__next_;
    while (__f1 != nullptr && __f2 != nullptr)
    {
        if (__comp(__f2->__value_, __f1->__value_))
        {
            __node_pointer __t = __f2;
            while (__t->__next_ != nullptr &&
                                 __comp(__t->__next_->__value_, __f1->__value_))
                __t = __t->__next_;
            __p->__next_ = __f2;
            __f2 = __t->__next_;
            __t->__next_ = __f1;
        }
        __p = __f1;
        __f1 = __f1->__next_;
    }
    if (__f2 != nullptr)
        __p->__next_ = __f2;
    return __r;
}

// splice_after
template <class _Tp, class _Alloc>
void
/**
 * 把 __x 的所有的元素插入到 __p 的后面
 */
forward_list<_Tp, _Alloc>::splice_after(const_iterator __p, forward_list& __x)
{
    if (!__x.empty())
    {
        if (__p.__get_begin() -> __next_ != nullptr)
        {
            const_iterator __lm1 = __x.before_begin();
            while (__lm1.__get_begin() -> __next_ != nullptr)
                ++__lm1;
            __lm1.__get_begin() -> __next_ = __p.__before_begin()->__next_;
        }
        __p.__get_begin() -> __next_ = __x.__before_begin() -> __next_;
        __x.__before_begin() -> __next_ = nullptr;
    }
}

template <class _Tp, class _Alloc>
void
/**
 * 由于 __i 的存在，那么 forward_list 参数变成了非并要的参数
 * 这里只插入一个元素 __i 的后继结点, __other 的其他元素要保持链状
 */
forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                        forward_list& /*__other*/,
                                        const_iterator __i)
{
    const_iterator __lm1 = yjh_def::next(__i);
    if (__p != __i && __p != __lm1)
    /**
     * 当然如果把自己插入到自己的后面，或者要插入的元素就在自己的后面，那就不要进行操作了
     */
    {
        __i.__get_begin()->__next_ = __lm1.__get_begin()->__next_;
        // 架空 __lm1 ，即 __i 连接 __lm1 的后一个元素
        __lm1.__get_begin()->__next_ = __p.__get_begin()->__next_;
        // __lm1 插入到 __p 的后面
        __p.__get_begin()->__next_ = __lm1.__get_unsafe_node_pointer();
        // __p 的后继结点设置为 __lm1
    }
}

template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                        forward_list& /*__other*/,
                                        const_iterator __f, const_iterator __l)
{
    if (__f != __l && __p != __f)
    {
        const_iterator __lm1 = __f;
        while (__lm1.__get_begin()->__next_ != __l.__get_begin())
            ++__lm1;
        if (__f != __lm1)
        {
            __lm1.__get_begin()->__next_ = __p.__get_begin()->__next_;
            __p.__get_begin()->__next_ = __f.__get_begin()->__next_;
            __f.__get_begin()->__next_ = __l.__get_unsafe_node_pointer();
        }
    }
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void
forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                        forward_list&& __x)
{
    splice_after(__p, __x);
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void
forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                        forward_list&& __x,
                                        const_iterator __i)
{
    splice_after(__p, __x, __i);
}

template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
void
forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                        forward_list&& __x,
                                        const_iterator __f, const_iterator __l)
{
    splice_after(__p, __x, __f, __l);
}

// remove
template <class _Tp, class _Alloc>
typename forward_list<_Tp, _Alloc>::__remove_return_type
forward_list<_Tp, _Alloc>::remove(const value_type& __v)
{
    forward_list<_Tp, _Alloc> __deleted_nodes(get_allocator()); 
    // collect the nodes we're removing
    // 用来收集那些要被移除的节点
    typename forward_list<_Tp, _Alloc>::size_type __count_removed = 0;
    const iterator __e = end();
    for (iterator __i = before_begin(); __i.__get_begin()->__next_ != nullptr;)
    {
        if (__i.__get_begin()->__next_->__value_ == __v)
        // 查看链表中的每一个元素的值是否等于 __v
        {
            ++__count_removed;
            iterator __j = yjh_def::next(__i, 2);
            /**
             * 存储的值和 __v 相等的节点在 __i 和 __j 的中间
             * __i --> will_be_removed --> __j
             */
            for (; __j != __e && *__j == __v; ++__j)
            // 可能存在着连续的多个节点的数据值等于 __v
                ++__count_removed;
            __deleted_nodes.splice_after(__deleted_nodes.before_begin(), *this, __i, __j);
            // 把待删除的节点从当前的链表中掏出来，放到 __deleted_nodes 链表当中
            if (__j == __e)
                break;
            __i = __j;
        }
        else
            ++__i;
    }
    
    return (__remove_return_type) __count_removed;
}

template <class _Tp, class _Alloc>
template <class _Predicate>
typename forward_list<_Tp, _Alloc>::__remove_return_type
/**
 * 根据条件 __pred 判断需要移除哪一些元素
 */
forward_list<_Tp, _Alloc>::remove_if(_Predicate __pred)
{
    forward_list<_Tp, _Alloc> __deleted_nodes(get_allocator()); 
    // collect the nodes we're removing
    typename forward_list<_Tp, _Alloc>::size_type __count_removed = 0;
    const iterator __e = end();
    for (iterator __i = before_begin(); __i.__get_begin()->__next_ != nullptr;)
    {
        if (__pred(__i.__get_begin()->__next_->__value_))
        {
            ++__count_removed;
            iterator __j = yjh_def::next(__i, 2);
            for (; __j != __e && __pred(*__j); ++__j)
                ++__count_removed;
            __deleted_nodes.splice_after(__deleted_nodes.before_begin(), *this, __i, __j);
            if (__j == __e)
                break;
            __i = __j;
        }
        else
            ++__i;
    }
    
    return (__remove_return_type) __count_removed;
}

// reverse
template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::reverse() noexcept
{
    /** 基本过程
     * bf_begin ->  p -> f -> c -> x -> null
     * nullptr   <- p    f -> c -> x -> null
     * nullptr   <- p <- f    c -> x -> null
     * nullptr  <- p <- f <- c    x -> null
     * nullptr  <- p <- f <- c <- x    null
     * nullptr  <- p <- f <- c <- x  <- bf_begin
     */
    __node_pointer __p = base::__before_begin() -> __next_;
    if (__p != nullptr)
    {
        __node_pointer __f = __p->__next_;
        __p->__next_ = nullptr;
        while (__f != nullptr)
        {
            __node_pointer __t =  __f->__next_;
            __f->__next_ = __p;
            __p = __f;
            __f = __t;
        }
    }
}

// unique
template <class _Tp, class _Alloc>
template <class _BinaryPredicate>
typename forward_list<_Tp, _Alloc>::__remove_return_type
/**
 * 返回链表中满足特定条件的节点的总个数
 * 移除连续的重复的元素
 */
forward_list<_Tp, _Alloc>::unique(_BinaryPredicate __binary_pred)
{
    forward_list<_Tp, _Alloc> __deleted_nodes(get_allocator()); 
    // collect the nodes we're removing
    typename forward_list<_Tp, _Alloc>::size_type __count_removed = 0;
    for (iterator __i = begin(), __e = end(); __i != __e;)
    {
        iterator __j = yjh_def::next(__i);
        for (; __j != __e && __binary_pred(*__i, *__j); ++__j)
            ++__count_removed;
        if (__i.__get_begin()->__next_ != __j.__get_unsafe_node_pointer())
            /**
             * 只有连续重复(连续两个节点重复，或者两个以上)
             */
            __deleted_nodes.splice_after(__deleted_nodes.before_begin(), *this, __i, __j);
        __i = __j;
    }
    
    return (__remove_return_type) __count_removed;
}

// sort
// 采用归并排序的方法
template <class _Tp, class _Alloc>
template <class _Compare>
typename forward_list<_Tp, _Alloc>::__node_pointer
forward_list<_Tp, _Alloc>::__sort(__node_pointer __f1, difference_type __sz,
                                  _Compare& __comp)
{
    switch (__sz)
    {
    case 0:
    case 1:
        return __f1;
    case 2:
        if (__comp(__f1->__next_->__value_, __f1->__value_))
        {
            __node_pointer __t = __f1->__next_;
            __t->__next_ = __f1;
            __f1->__next_ = nullptr;
            __f1 = __t;
        }
        return __f1;
    }
    difference_type __sz1 = __sz / 2;
    difference_type __sz2 = __sz - __sz1;
    __node_pointer __t = yjh_def::next(iterator(__f1), __sz1 - 1).__get_unsafe_node_pointer();
    __node_pointer __f2 = __t->__next_;
    __t->__next_ = nullptr;
    return __merge(__sort(__f1, __sz1, __comp),
                   __sort(__f2, __sz2, __comp), __comp);
}

// operator == 
template <class _Tp, class _Alloc>
bool operator==(const forward_list<_Tp, _Alloc>& __x, 
            const forward_list<_Tp, _Alloc>& __y)
{
    typedef forward_list<_Tp, _Alloc> _Cp;
    typedef typename _Cp::const_iterator _Ip;
    _Ip __ix = __x.begin();
    _Ip __ex = __x.end();
    _Ip __iy = __y.begin();
    _Ip __ey = __y.end();
    for (; __ix != __ex && __iy != __ey; ++__ix, ++__iy)
        if (! (*__ix == *__iy) )
            return false;
    return (__ix == __ex) == (__iy == __ey);
}

// operator !=
template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool operator!=(const forward_list<_Tp, _Alloc>& __x,
                const forward_list<_Tp, _Alloc>& __y)
{
    return !(__x == __y);
}

// operator < 
template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool operator< (const forward_list<_Tp, _Alloc>& __x,
                const forward_list<_Tp, _Alloc>& __y)
{
    return yjh_def::lexicographical_compare(__x.begin(), __x.end(),
                                         __y.begin(), __y.end());
}

// operator > 
template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool operator> (const forward_list<_Tp, _Alloc>& __x,
                const forward_list<_Tp, _Alloc>& __y)
{
    return __y < __x;
}

// operator >=
template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool operator>=(const forward_list<_Tp, _Alloc>& __x,
                const forward_list<_Tp, _Alloc>& __y)
{
    return !(__x < __y);
}

// operator <=
template <class _Tp, class _Alloc>
inline _LIBCPP_INLINE_VISIBILITY
bool operator<=(const forward_list<_Tp, _Alloc>& __x,
                const forward_list<_Tp, _Alloc>& __y)
{
    return !(__x > __y);
}

// erase after C++20
#if _LIBCPP_STD_VER > 17
template <class _Tp, class _Allocator, class _Predicate>
inline 
void erase_if(forward_list<_Tp, _Allocator>& __c, _Predicate __pred)
{
    __c.remove_if(__pred);
}

template <class _Tp, class _Allocator, class _Up>
inline _LIBCPP_INLINE_VISIBILITY
void erase(forward_list<_Tp, _Allocator>& __c, const _Up& __v)
{ yjh_def::erase_if(__c, [&](auto& __elem) { return __elem == __v; }); }
#endif

// assign
template <class _Tp, class _Alloc>
template <class _InputIterator>
typename enable_if
        <
            __is_input_iterator<_InputIterator>::value,
            void
        >::type
forward_list<_Tp, _Alloc>::assign(_InputIterator __f, _InputIterator __l)
{
    iterator __i = before_begin();
    iterator __j = yjh_def::next(__i);
    iterator __e = end();
    for (; __j != __e && __f != __l; ++ __i, (void)++__j, ++__f)
    {
        *__j = *__f;   // *__j 返回 value_type&
    }
    if (__j == __e)
        insert_after(__i, __f, __l);
    else 
        erase_after(__i, __e);
}

template <class _Tp, class _Alloc>
void
forward_list<_Tp, _Alloc>::assign(size_type __n, const value_type& __v)
{
    iterator __i = before_begin();
    iterator __j = yjh_def::next(__i);
    iterator __e = end();
    for (; __j != __e && __n > 0; --__n, ++__i, ++__j)
        *__j = __v; // 
    if (__j == __e)
        insert_after(__i, __n, __v);
    else
        erase_after(__i, __e);
}

template <class _Tp, class _Alloc>
inline
void
forward_list<_Tp, _Alloc>::assign(initializer_list<value_type> __il)
{
    assign(__il.begin(), __il.end());
}

} // end_if namespace yjh_def
_LIBCPP_POP_MACROS

#endif
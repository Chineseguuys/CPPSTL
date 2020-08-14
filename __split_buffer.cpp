// -*- C++ -*-
#ifndef _LIBCPP_SPLIT_BUFFER
#define _LIBCPP_SPLIT_BUFFER

#include "__config.cpp"
#include "type_traits.cpp"
#include "algorithm.cpp"
#include "memory.cpp"

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"

namespace yjh_def
{
template <bool>
class __split_buffer_common
{
protected:
    void __throw_length_error() const;
    void __throw_out_of_range() const;
};

template <class _Tp, class _Allocator = allocator<_Tp> >
struct __split_buffer
    : private __split_buffer_common<true>
{
private:
    __split_buffer(const __split_buffer&);
    __split_buffer& operator=(const __split_buffer&);
public:
    typedef _Tp                                             value_type;
    typedef _Allocator                                      allocator_type;
    typedef typename remove_reference<allocator_type>::type __alloc_rr;
    typedef allocator_traits<__alloc_rr>                    __alloc_traits;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference;
    typedef typename __alloc_traits::size_type              size_type;
    typedef typename __alloc_traits::difference_type        difference_type;
    typedef typename __alloc_traits::pointer                pointer;
    typedef typename __alloc_traits::const_pointer          const_pointer;
    typedef pointer                                         iterator;
    typedef const_pointer                                   const_iterator;

    pointer                                         __first_;
    pointer                                         __begin_;
    pointer                                         __end_;
    __compressed_pair<pointer, allocator_type>      __end_cap_;

    typedef typename add_lvalue_reference<allocator_type>::type __alloc_ref;
    typedef typename add_lvalue_reference<allocator_type>::type __alloc_const_ref;

    _LIBCPP_INLINE_VISIBILITY __alloc_rr&           __alloc() _NOEXCEPT         {return __end_cap_.second();}
    _LIBCPP_INLINE_VISIBILITY const __alloc_rr&     __alloc() const _NOEXCEPT   {return __end_cap_.second();}
    _LIBCPP_INLINE_VISIBILITY pointer&              __end_cap() _NOEXCEPT       {return __end_cap_.first();}
    _LIBCPP_INLINE_VISIBILITY const pointer&        __end_cap() const _NOEXCEPT {return __end_cap_.first();}

    _LIBCPP_INLINE_VISIBILITY
    __split_buffer()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);

    _LIBCPP_INLINE_VISIBILITY
    explicit __split_buffer(__alloc_rr& __a);

    _LIBCPP_INLINE_VISIBILITY
    explicit __split_buffer(const __alloc_rr& __a);

    __split_buffer(size_type __cap, size_type __start, __alloc_rr& __a);

    ~__split_buffer();

#ifndef _LIBCPP_CXX03_LANG
    __split_buffer(__split_buffer&& __c)
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value);

    __split_buffer(__split_buffer&& __c, const __alloc_rr& __a);

    __split_buffer& operator=(__split_buffer&& __c)
        _NOEXCEPT_((__alloc_traits::propagate_on_container_move_assignment::value &&
                is_nothrow_move_assignable<allocator_type>::value) ||
               !__alloc_traits::propagate_on_container_move_assignment::value);
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY       iterator begin() _NOEXCEPT       {return __begin_;}
    _LIBCPP_INLINE_VISIBILITY const_iterator begin() const _NOEXCEPT {return __begin_;}
    _LIBCPP_INLINE_VISIBILITY       iterator end() _NOEXCEPT         {return __end_;}
    _LIBCPP_INLINE_VISIBILITY const_iterator end() const _NOEXCEPT   {return __end_;}

    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT
        {__destruct_at_end(__begin_);}
    _LIBCPP_INLINE_VISIBILITY size_type size() const {return static_cast<size_type>(__end_ - __begin_);}
    _LIBCPP_INLINE_VISIBILITY bool empty()     const {return __end_ == __begin_;}
    _LIBCPP_INLINE_VISIBILITY size_type capacity() const {return static_cast<size_type>(__end_cap() - __first_);}
    _LIBCPP_INLINE_VISIBILITY size_type __front_spare() const {return static_cast<size_type>(__begin_ - __first_);}
    _LIBCPP_INLINE_VISIBILITY size_type __back_spare() const {return static_cast<size_type>(__end_cap() - __end_);}
 
    _LIBCPP_INLINE_VISIBILITY       reference front()       {return *__begin_;}
    _LIBCPP_INLINE_VISIBILITY const_reference front() const {return *__begin_;}
    _LIBCPP_INLINE_VISIBILITY       reference back()        {return *(__end_ - 1);}
    _LIBCPP_INLINE_VISIBILITY const_reference back() const  {return *(__end_ - 1);}

    void reserve(size_type __n);
    void shrink_to_fit() _NOEXCEPT;
    void push_front(const_reference __x);
    _LIBCPP_INLINE_VISIBILITY void push_back(const_reference __x);
#ifndef _LIBCPP_CXX03_LANG
    void push_front(value_type&& __x);
    void push_back(value_type&& __x);
    template <class... _Args>
        void emplace_back(_Args&&... __args);
#endif  // !defined(_LIBCPP_CXX03_LANG)

    _LIBCPP_INLINE_VISIBILITY void pop_front() {__destruct_at_begin(__begin_+1);}
    _LIBCPP_INLINE_VISIBILITY void pop_back() {__destruct_at_end(__end_-1);}

    void __construct_at_end(size_type __n);
    void __construct_at_end(size_type __n, const_reference __x);
    template <class _InputIter>
        typename enable_if
        <
            __is_input_iterator<_InputIter>::value &&
           !__is_forward_iterator<_InputIter>::value,
            void
        >::type
        __construct_at_end(_InputIter __first, _InputIter __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            void
        >::type
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last);

    _LIBCPP_INLINE_VISIBILITY void __destruct_at_begin(pointer __new_begin)
        {__destruct_at_begin(__new_begin, is_trivially_destructible<value_type>());}
        _LIBCPP_INLINE_VISIBILITY
        void __destruct_at_begin(pointer __new_begin, false_type);
        _LIBCPP_INLINE_VISIBILITY
        void __destruct_at_begin(pointer __new_begin, true_type);

    _LIBCPP_INLINE_VISIBILITY
    void __destruct_at_end(pointer __new_last) _NOEXCEPT
        {__destruct_at_end(__new_last, false_type());}
    _LIBCPP_INLINE_VISIBILITY
        void __destruct_at_end(pointer __new_last, false_type) _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
        void __destruct_at_end(pointer __new_last, true_type) _NOEXCEPT;

    void swap(__split_buffer& __x)
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value||
                   __is_nothrow_swappable<__alloc_rr>::value);

    bool __invariants() const;

private:
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__split_buffer& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = yjh_def::move(__c.__alloc());
        }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__split_buffer&, false_type) _NOEXCEPT
        {}

    struct _ConstructTransaction {
      explicit _ConstructTransaction(pointer* __p, size_type __n) _NOEXCEPT
      : __pos_(*__p), __end_(*__p + __n), __dest_(__p) {
      }
      ~_ConstructTransaction() {
          /**
           * 使得 __split_buffer 中的 __end_ 指向创建完元素后的新的末尾位置
           */
        *__dest_ = __pos_;
      }
      pointer __pos_;
     const pointer __end_;
    private:
     pointer *__dest_;  // 指针 __end_ 指针的指针
    };
};

template <class _Tp, class _Allocator>
bool
__split_buffer<_Tp, _Allocator>::__invariants() const
{
    if(__first_ == nullptr)
    {
        if(__begin_ != nullptr) //在什么情况下会出现这种事件呢
            return false;
        if(__end_ != nullptr)
            return false;
        if(__end_cap() != nullptr)
            return false;
    }
    else
    {
        if(__begin_ < __first_)
            return false;
        if(__end_ < __begin_)
            return false;
        if(__end_cap() < __end_)
            return false;
    }
    return true;
}
//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == size() + __n
template <class _Tp, class _Allocator>
void
__split_buffer<_Tp, _Allocator>::__construct_at_end(size_type __n)
{
    _ConstructTransaction __tx(&this->__end_, __n);
    for(; __tx.__pos_ != __tx.__end_; ++__tx.__pos_)
    {
        __alloc_traits::construct(this->__alloc(),
                    yjh_def::__to_raw_pointer(__tx.__pos_));
    }
}

//  Copy constructs __n objects starting at __end_ from __x
//  throws if construction throws
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == old size() + __n
//  Postcondition:  [i] == __x for all i in [size() - __n, __n)
template <class _Tp, class _Allocator>
void
__split_buffer<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
{
    _ConstructTransaction __tx(&this->__end_, __n);
    for (; __tx.__pos_ != __tx.__end_; ++__tx.__pos_);
    {
        __alloc_traits::construct(this->__alloc(),
                    yjh_def::__to_raw_pointer(__tx.__pos_), __x);
    }
}

template <class _Tp, class _Allocator>
template <class _InputIter>
typename enable_if
<
     __is_input_iterator<_InputIter>::value &&
    !__is_forward_iterator<_InputIter>::value,
    void
>::type
__split_buffer<_Tp, _Allocator>::__construct_at_end(_InputIter __first, _InputIter __last)
{
    __alloc_rr& __a = this->__alloc();
    for (; __first != __last; ++__first)
    {
        if (__end_ == __end_cap())
        {
            /**
             * 重新分配空间，现在的空间不够了，分配的新空间是旧的空间的两倍
             * 并把旧的空间中的元素以拷贝的方式拷贝到新的空间当中
             */
            size_type __old_cap = __end_cap() - __first_;
            size_type __new_cap = yjh_def::max<size_type>(2 * __old_cap, 8);
            __split_buffer __buf(__new_cap, 0, __a);
            for (pointer __p = __begin_; __p != __end_; ++__p, ++__buf.__end_)
                __alloc_traits::construct(__buf.__alloc(),
                        yjh_def::__to_raw_pointer(__buf.__end_), yjh_def::move(*__p));
            swap(__buf);    // 将 __buf 和当前的类进行交换，当前的空间进入
        }
        __alloc_traits::construct(__a, yjh_def::__to_raw_pointer(this->__end_), *__first);
        ++this->__end_;
    }
}

template <class _Tp, class _Alloctor>
template <class _ForwardIterator>
typename enable_if
    <
        __is_forward_iterator<_ForwardIterator>::value,
        void
    >::type
__split_buffer<_Tp, _Alloctor>::__construct_at_end(_ForwardIterator __first,
                    _ForwardIterator __last)
/**
 * 为什么上面有对数据量超出 capacity() 时的处理(重新分配空间)。 而这里却不考虑数据量超出的情况呢
 */
{
    _ConstructTransaction __tx(&this->__end_, yjh_def::distance(__first, __last));
    for (; __tx.__pos_ != __tx.__end_; ++__tx.__pos_, ++__first)
    {
        __alloc_traits::construct(this->__alloc(),
                yjh_def::__to_raw_pointer(__tx.__pos_), *__first);
    }
}

template <class _Tp, class _Allocator>
inline
void
/**
 * 如果 _Tp 没有平凡的析构函数，则说明了 _Tp 类型的对象，在销毁的时候不可以通过简单的
 * 回收内存来实现，需要调用其析构函数完成析构之后才可以再回收内存
 */
__split_buffer<_Tp, _Allocator>::__destruct_at_begin(pointer __new_begin, false_type)
{
    while (__begin_ != __new_begin)
        __alloc_traits::destroy(__alloc(), __to_raw_pointer(__begin_++));
}

template <class _Tp, class _Allocator>
inline
void
/**
 * 如果 _Tp 类型具有平凡的析构函数，那么直接回收内存，相应的数据也就被销毁了，不需要担心是否
 * 有资源没有释放，仍然被占用
 * 这个时候将 __begin_ 指向新的 begin 就完成了操作
 */
__split_buffer<_Tp, _Allocator>::__destruct_at_begin(pointer __new_begin, true_type)
{
    __begin_ = __new_begin;
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
__split_buffer<_Tp, _Allocator>::__destruct_at_end(pointer __new_last, false_type) _NOEXCEPT
{
    while (__new_last != __end_)
        __alloc_traits::destroy(__alloc(), __to_raw_pointer(--__end_));
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
__split_buffer<_Tp, _Allocator>::__destruct_at_end(pointer __new_last, true_type) _NOEXCEPT
{
    __end_ = __new_last;
}


// __split_buffer constructor
template <class _Tp, class _Allocator>
__split_buffer<_Tp, _Allocator>::__split_buffer(
    size_type __cap,
    size_type __start,
    __alloc_rr& __a
)   :   __end_cap_(nullptr, __a)
/**
 * __cap 是需要分配的内存大小
 * __first_ 是分配的内存的开始地址
 * __begin_ 第一个存储的元素的位置
 * __end_  存储的最后一个元素的下一个位置
 * __end_cap() 整个内存空间的末尾的位置
 */
{
    __first_ = __cap != 0 ? __alloc_traits::allocate(__alloc(), __cap) : nullptr;
    __begin_ = __end_ = __first_ + __start;
    __end_cap() = __first_ + __cap;
}

template <class _Tp, class _Allocator>
inline
__split_buffer<_Tp, _Allocator>::__split_buffer()
    _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
    : __first_(nullptr), __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr)
{
}

template <class _Tp, class _Allocator>
inline
__split_buffer<_Tp, _Allocator>::__split_buffer(__alloc_rr& __a)
    : __first_(nullptr), __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr, __a)
{
}

template <class _Tp, class _Allocator>
inline
__split_buffer<_Tp, _Allocator>::__split_buffer(const __alloc_rr& __a)
    : __first_(nullptr), __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr, __a)
{
}

template <class _Tp, class _Allocator>
__split_buffer<_Tp, _Allocator>::~__split_buffer()
/**
 * 这个类的析构函数，要回收所有的内存空间
 */
{
    clear();
    if (__first_)
        __alloc_traits::deallocate(__alloc(), __first_, capacity());
}

#ifndef _LIBCPP_CXX03_LANG
/**
 * 看是否支持移动构造、赋值、拷贝
 */
template <class _Tp, class _Allocator>
__split_buffer<_Tp, _Allocator>::__split_buffer(__split_buffer&& __c)
    _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value)
    : __first_(yjh_def::move(__c.__first_)),
      __begin_(yjh_def::move(__c.__begin_)),
      __end_(yjh_def::move(__c.__end_)),
      __end_cap_(yjh_def::move(__c.__end_cap_))
{
    /**
     * 所谓的移动构造，并不是真正的移动，而是一种象征意义上的移动，将一个实例的所有内容都原模原样的
     * 给另一个实例，就被称之为移动
     */
    __c.__first_ = nullptr;
    __c.__begin_ = nullptr;
    __c.__end_ = nullptr;
    __c.__end_cap() = nullptr;
}

template <class _Tp, class _Allocator>
__split_buffer<_Tp, _Allocator>::__split_buffer(__split_buffer&& __c, const __alloc_rr& __a)
    : __end_cap_(__a)
{
    /**
     * 使用一种 allocator 开辟的空间，一般不能使用另一种 allocator 进行管理，容易发生各种问题，所以如果 __a 和 __c 的 
     * allocator 不是同一种的话，那么我们用 __a 进行数据的拷贝，而不是进行移动。
     * 这样可以避免发生一些意料之外的错误
     * 当然如何是同一种 allocator 的话，他们的内存管理机制是一样的，所以采用移动的方式是没有问题的
     */
    if (__a == __c.__alloc())
    {
        __first_ = __c.__first_;
        __begin_ = __c.__begin_;
        __end_ = __c.__end_;
        __end_cap() = __c.__end_cap();
        __c.__first_ = nullptr;
        __c.__begin_ = nullptr;
        __c.__end_ = nullptr;
        __c.__end_cap() = nullptr;
    }
    else
    {
        size_type __cap = __c.size();
        __first_ = __alloc_traits::allocate(__alloc(), __cap);
        __begin_ = __end_ = __first_;
        __end_cap() = __first_ + __cap;
        typedef move_iterator<iterator> _Ip;
        __construct_at_end(_Ip(__c.begin()), _Ip(__c.end()));
    }
}

template <class _Tp, class _Allocator>
__split_buffer<_Tp, _Allocator>&
__split_buffer<_Tp, _Allocator>::operator=(__split_buffer&& __c)
    _NOEXCEPT_((__alloc_traits::propagate_on_container_move_assignment::value &&    // 指示 alloctor 是否支持移动
                is_nothrow_move_assignable<allocator_type>::value) ||
               !__alloc_traits::propagate_on_container_move_assignment::value)
{
    clear();     // 清除当前的存储空间中的所有的元素
    shrink_to_fit();
    __first_ = __c.__first_;
    __begin_ = __c.__begin_;
    __end_ = __c.__end_;
    __end_cap() = __c.__end_cap();
    __move_assign_alloc(__c,
        integral_constant<bool,
                          __alloc_traits::propagate_on_container_move_assignment::value>());
    __c.__first_ = __c.__begin_ = __c.__end_ = __c.__end_cap() = nullptr;   // 原 __split_buffer 的所有指针全部置 0 
    return *this;
}
#endif

template <class _Tp, class _Allocator>
void __split_buffer<_Tp, _Allocator>::swap(__split_buffer& __x)
    _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value||
                   __is_nothrow_swappable<__alloc_rr>::value)
{
    yjh_def::swap(__first_, __x.__first_);
    yjh_def::swap(__begin_, __x.__begin_);
    yjh_def::swap(__end_, __x.__end_);
    yjh_def::swap(__end_cap(), __x.__end_cap());
    __swap_allocator(__alloc(), __x.__alloc());
}

template <class _Tp, class _Allocator>
void
/**
 * 保留一部分元素
 */
__split_buffer<_Tp, _Allocator>::reserve(size_type __n)
{
    if (__n < capacity())
    {
        __split_buffer<value_type, __alloc_rr&> __t(__n, 0, __alloc());
        __t.__construct_at_end(move_iterator<pointer>(__begin_),
                               move_iterator<pointer>(__end_));
        yjh_def::swap(__first_, __t.__first_);
        yjh_def::swap(__begin_, __t.__begin_);
        yjh_def::swap(__end_, __t.__end_);
        yjh_def::swap(__end_cap(), __t.__end_cap());
    }
}

template <class _Tp, class _Allocator>
void
/**
 * 将 __split_buffer 的 capacity 收缩到 size() 大小
 */
__split_buffer<_Tp, _Allocator>::shrink_to_fit() _NOEXCEPT
{
    if (capacity() > size())
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            __split_buffer<value_type, __alloc_rr&> __t(size(), 0, __alloc());
            __t.__construct_at_end(move_iterator<pointer>(__begin_),
                                   move_iterator<pointer>(__end_));
            __t.__end_ = __t.__begin_ + (__end_ - __begin_);
            yjh_def::swap(__first_, __t.__first_);
            yjh_def::swap(__begin_, __t.__begin_);
            yjh_def::swap(__end_, __t.__end_);
            yjh_def::swap(__end_cap(), __t.__end_cap());
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }
}

template <class _Tp, class _Allocator>
void
/**
 * 从数据区的前面(__begin_的前面)插入一组数据
 * ------------------------------------------------------------------------------------------------
 * |-空闲内存--------------|-----------data part------------------------------|----空闲内存---------|
 *__first_            __begin_                                             __end_              __end_cap()         
 */                    
__split_buffer<_Tp, _Allocator>::push_front(const_reference __x)
{
    if (__begin_ == __first_)   // 前面的空闲内存满了,查不进去数据了
    {
        if (__end_ < __end_cap())  // 但是后面的空闲区域还可以插入数据
        {
            difference_type __d = __end_cap() - __end_; // 尾部还有多少空闲的内存
            __d = (__d + 1) / 2;    // 整体的数据区向后面挪动 __d 的距离，那么整体的前面就可以空出 __d 的空间
            __begin_ = yjh_def::move_backward(__begin_, __end_, __end_ + __d);      // 反向复制
            __end_ += __d;
        }
        else    // 后面的空闲区域都插不进数据了
        {
            // 那就说明了所有的空间全部满了，那只有重新分配空间来解决这个问题了，将整体的空间扩大两倍
            size_type __c = max<size_type>(2 * static_cast<size_t>(__end_cap() - __first_), 1);
            __split_buffer<value_type, __alloc_rr&> __t(__c, (__c + 3) / 4, __alloc()); // (__c+3)/4 的位置开始，刚好可以在旧的数据存入新的空间后
            // 前后空闲区域的大小是一样大的
            __t.__construct_at_end(move_iterator<pointer>(__begin_),
                                   move_iterator<pointer>(__end_)); // 把旧的数据拷贝进来
            yjh_def::swap(__first_, __t.__first_);
            yjh_def::swap(__begin_, __t.__begin_);
            yjh_def::swap(__end_, __t.__end_);
            yjh_def::swap(__end_cap(), __t.__end_cap());
        }
    }
    __alloc_traits::construct(__alloc(), yjh_def::__to_raw_pointer(__begin_-1), __x); // 在前面插入数据
    --__begin_;
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
void
__split_buffer<_Tp, _Allocator>::push_front(value_type&& __x)
{
    if (__begin_ == __first_)
    {
        if (__end_ < __end_cap())
        {
            difference_type __d = __end_cap() - __end_;
            __d = (__d + 1) / 2;
            __begin_ = yjh_def::move_backward(__begin_, __end_, __end_ + __d);
            __end_ += __d;
        }
        else
        {
            size_type __c = max<size_type>(2 * static_cast<size_t>(__end_cap() - __first_), 1);
            __split_buffer<value_type, __alloc_rr&> __t(__c, (__c + 3) / 4, __alloc());
            __t.__construct_at_end(move_iterator<pointer>(__begin_),
                                   move_iterator<pointer>(__end_));
            yjh_def::swap(__first_, __t.__first_);
            yjh_def::swap(__begin_, __t.__begin_);
            yjh_def::swap(__end_, __t.__end_);
            yjh_def::swap(__end_cap(), __t.__end_cap());
        }
    }
    __alloc_traits::construct(__alloc(), yjh_def::__to_raw_pointer(__begin_-1),
            yjh_def::move(__x));
    --__begin_;
}
#endif

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
/**
 * 从后面插入和从前面插入是同样的考虑方法
 * 首先，后面还是否有空间可以插入
 * 其次，如果后面没有剩余的空间可以插入，那么前面是否有剩余的空间可以插入
 * 如果前面和后面都没有剩余的空间
 */
__split_buffer<_Tp, _Allocator>::push_back(const_reference __x)
{
    if (__end_ == __end_cap())
    {
        if (__begin_ > __first_)
        {
            difference_type __d = __begin_ - __first_;
            __d = (__d + 1) / 2;
            __end_ = yjh_def::move(__begin_, __end_, __begin_ - __d);
            __begin_ -= __d;
        }
        else
        {
            size_type __c = max<size_type>(2 * static_cast<size_t>(__end_cap() - __first_), 1);
            __split_buffer<value_type, __alloc_rr&> __t(__c, __c / 4, __alloc());
            __t.__construct_at_end(move_iterator<pointer>(__begin_),
                                   move_iterator<pointer>(__end_));
            yjh_def::swap(__first_, __t.__first_);
            yjh_def::swap(__begin_, __t.__begin_);
            yjh_def::swap(__end_, __t.__end_);
            yjh_def::swap(__end_cap(), __t.__end_cap());
        }
    }
    __alloc_traits::construct(__alloc(), yjh_def::__to_raw_pointer(__end_), __x);
    ++__end_;
}


#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
void
__split_buffer<_Tp, _Allocator>::push_back(value_type&& __x)
{
    if (__end_ == __end_cap())
    { 
        if (__begin_ > __first_)
        {
            difference_type __d = __begin_ - __first_;
            __d = (__d + 1) / 2;
            __end_ = yjh_def::move(__begin_, __end_, __begin_ - __d);
            __begin_ -= __d;
        }
        else
        {
            size_type __c = max<size_type>(2 * static_cast<size_t>(__end_cap() - __first_), 1);
            __split_buffer<value_type, __alloc_rr&> __t(__c, __c / 4, __alloc());
            __t.__construct_at_end(move_iterator<pointer>(__begin_),
                                   move_iterator<pointer>(__end_));
            yjh_def::swap(__first_, __t.__first_);
            yjh_def::swap(__begin_, __t.__begin_);
            yjh_def::swap(__end_, __t.__end_);
            yjh_def::swap(__end_cap(), __t.__end_cap());
        }
    }
    __alloc_traits::construct(__alloc(), yjh_def::__to_raw_pointer(__end_),
            yjh_def::move(__x));
    ++__end_;
}


template <class _Tp, class _Allocator>
template <class... _Args>
void
/**
 * _Args&&... __args 为 _Tp 的初始化参数
 * 注意引用转发
 */
__split_buffer<_Tp, _Allocator>::emplace_back(_Args&&... __args)
{
    if (__end_ == __end_cap())
    {
        if (__begin_ > __first_)
        {
            difference_type __d = __begin_ - __first_;
            __d = (__d + 1) / 2;
            __end_ = yjh_def::move(__begin_, __end_, __begin_ - __d);
            __begin_ -= __d;
        }
        else
        {
            size_type __c = max<size_type>(2 * static_cast<size_t>(__end_cap() - __first_), 1);
            __split_buffer<value_type, __alloc_rr&> __t(__c, __c / 4, __alloc());
            __t.__construct_at_end(move_iterator<pointer>(__begin_),
                                   move_iterator<pointer>(__end_));
            yjh_def::swap(__first_, __t.__first_);
            yjh_def::swap(__begin_, __t.__begin_);
            yjh_def::swap(__end_, __t.__end_);
            yjh_def::swap(__end_cap(), __t.__end_cap());
        }
    }
    __alloc_traits::construct(__alloc(), yjh_def::__to_raw_pointer(__end_),
                              yjh_def::forward<_Args>(__args)...);
    ++__end_;
}
#endif


template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(__split_buffer<_Tp, _Allocator>& __x, __split_buffer<_Tp, _Allocator>& __y)
    noexcept(noexcept(__x.swap(__y)))
{
    __x.swap(__y);
}

}

_LIBCPP_POP_MACROS

#endif
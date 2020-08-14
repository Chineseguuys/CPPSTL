#ifndef _YJH_DEQUE
#define _YJH_DEQUE

#include "__config.cpp"
#include "type_traits.cpp"
#include "initializer_list.cpp"
#include "iterator.cpp"
#include "algorithm.cpp"
#include "stdexcept.cpp"
#include "memory.cpp"
#include "__split_buffer.cpp"

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"

namespace yjh_def
{
template <class _Tp, class _Allocator> class __deque_base;
template <class _Tp, class _Allocator = allocator<_Tp> > class _LIBCPP_TEMPLATE_VIS deque;

template <class _ValueType, class _Pointer, class _Reference, class _MapPointer,
          class _DiffType, _DiffType _BlockSize>
class _LIBCPP_TEMPLATE_VIS __deque_iterator;

template <  class _RAIter,
            class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy(   _RAIter __f,
        _RAIter __l,
        __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
        typename enable_if<__is_random_access_iterator<_RAIter>::value>::type* = 0);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
copy(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     _OutputIterator __r);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy_backward(_RAIter __f,
              _RAIter __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
              typename enable_if<__is_random_access_iterator<_RAIter>::value>::type* = 0);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
copy_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              _OutputIterator __r);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move(_RAIter __f,
     _RAIter __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
     typename enable_if<__is_random_access_iterator<_RAIter>::value>::type* = 0);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
move(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     _OutputIterator __r);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move_backward(_RAIter __f,
              _RAIter __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
              typename enable_if<__is_random_access_iterator<_RAIter>::value>::type* = 0);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
move_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              _OutputIterator __r);

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

/**
 * 这是什么意思？
 */
template <class _ValueType, class _DiffType>
struct __deque_block_size
{
    /**
     * deque 的存储按需自动扩展及收缩。
     * 扩张 deque 比扩展 std::vector 便宜，因为它不涉及到复制既存元素到新内存位置。
     * 另一方面， deque 典型地拥有较大的最小内存开销；只保有一个元素的 deque 必须分配其整个内部数组
     * （例如 64 位 libstdc++ 上为对象大小 8 倍； 
     * 64 位 libc++ 上为对象大小 16 倍或 4096 字节的较大者）
     */
    static const _DiffType value = sizeof(_ValueType) < 256 ? 4096 / sizeof(_ValueType) : 16;
};

template <class _ValueType, class _Pointer, class _Reference, class _MapPointer,
            class _DiffType, _DiffType _BS = 
                __deque_block_size<_ValueType, _DiffType>::value
        >
class _LIBCPP_TEMPLATE_VIS __deque_iterator
{
    typedef _MapPointer     __map_iterator;
public:
    typedef _Pointer        pointer;
    typedef _DiffType       difference_type;
private:
    __map_iterator          __m_iter_;  // _Tp**
    pointer                 __ptr_;     // _Tp*

    static const difference_type    __block_size;
public:
    typedef _ValueType value_type;
    typedef random_access_iterator_tag      iterator_category;
    typedef _Reference                      reference;

    _LIBCPP_INLINE_VISIBILITY __deque_iterator() noexcept
    #if _LIBCPP_STD_VER > 11
        : __m_iter_(nullptr), __ptr_(nullptr)
    #endif
    {}

    template <class _Pp, class _Rp, class _MP>
    _LIBCPP_INLINE_VISIBILITY
    __deque_iterator(const __deque_iterator<value_type, _Pp, _Rp, _MP, difference_type, _BS>& __it,
                typename enable_if<is_convertible<_Pp, pointer>::value>::type* = 0) _NOEXCEPT
        : __m_iter_(__it.__m_iter_), __ptr_(__it.__ptr_) {}

    _LIBCPP_INLINE_VISIBILITY reference operator*() const {return *__ptr_;} // _Tp
    _LIBCPP_INLINE_VISIBILITY pointer operator->() const {return __ptr_;}    //_Tp* 

    _LIBCPP_INLINE_VISIBILITY __deque_iterator& operator++()    // 前置 ++
    {
        /**
         * 每一个 __m_iter 指向一个 _Tp* 指针，这个 _Tp* 指针包含了 __block_size 个_Tp 类型的数据
         * 如果 ++__ptr_ - *__m_iter == __block_size 的话，那么说明 __ptr_ 已经走到了 这个 block 的末尾的
         * 位置，我们需要换到下一个 block 继续进行遍历
         */
        if (++__ptr_ - *__m_iter_ == __block_size)
        {
            ++__m_iter_;    // 换到新的 block
            __ptr_ = *__m_iter_;    // 指向这个 block 的开始的位置
        }
        return *this;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator operator++(int)
    {
        __deque_iterator __tmp = *this;
        ++(*this);
        return __tmp;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator& operator--()
    {
        /**
         * 如果 __ptr_ 指向当前的 block 块的开始的位置，那么再次 -- 的话，我们需要转移到
         * 上一个 block 块的末尾的位置
         */
        if (__ptr_ == *__m_iter_)
        {
            --__m_iter_;    // 来到上一个 block 块
            __ptr_ = *__m_iter_ + __block_size; 
            // 指向这个 block 块的末尾的位置 【非元素位置,该 block 块的最后一个元素的下一个位置】
        }
        --__ptr_;   // 指向 block 块的最后一个元素
        return *this;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator operator--(int)
    {
        __deque_iterator __tmp = *this;
        --(*this);
        return __tmp;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator& operator+=(difference_type __n)
    {
        if (__n != 0)
        {
            __n += __ptr_ - *__m_iter_;
            if (__n > 0)
            {
                __m_iter_ += __n / __block_size;
                __ptr_ = *__m_iter_ + __n % __block_size;
            }
            else // (__n < 0)
            {
                difference_type __z = __block_size - 1 - __n;
                __m_iter_ -= __z / __block_size;
                __ptr_ = *__m_iter_ + (__block_size - 1 - __z % __block_size);
            }
        }
        return *this;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator& operator-=(difference_type __n)
    {
        return *this += -__n;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator operator+(difference_type __n) const
    {
        __deque_iterator __t(*this);
        __t += __n;
        return __t;
    }

    _LIBCPP_INLINE_VISIBILITY __deque_iterator operator-(difference_type __n) const
    {
        __deque_iterator __t(*this);
        __t -= __n;
        return __t;
    }

    _LIBCPP_INLINE_VISIBILITY
    friend __deque_iterator operator+(difference_type __n, const __deque_iterator& __it)
        {return __it + __n;}

    _LIBCPP_INLINE_VISIBILITY
    /**
     * 两个 iterator 之间相差多少个元素 
     */
    friend difference_type operator-(const __deque_iterator& __x, const __deque_iterator& __y)
    {
        if (__x != __y)
            return (__x.__m_iter_ - __y.__m_iter_) * __block_size
                 + (__x.__ptr_ - *__x.__m_iter_)
                 - (__y.__ptr_ - *__y.__m_iter_);
        return 0;
    }

    _LIBCPP_INLINE_VISIBILITY reference operator[](difference_type __n) const
        {return *(*this + __n);}

    _LIBCPP_INLINE_VISIBILITY friend
        bool operator==(const __deque_iterator& __x, const __deque_iterator& __y)
        {return __x.__ptr_ == __y.__ptr_;}

    _LIBCPP_INLINE_VISIBILITY friend
        bool operator!=(const __deque_iterator& __x, const __deque_iterator& __y)
        {return !(__x == __y);}

    _LIBCPP_INLINE_VISIBILITY friend
        bool operator<(const __deque_iterator& __x, const __deque_iterator& __y)
        {return __x.__m_iter_ < __y.__m_iter_ ||
               (__x.__m_iter_ == __y.__m_iter_ && __x.__ptr_ < __y.__ptr_);}

    _LIBCPP_INLINE_VISIBILITY friend
        bool operator>(const __deque_iterator& __x, const __deque_iterator& __y)
        {return __y < __x;}

    _LIBCPP_INLINE_VISIBILITY friend
        bool operator<=(const __deque_iterator& __x, const __deque_iterator& __y)
        {return !(__y < __x);}

    _LIBCPP_INLINE_VISIBILITY friend
        bool operator>=(const __deque_iterator& __x, const __deque_iterator& __y)
        {return !(__x < __y);}

private:
    _LIBCPP_INLINE_VISIBILITY __deque_iterator(__map_iterator __m, pointer __p) _NOEXCEPT
        : __m_iter_(__m), __ptr_(__p) {}

    template <class _Tp, class _Ap> friend class __deque_base;
    template <class _Tp, class _Ap> friend class _LIBCPP_TEMPLATE_VIS deque;
    template <class _Vp, class _Pp, class _Rp, class _MP, class _Dp, _Dp>
        friend class _LIBCPP_TEMPLATE_VIS __deque_iterator;

    template <class _RAIter,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    copy(_RAIter __f,
         _RAIter __l,
         __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
         typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _OutputIterator>
    friend
    _OutputIterator
    copy(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
         __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
         _OutputIterator __r);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    copy(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
         __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
         __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

    template <class _RAIter,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    copy_backward(_RAIter __f,
                  _RAIter __l,
                  __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
                  typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _OutputIterator>
    friend
    _OutputIterator
    copy_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
                  __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
                  _OutputIterator __r);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    copy_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
                  __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
                  __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

    template <class _RAIter,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    move(_RAIter __f,
         _RAIter __l,
         __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
         typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _OutputIterator>
    friend
    _OutputIterator
    move(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
         __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
         _OutputIterator __r);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    move(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
         __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
         __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);

    template <class _RAIter,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    move_backward(_RAIter __f,
                  _RAIter __l,
                  __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
                  typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _OutputIterator>
    friend
    _OutputIterator
    move_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
                  __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
                  _OutputIterator __r);

    template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
              class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
    friend
    __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
    move_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
                  __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
                  __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r);
};
// 类中的 static const 类型数据的初始化
template <class _ValueType, class _Pointer, class _Reference, class _MapPointer,
          class _DiffType, _DiffType _BlockSize>
const _DiffType __deque_iterator<_ValueType, _Pointer, _Reference, _MapPointer,
                                 _DiffType, _BlockSize>::__block_size =
    __deque_block_size<_ValueType, _DiffType>::value;

// copy

template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy(_RAIter __f,
     _RAIter __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
     typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*)
{
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::difference_type difference_type;
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::pointer pointer;
    const difference_type __block_size = __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::__block_size;
    while (__f != __l)
    {
        pointer __rb = __r.__ptr_;
        pointer __re = *__r.__m_iter_ + __block_size;
        difference_type __bs = __re - __rb;
        difference_type __n = __l - __f;
        _RAIter __m = __l;
        if (__n > __bs)
        {
            __n = __bs;
            __m = __f + __n;
        }
        yjh_def::copy(__f, __m, __rb);
        __f = __m;
        __r += __n;
    }
    return __r;
}

/**
 * 最底层的 copy 函数 有两个
 * 1. 根据迭代器进行的逐个元素的拷贝过程
 * 2. 根据指针的连续的内存空间的拷贝过程
 */
template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
copy(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     _OutputIterator __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    const difference_type __block_size = __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::__block_size;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        pointer __fb = __f.__ptr_;
        pointer __fe = *__f.__m_iter_ + __block_size;
        difference_type __bs = __fe - __fb;
        if (__bs > __n)
        {
            __bs = __n;
            __fe = __fb + __bs;
        }
        __r = yjh_def::copy(__fb, __fe, __r);
        __n -= __bs;
        __f += __bs;
    }
    return __r;
}

/**
 * 将从 __f 开始到 __l 结束的所有的数据拷贝到 __r 开始的地方
 */
template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    const difference_type __block_size = __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::__block_size;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        pointer __fb = __f.__ptr_;
        pointer __fe = *__f.__m_iter_ + __block_size;
        difference_type __bs = __fe - __fb;
        /**
         * --------------------------------------------------------
         * block |
         * -------------|-----------------__bs--------------------|
         *           __fb                                      __fe
         */
        if (__bs > __n)
        {
            __bs = __n;
            __fe = __fb + __bs;
        }
        __r = yjh_def::copy(__fb, __fe, __r);   //调用上面的
        __n -= __bs;
        __f += __bs;
    }
    return __r;
}

// copy_backward

template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy_backward(_RAIter __f,
              _RAIter __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
              typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*)
{
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::difference_type difference_type;
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::pointer pointer;
    while (__f != __l)
    {
        __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __rp = yjh_def::prev(__r);
        pointer __rb = *__rp.__m_iter_;
        pointer __re = __rp.__ptr_ + 1;
        difference_type __bs = __re - __rb;
        difference_type __n = __l - __f;
        _RAIter __m = __f;
        if (__n > __bs)
        {
            __n = __bs;
            __m = __l - __n;
        }
        yjh_def::copy_backward(__m, __l, __re);
        __l = __m;
        __r -= __n;
    }
    return __r;
}

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
copy_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              _OutputIterator __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        --__l;
        pointer __lb = *__l.__m_iter_;
        pointer __le = __l.__ptr_ + 1;
        difference_type __bs = __le - __lb;
        if (__bs > __n)
        {
            __bs = __n;
            __lb = __le - __bs;
        }
        __r = yjh_def::copy_backward(__lb, __le, __r);
        __n -= __bs;
        __l -= __bs - 1;
    }
    return __r;
}

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
copy_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        --__l;
        pointer __lb = *__l.__m_iter_;
        pointer __le = __l.__ptr_ + 1;
        difference_type __bs = __le - __lb;
        if (__bs > __n)
        {
            __bs = __n;
            __lb = __le - __bs;
        }
        __r = yjh_def::copy_backward(__lb, __le, __r);
        __n -= __bs;
        __l -= __bs - 1;
    }
    return __r;
}

// move
/**
 * 将从 __f 开始，到 __l 结束的迭代器的数据拷贝到从 __r 开始的空间当中
 */
template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move(_RAIter __f,
     _RAIter __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
     typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*)
{
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::difference_type difference_type;
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::pointer pointer;
    const difference_type __block_size = __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::__block_size;
    while (__f != __l)
    {
        pointer __rb = __r.__ptr_;
        pointer __re = *__r.__m_iter_ + __block_size;
        difference_type __bs = __re - __rb;
        difference_type __n = __l - __f;
        _RAIter __m = __l;
        if (__n > __bs)
        {
            __n = __bs;
            __m = __f + __n;
        }
        yjh_def::move(__f, __m, __rb);
        __f = __m;
        __r += __n;
    }
    return __r;
}

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
move(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     _OutputIterator __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    const difference_type __block_size = __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::__block_size;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        pointer __fb = __f.__ptr_;
        pointer __fe = *__f.__m_iter_ + __block_size;
        difference_type __bs = __fe - __fb;
        if (__bs > __n)
        {
            __bs = __n;
            __fe = __fb + __bs;
        }
        __r = yjh_def::move(__fb, __fe, __r);
        __n -= __bs;
        __f += __bs;
    }
    return __r;
}

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
     __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
     __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    const difference_type __block_size = __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::__block_size;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        pointer __fb = __f.__ptr_;
        pointer __fe = *__f.__m_iter_ + __block_size;
        difference_type __bs = __fe - __fb;
        if (__bs > __n)
        {
            __bs = __n;
            __fe = __fb + __bs;
        }
        __r = yjh_def::move(__fb, __fe, __r);
        __n -= __bs;
        __f += __bs;
    }
    return __r;
}

// move_backward

template <class _RAIter,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move_backward(_RAIter __f,
              _RAIter __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r,
              typename enable_if<__is_random_access_iterator<_RAIter>::value>::type*)
{
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::difference_type difference_type;
    typedef typename __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>::pointer pointer;
    while (__f != __l)
    {
        __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __rp = yjh_def::prev(__r);
        /**
         * -------------------------------------------
         * block| 
         * ------|------------------------|---|----------
         *    __rb                     __rp  __re
         * 确定在当前的 block 中，反向拷贝的开始位置，以及当前的 block 中可以反向拷贝多少个元素
         */
        pointer __rb = *__rp.__m_iter_;
        pointer __re = __rp.__ptr_ + 1;
        difference_type __bs = __re - __rb;
        difference_type __n = __l - __f;
        _RAIter __m = __f;
        if (__n > __bs)
        {
            __n = __bs;
            __m = __l - __n;
        }
        yjh_def::move_backward(__m, __l, __re);
        __l = __m;
        __r -= __n;
    }
    return __r;
}

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _OutputIterator>
_OutputIterator
move_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              _OutputIterator __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        --__l;
        pointer __lb = *__l.__m_iter_;
        pointer __le = __l.__ptr_ + 1;
        difference_type __bs = __le - __lb;
        if (__bs > __n)
        {
            __bs = __n;
            __lb = __le - __bs;
        }
        __r = yjh_def::move_backward(__lb, __le, __r);
        __n -= __bs;
        __l -= __bs - 1;
    }
    return __r;
}

template <class _V1, class _P1, class _R1, class _M1, class _D1, _D1 _B1,
          class _V2, class _P2, class _R2, class _M2, class _D2, _D2 _B2>
__deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2>
move_backward(__deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __f,
              __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1> __l,
              __deque_iterator<_V2, _P2, _R2, _M2, _D2, _B2> __r)
{
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::difference_type difference_type;
    typedef typename __deque_iterator<_V1, _P1, _R1, _M1, _D1, _B1>::pointer pointer;
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        --__l;
        pointer __lb = *__l.__m_iter_;
        pointer __le = __l.__ptr_ + 1;
        difference_type __bs = __le - __lb;
        if (__bs > __n)
        {
            __bs = __n;
            __lb = __le - __bs;
        }
        __r = yjh_def::move_backward(__lb, __le, __r);
        __n -= __bs;
        __l -= __bs - 1;
    }
    return __r;
}

template <bool>
class __deque_base_common
{
protected:
    _LIBCPP_NORETURN void __throw_length_error() const;
    _LIBCPP_NORETURN void __throw_out_of_range() const;
};

template <bool __b>
void
__deque_base_common<__b>::__throw_length_error() const
{
    yjh_def::__throw_length_error("deque");
}

template <bool __b>
void
__deque_base_common<__b>::__throw_out_of_range() const
{
    yjh_def::__throw_out_of_range("deque");
}

template <class _Tp, class _Alloctor>
class __deque_base
    : protected __deque_base_common<true>
{
    __deque_base(const __deque_base& __c);
    __deque_base&   operator=(const __deque_base& __c);
public:
    typedef _Alloctor                                   allocator_type;
    typedef allocator_traits<allocator_type>            __alloc_traits;
    typedef typename __alloc_traits::size_type          size_type;

    typedef _Tp                                         value_type;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef typename __alloc_traits::difference_type    difference_type;
    typedef typename __alloc_traits::pointer            pointer;    // _Tp*
    typedef typename __alloc_traits::const_pointer      const_pointer;  // const _Tp* 

    static const difference_type  __block_size;

    typedef typename __rebind_alloc_helper<__alloc_traits, pointer>::type __pointer_allocator;
    typedef allocator_traits<__pointer_allocator>        __map_traits;
    typedef typename __map_traits::pointer               __map_pointer; // _Tp** 
    typedef typename __rebind_alloc_helper<__alloc_traits, const_pointer>::type __const_pointer_allocator; // const _Tp**
    typedef typename allocator_traits<__const_pointer_allocator>::const_pointer __map_const_pointer;
    typedef __split_buffer<pointer, __pointer_allocator> __map;

    typedef __deque_iterator<value_type, pointer, reference, __map_pointer,
                             difference_type>    iterator;
    typedef __deque_iterator<value_type, const_pointer, const_reference, __map_const_pointer,
                             difference_type>    const_iterator;

    struct __deque_block_range
    /**
     * 这个类存储的是 一个 block 所有的元素的起始位置，pointer 为 _Tp* 类型
     */
    {
        explicit __deque_block_range(pointer __b, pointer __e) _NOEXCEPT
            : __begin_(__b), __end_(__e){}
        const pointer __begin_;   // _Tp*
        const pointer __end_;   // _Tp*
    };      

    struct __deque_range
    {
        iterator __pos_;
        const iterator __end_;

        __deque_range(iterator __pos, iterator __e) _NOEXCEPT
            : __pos_(__pos), __end_(__e) {}
        
        explicit operator bool() const _NOEXCEPT
        {
            return __pos_ != __end_;
        }

        __deque_range begin() const
        {
            return *this;
        }

        __deque_range end() const
        {
            return __deque_range(__end_, __end_);
        }

        __deque_block_range operator*() const noexcept
        /**
         * 返回一个 block 的开始地址和结束地址
         */
        {
            if(__pos_.__m_iter_ == __end_.__m_iter_)    // 如果两个迭代器的 是同一个 block 块的话
            {
                return __deque_block_range(__pos_.__ptr_, __end_.__ptr_);
            }
            return __deque_block_range(__pos_.__ptr_, *__pos_.__m_iter_ + __block_size);    // 从当前 block 的某一个位置开始，到该 block 的尾部
        }

        __deque_range& operator++() noexcept
        /**
         * 指向下一个 block 
         */
        {
            if (__pos_.__m_iter_ == __end_.__m_iter_)
                __pos_ = __end_;
            else
            {
                ++__pos_.__m_iter_;
                __pos_.__ptr_ = *__pos_.__m_iter_;
            }
            return *this;
        }

        friend  bool operator== (const __deque_range & __lhs, const __deque_range& __rhs)
        {
            return __lhs.__pos_ == __rhs.__pos_;
        }

        friend bool operator!=(const __deque_range& __lhs, const __deque_range& __rhs)
        {
            return !(__lhs == __rhs);
        }
    };

    struct _ConstructTransaction {
      _ConstructTransaction(__deque_base* __db, __deque_block_range& __r)
        : __pos_(__r.__begin_), __end_(__r.__end_), __begin_(__r.__begin_), __base_(__db) {}


      ~_ConstructTransaction() {
        __base_->size() += (__pos_ - __begin_);      // 修改了 deque 中统计元素个数的变量
      }

      pointer __pos_;
      const pointer __end_; // 说明了 __end_ 是不允许被改变的  一个块内存的末尾地址是固定的，不需要改变的
    private:
      const pointer __begin_;
      __deque_base * const __base_;
    };
protected:
    __map __map_;
    size_type __start_; // 第一个元素存储在开辟的空间的第 __start_ 个位置
    /**
     * 第一个元素不一定存储在开辟的空间的最前端[即 __split_buffer 第一个存储的 _Tp** 所指向的 _Tp*
     * 指向的大小为 __block_size 大小的内存空间的第一个空间]。
     * 因为deque 是一个双端的队列，所以它的存储空间的前面应该留有空闲的空间，方便从前面进行插入，所以第一个元素
     * 不会存储在 __split_buffer::__begin_ 指向的 _Tp* 所指向的 内存空间的第一个元素
     */
    __compressed_pair<size_type, allocator_type> __size_;

    iterator        begin() noexcept;
    const_iterator  begin() const noexcept;
    iterator        end() noexcept;
    const_iterator  end() const noexcept;

    _LIBCPP_INLINE_VISIBILITY size_type&        size() { __size_.first(); }
    // 现在一共存储的元素的个数
    _LIBCPP_INLINE_VISIBILITY
    const size_type& size() const noexcept {return __size_.first();}
    _LIBCPP_INLINE_VISIBILITY allocator_type& __alloc() {return __size_.second();}
    _LIBCPP_INLINE_VISIBILITY
    const allocator_type& __alloc() const noexcept {return __size_.second();}

    _LIBCPP_INLINE_VISIBILITY
    __deque_base()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);
    _LIBCPP_INLINE_VISIBILITY
    explicit __deque_base(const allocator_type& __a);
public:
    ~__deque_base();

#ifndef _LIBCPP_CXX03_LANG
    __deque_base(__deque_base&& __c)
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value);
    __deque_base(__deque_base&& __c, const allocator_type& __a);
#endif  // _LIBCPP_CXX03_LANG

    void swap(__deque_base& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value);
#endif
protected:
    void clear() _NOEXCEPT;

    bool __invariants() const;  // 不变量

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign(__deque_base& __c)
        _NOEXCEPT_(__alloc_traits::propagate_on_container_move_assignment::value &&
                   is_nothrow_move_assignable<allocator_type>::value)
    {
        __map_ = yjh_def::move(__c.__map_);
        __start_ = __c.__start_;
        size() = __c.size();
        __move_assign_alloc(__c);
        __c.__start_ = __c.size() = 0;  
    }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__deque_base& __c)
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_move_assignment::value ||
                   is_nothrow_move_assignable<allocator_type>::value)
        {__move_assign_alloc(__c, integral_constant<bool,
                      __alloc_traits::propagate_on_container_move_assignment::value>());}

private:
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__deque_base& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = yjh_def::move(__c.__alloc());
        }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__deque_base&, false_type) _NOEXCEPT
        {}
};

// 对 static 变量的初始化定义
template <class _Tp, class _Allocator>
const typename __deque_base<_Tp, _Allocator>::difference_type
    __deque_base<_Tp, _Allocator>::__block_size = 
        __deque_block_size<value_type, difference_type>::value;

template <class _Tp, class _Allocator>
bool
__deque_base<_Tp, _Allocator>::__invariants() const
{
    if (!__map_.__invariants())
        return false;
    if (__map_.size() >= size_type(-1) / __block_size)
        return false;
    for (typename __map::const_iterator __i = __map_.begin(), __e = __map_.end();
         __i != __e; ++__i)
        if (*__i == nullptr)
            return false;
    if (__map_.size() != 0)
    {
        if (size() >= __map_.size() * __block_size)
            return false;
        if (__start_ >= __map_.size() * __block_size - size())
            return false;
    }
    else
    {
        if (size() != 0)
            return false;
        if (__start_ != 0)
            return false;
    }
    return true;
}

template <class _Tp, class _Allocator>
typename __deque_base<_Tp, _Allocator>::iterator     //遍历deque 元素的迭代器，其中保存了 block 的指针和单个元素的指针
__deque_base<_Tp, _Allocator>::begin() _NOEXCEPT
{
    /**
     * __start_ 指代了当前的迭代器应该指向哪一个元素
     */
    __map_pointer __mp = __map_.begin() + __start_ / __block_size;
    // __start / __block_size 指示的是 __mp 应该指向哪一个 block
    return iterator(__mp, __map_.empty() ? 0 : *__mp + __start_ % __block_size);
    //  __start_ % __block_size 指示了  _Tp* 指向该 block 的哪一个元素
}

template <class _Tp, class _Allocator>
typename __deque_base<_Tp, _Allocator>::const_iterator
/**
 * 和上面的功能是相同的，只不过返回的指针为 const 类型  [不允许元素被修改]
 */
__deque_base<_Tp, _Allocator>::begin() const _NOEXCEPT
{
    __map_const_pointer __mp = static_cast<__map_const_pointer>(__map_.begin() + __start_ / __block_size);
    return const_iterator(__mp, __map_.empty() ? 0 : *__mp + __start_ % __block_size);
}

template <class _Tp, class _Allocator>
typename __deque_base<_Tp, _Allocator>::iterator
__deque_base<_Tp, _Allocator>::end() _NOEXCEPT
{
    size_type __p = size() + __start_;     // 最后一个元素存储在第多少个开辟的空间中
    __map_pointer __mp = __map_.begin() + __p / __block_size;
    return iterator(__mp, __map_.empty() ? 0 : *__mp + __p % __block_size);
}

template <class _Tp, class _Allocator>
typename __deque_base<_Tp, _Allocator>::const_iterator
__deque_base<_Tp, _Allocator>::end() const _NOEXCEPT
{
    size_type __p = size() + __start_;
    __map_const_pointer __mp = static_cast<__map_const_pointer>(__map_.begin() + __p / __block_size);
    return const_iterator(__mp, __map_.empty() ? 0 : *__mp + __p % __block_size);
}

template <class _Tp, class _Allocator>
inline
__deque_base<_Tp, _Allocator>::__deque_base()
    _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
    : __start_(0), __size_(0) {}    // 注意 __start_ 的默认值

template <class _Tp, class _Allocator>
inline
__deque_base<_Tp, _Allocator>::__deque_base(const allocator_type& __a)
    : __map_(__pointer_allocator(__a)), __start_(0), __size_(0, __a) {}

template <class _Tp, class _Allocator>
__deque_base<_Tp, _Allocator>::~__deque_base()
{
    clear();
    typename __map::iterator __i = __map_.begin();
    typename __map::iterator __e = __map_.end();
    for (; __i != __e; ++__i)
        __alloc_traits::deallocate(__alloc(), *__i, __block_size);
        /**
         * 依此释放掉每一个 block 的空间
         */
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
__deque_base<_Tp, _Allocator>::__deque_base(__deque_base&& __c)
    _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value)
    : __map_(yjh_def::move(__c.__map_)),
      __start_(yjh_def::move(__c.__start_)),
      __size_(yjh_def::move(__c.__size_))
{
    __c.__start_ = 0;
    __c.size() = 0;
}

template <class _Tp, class _Allocator>
/**
 * 这个地方没有弄懂是什么意思， __map_ 是如何完成 copy 的工作的
 */
__deque_base<_Tp, _Allocator>::__deque_base(__deque_base&& __c, const allocator_type& __a)
    : __map_(yjh_def::move(__c.__map_), __pointer_allocator(__a)),  // ????
        /**
         * 注意 __map_ 的移动构造，也会检查 __pointer_allocator(__a) 和 __c.__map_ 的 allocator
         * 是否是同类
         * 不是同类的话，执行拷贝，__c 依然保留所有的数据
         * 是同类的话，执行移动，__c.__map_ 中的指针都清零 [交出了内存的控制权]
         */
      __start_(yjh_def::move(__c.__start_)),
      __size_(yjh_def::move(__c.size()), __a)
{
    if (__a == __c.__alloc())
    /**
     * 查看新的 allocator 和 __c 中的 allocator 是否相同，如果相同， 说明了__c 中的数据也可以用 
     * __a 来进行处理(销毁)
     */
    {
        __c.__start_ = 0;
        __c.size() = 0;
    }
    else
    /**
     * 否则的话，就不可以用 __a 来管理 __c 中分配的内存，那么拷贝过来的__map_ 的数据被清除
     */
    {
        __map_.clear();     
        __start_ = 0;
        size() = 0;
    }
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
void
__deque_base<_Tp, _Allocator>::swap(__deque_base& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT
#else
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value)
#endif
{
    __map_.swap(__c.__map_);
    yjh_def::swap(__start_, __c.__start_);
    yjh_def::swap(size(), __c.size());
    __swap_allocator(__alloc(), __c.__alloc());
}

template <class _Tp, class _Allocator>
void
__deque_base<_Tp, _Allocator>::clear() _NOEXCEPT
{
    allocator_type& __a = __alloc();
    for (iterator __i = begin(), __e = end(); __i != __e; ++__i)    
        __alloc_traits::destroy(__a, yjh_def::addressof(*__i));   //*__i 指代 _Tp 对象 析构所有的 _Tp 对象
    size() = 0;
    while (__map_.size() > 2)  
    /**所以的 _Tp 数据都被析构了，__map_ 中的 _Tp** 指针指向的_Tp*
     * 指向的内存块 block 被没有被回收, 但是我们希望只保留不超过两个 block 块， 并把我们的 __start_ 位置指定在最中心的位置
    */
    {
        __alloc_traits::deallocate(__a, __map_.front(), __block_size);  /*从 __map_ 的前端开始释放一些内存块的内存*/
        __map_.pop_front();
    }
    switch (__map_.size())
    {
        /**
         * 指定新的数据开始的位置
         */
    case 1:
        __start_ = __block_size / 2;
        break;
    case 2:
        __start_ = __block_size;
        break;
    }
}

// deque 
/**
 * 这里是 deque 的主类
 */
template <class _Tp, class _Allocator>
class _LIBCPP_TEMPLATE_VIS deque
    : private __deque_base<_Tp, _Allocator>
{
public:
    // types:
    
    typedef _Tp         value_type;
    typedef _Allocator  allocator_type;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");
    
    typedef __deque_base<value_type, allocator_type> __base;

    typedef typename __base::__alloc_traits        __alloc_traits;
    typedef typename __base::reference             reference;
    typedef typename __base::const_reference       const_reference;
    typedef typename __base::iterator              iterator;
    typedef typename __base::const_iterator        const_iterator;
    typedef typename __base::size_type             size_type;
    typedef typename __base::difference_type       difference_type;

    typedef typename __base::pointer               pointer;
    typedef typename __base::const_pointer         const_pointer;

    typedef typename yjh_def::reverse_iterator<iterator>            reverse_iterator;
    typedef typename yjh_def::reverse_iterator<const_iterator>      const_reverse_iterator;

    using typename __base::__deque_range;
    using typename __base::__deque_block_range;
    using typename __base::_ConstructTransaction;

    // construct/copy/destroy:
    _LIBCPP_INLINE_VISIBILITY
    deque()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value){}

    _LIBCPP_INLINE_VISIBILITY 
    explicit deque(const allocator_type& __a) : __base(__a) {}

    explicit deque(size_type __n);

#if _LIBCPP_STD_VER > 11
    explicit deque(size_type __n, const _Allocator& __a);
#endif
    deque(size_type __n, const value_type& __v);
    deque(size_type __n, const value_type& __v, const allocator_type& __a);
    template <class _InputIter>
        deque(_InputIter __f, _InputIter __l,
              typename enable_if<__is_input_iterator<_InputIter>::value>::type* = 0);

    template <class _InputIter>
        deque(_InputIter __f, _InputIter __l, const allocator_type& __a,
              typename enable_if<__is_input_iterator<_InputIter>::value>::type* = 0);

    deque(const deque& __c);
    deque(const deque& __c, const allocator_type& __a);

    deque& operator=(const deque& __c);

#ifndef _LIBCPP_CXX03_LANG
    deque(initializer_list<value_type> __il);
    deque(initializer_list<value_type> __il, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    deque& operator=(initializer_list<value_type> __il) {assign(__il); return *this;}

    _LIBCPP_INLINE_VISIBILITY
    deque(deque&& __c) _NOEXCEPT_(is_nothrow_move_constructible<__base>::value);

    _LIBCPP_INLINE_VISIBILITY
    deque(deque&& __c, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    deque& operator=(deque&& __c)
        _NOEXCEPT_(__alloc_traits::propagate_on_container_move_assignment::value &&
                   is_nothrow_move_assignable<allocator_type>::value);

    _LIBCPP_INLINE_VISIBILITY
    void assign(initializer_list<value_type> __il) {assign(__il.begin(), __il.end());}
#endif  // _LIBCPP_CXX03_LANG

    template <class _InputIter>
        void assign(_InputIter __f, _InputIter __l,
                    typename enable_if<__is_input_iterator<_InputIter>::value &&
                                      !__is_random_access_iterator<_InputIter>::value>::type* = 0);
    template <class _RAIter>
        void assign(_RAIter __f, _RAIter __l,
                    typename enable_if<__is_random_access_iterator<_RAIter>::value>::type* = 0);
    void assign(size_type __n, const value_type& __v);

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT;

    // iterators:
    /**
     * __deque_base 和 __deque_iterator 已经提供了完善的迭代器的功能，这里直接使用就可以了
     */

    _LIBCPP_INLINE_VISIBILITY
    iterator       begin() _NOEXCEPT       {return __base::begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT {return __base::begin();}
    _LIBCPP_INLINE_VISIBILITY
    iterator       end() _NOEXCEPT         {return __base::end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end()   const _NOEXCEPT {return __base::end();}

    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator       rbegin() _NOEXCEPT
        {return       reverse_iterator(__base::end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin() const _NOEXCEPT
        {return const_reverse_iterator(__base::end());}
    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator       rend() _NOEXCEPT
        {return       reverse_iterator(__base::begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend()   const _NOEXCEPT
        {return const_reverse_iterator(__base::begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cbegin()  const _NOEXCEPT
        {return __base::begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cend()    const _NOEXCEPT
        {return __base::end();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return const_reverse_iterator(__base::end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend()   const _NOEXCEPT
        {return const_reverse_iterator(__base::begin());}


    // capacity:
    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT {return __base::size();}

    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT
        {return yjh_def::min<size_type>(
            __alloc_traits::max_size(__base::__alloc()),
            numeric_limits<difference_type>::max());}

    void resize(size_type __n);
    void resize(size_type __n, const value_type& __v);
    void shrink_to_fit() _NOEXCEPT;
    _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT {return __base::size() == 0;}


    // element access:
    _LIBCPP_INLINE_VISIBILITY
    reference operator[](size_type __i) _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    const_reference operator[](size_type __i) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    reference at(size_type __i);
    _LIBCPP_INLINE_VISIBILITY
    const_reference at(size_type __i) const;
    _LIBCPP_INLINE_VISIBILITY
    reference front() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    const_reference front() const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    reference back() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    const_reference back() const _NOEXCEPT;



    // 23.2.2.3 modifiers:
    void push_front(const value_type& __v);
    void push_back(const value_type& __v);
#ifndef _LIBCPP_CXX03_LANG
#if _LIBCPP_STD_VER > 14
    template <class... _Args> reference emplace_front(_Args&&... __args);
    template <class... _Args> reference emplace_back (_Args&&... __args);
#else
    template <class... _Args> void      emplace_front(_Args&&... __args);
    template <class... _Args> void      emplace_back (_Args&&... __args);
#endif
    template <class... _Args> iterator emplace(const_iterator __p, _Args&&... __args);

    void push_front(value_type&& __v);
    void push_back(value_type&& __v);
    iterator insert(const_iterator __p, value_type&& __v);

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, initializer_list<value_type> __il)
        {return insert(__p, __il.begin(), __il.end());}
#endif  // _LIBCPP_CXX03_LANG
    iterator insert(const_iterator __p, const value_type& __v);
    iterator insert(const_iterator __p, size_type __n, const value_type& __v);
    template <class _InputIter>
        iterator insert(const_iterator __p, _InputIter __f, _InputIter __l,
                         typename enable_if<__is_input_iterator<_InputIter>::value
                                         &&!__is_forward_iterator<_InputIter>::value>::type* = 0);
    template <class _ForwardIterator>
        iterator insert(const_iterator __p, _ForwardIterator __f, _ForwardIterator __l,
                               typename enable_if<__is_forward_iterator<_ForwardIterator>::value
                                         &&!__is_bidirectional_iterator<_ForwardIterator>::value>::type* = 0);
    template <class _BiIter>
        iterator insert(const_iterator __p, _BiIter __f, _BiIter __l,
                         typename enable_if<__is_bidirectional_iterator<_BiIter>::value>::type* = 0);

    void pop_front();
    void pop_back();
    iterator erase(const_iterator __p);
    iterator erase(const_iterator __f, const_iterator __l);

    _LIBCPP_INLINE_VISIBILITY
    void swap(deque& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<allocator_type>::value);
#endif
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    bool __invariants() const {return __base::__invariants();}

    typedef typename __base::__map_const_pointer __map_const_pointer;

    _LIBCPP_INLINE_VISIBILITY
    static size_type __recommend_blocks(size_type __n)
    /**
     * 大致估计了元素的个数为 __n, 那么会给你一个合理的 block 分配的个数，保证不会有大量的内存空间浪费
     */
    {
        return __n / __base::__block_size + (__n % __base::__block_size != 0);
    }
    _LIBCPP_INLINE_VISIBILITY
    size_type __capacity() const
    {
        /**
         * __map_ 中存储的都是指向 _Tp 数据类型的指针的指针，size() 指示了其中已经分配了
         * __map_.size() 指示了有多少个 block
         */
        return __base::__map_.size() == 0 ? 0 : __base::__map_.size() * __base::__block_size - 1;
    }
    _LIBCPP_INLINE_VISIBILITY
    size_type __block_count() const // 查看 deque 有多少个块  block
    {
        return __base::__map_.size();
    }

    _LIBCPP_INLINE_VISIBILITY
    size_type __front_spare() const
    {
        return __base::__start_;    /*__start_ 指示了第一个元素存储的位置，它前面的位置都是空闲的位置  __start_ 的值最小为 0*/
    }
    _LIBCPP_INLINE_VISIBILITY
    size_type __front_spare_blocks() const {
      return __front_spare() / __base::__block_size;
    }
    _LIBCPP_INLINE_VISIBILITY
    size_type __back_spare() const
    {
        /**
         * 
         */
        return __capacity() - (__base::__start_ + __base::size());
    }
    _LIBCPP_INLINE_VISIBILITY
    size_type __back_spare_blocks() const {
      return __back_spare() / __base::__block_size;
    }

 private:
    _LIBCPP_INLINE_VISIBILITY
    /**
     * 是否移除前面的存储空间
     * __keep_one 指示是否在前面保留一个空闲的 block 以供以后的使用
     */
    bool __maybe_remove_front_spare(bool __keep_one = true) {
      if (__front_spare_blocks() >= 2 || (!__keep_one && __front_spare_blocks())) {
        __alloc_traits::deallocate(__base::__alloc(), __base::__map_.front(),   // __map_front() 返回 _Tp* 即 block的内存地址
                                   __base::__block_size);
        __base::__map_.pop_front();
        __base::__start_ -= __base::__block_size;
        return true;
      }
      return false;
    }

    _LIBCPP_INLINE_VISIBILITY
    bool __maybe_remove_back_spare(bool __keep_one = true) {
      if (__back_spare_blocks() >= 2 || (!__keep_one && __back_spare_blocks())) {
        __alloc_traits::deallocate(__base::__alloc(), __base::__map_.back(),
                                   __base::__block_size);
        __base::__map_.pop_back();
        return true;
      }
      return false;
    }

    template <class _InpIter>
        void __append(_InpIter __f, _InpIter __l,
                 typename enable_if<__is_input_iterator<_InpIter>::value &&
                                   !__is_forward_iterator<_InpIter>::value>::type* = 0);
    template <class _ForIter>
        void __append(_ForIter __f, _ForIter __l,
                      typename enable_if<__is_forward_iterator<_ForIter>::value>::type* = 0);
    void __append(size_type __n);
    void __append(size_type __n, const value_type& __v);
    void __erase_to_end(const_iterator __f);
    void __add_front_capacity();
    void __add_front_capacity(size_type __n);
    void __add_back_capacity();
    void __add_back_capacity(size_type __n);
    iterator __move_and_check(iterator __f, iterator __l, iterator __r,
                              const_pointer& __vt);
    iterator __move_backward_and_check(iterator __f, iterator __l, iterator __r,
                                       const_pointer& __vt);
    void __move_construct_and_check(iterator __f, iterator __l,
                                    iterator __r, const_pointer& __vt);
    void __move_construct_backward_and_check(iterator __f, iterator __l,
                                             iterator __r, const_pointer& __vt);

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const deque& __c)
        {__copy_assign_alloc(__c, integral_constant<bool,
                      __alloc_traits::propagate_on_container_copy_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const deque& __c, true_type)
        {
            if (__base::__alloc() != __c.__alloc())
            {
                clear();
                shrink_to_fit();
            }
            __base::__alloc() = __c.__alloc();
            __base::__map_.__alloc() = __c.__map_.__alloc();
        }

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const deque&, false_type)
        {}

    void __move_assign(deque& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);
    void __move_assign(deque& __c, false_type);
};

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(size_type __n)
{
    if (__n > 0)
        __append(__n);
}

#if _LIBCPP_STD_VER > 11
template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(size_type __n, const _Allocator& __a)
    : __base(__a)
{
    if (__n > 0)
        __append(__n);
}
#endif

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(size_type __n, const value_type& __v)
{
    if (__n > 0)
        __append(__n, __v);
}

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(size_type __n, const value_type& __v, const allocator_type& __a)
    : __base(__a)
{
    if (__n > 0)
        __append(__n, __v);
}

template <class _Tp, class _Allocator>
template <class _InputIter>
deque<_Tp, _Allocator>::deque(_InputIter __f, _InputIter __l,
              typename enable_if<__is_input_iterator<_InputIter>::value>::type*)
{
    __append(__f, __l);
}

template <class _Tp, class _Allocator>
template <class _InputIter>
deque<_Tp, _Allocator>::deque(_InputIter __f, _InputIter __l, const allocator_type& __a,
              typename enable_if<__is_input_iterator<_InputIter>::value>::type*)
    : __base(__a)
{
    __append(__f, __l);
}

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(const deque& __c)
    : __base(__alloc_traits::select_on_container_copy_construction(__c.__alloc()))
{
    __append(__c.begin(), __c.end());
}

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(const deque& __c, const allocator_type& __a)
    : __base(__a)
{
    __append(__c.begin(), __c.end());
}

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>&
deque<_Tp, _Allocator>::operator=(const deque& __c)
{
    if (this != &__c)
    {
        __copy_assign_alloc(__c);
        assign(__c.begin(), __c.end());
    }
    return *this;
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(initializer_list<value_type> __il)
{
    __append(__il.begin(), __il.end());
}

template <class _Tp, class _Allocator>
deque<_Tp, _Allocator>::deque(initializer_list<value_type> __il, const allocator_type& __a)
    : __base(__a)
{
    __append(__il.begin(), __il.end());
}

template <class _Tp, class _Allocator>
inline
deque<_Tp, _Allocator>::deque(deque&& __c)
    _NOEXCEPT_(is_nothrow_move_constructible<__base>::value)
    : __base(yjh_def::move(__c))
{
}

template <class _Tp, class _Allocator>
inline
deque<_Tp, _Allocator>::deque(deque&& __c, const allocator_type& __a)
    : __base(yjh_def::move(__c), __a)
{
    if (__a != __c.__alloc())
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__c.begin()), _Ip(__c.end()));
    }
}


template <class _Tp, class _Allocator>
/**
 * allocator 不具有 move 的特性
 */
void
deque<_Tp, _Allocator>::__move_assign(deque& __c, false_type)
{
    if (__base::__alloc() != __c.__alloc())
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__c.begin()), _Ip(__c.end()));
    }
    else
        __move_assign(__c, true_type());
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::__move_assign(deque& __c, true_type)
    _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
{
    clear();
    shrink_to_fit();
    __base::__move_assign(__c);     // 调用基类的 __move_assign() 函数
}


// deque::assign
template <class _Tp, class _Allocator>
template <class _InputIter>
void
deque<_Tp, _Allocator>::assign(_InputIter __f, _InputIter __l,
                    typename enable_if
                        <
                            __is_input_iterator<_InputIter>::value && 
                            !__is_random_access_iterator<_InputIter>::value
                        >::type*
                    )
{
    iterator __i = __base::begin();
    iterator __e = __base::end();
    /**
     * 注意如果这个时候的 deque 是空的，那么 __i == __e
     */
    for (; __f != __l && __i != __e; ++__f, (void)++__i)    // 存疑问
        *__i = *__f;
    if (__f != __l)
        __append(__f, __l);
    else
        __erase_to_end(__i);
}

template <class _Tp, class _Allocator>
template <class _RAIter>
void
deque<_Tp, _Allocator>::assign(_RAIter __f, _RAIter __l,
            typename enable_if
                <
                    __is_random_access_iterator<_RAIter>::value
                >::type*)
{
    if(static_cast<size_type>(__l - __f) > __base::size())
    {
        _RAIter __m = __f + __base::size();
        yjh_def::copy(__f, __m, __base::begin());
        __append(__m, __l);
    }
    else
        __erase_to_end(yjh_def::copy(__f, __l, __base::begin()));
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::assign(size_type __n, const value_type& __v)
{
    if (__n > __base::size())
    {
        yjh_def::fill_n(__base::begin(), __base::size(), __v);
        __n -= __base::size();
        __append(__n, __v);
    }
    else
        __erase_to_end(yjh_def::fill_n(__base::begin(), __n, __v));
        /**
         * 剩余的部分全部销毁
         */
}

template <class _Tp, class _Allocator>
void
/**
 * 删除从 __f 到 尾部的所有的数据
 */
deque<_Tp, _Allocator>::__erase_to_end(const_iterator __f)
{
    iterator __e = __base::end();
    difference_type __n = __e - __f;
    if (__n > 0)
    {
        allocator_type& __a = __base::__alloc();
        iterator __b = __base::begin();
        difference_type __pos = __f - __b;
        for (iterator __p = __b + __pos; __p != __e; ++__p)
            __alloc_traits::destroy(__a, yjh_def::addressof(*__p)); /*析构这些数据的内容，但是不回收空间*/
        __base::size() -= __n;
        while (__maybe_remove_back_spare()) {   // 回收后面多余的 block
        }
    }
}


template <class _Tp, class _Allocator>
inline
deque<_Tp, _Allocator>&
deque<_Tp, _Allocator>::operator=(deque&& __c)
        _NOEXCEPT_(__alloc_traits::propagate_on_container_move_assignment::value &&
                   is_nothrow_move_assignable<allocator_type>::value)
{
    __move_assign(__c, integral_constant<bool,
          __alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
inline
_Allocator
deque<_Tp, _Allocator>::get_allocator() const _NOEXCEPT
{
    return __base::__alloc();
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::resize(size_type __n)
{
    if (__n > __base::size())
        __append(__n - __base::size());
    else if (__n < __base::size())
        __erase_to_end(__base::begin() + __n);
    /**
     * 等于的情况不需要做任何的调整
     */
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::resize(size_type __n, const value_type& __v)
{
    if (__n > __base::size())
        __append(__n - __base::size(), __v);
    else if (__n < __base::size())
        __erase_to_end(__base::begin() + __n);
}

// shrink_to_fit
// 合理收缩，节约内存
template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::shrink_to_fit() noexcept
{
    allocator_type& __a = __base::__alloc();
    if (empty())
    {
        while(__base::__map_.size() > 0)
        {
            __alloc_traits::deallocate(__a, __base::__map_.back(), __base::__block_size);
            // 回收一个 block 的内存 
            __base::__map_.pop_back(); // 消除指向这种 block 的指针
        }
        __base::__start_ = 0;   
    }
    else
    {
        __maybe_remove_front_spare(false);
        __maybe_remove_back_spare(false);
    }
    __base::__map_.shrink_to_fit();
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::reference
deque<_Tp, _Allocator>::operator[](size_type __i) _NOEXCEPT
{
    size_type __p = __base::__start_ + __i;
    return *(*(__base::__map_.begin() + __p / __base::__block_size) + __p % __base::__block_size);
    /**
     * __p / __block_size 确定 是哪一个 block
     * __p % __block_size 确定是这个  block 中的哪一个元素
     */
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::const_reference
deque<_Tp, _Allocator>::operator[](size_type __i) const _NOEXCEPT
{
    size_type __p = __base::__start_ + __i;
    return *(*(__base::__map_.begin() + __p / __base::__block_size) + __p % __base::__block_size);
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::reference
deque<_Tp, _Allocator>::at(size_type __i)
{
    if (__i >= __base::size())
        __base::__throw_out_of_range();
    size_type __p = __base::__start_ + __i;
    return *(*(__base::__map_.begin() + __p / __base::__block_size) + __p % __base::__block_size);
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::const_reference
deque<_Tp, _Allocator>::at(size_type __i) const
{
    if (__i >= __base::size())
        __base::__throw_out_of_range();
    size_type __p = __base::__start_ + __i;
    return *(*(__base::__map_.begin() + __p / __base::__block_size) + __p % __base::__block_size);
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::reference
deque<_Tp, _Allocator>::front() _NOEXCEPT
/**
 * 获取第一个元素
 */
{
    return *(*(__base::__map_.begin() + __base::__start_ / __base::__block_size)
                                      + __base::__start_ % __base::__block_size);
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::const_reference
deque<_Tp, _Allocator>::front() const _NOEXCEPT
{
    return *(*(__base::__map_.begin() + __base::__start_ / __base::__block_size)
                                      + __base::__start_ % __base::__block_size);
}
// back
template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::reference
deque<_Tp, _Allocator>::back() _NOEXCEPT
{
    size_type __p = __base::size() + __base::__start_ - 1;
    return *(*(__base::__map_.begin() + __p / __base::__block_size) + __p % __base::__block_size);
}

template <class _Tp, class _Allocator>
inline
typename deque<_Tp, _Allocator>::const_reference
deque<_Tp, _Allocator>::back() const _NOEXCEPT
{
    size_type __p = __base::size() + __base::__start_ - 1;
    return *(*(__base::__map_.begin() + __p / __base::__block_size) + __p % __base::__block_size);
}

template <class _Tp, class _Allocator>
template <class _InpIter>
void
deque<_Tp, _Allocator>::__append(_InpIter __f, _InpIter __l,
        typename enable_if
            <
                __is_input_iterator<_InpIter>::value &&
                !__is_forward_iterator<_InpIter>::value
            >::type*
)
{
    for (; __f != __l; ++__f)
    #ifdef _LIBCPP_CXX03_LANG
        push_back(*__f);
    #else
        emplace_back(*__f);
    #endif
}

template <class _Tp, class _Allocator>
template <class _ForIter>
void
deque<_Tp, _Allocator>::__append(_ForIter __f, _ForIter __l,
            typename enable_if
                <
                    __is_forward_iterator<_ForIter>::value
                >::type*)
{
    size_type __n = yjh_def::distance(__f, __l);
    allocator_type& __a = __base::__alloc();
    size_type __back_capacity = __back_spare();
    if (__n > __back_capacity)  // 尾部剩余的空间无法再插入这么多的元素了
    // 只能再次增加空间
        __add_back_capacity(__n - __back_capacity);
    for (__deque_block_range __br : __deque_range(__base::end(), __base::end() + __n))    
    // __deque_range 有 begin() end(), 以及 operator++ 和 operator* 那么就可以把他看作是一个迭代器，在 for() 中使用
    {
        _ConstructTransaction __tx(this, __br); // 这个类在析构的时候会自动对 __base::size()进行更改
        for (; __tx.__pos_ != __tx.__end_; ++__tx.__pos_, (void)++__f)
        {
            __alloc_traits::construct(__a, yjh_def::__to_raw_pointer(__tx.__pos_), *__f);
        }
    }
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::__append(size_type __n)
{
    allocator_type& __a = __base::__alloc();
    size_type __back_capacity = __back_spare();
    if (__n > __back_capacity)
        __add_back_capacity(__n - __back_capacity);
    for (__deque_block_range __br : __deque_range(__base::end(), __base::end() + __n))
    {
        _ConstructTransaction __tx(this, __br);
        for (; __tx.__pos_ != __tx.__end_; ++__tx.__pos_)
            __alloc_traits::construct(__a, yjh_def::__to_raw_pointer(__tx.__pos_));
    }
}


// Create front capacity for one block of elements.
// Strong guarantee.  Either do it or don't touch anything.
template <class _Tp, class _Allocator>
void
/**
 * 在整体的前面添加一个 block
 */
deque<_Tp, _Allocator>::__add_front_capacity()
{
    allocator_type& __a = __base::__alloc();
    /**
     * 1. 后面有空余的 block 把他移动到前面
     * 2. 后面没有空余的话，再看 __map_ 是否还有内存空间没有被用于指向 block,如果有的话，那么就新建block
     * 3. __map_ 中都没有了 空闲的内存空间用于指向新的 block，那么只能重新分配 __map_ 的大小了
     */
    if (__back_spare() >= __base::__block_size)
    {
        __base::__start_ += __base::__block_size;   // 注意，这一步必不可少
        pointer __pt = __base::__map_.back();
        __base::__map_.pop_back();
        __base::__map_.push_front(__pt);
    }
    // Else if __base::__map_.size() < __base::__map_.capacity() then we need to allocate 1 buffer
    else if (__base::__map_.size() < __base::__map_.capacity())
    {   // we can put the new buffer into the map, but don't shift things around
        // until all buffers are allocated.  If we throw, we don't need to fix
        // anything up (any added buffers are undetectible)
        if (__base::__map_.__front_spare() > 0)
            __base::__map_.push_front(__alloc_traits::allocate(__a, __base::__block_size));
        else
        {
            __base::__map_.push_back(__alloc_traits::allocate(__a, __base::__block_size));
            // Done allocating, reorder capacity
            pointer __pt = __base::__map_.back();
            __base::__map_.pop_back();
            __base::__map_.push_front(__pt);
        }
        /**
         * 如果添加了一个 block 之后，整个 __map_ 中只指向了一个 block ,那就说明了目前 deque 中还没有存储任何的数据
         * __start_ 可以放在合适的位置，比如说，放在这个 block 的中心位置
         */
        __base::__start_ = __base::__map_.size() == 1 ?
                               __base::__block_size / 2 :
                               __base::__start_ + __base::__block_size;
    }
    // Else need to allocate 1 buffer, *and* we need to reallocate __map_.
    // __map_ 中都没有了 空闲的内存空间用于指向新的 block，那么只能重新分配 __map_ 的大小了
    else
    {
        __split_buffer<pointer, typename __base::__pointer_allocator&>
            __buf(max<size_type>(2 * __base::__map_.capacity(), 1),
                  0, __base::__map_.__alloc()); 

        typedef __allocator_destructor<_Allocator> _Dp;
        unique_ptr<pointer, _Dp> __hold(
            __alloc_traits::allocate(__a, __base::__block_size),    // 新分配的 block
            // 之所以使用 unique_ptr 可能是为了程序发生异常的情况下可以正常的释放这些内存
                _Dp(__a, __base::__block_size));
        __buf.push_back(__hold.get());
        __hold.release();

        for (typename __base::__map_pointer __i = __base::__map_.begin();
                __i != __base::__map_.end(); ++__i)
            __buf.push_back(*__i);
        yjh_def::swap(__base::__map_.__first_, __buf.__first_);
        yjh_def::swap(__base::__map_.__begin_, __buf.__begin_);
        yjh_def::swap(__base::__map_.__end_, __buf.__end_);
        yjh_def::swap(__base::__map_.__end_cap(), __buf.__end_cap());
        __base::__start_ = __base::__map_.size() == 1 ?
                               __base::__block_size / 2 :
                               __base::__start_ + __base::__block_size;
    }
}

// Create front capacity for __n elements.
// Strong guarantee.  Either do it or don't touch anything.
template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::__add_front_capacity(size_type __n)
{
    /**
     * 1. 首先根据 __n 确定我们需要添加多少个 block
     * 2. 查看尾部是否有足够多的空闲的 block 可以使用，如果够的话，就把他们移动到前面去
     * 3. 如果尾部没有足够多的空闲的 block 可以使用的话，那么我们查看 __map_ 中是否有空间
     * 还没有指向 block,如果这些空间比需要添加的 block 的个数多的话，那么就可以创建新的block
     * 4. 如果上面的这一些都不能满足的话，那就只能对 __map_ 进行扩充了
     */
    allocator_type& __a = __base::__alloc();
    size_type __nb = __recommend_blocks(__n + __base::__map_.empty());
    // Number of unused blocks at back:
    size_type __back_capacity = __back_spare() / __base::__block_size;
    __back_capacity = yjh_def::min(__back_capacity, __nb);  // don't take more than you need
    __nb -= __back_capacity;  // number of blocks need to allocate
    // If __nb == 0, then we have sufficient capacity.
    if (__nb == 0)
    {
        __base::__start_ += __base::__block_size * __back_capacity;
        for (; __back_capacity > 0; --__back_capacity)
        {
            pointer __pt = __base::__map_.back();
            __base::__map_.pop_back();
            __base::__map_.push_front(__pt);
        }
    }
    // Else if __nb <= __map_.capacity() - __map_.size() then we need to allocate __nb buffers
    else if (__nb <= __base::__map_.capacity() - __base::__map_.size())
    {   // we can put the new buffers into the map, but don't shift things around
        // until all buffers are allocated.  If we throw, we don't need to fix
        // anything up (any added buffers are undetectible)
        for (; __nb > 0; --__nb, __base::__start_ += __base::__block_size - (__base::__map_.size() == 1))
        {
            if (__base::__map_.__front_spare() == 0)
                break;
            __base::__map_.push_front(__alloc_traits::allocate(__a, __base::__block_size));
        }
        for (; __nb > 0; --__nb, ++__back_capacity)
            __base::__map_.push_back(__alloc_traits::allocate(__a, __base::__block_size));
        // Done allocating, reorder capacity
        __base::__start_ += __back_capacity * __base::__block_size;
        for (; __back_capacity > 0; --__back_capacity)
        {
            pointer __pt = __base::__map_.back();
            __base::__map_.pop_back();
            __base::__map_.push_front(__pt);
        }
    }
    // Else need to allocate __nb buffers, *and* we need to reallocate __map_.
    else
    {
        /*注意上面的代码中 __nb -= __back_capacity 中 __nb 被减少了，在这里我们需要加回来*/
        /**
         * __map_.empty() :
         * 如果 __map_ 是空的，那么 __start_ 放置在最后一个空间位置上，这个位置上实际上没有存储任何的数据
         * 如果不是空的，那就不需要考虑这个问题
         */
        size_type __ds = (__nb + __back_capacity) * __base::__block_size - __base::__map_.empty();
        __split_buffer<pointer, typename __base::__pointer_allocator&>
            __buf(max<size_type>(2* __base::__map_.capacity(),
                                 __nb + __base::__map_.size()),
                  0, __base::__map_.__alloc());
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (; __nb > 0; --__nb)
            /**
             * 先在前面插入需要增加的 block
             */
                __buf.push_back(__alloc_traits::allocate(__a, __base::__block_size));
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            for (typename __base::__map_pointer __i = __buf.begin();
                    __i != __buf.end(); ++__i)
                __alloc_traits::deallocate(__a, *__i, __base::__block_size);
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        /**
         * 把原先的 __map_ 的尾部的空闲的 block 添加到新的 __map_ 当中
         */
        for (; __back_capacity > 0; --__back_capacity)
        {
            __buf.push_back(__base::__map_.back());
            __base::__map_.pop_back();
        }
        /**
         * 把旧的 __map_ 的中间部分插入到新的 __map_ 中
         */
        for (typename __base::__map_pointer __i = __base::__map_.begin();
                __i != __base::__map_.end(); ++__i)
            __buf.push_back(*__i);
        yjh_def::swap(__base::__map_.__first_, __buf.__first_);
        yjh_def::swap(__base::__map_.__begin_, __buf.__begin_);
        yjh_def::swap(__base::__map_.__end_, __buf.__end_);
        yjh_def::swap(__base::__map_.__end_cap(), __buf.__end_cap());
        __base::__start_ += __ds;   // 记得调整 __start_ 的位置
    }
}



// Create back capacity for __n elements.
// Strong guarantee.  Either do it or don't touch anything.
template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::__add_back_capacity(size_type __n)
{
    allocator_type& __a = __base::__alloc();
    size_type __nb = __recommend_blocks(__n + __base::__map_.empty());
    // Number of unused blocks at front:
    size_type __front_capacity = __front_spare() / __base::__block_size;    // 数据结构的前面有多少个空闲的 block
    __front_capacity = yjh_def::min(__front_capacity, __nb);  // don't take more than you need
    __nb -= __front_capacity;  // number of blocks need to allocate
    // If __nb == 0, then we have sufficient capacity.
    if (__nb == 0)
    {
        /**
         * 把前面这些空闲的 block 都移动到后面
         */
        __base::__start_ -= __base::__block_size * __front_capacity;
        for (; __front_capacity > 0; --__front_capacity)
        {
            pointer __pt = __base::__map_.front();
            __base::__map_.pop_front();
            __base::__map_.push_back(__pt);
        }
    }
    // Else if __nb <= __map_.capacity() - __map_.size() then we need to allocate __nb buffers
    else if (__nb <= __base::__map_.capacity() - __base::__map_.size())
    /**
     * 虽然 block 的个数不够，但是在 __map_ 中还有空间可以指向新的 _Tp* 类型，所以分别在__map_ 的后面和前面构建新的 block
     */
    {   // we can put the new buffers into the map, but don't shift things around
        // until all buffers are allocated.  If we throw, we don't need to fix
        // anything up (any added buffers are undetectible)
        for (; __nb > 0; --__nb)
        {
            if (__base::__map_.__back_spare() == 0)
                break;
            __base::__map_.push_back(__alloc_traits::allocate(__a, __base::__block_size));
        }
        for (; __nb > 0; --__nb, ++__front_capacity, __base::__start_ +=
                                 __base::__block_size - (__base::__map_.size() == 1))
            __base::__map_.push_front(__alloc_traits::allocate(__a, __base::__block_size));
        // Done allocating, reorder capacity
        __base::__start_ -= __base::__block_size * __front_capacity;
        for (; __front_capacity > 0; --__front_capacity)
        /**
         * 把前面增加的 block 移动到后面去
         */
        {
            pointer __pt = __base::__map_.front();
            __base::__map_.pop_front();
            __base::__map_.push_back(__pt);
        }
    }
    // Else need to allocate __nb buffers, *and* we need to reallocate __map_.
    /**
     * 这种情况下，我们需要向 __map_ 中添加新的 block
     */
    else
    {
        size_type __ds = __front_capacity * __base::__block_size;
        __split_buffer<pointer, typename __base::__pointer_allocator&>
            __buf(max<size_type>(2* __base::__map_.capacity(),
                                 __nb + __base::__map_.size()),
                  __base::__map_.size() - __front_capacity,
                  __base::__map_.__alloc());
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            for (; __nb > 0; --__nb)
                __buf.push_back(__alloc_traits::allocate(__a, __base::__block_size));
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            for (typename __base::__map_pointer __i = __buf.begin();
                    __i != __buf.end(); ++__i)
                __alloc_traits::deallocate(__a, *__i, __base::__block_size);
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
        for (; __front_capacity > 0; --__front_capacity)
        {
            __buf.push_back(__base::__map_.front());
            __base::__map_.pop_front();
        }
        for (typename __base::__map_pointer __i = __base::__map_.end();
                __i != __base::__map_.begin();)
            __buf.push_front(*--__i);
        yjh_def::swap(__base::__map_.__first_, __buf.__first_);
        yjh_def::swap(__base::__map_.__begin_, __buf.__begin_);
        yjh_def::swap(__base::__map_.__end_, __buf.__end_);
        yjh_def::swap(__base::__map_.__end_cap(), __buf.__end_cap());
        __base::__start_ -= __ds;
    }
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::push_front(const value_type& __v)
{
    allocator_type& __a = __base::__alloc();
    if (__front_spare() == 0)
        __add_front_capacity();
    // __front_spare() >= 1
    __alloc_traits::construct(__a, yjh_def::addressof(*--__base::begin()), __v);
    --__base::__start_;
    ++__base::size();
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::push_back(const value_type& __v)
{
    allocator_type& __a = __base::__alloc();    // 这个 allocator 是分配 _Tp 类型数据内存的分配器
    if (__back_spare() == 0)
        __add_back_capacity();
    __alloc_traits::construct(__a, yjh_def::addressof(*__base::end()), __v);
    ++__base::size();
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::push_back(value_type&& __v)
{
    allocator_type& __a = __base::__alloc();
    if (__back_spare() == 0)
        __add_back_capacity();
    // __back_spare() >= 1
    __alloc_traits::construct(__a, yjh_def::addressof(*__base::end()), yjh_def::move(__v));
    ++__base::size();
}

template <class _Tp, class _Allocator>
template <class... _Args>
#if _LIBCPP_STD_VER > 14
typename deque<_Tp, _Allocator>::reference
#else
void
#endif
deque<_Tp, _Allocator>::emplace_back(_Args&&... __args)
{
    allocator_type& __a = __base::__alloc();
    if (__back_spare() == 0)
        __add_back_capacity();
    // __back_spare() >= 1
    __alloc_traits::construct(__a, yjh_def::addressof(*__base::end()),
                              yjh_def::forward<_Args>(__args)...);
    ++__base::size();
#if _LIBCPP_STD_VER > 14
    return *--__base::end();
#endif
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::push_front(value_type&& __v)
{
    allocator_type& __a = __base::__alloc();
    if (__front_spare() == 0)
        __add_front_capacity();
    // __front_spare() >= 1
    __alloc_traits::construct(__a, yjh_def::addressof(*--__base::begin()), yjh_def::move(__v));
    --__base::__start_;
    ++__base::size();
}

template <class _Tp, class _Allocator>
template <class... _Args>
#if _LIBCPP_STD_VER > 14
typename deque<_Tp, _Allocator>::reference
#else
void
#endif
deque<_Tp, _Allocator>::emplace_front(_Args&&... __args)
{
    allocator_type& __a = __base::__alloc();
    if (__front_spare() == 0)
        __add_front_capacity();
    // __front_spare() >= 1
    __alloc_traits::construct(__a, yjh_def::addressof(*--__base::begin()), 
                            yjh_def::forward<_Args>(__args)...);
    --__base::__start_;
    ++__base::size();
#if _LIBCPP_STD_VER > 14
    return *__base::begin();
#endif
}

/**
 * 为什么 deque 要支持 insert 
 * 这是很奇怪的要求
 */
template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::insert(const_iterator __p, value_type&& __v)
{
    size_type __pos = __p - __base::begin();    // __pos 和 开始位置的距离
    size_type __to_end = __base::size() - __pos;    // __pos 和结束为止的距离
    allocator_type& __a = __base::__alloc();
    /**
     * 插入元素需要移动大量的数据，如果插入的数据在前半个区间的话，我们尽量往前面进行移动
     * 首先把第一个元素存储到第一个元素的前面的一个位置，之后，从第2个元素开始，依次将他们向前面
     * 挪动一位，这种移动的过程一直到 __pos 为止，这个时候，__pos 的位置就会空出来，这时候插入
     * 要插入的元素就可以了
     * 同理，如果插入的区域在后半个区间的时候，采用像后面移动比较方便
     */
    if (__pos < __to_end)   // 
    {   // insert by shifting things backward
        if (__front_spare() == 0)
            __add_front_capacity();
        // __front_spare() >= 1
        if (__pos == 0)     // __pos 指向 begin() ，元素插入整体的前面
        {
            __alloc_traits::construct(__a, yjh_def::addressof(*--__base::begin()), yjh_def::move(__v));
            --__base::__start_;
            ++__base::size();
        }
        else
        {
            iterator __b = __base::begin();
            iterator __bm1 = yjh_def::prev(__b);   //指向 __b 的前面一个元素的地址
            __alloc_traits::construct(__a, yjh_def::addressof(*__bm1), yjh_def::move(*__b));
            --__base::__start_;
            ++__base::size();
            if (__pos > 1)
                __b = yjh_def::move(yjh_def::next(__b), __b + __pos, __b);
            *__b = yjh_def::move(__v);
        }
    }
    else
    {   // insert by shifting things forward
        if (__back_spare() == 0)
            __add_back_capacity();
        // __back_capacity >= 1
        size_type __de = __base::size() - __pos;
        if (__de == 0)
        {
            __alloc_traits::construct(__a, yjh_def::addressof(*__base::end()), yjh_def::move(__v));
            ++__base::size();
        }
        else
        {
            iterator __e = __base::end();
            iterator __em1 = yjh_def::prev(__e);
            __alloc_traits::construct(__a, yjh_def::addressof(*__e), yjh_def::move(*__em1));
            ++__base::size();
            if (__de > 1)
                __e = yjh_def::move_backward(__e - __de, __em1, __e);
            *--__e = yjh_def::move(__v);
        }
    }
    return __base::begin() + __pos;
}

template <class _Tp, class _Allocator>
template <class... _Args>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::emplace(const_iterator __p, _Args&&... __args)
{
    size_type __pos = __p - __base::begin();
    size_type __to_end = __base::size() - __pos;
    allocator_type& __a = __base::__alloc();
    if (__pos < __to_end)
    {   // insert by shifting things backward
        if (__front_spare() == 0)
            __add_front_capacity();
        // __front_spare() >= 1
        if (__pos == 0)
        {
            __alloc_traits::construct(__a, yjh_def::addressof(*--__base::begin()), yjh_def::forward<_Args>(__args)...);
            --__base::__start_;
            ++__base::size();
        }
        else
        {
            __temp_value<value_type, _Allocator> __tmp(this->__alloc(), yjh_def::forward<_Args>(__args)...);
            iterator __b = __base::begin();
            iterator __bm1 = yjh_def::prev(__b);
            __alloc_traits::construct(__a, yjh_def::addressof(*__bm1), yjh_def::move(*__b));
            --__base::__start_;
            ++__base::size();
            if (__pos > 1)
                __b = yjh_def::move(yjh_def::next(__b), __b + __pos, __b);
            *__b = yjh_def::move(__tmp.get());
        }
    }
    else
    {   // insert by shifting things forward
        if (__back_spare() == 0)
            __add_back_capacity();
        // __back_capacity >= 1
        size_type __de = __base::size() - __pos;
        if (__de == 0)
        {
            __alloc_traits::construct(__a, yjh_def::addressof(*__base::end()), yjh_def::forward<_Args>(__args)...);
            ++__base::size();
        }
        else
        {
            __temp_value<value_type, _Allocator> __tmp(this->__alloc(), yjh_def::forward<_Args>(__args)...);
            iterator __e = __base::end();
            iterator __em1 = yjh_def::prev(__e);
            __alloc_traits::construct(__a, yjh_def::addressof(*__e), yjh_def::move(*__em1));
            ++__base::size();
            if (__de > 1)
                __e = yjh_def::move_backward(__e - __de, __em1, __e);
            *--__e = yjh_def::move(__tmp.get());
        }
    }
    return __base::begin() + __pos;
}

#endif

template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::insert(const_iterator __p, const value_type& __v)
{
    size_type __pos = __p - __base::begin();
    size_type __to_end = __base::size() - __pos;
    allocator_type& __a = __base::__alloc();
    if (__pos < __to_end)
    {   // insert by shifting things backward
        if (__front_spare() == 0)
            __add_front_capacity();
        // __front_spare() >= 1
        if (__pos == 0)
        {
            __alloc_traits::construct(__a, yjh_def::addressof(*--__base::begin()), __v);
            --__base::__start_;
            ++__base::size();
        }
        else
        {
            const_pointer __vt = pointer_traits<const_pointer>::pointer_to(__v);
            iterator __b = __base::begin();
            iterator __bm1 = yjh_def::prev(__b);
            if (__vt == pointer_traits<const_pointer>::pointer_to(*__b))
                __vt = pointer_traits<const_pointer>::pointer_to(*__bm1);
            __alloc_traits::construct(__a, yjh_def::addressof(*__bm1), yjh_def::move(*__b));
            --__base::__start_;
            ++__base::size();
            if (__pos > 1)
                __b = __move_and_check(yjh_def::next(__b), __b + __pos, __b, __vt);
            *__b = *__vt;
        }
    }
    else
    {   // insert by shifting things forward
        if (__back_spare() == 0)
            __add_back_capacity();
        // __back_capacity >= 1
        size_type __de = __base::size() - __pos;
        if (__de == 0)
        {
            __alloc_traits::construct(__a, yjh_def::addressof(*__base::end()), __v);
            ++__base::size();
        }
        else
        {
            const_pointer __vt = pointer_traits<const_pointer>::pointer_to(__v);
            iterator __e = __base::end();
            iterator __em1 = yjh_def::prev(__e);
            if (__vt == pointer_traits<const_pointer>::pointer_to(*__em1))
                __vt = pointer_traits<const_pointer>::pointer_to(*__e);
            __alloc_traits::construct(__a, yjh_def::addressof(*__e), yjh_def::move(*__em1));
            ++__base::size();
            if (__de > 1)
                __e = __move_backward_and_check(__e - __de, __em1, __e, __vt);
            *--__e = *__vt;
        }
    }
    return __base::begin() + __pos;
}

template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::insert(const_iterator __p, size_type __n, const value_type& __v)
{
    size_type __pos = __p - __base::begin();
    size_type __to_end = __base::size() - __pos;
    allocator_type& __a = __base::__alloc();
    if (__pos < __to_end)
    {   // insert by shifting things backward
        if (__n > __front_spare())
            __add_front_capacity(__n - __front_spare());
        // __n <= __front_spare()
        iterator __old_begin = __base::begin();
        iterator __i = __old_begin;
        if (__n > __pos)
        {
            for (size_type __m = __n - __pos; __m; --__m, --__base::__start_, ++__base::size())
                __alloc_traits::construct(__a, yjh_def::addressof(*--__i), __v);
            __n = __pos;
        }
        if (__n > 0)
        {
            const_pointer __vt = pointer_traits<const_pointer>::pointer_to(__v);
            iterator __obn = __old_begin + __n;
            __move_construct_backward_and_check(__old_begin, __obn, __i, __vt);
            if (__n < __pos)
                __old_begin = __move_and_check(__obn, __old_begin + __pos, __old_begin, __vt);
            yjh_def::fill_n(__old_begin, __n, *__vt);
        }
    }
    else
    {   // insert by shifting things forward
        size_type __back_capacity = __back_spare();
        if (__n > __back_capacity)
            __add_back_capacity(__n - __back_capacity);
        // __n <= __back_capacity
        iterator __old_end = __base::end();
        iterator __i = __old_end;
        size_type __de = __base::size() - __pos;
        if (__n > __de)
        {
            for (size_type __m = __n - __de; __m; --__m, ++__i, ++__base::size())
                __alloc_traits::construct(__a, yjh_def::addressof(*__i), __v);
            __n = __de;
        }
        if (__n > 0)
        {
            const_pointer __vt = pointer_traits<const_pointer>::pointer_to(__v);
            iterator __oen = __old_end - __n;
            __move_construct_and_check(__oen, __old_end, __i, __vt);
            if (__n < __de)
                __old_end = __move_backward_and_check(__old_end - __de, __oen, __old_end, __vt);
            yjh_def::fill_n(__old_end - __n, __n, *__vt);
        }
    }
    return __base::begin() + __pos;
}

template <class _Tp, class _Allocator>
template <class _InputIter>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::insert(const_iterator __p, _InputIter __f, _InputIter __l,
                               typename enable_if<__is_input_iterator<_InputIter>::value
                                               &&!__is_forward_iterator<_InputIter>::value>::type*)
{
    __split_buffer<value_type, allocator_type&> __buf(__base::__alloc());
    __buf.__construct_at_end(__f, __l);
    typedef typename __split_buffer<value_type, allocator_type&>::iterator __bi;
    return insert(__p, move_iterator<__bi>(__buf.begin()), move_iterator<__bi>(__buf.end()));
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::insert(const_iterator __p, _ForwardIterator __f, _ForwardIterator __l,
                               typename enable_if<__is_forward_iterator<_ForwardIterator>::value
                                               &&!__is_bidirectional_iterator<_ForwardIterator>::value>::type*)
{
    size_type __n = yjh_def::distance(__f, __l);
    __split_buffer<value_type, allocator_type&> __buf(__n, 0, __base::__alloc());
    __buf.__construct_at_end(__f, __l);
    typedef typename __split_buffer<value_type, allocator_type&>::iterator __fwd;
    return insert(__p, move_iterator<__fwd>(__buf.begin()), move_iterator<__fwd>(__buf.end()));
}

template <class _Tp, class _Allocator>
template <class _BiIter>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::insert(const_iterator __p, _BiIter __f, _BiIter __l,
                               typename enable_if<__is_bidirectional_iterator<_BiIter>::value>::type*)
{
    size_type __n = yjh_def::distance(__f, __l);
    size_type __pos = __p - __base::begin();
    size_type __to_end = __base::size() - __pos;
    allocator_type& __a = __base::__alloc();
    if (__pos < __to_end)
    {   // insert by shifting things backward
        if (__n > __front_spare())
            __add_front_capacity(__n - __front_spare());
        // __n <= __front_spare()
        iterator __old_begin = __base::begin();
        iterator __i = __old_begin;
        _BiIter __m = __f;
        if (__n > __pos)
        {
            __m = __pos < __n / 2 ? yjh_def::prev(__l, __pos) : yjh_def::next(__f, __n - __pos);
            for (_BiIter __j = __m; __j != __f; --__base::__start_, ++__base::size())
                __alloc_traits::construct(__a, yjh_def::addressof(*--__i), *--__j);
            __n = __pos;
        }
        if (__n > 0)
        {
            iterator __obn = __old_begin + __n;
            for (iterator __j = __obn; __j != __old_begin;)
            {
                __alloc_traits::construct(__a, yjh_def::addressof(*--__i), yjh_def::move(*--__j));
                --__base::__start_;
                ++__base::size();
            }
            if (__n < __pos)
                __old_begin = yjh_def::move(__obn, __old_begin + __pos, __old_begin);
            yjh_def::copy(__m, __l, __old_begin);
        }
    }
    else
    {   // insert by shifting things forward
        size_type __back_capacity = __back_spare();
        if (__n > __back_capacity)
            __add_back_capacity(__n - __back_capacity);
        // __n <= __back_capacity
        iterator __old_end = __base::end();
        iterator __i = __old_end;
        _BiIter __m = __l;
        size_type __de = __base::size() - __pos;
        if (__n > __de)
        {
            __m = __de < __n / 2 ? yjh_def::next(__f, __de) : yjh_def::prev(__l, __n - __de);
            for (_BiIter __j = __m; __j != __l; ++__i, (void) ++__j, ++__base::size())
                __alloc_traits::construct(__a, yjh_def::addressof(*__i), *__j);
            __n = __de;
        }
        if (__n > 0)
        {
            iterator __oen = __old_end - __n;
            for (iterator __j = __oen; __j != __old_end; ++__i, ++__j, ++__base::size())
                __alloc_traits::construct(__a, yjh_def::addressof(*__i), yjh_def::move(*__j));
            if (__n < __de)
                __old_end = yjh_def::move_backward(__old_end - __de, __oen, __old_end);
            yjh_def::copy_backward(__f, __m, __old_end);
        }
    }
    return __base::begin() + __pos;
}



template <class _Tp, class _Allocator>
void
/*
front                __begin_                           __end_                back  -----> 指针增加的方向
------------------------|-----------------------------------|----------------------        对应于 __split_buffer
-----------------------------------------------------------------------------------
-----------------------|-----------------------------------|-----------------------      对应于 deque
front                                                                          back     -----> __start_  减小的方向
*/
deque<_Tp, _Allocator>::__add_back_capacity()
{
    /**
     * 默认的情况下，添加一个 block ，也就是 __block_size 个可以容纳 _Tp 数据的空间
     */
    allocator_type& __a = __base::__alloc();    // 分配 _Tp 类型数据的分配器
    if (__front_spare() >= __base::__block_size)    // 前面的空间还大于 __block_size 的时候
    {
        /**
         * 把前面的一个 _Tp** 挪动到后面，实际上相当于在 deque 中将 front 中 __block_size 个 _Tp 类型的空间移动到后面
         * 这 __block_size 个 _Tp 类型的空间还没有分配数据
         */
        __base::__start_ -= __base::__block_size;   // 这个  __start_ 指代的是什么
        pointer _pt = __base::__map_.front();   // 返回的是指向第一个元素的指针
        __base::__map_.pop_front(); // __map_ 中指向 _Tp* 的指针向前移动一位
        __base::__map_.push_back(_pt);
    }   // 下面都是 __front_spare() < __base::__block_size 的情况
    else if (__base::__map_.size() < __base::__map_.capacity())
    {   /*
        * 如果 __split_buffer 中还有没有被使用的空间的话 存储的是 _Tp** 类型
        * 我们在
        */
        if(__base::__map_.__back_spare() != 0)  // __split_buffer 的 back 依然有空余的空间
            __base::__map_.push_back(__alloc_traits::allocate(__a, __base::__block_size));
            /**
             * 在 __split_buffer 的__end_ 后面插入了一个 _Tp** 类型，这个指针指向一个指针 _Tp* ,_Tp* 指向 __block_size 的 _Tp 内存空间
             */
        else    // __split_buffer 的尾部已经没有空间了， 但在这种情况下，首端一定还有空间可以存储 _Tp**
        {
            __base::__map_.push_front(__alloc_traits::allocate(__a, __base::__block_size)); 
            // 在首端分配一个 _Tp** 指向一个 指针 _Tp* ,这个_Tp* 指向 __block_size 个连续的 _Tp 对象内存空间
            pointer _pt = __base::__map_.front();   // 把这个空间从 __split_buffer 的前面移动到 __split_buffer 的后面
            __base::__map_.pop_front();
            __base::__map_.push_back(_pt);
        }
    }
    // Else need to allocate 1 buffer, *and* we need to reallocate __map_.
    /**
     * 这种情况下， __split_buffer 中的所有的空间都已经存储了 _Tp** 类型的数据(当然其指向的 _Tp* 数组中是否存储了 _Tp 类型数据未知)
     * 显然至少 在前端中还可以分配给 _Tp 类型的空间的数量一定是小于 __block_size 的
     * 这种情况下需要扩大 __split_buffer
     */
    else
    {
        __split_buffer<pointer, typename __base::__pointer_allocator&>
            __buf(max<size_type>(2* __base::__map_.capacity(), 1),
                  __base::__map_.size(),
                  __base::__map_.__alloc());

        typedef __allocator_destructor<_Allocator> _Dp; // 功能只有一个，那就是调用 allocator 的 deallocator 函数
        unique_ptr<pointer, _Dp> __hold(
            __alloc_traits::allocate(__a, __base::__block_size),    // 分配了 __block_size 个 _Tp 类型数据空间
                _Dp(__a, __base::__block_size));
        __buf.push_back(__hold.get());
        __hold.release();

        for (typename __base::__map_pointer __i = __base::__map_.end();
                __i != __base::__map_.begin();)
            __buf.push_front(*--__i);
        yjh_def::swap(__base::__map_.__first_, __buf.__first_);
        yjh_def::swap(__base::__map_.__begin_, __buf.__begin_);
        yjh_def::swap(__base::__map_.__end_, __buf.__end_);
        yjh_def::swap(__base::__map_.__end_cap(), __buf.__end_cap());
    }
}

// pop 
template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::pop_front()
{
    allocator_type& __a = __base::__alloc();
    __alloc_traits::destroy(__a, __to_raw_pointer(*(__base::__map_.begin() +
                                                    __base::__start_ / __base::__block_size) +
                                                    __base::__start_ % __base::__block_size));
    --__base::size();
    ++__base::__start_;
    __maybe_remove_front_spare();
}

template <class _Tp, class _Allocator>
void
deque<_Tp, _Allocator>::pop_back()
{
    _LIBCPP_ASSERT(!empty(), "deque::pop_back called for empty deque");
    allocator_type& __a = __base::__alloc();
    size_type __p = __base::size() + __base::__start_ - 1;
    __alloc_traits::destroy(__a, __to_raw_pointer(*(__base::__map_.begin() +
                                                    __p / __base::__block_size) +
                                                    __p % __base::__block_size));
    --__base::size();
    __maybe_remove_back_spare();
}


// move assign [__f, __l) to [__r, __r + (__l-__f)).
// If __vt points into [__f, __l), then subtract (__f - __r) from __vt.
template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::__move_and_check(iterator __f, iterator __l, iterator __r,
                                         const_pointer& __vt)
{
    // as if
    //   for (; __f != __l; ++__f, ++__r)
    //       *__r = yjh_def::move(*__f);
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        pointer __fb = __f.__ptr_;
        pointer __fe = *__f.__m_iter_ + __base::__block_size;
        difference_type __bs = __fe - __fb;
        if (__bs > __n)
        {
            __bs = __n;
            __fe = __fb + __bs;
        }
        if (__fb <= __vt && __vt < __fe)
            __vt = (const_iterator(static_cast<__map_const_pointer>(__f.__m_iter_), __vt) -= __f - __r).__ptr_;
        __r = yjh_def::move(__fb, __fe, __r);
        __n -= __bs;
        __f += __bs;
    }
    return __r;
}

// move assign [__f, __l) to [__r - (__l-__f), __r) backwards.
// If __vt points into [__f, __l), then add (__r - __l) to __vt.
template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
deque<_Tp, _Allocator>::__move_backward_and_check(iterator __f, iterator __l, iterator __r,
                                                  const_pointer& __vt)
{
    // as if
    //   while (__f != __l)
    //       *--__r = yjh_def::move(*--__l);
    difference_type __n = __l - __f;
    while (__n > 0)
    {
        --__l;
        pointer __lb = *__l.__m_iter_;
        pointer __le = __l.__ptr_ + 1;
        difference_type __bs = __le - __lb;
        if (__bs > __n)
        {
            __bs = __n;
            __lb = __le - __bs;
        }
        if (__lb <= __vt && __vt < __le)
            __vt = (const_iterator(static_cast<__map_const_pointer>(__l.__m_iter_), __vt) += __r - __l - 1).__ptr_;
        __r = yjh_def::move_backward(__lb, __le, __r);
        __n -= __bs;
        __l -= __bs - 1;
    }
    return __r;
}

template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
/**
 * 擦除__f 这个数据，其他的进行保留
 */
deque<_Tp, _Allocator>::erase(const_iterator __f)
{
    iterator __b = __base::begin();
    difference_type __pos = __f - __b;
    iterator __p = __b + __pos;
    allocator_type& __a = __base::__alloc();
    if (static_cast<size_t>(__pos) <= (__base::size() - 1) / 2)
    {   // erase from front
        /**
         * 如果__f 没有到整个 deque 的一半的话，那么就将__f 前面的所有的元素往右边移动
         * 移位，将 __f 的数据挤掉就可以了
         */
        yjh_def::move_backward(__b, __p, yjh_def::next(__p));
        __alloc_traits::destroy(__a, yjh_def::addressof(*__b));
        --__base::size();
        ++__base::__start_;
        __maybe_remove_front_spare();
    }
    else
    {   // erase from back
        /**
         * 同样的道理，如果 __f 的数据比较的接近尾部，那么就将 __f 后面的所有的数据往左边移动一位，
         * 挤掉 __f 的数据就可以了
         */
        iterator __i = yjh_def::move(yjh_def::next(__p), __base::end(), __p);
        __alloc_traits::destroy(__a, yjh_def::addressof(*__i));
        --__base::size();
        __maybe_remove_back_spare();
    }
    return __base::begin() + __pos;
}


template <class _Tp, class _Allocator>
typename deque<_Tp, _Allocator>::iterator
/**
 * 擦除 __f 到 __l 的所有的数据，其他的保留
 */
deque<_Tp, _Allocator>::erase(const_iterator __f, const_iterator __l)
{
    difference_type __n = __l - __f;
    iterator __b = __base::begin();
    difference_type __pos = __f - __b;
    iterator __p = __b + __pos;
    if (__n > 0)
    {
        allocator_type& __a = __base::__alloc();
        if (static_cast<size_t>(__pos) <= (__base::size() - __n) / 2)
        {   // erase from front
            /**
             * -----------------------------------------------------
             * |-----pos------|---------|------------|---------------
             * __b           __f     __l-pos        __l
             * 将 从 __b 到 __f 的空间反向复制到 __f 到 __l 的空间中，析构掉
             * 从 __b 到 __l-pos 的所有的元素
             */
            iterator __i = yjh_def::move_backward(__b, __p, __p + __n);
            for (; __b != __i; ++__b)
                __alloc_traits::destroy(__a, yjh_def::addressof(*__b));
            __base::size() -= __n;
            __base::__start_ += __n;
            while (__maybe_remove_front_spare()) {
            }
        }
        else
        {   // erase from back
            iterator __i = yjh_def::move(__p + __n, __base::end(), __p);
            for (iterator __e = __base::end(); __i != __e; ++__i)
                __alloc_traits::destroy(__a, yjh_def::addressof(*__i));
            __base::size() -= __n;
            while (__maybe_remove_back_spare()) {
            }
        }
    }
    return __base::begin() + __pos;
}

template <class _Tp, class _Allocator>
inline
void
deque<_Tp, _Allocator>::swap(deque& __c)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT
#else
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value)
#endif
{
    __base::swap(__c);
}

template <class _Tp, class _Allocator>
inline
void
deque<_Tp, _Allocator>::clear() _NOEXCEPT
{
    __base::clear();
}

// deque 的一些比较运算符的重载
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(const deque<_Tp, _Allocator>& __x, const deque<_Tp, _Allocator>& __y)
{
    const typename deque<_Tp, _Allocator>::size_type __sz = __x.size();
    return __sz == __y.size() && yjh_def::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const deque<_Tp, _Allocator>& __x, const deque<_Tp, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator< (const deque<_Tp, _Allocator>& __x, const deque<_Tp, _Allocator>& __y)
{
    return yjh_def::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator> (const deque<_Tp, _Allocator>& __x, const deque<_Tp, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator>=(const deque<_Tp, _Allocator>& __x, const deque<_Tp, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator<=(const deque<_Tp, _Allocator>& __x, const deque<_Tp, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(deque<_Tp, _Allocator>& __x, deque<_Tp, _Allocator>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

#if _LIBCPP_STD_VER > 17
template <class _Tp, class _Allocator, class _Up>
inline _LIBCPP_INLINE_VISIBILITY
void erase(deque<_Tp, _Allocator>& __c, const _Up& __v)
{ __c.erase(yjh_def::remove(__c.begin(), __c.end(), __v), __c.end()); }

template <class _Tp, class _Allocator, class _Predicate>
inline _LIBCPP_INLINE_VISIBILITY
void erase_if(deque<_Tp, _Allocator>& __c, _Predicate __pred)
{ __c.erase(yjh_def::remove_if(__c.begin(), __c.end(), __pred), __c.end()); }
#endif

}

_LIBCPP_POP_MACROS
#endif
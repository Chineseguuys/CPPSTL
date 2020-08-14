#ifndef _LIBCPP_ITERATOR
#define _LIBCPP_ITERATOR

#include "type_traits.cpp"

namespace yjh_def
{
struct  input_iterator_tag {};
struct  output_iterator_tag {};
struct  forward_iterator_tag        : public input_iterator_tag {}; /*前向迭代器不能使用 + - -- 运算符和 [] 运算符*/
struct  bidirectional_iterator_tag  : public forward_iterator_tag {};
struct  random_access_iterator_tag  : public bidirectional_iterator_tag {};

template <class _Tp>
struct __has_iterator_category
{
private:
    struct __two    {char __lx; char __lxx;};
    template <class _Up>    static  __two   __test(...);
    template <class _Up>    static  char    __test(typename _Up::iterator_category* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Iter, bool> struct ____iterator_traits {};

template <class _Iter>
struct ____iterator_traits<_Iter, true>
{
    typedef typename _Iter::difference_type             difference_type;
    typedef typename _Iter::value_type                  value_type;
    typedef typename _Iter::pointer                     pointer;
    typedef typename _Iter::reference                   reference;
    typedef typename _Iter::iterator_category           iterator_catefory;
};

template <class _Iter, bool> struct __iterator_traits {};

template <class _Iter>
struct __iterator_traits<_Iter, true>
    : ____iterator_traits
        <
            _Iter,
            is_convertible<typename _Iter::iterator_category, input_iterator_tag>::value ||
            is_convertible<typename _Iter::iterator_category, output_iterator_tag>::value
        >
{};

template <class _Iter>
struct iterator_traits
    : __iterator_traits<_Iter, __has_iterator_category<_Iter>::value> {};

template <class _Tp>
struct iterator_traits<_Tp*>
{
    typedef ptrdiff_t                               difference_type;
    typedef typename remove_const<_Tp>::type        value_type;
    typedef _Tp*                                    pointer;
    typedef _Tp&                                    reference;
    typedef random_access_iterator_tag              iterator_category;
};

template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value>
struct __has_iterator_category_convertible_to
    : public integral_constant<bool, is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
{};
// 偏特化
template <class _Tp, class _Up>
struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

template <class _Tp>
struct __is_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

template <class _Tp>
struct __is_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

template <class _Tp>
struct __is_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

template <class _Tp>
struct __is_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};


template <  class _Category, class _Tp, class _Distance = ptrdiff_t,
            class _Pointer = _Tp*, class _Reference = _Tp&>
struct  iterator
{
    typedef _Tp                 value_type;
    typedef _Distance           difference_type;
    typedef _Pointer            pointer;
    typedef _Reference          reference;
    typedef _Category           iterator_category;
};

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void __advance(_InputIter& __i,
            typename iterator_traits<_InputIter>::difference_type __n, 
            input_iterator_tag)
{
    for (; __n > 0; --__n)
        ++__i;
}

template <class _BiDirIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void __advance(_BiDirIter& __i,
             typename iterator_traits<_BiDirIter>::difference_type __n, 
             bidirectional_iterator_tag)
{
    if (__n >= 0)
        for (; __n > 0; --__n)
            ++__i;
    else
        for (; __n < 0; ++__n)
            --__i;
}

template <class _RandIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void __advance(_RandIter& __i,
             typename iterator_traits<_RandIter>::difference_type __n, 
             random_access_iterator_tag)
{
   __i += __n;
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void advance(_InputIter& __i,
             typename iterator_traits<_InputIter>::difference_type __n)
{
    #ifdef _DEBUG_
    _LIBCPP_ASSERT(__n >= 0 || __is_bidirectional_iterator<_InputIter>::value,
                       "Attempt to advance(it, -n) on a non-bidi iterator");
    #endif
    __advance(__i, __n, typename iterator_traits<_InputIter>::iterator_category());
}


// distance
template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename iterator_traits<_InputIter>::difference_type
__distance(_InputIter __first, _InputIter __last, input_iterator_tag)
{
    typename iterator_traits<_InputIter>::difference_type __r(0);
    for (; __first != __last; ++__first)
        ++__r;
    return __r;
}

template <class _RandIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename iterator_traits<_RandIter>::difference_type
__distance(_RandIter __first, _RandIter __last, random_access_iterator_tag)
{
    return __last - __first;
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename iterator_traits<_InputIter>::difference_type
distance(_InputIter __first, _InputIter __last)
{
    return __distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename enable_if
    <
        __is_input_iterator<_InputIter>::value,
        _InputIter
    >::type
next(_InputIter __x,
        typename iterator_traits<_InputIter>::difference_type __n = 1)
{
    yjh_def::advance(__x, __n);
    return __x;
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename enable_if
<
    __is_input_iterator<_InputIter>::value,
    _InputIter
>::type
prev(_InputIter __x,
     typename iterator_traits<_InputIter>::difference_type __n = 1)
{
    #ifdef _DEBUG_
    _LIBCPP_ASSERT(__n <= 0 || __is_bidirectional_iterator<_InputIter>::value,
                       "Attempt to prev(it, +n) on a non-bidi iterator");
    #endif
    yjh_def::advance(__x, -__n);
    return __x;
}


template <class _Iter>
class reverse_iterator
    : public iterator<  typename iterator_traits<_Iter>::iterator_category,
                        typename iterator_traits<_Iter>::value_type,
                        typename iterator_traits<_Iter>::difference_type,
                        typename iterator_traits<_Iter>::pointer,
                        typename iterator_traits<_Iter>::reference
    >
{
private:
    mutable _Iter __t;
protected:
    _Iter current;
public:
    typedef _Iter                                                   iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type        difference_type;
    typedef typename iterator_traits<_Iter>::reference              reference;
    typedef typename iterator_traits<_Iter>::pointer                pointer;

    reverse_iterator() : current() {};
    explicit reverse_iterator(_Iter __x) : __t(__x) {};
    template <class _Up>
    reverse_iterator(const reverse_iterator<_Up>& __u)
        : __t(__u.base()), current(__u.base()) {};
    
    _Iter base() const {return current;}
    reference operator*() const {__t = current; return *--__t;}
    pointer operator->() const {return &(operator*());}

    reverse_iterator& operator++() {--current; return *this;}
    reverse_iterator operator++(int) 
        {reverse_iterator __temp(*this); --current; return __temp;}

    reverse_iterator& operator--() {++current; return *this;}
    reverse_iterator operator--(int)
        {reverse_iterator __temp(*this); ++current; return __temp;}
    
    reverse_iterator operator+ (difference_type __n) const
        {return reverse_iterator(current - __n);}
    reverse_iterator& operator+= (difference_type __n) 
        {current -= __n; return *this;}
    reverse_iterator operator- (difference_type __n) const
        {return reverse_iterator(current + __n);}
    reverse_iterator& operator-= (difference_type __n)
        {current += __n; return *this;}

    reference operator[](difference_type __n) const
        {return current[-__n-1];}
};

template <class _Iter1, class _Iter2>
bool operator == (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool operator < (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

/**
 * back_insert_iterator 是一个附在容器的末尾的迭代器，对 back_insert_iterator 进行赋值，就会调用容器的 push_back(value) 将值插入到容器的末尾当中
 * 你无法改变迭代器指定的位置。 back_insert_iterator 实际上有用的功能只有一个函数 operator= (value) 。 向容器中插入元素 
 * back_insert_iterator 并不是一个真正意义上的迭代器，因为其实际上不指向任何的元素，也不能进行移动
 */
template <class _Container>
class back_insert_iterator
    : public iterator<  output_iterator_tag,
                        void,
                        void,
                        void,
                        back_insert_iterator<_Container>&>
{
protected:
    _Container* container;
public:
    typedef _Container container_type;

    explicit back_insert_iterator(_Container& __x) : container(&__x) {}
    back_insert_iterator&           operator= (const typename _Container::value_type& __value_)
        {container->push_back(__value_); return *this;}
    /**
     * 还没有实现 move() 函数，这里暂时不写
    */
    //back_insert_iterator&         operator = (const typename _Container::value_type&& __value_) {}
    back_insert_iterator&           operator*()         {return *this;}
    back_insert_iterator&           operator++()        {return *this;}
    back_insert_iterator            operator++(int)     {return *this;}
};

template <class _Container>
inline back_insert_iterator<_Container>
back_inserter(_Container& __x)
{
    return back_insert_iterator<_Container>(__x);
} 

/**
 * 顾名思义， front_insert_iterator 和 back_insert_iterator 具有相似的功能，只是插入的位置不同，一个从容器的前端进行插入，一个从容器的后端进行插入
 */
template <class _Container>
class front_insert_iterator
    : public iterator<  output_iterator_tag,
                        void,
                        void,
                        void,
                        front_insert_iterator<_Container>&
                        >
{
protected:
    _Container* container;
public:
    typedef _Container          container_type;

    explicit front_insert_iterator(_Container& __x) : container(&__x) {}
    front_insert_iterator&              operator = (const typename _Container::value_type& __value_)
        {container->push_front(__value_); return *this;}
    /**
     * 没有实现 move() 函数，下面的函数暂时不进行实现
     */
    //front_insert_iterator&              operator = (const _Container::value_type&& __value_) {}
    front_insert_iterator&              operator*()             {return *this;}
    front_insert_iterator&              operator++()            {return *this;}
    front_insert_iterator               operator++(int)         {return *this;}
};

/**
 * front_insert_iterator 的工厂函数
 * 根据输入的迭代器来构建一个 front_insert_iterator 对象
 */
template <class _Container>
inline front_insert_iterator<_Container>
front_inserter(_Container& __x)
{
    return front_insert_iterator<_Container>(__x);
}

//move_iterator 
template <class _Iter>
class move_iterator
{
private:
    _Iter __i;
public:
    typedef _Iter                                               iterator_type;
    typedef typename iterator_traits<_Iter>::iterator_catagory  iterator_category;
    typedef typename iterator_traits<_Iter>::value_type         value_type;
    typedef typename iterator_traits<_Iter>::difference_type    difference_type;
    typedef typename iterator_traits<_Iter>::pointer            pointer;

    typedef value_type&&        reference;

    move_iterator() : __i() {}
    explicit move_iterator(_Iter __x) : __i(__x) {}
    template <class _Up>
    explicit move_iterator(const move_iterator<_Up>& __u) : __i(__u.base()) {}

    reference                   operator*() const 
        {return static_cast<reference>(*__i);}
    pointer                     operator->() const
    {
        typename iterator_traits<iterator_type>::reference __ref = *__i;
        return &__i;
    }
    _Iter base() const {return __i;}

    move_iterator&              operator++()        {++__i; return *this;}
    move_iterator               operator++(int)     {move_iterator __temp(*this); ++__i; return __temp;}
    move_iterator&              operator--()        {--__i; return *this;}
    move_iterator               operator--(int)     {move_iterator __temp(*this); --__i; return __temp;}
    move_iterator               operator+ (difference_type __n) const
        {return move_iterator(__i + __n);}
    move_iterator&              operator+= (difference_type __n)
        {__i += __n; return *this;}
    move_iterator               operator- (difference_type __n) const
        {return move_iterator(__i - __n);}
    move_iterator&              operator-= (difference_type __n)
        {__i -= __n; return *this;}
    
    reference                   operator[] (difference_type __n)
        {return static_cast<reference>(__i[__n]);}
};


// __wrap_iter
// 包裹  iterator 对象
// 下面都是一些 forward 函数的声明，具体的定义在后面
template <class _Iter> class __wrap_iter;

template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
auto
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
-> decltype(__x.base() - __y.base());
#else
template <class _Iter1, class _Iter2>
_LIBCPP_INLINE_VISIBILITY
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;
#endif

template <class _Iter>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
__wrap_iter<_Iter>
operator+(typename __wrap_iter<_Iter>::difference_type, __wrap_iter<_Iter>) _NOEXCEPT;

template <class _Ip, class _Op> _Op _LIBCPP_INLINE_VISIBILITY copy(_Ip, _Ip, _Op);
template <class _B1, class _B2> _B2 _LIBCPP_INLINE_VISIBILITY copy_backward(_B1, _B1, _B2);
template <class _Ip, class _Op> _Op _LIBCPP_INLINE_VISIBILITY move(_Ip, _Ip, _Op);
template <class _B1, class _B2> _B2 _LIBCPP_INLINE_VISIBILITY move_backward(_B1, _B1, _B2);

#if _LIBCPP_DEBUG_LEVEL < 2

template <class _Tp>
_LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
typename enable_if
<
    is_trivially_copy_assignable<_Tp>::value,
    _Tp*
>::type
__unwrap_iter(__wrap_iter<_Tp*>);

#else

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
typename enable_if
<
    is_trivially_copy_assignable<_Tp>::value,
    __wrap_iter<_Tp*>
>::type
__unwrap_iter(__wrap_iter<_Tp*> __i);

#endif

template <class _Iter>
/**
 * iterator_traits<> 用于包装 iterator 让所有的类型可以兼容 iterator 具有的数据结构
 * __weap_iter 对 iterator 进行包装，让所有的类型可以兼容 iterator 的函数调用
 * 目前已经知道可以进行包装的内容   iterator 对象 , 数据的指针
 */
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
private:
    iterator_type __i;
public:
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter() _NOEXCEPT
#if _LIBCPP_STD_VER > 11
                : __i{}
#endif
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__insert_i(this);
#endif
    }
    template <class _Up> _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
        __wrap_iter(const __wrap_iter<_Up>& __u,
            typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = 0) _NOEXCEPT
            : __i(__u.base())
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__iterator_copy(this, &__u);
#endif
    }
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
    __wrap_iter(const __wrap_iter& __x)
        : __i(__x.base())
    {
        __get_db()->__iterator_copy(this, &__x);
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
    __wrap_iter& operator=(const __wrap_iter& __x)
    {
        if (this != &__x)
        {
            __get_db()->__iterator_copy(this, &__x);
            __i = __x.__i;
        }
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
    ~__wrap_iter()
    {
        __get_db()->__erase_i(this);
    }
#endif
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG reference operator*() const _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to dereference a non-dereferenceable iterator");
#endif
        return *__i;
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG pointer  operator->() const _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to dereference a non-dereferenceable iterator");
#endif
        return (pointer)yjh_def::addressof(*__i);
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter& operator++() _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
                       "Attempted to increment non-incrementable iterator");
#endif
        ++__i;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter  operator++(int) _NOEXCEPT
        {__wrap_iter __tmp(*this); ++(*this); return __tmp;}

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter& operator--() _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__decrementable(this),
                       "Attempted to decrement non-decrementable iterator");
#endif
        --__i;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter  operator--(int) _NOEXCEPT
        {__wrap_iter __tmp(*this); --(*this); return __tmp;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter  operator+ (difference_type __n) const _NOEXCEPT
        {__wrap_iter __w(*this); __w += __n; return __w;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter& operator+=(difference_type __n) _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__addable(this, __n),
                   "Attempted to add/subtract iterator outside of valid range");
#endif
        __i += __n;
        return *this;
    }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter  operator- (difference_type __n) const _NOEXCEPT
        {return *this + (-__n);}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter& operator-=(difference_type __n) _NOEXCEPT
        {*this += -__n; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG reference    operator[](difference_type __n) const _NOEXCEPT
    {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__subscriptable(this, __n),
                   "Attempted to subscript iterator outside of valid range");
#endif
        return __i[__n];
    }

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG iterator_type base() const _NOEXCEPT {return __i;}

private:
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter(const void* __p, iterator_type __x) : __i(__x)
    {
        __get_db()->__insert_ic(this, __p);
    }
#else
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG __wrap_iter(iterator_type __x) _NOEXCEPT : __i(__x) {}
#endif

    template <class _Up> friend class __wrap_iter;
    template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
    template <class _Tp, class _Alloc> friend class _LIBCPP_TEMPLATE_VIS vector;
    template <class _Tp, size_t> friend class _LIBCPP_TEMPLATE_VIS span;

    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    bool
    operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    bool
    operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    bool
    operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    bool
    operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    bool
    operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    bool
    operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

#ifndef _LIBCPP_CXX03_LANG
    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    auto
    operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
    -> decltype(__x.base() - __y.base());
#else
    template <class _Iter1, class _Iter2>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    typename __wrap_iter<_Iter1>::difference_type
    operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;
#endif

    template <class _Iter1>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    __wrap_iter<_Iter1>
    operator+(typename __wrap_iter<_Iter1>::difference_type, __wrap_iter<_Iter1>) _NOEXCEPT;

    template <class _Ip, class _Op> friend _Op copy(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 copy_backward(_B1, _B1, _B2);
    template <class _Ip, class _Op> friend _Op move(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);

#if _LIBCPP_DEBUG_LEVEL < 2
    template <class _Tp>
    _LIBCPP_CONSTEXPR_IF_NODEBUG friend
    typename enable_if
    <
        is_trivially_copy_assignable<_Tp>::value,
        _Tp*
    >::type
    __unwrap_iter(__wrap_iter<_Tp*>);
#else
  template <class _Tp>
  inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
  typename enable_if
  <
      is_trivially_copy_assignable<_Tp>::value,
      __wrap_iter<_Tp*>
  >::type
  __unwrap_iter(__wrap_iter<_Tp*> __i);
#endif
};  // end of class __wrap_iter 

// 对于 __wrap_iter 的 friend 函数的声明
template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator == (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() == __x.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
bool
operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
auto
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
->  decltype(__x.base() - __y.base())
{
    return __x.base() - __y.base();
}

#else
template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__less_than_comparable(&__x, &__y),
                   "Attempted to subtract incompatible iterators");
#endif
    return __x.base() - __y.base();
}
#endif

template <class _Iter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
__wrap_iter<_Iter>
operator+(typename __wrap_iter<_Iter>::difference_type __n,
          __wrap_iter<_Iter> __x) _NOEXCEPT
{
    __x += __n;
    return __x;
}

}

#endif
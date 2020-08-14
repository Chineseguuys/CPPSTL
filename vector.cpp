#ifndef _LIBCPP_VECTOR
#define _LIBCPP_VECTOR

#include "__config.cpp"
#include "type_traits.cpp"
#include "iosfwd.cpp"
#include "limits.cpp"
#include "initializer_list.cpp"
#include "memory.cpp"
#include "stdexcept.cpp"
#include "algorithm.cpp"
#include "cstring.cpp"
#include "__split_buffer.cpp"
#include "__functional_base.cpp"

#if  !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"

namespace yjh_def
{
template <bool>
class __vector_base_common
{
protected:
	__vector_base_common() {}
	void __throw_length_error() const;
	void __throw_out_of_range() const;
};

template <bool __b>
void
__vector_base_common<__b>::__throw_length_error() const
{
	throw length_error("vector");
}

template <bool __b>
void
__vector_base_common<__b>::__throw_out_of_range() const
{
	throw out_of_range("vector");
}

template <class _Tp, class _Allocator>
class __vector_base
	: protected __vector_base_common<true>
{
public:
    typedef _Allocator                               allocator_type;
    typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef typename __alloc_traits::size_type       size_type;
protected:
    typedef _Tp                                      value_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename __alloc_traits::difference_type difference_type;
    typedef typename __alloc_traits::pointer         pointer;
    typedef typename __alloc_traits::const_pointer   const_pointer;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;

    pointer                                         __begin_;
    pointer                                         __end_;
    __compressed_pair<pointer, allocator_type> __end_cap_;

    _LIBCPP_INLINE_VISIBILITY
    allocator_type& __alloc() _NOEXCEPT
        {return __end_cap_.second();}

    _LIBCPP_INLINE_VISIBILITY
    const allocator_type& __alloc() const _NOEXCEPT
        {return __end_cap_.second();}

    _LIBCPP_INLINE_VISIBILITY
    pointer& __end_cap() _NOEXCEPT
        {return __end_cap_.first();}

    _LIBCPP_INLINE_VISIBILITY
    const pointer& __end_cap() const _NOEXCEPT
        {return __end_cap_.first();}

    _LIBCPP_INLINE_VISIBILITY
    __vector_base()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);

    _LIBCPP_INLINE_VISIBILITY __vector_base(const allocator_type& __a);
#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY __vector_base(allocator_type&& __a) _NOEXCEPT;
#endif

    ~__vector_base();

    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {__destruct_at_end(__begin_);}

    _LIBCPP_INLINE_VISIBILITY
    size_type capacity() const _NOEXCEPT
        {return static_cast<size_type>(__end_cap() - __begin_);}

    _LIBCPP_INLINE_VISIBILITY
    void __destruct_at_end(pointer __new_last) _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __vector_base& __c)
        {__copy_assign_alloc(__c, integral_constant<bool,
                      __alloc_traits::propagate_on_container_copy_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__vector_base& __c)
        _NOEXCEPT_(
            !__alloc_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<allocator_type>::value)
        {__move_assign_alloc(__c, integral_constant<bool,
                      __alloc_traits::propagate_on_container_move_assignment::value>());}
private:
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __vector_base& __c, true_type)
        {
			/**
			 * 如果使用新的 allocator, 由于两种不同的 allocator 之间在分配方式上可能不同，
			 * 所以旧的 allocator 开辟的空间可能无法使用新的 allocator 进行释放，所以
			 * 必须释放掉旧的 allocator 开辟的空间之后，再接受新的 allocator
			 */
            if (__alloc() != __c.__alloc())
            {
                clear();
                __alloc_traits::deallocate(__alloc(), __begin_, capacity());
                __begin_ = __end_ = __end_cap() = nullptr;
            }
            __alloc() = __c.__alloc();
        }

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __vector_base&, false_type)
        {}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__vector_base& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = yjh_def::move(__c.__alloc());
        }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__vector_base&, false_type)
        _NOEXCEPT
        {}

};

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
__vector_base<_Tp, _Allocator>::__destruct_at_end(pointer __new_last) _NOEXCEPT
{
	/**
	 * 注意，只进行了析构，并不会收内存
	 */
    pointer __soon_to_be_end = __end_;
    while (__new_last != __soon_to_be_end)
        __alloc_traits::destroy(__alloc(), yjh_def::__to_raw_pointer(--__soon_to_be_end));
    __end_ = __new_last;
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
__vector_base<_Tp, _Allocator>::__vector_base()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr)
{
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type& __a)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr, __a)
{
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
__vector_base<_Tp, _Allocator>::__vector_base(allocator_type&& __a) _NOEXCEPT
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr, yjh_def::move(__a)) {}
#endif

template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::~__vector_base()
{
    if (__begin_ != nullptr)
    {
        clear();
        __alloc_traits::deallocate(__alloc(), __begin_, capacity());
    }
}

template <class _Tp, class _Allocator>
class _LIBCPP_TEMPLATE_VIS vector
	: private __vector_base<_Tp, _Allocator>
{
private:
    typedef __vector_base<_Tp, _Allocator>           __base;
    typedef allocator<_Tp>                           __default_allocator_type;
public:
    typedef vector                                   __self;
    typedef _Tp                                      value_type;
    typedef _Allocator                               allocator_type;
    typedef typename __base::__alloc_traits          __alloc_traits;
    typedef typename __base::reference               reference;
    typedef typename __base::const_reference         const_reference;
    typedef typename __base::size_type               size_type;
    typedef typename __base::difference_type         difference_type;
    typedef typename __base::pointer                 pointer;
    typedef typename __base::const_pointer           const_pointer;
    typedef __wrap_iter<pointer>                     iterator;
    typedef __wrap_iter<const_pointer>               const_iterator;
    typedef yjh_def::reverse_iterator<iterator>         reverse_iterator;
    typedef yjh_def::reverse_iterator<const_iterator>   const_reverse_iterator;

	static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");

	_LIBCPP_INLINE_VISIBILITY
	vector() noexcept(is_nothrow_default_constructible<allocator_type>::value)
	{}

	_LIBCPP_INLINE_VISIBILITY explicit vector(const allocator_type& __a)
		: __base(__a){}
	
	explicit vector(size_type __n);

	#if _LIBCPP_STD_VER > 11
	explicit vector(size_type __n, const allocator_type& __a);
	#endif

    vector(size_type __n, const value_type& __x);
    vector(size_type __n, const value_type& __x, const allocator_type& __a);

    template <class _InputIterator>
    vector(_InputIterator __first,
            typename enable_if
				<
					__is_input_iterator<_InputIterator>::value &&
                    !__is_forward_iterator<_InputIterator>::value &&
                    is_constructible
						<
                            value_type,
                            typename iterator_traits<_InputIterator>::reference
						>::value,
                    _InputIterator
				>::type __last);

    template <class _InputIterator>
    vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
            typename enable_if
						<
							__is_input_iterator<_InputIterator>::value &&
                        	!__is_forward_iterator<_InputIterator>::value &&
                        	is_constructible
								<
                            		value_type,
                            		typename iterator_traits<_InputIterator>::reference
								>::value
						>::type* = 0);

    template <class _ForwardIterator>
    vector(_ForwardIterator __first,
            typename enable_if
						<
							__is_forward_iterator<_ForwardIterator>::value &&
                        	is_constructible
								<
                            		value_type,
                            		typename iterator_traits<_ForwardIterator>::reference
								>::value,
                            _ForwardIterator
						>::type __last);

    template <class _ForwardIterator>
    vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
            typename enable_if
						<
							__is_forward_iterator<_ForwardIterator>::value &&
                    		is_constructible
								<
                        			value_type,
                        			typename iterator_traits<_ForwardIterator>::reference
								>::value
						>::type* = 0);
    _LIBCPP_INLINE_VISIBILITY
    ~vector()
    {
        __annotate_delete();
#if _LIBCPP_DEBUG_LEVEL >= 2
        __get_db()->__erase_c(this);
#endif
    }

    vector(const vector& __x);
    vector(const vector& __x, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(const vector& __x);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    vector(initializer_list<value_type> __il);

    _LIBCPP_INLINE_VISIBILITY
    vector(initializer_list<value_type> __il, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    vector(vector&& __x)
#if _LIBCPP_STD_VER > 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value);
#endif

    _LIBCPP_INLINE_VISIBILITY
    vector(vector&& __x, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(vector&& __x)
        _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value));

    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

#endif  // !_LIBCPP_CXX03_LANG

    template <class _InputIterator>
    typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_InputIterator>::reference>::value,
            void
        >::type
    assign(_InputIterator __first, _InputIterator __last);

    template <class _ForwardIterator>
    typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_ForwardIterator>::reference>::value,
            void
        >::type
    assign(_ForwardIterator __first, _ForwardIterator __last);

    void assign(size_type __n, const_reference __u);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}
#endif

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT
        {return this->__alloc();}

    _LIBCPP_INLINE_VISIBILITY iterator               begin() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY const_iterator         begin()   const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY iterator               end() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY const_iterator         end()     const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator       rbegin() _NOEXCEPT
        {return       reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin()  const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator       rend() _NOEXCEPT
        {return       reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend()    const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cbegin()  const _NOEXCEPT
        {return begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cend()    const _NOEXCEPT
        {return end();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return rbegin();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend()   const _NOEXCEPT
        {return rend();}

    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT
        {return static_cast<size_type>(this->__end_ - this->__begin_);}
    _LIBCPP_INLINE_VISIBILITY
    size_type capacity() const _NOEXCEPT
        {return __base::capacity();}
    _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT
        {return this->__begin_ == this->__end_;}
    size_type max_size() const _NOEXCEPT;
    void reserve(size_type __n);
    void shrink_to_fit() _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY reference       operator[](size_type __n) _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY const_reference operator[](size_type __n) const _NOEXCEPT;

    reference       at(size_type __n);
    const_reference at(size_type __n) const;

    _LIBCPP_INLINE_VISIBILITY reference       front() _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
        return *this->__begin_;
    }

    _LIBCPP_INLINE_VISIBILITY const_reference front() const _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
        return *this->__begin_;
    }

    _LIBCPP_INLINE_VISIBILITY reference       back() _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
        return *(this->__end_ - 1);
    }

    _LIBCPP_INLINE_VISIBILITY const_reference back()  const _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
        return *(this->__end_ - 1);
    }

    _LIBCPP_INLINE_VISIBILITY
    value_type*       data() _NOEXCEPT
        {return yjh_def::__to_raw_pointer(this->__begin_);}
    _LIBCPP_INLINE_VISIBILITY
    const value_type* data() const _NOEXCEPT
        {return yjh_def::__to_raw_pointer(this->__begin_);}

#ifdef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void __emplace_back(const value_type& __x) { push_back(__x); }
#else
    template <class _Arg>
    _LIBCPP_INLINE_VISIBILITY
    void __emplace_back(_Arg&& __arg) {
      emplace_back(yjh_def::forward<_Arg>(__arg));
    }
#endif

    _LIBCPP_INLINE_VISIBILITY void push_back(const_reference __x);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY void push_back(value_type&& __x);

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
#if _LIBCPP_STD_VER > 14
        reference emplace_back(_Args&&... __args);
#else
        void      emplace_back(_Args&&... __args);
#endif
#endif // !_LIBCPP_CXX03_LANG


    _LIBCPP_INLINE_VISIBILITY
    void pop_back();

    iterator insert(const_iterator __position, const_reference __x);

#ifndef _LIBCPP_CXX03_LANG
    iterator insert(const_iterator __position, value_type&& __x);
    template <class... _Args>
        iterator emplace(const_iterator __position, _Args&&... __args);
#endif  // !_LIBCPP_CXX03_LANG

    iterator insert(const_iterator __position, size_type __n, const_reference __x);
    template <class _InputIterator>
    typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_InputIterator>::reference>::value,
            iterator
        >::type
    insert(const_iterator __position, _InputIterator __first, _InputIterator __last);

    template <class _ForwardIterator>
    typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_ForwardIterator>::reference>::value,
            iterator
        >::type
    insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __position, initializer_list<value_type> __il)
        {return insert(__position, __il.begin(), __il.end());}
#endif

    _LIBCPP_INLINE_VISIBILITY iterator erase(const_iterator __position);
    iterator erase(const_iterator __first, const_iterator __last);

    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT
    {
        size_type __old_size = size();
        __base::clear(); 
        __annotate_shrink(__old_size);
        __invalidate_all_iterators();
    }

    void resize(size_type __sz);
    void resize(size_type __sz, const_reference __x);

    void swap(vector&)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value);
#endif

    bool __invariants() const;

#if _LIBCPP_DEBUG_LEVEL >= 2

    bool __dereferenceable(const const_iterator* __i) const;
    bool __decrementable(const const_iterator* __i) const;
    bool __addable(const const_iterator* __i, ptrdiff_t __n) const;
    bool __subscriptable(const const_iterator* __i, ptrdiff_t __n) const;

#endif  // _LIBCPP_DEBUG_LEVEL >= 2

private:
    _LIBCPP_INLINE_VISIBILITY void __invalidate_all_iterators();

    _LIBCPP_INLINE_VISIBILITY void __invalidate_iterators_past(pointer __new_last);

    void __vallocate(size_type __n);

    void __vdeallocate() _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY size_type __recommend(size_type __new_size) const;

    void __construct_at_end(size_type __n);

    _LIBCPP_INLINE_VISIBILITY
    void __construct_at_end(size_type __n, const_reference __x);

    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            void
        >::type
    __construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n);

    void __append(size_type __n);

    void __append(size_type __n, const_reference __x);

    _LIBCPP_INLINE_VISIBILITY
    iterator       __make_iter(pointer __p) _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    const_iterator __make_iter(const_pointer __p) const _NOEXCEPT;

    void __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v);

    pointer __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p);

    void __move_range(pointer __from_s, pointer __from_e, pointer __to);

    void __move_assign(vector& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);

    void __move_assign(vector& __c, false_type)
        _NOEXCEPT_(__alloc_traits::is_always_equal::value);

    _LIBCPP_INLINE_VISIBILITY
    void __destruct_at_end(pointer __new_last) _NOEXCEPT
    {
        __invalidate_iterators_past(__new_last);
        size_type __old_size = size();
        __base::__destruct_at_end(__new_last);
        __annotate_shrink(__old_size);
    }

#ifndef _LIBCPP_CXX03_LANG
    template <class _Up>
    _LIBCPP_INLINE_VISIBILITY
    inline void __push_back_slow_path(_Up&& __x);

    template <class... _Args>
    _LIBCPP_INLINE_VISIBILITY
    inline void __emplace_back_slow_path(_Args&&... __args);
#else
    template <class _Up>
    _LIBCPP_INLINE_VISIBILITY
    inline void __push_back_slow_path(_Up& __x);
#endif

    // The following functions are no-ops outside of AddressSanitizer mode.
    // We call annotatations only for the default Allocator because other allocators
    // may not meet the AddressSanitizer alignment constraints.
    // See the documentation for __sanitizer_annotate_contiguous_container for more details.
#ifndef _LIBCPP_HAS_NO_ASAN
    void __annotate_contiguous_container(const void *__beg, const void *__end,
                                         const void *__old_mid,
                                         const void *__new_mid) const
    {

      if (__beg && is_same<allocator_type, __default_allocator_type>::value)
        __sanitizer_annotate_contiguous_container(__beg, __end, __old_mid, __new_mid);
    }
#else
    _LIBCPP_INLINE_VISIBILITY
    void __annotate_contiguous_container(const void*, const void*, const void*,
                                         const void*) const _NOEXCEPT {}
#endif
    _LIBCPP_INLINE_VISIBILITY
    void __annotate_new(size_type __current_size) const _NOEXCEPT {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + capacity(), data() + __current_size);
    }

    _LIBCPP_INLINE_VISIBILITY
    void __annotate_delete() const _NOEXCEPT {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + size(), data() + capacity());
    }

    _LIBCPP_INLINE_VISIBILITY
    void __annotate_increase(size_type __n) const _NOEXCEPT
    {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + size(), data() + size() + __n);
    }

    _LIBCPP_INLINE_VISIBILITY
    void __annotate_shrink(size_type __old_size) const _NOEXCEPT
    {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + __old_size, data() + size());    // 这个函数是空的，什么都没执行
    }

  struct _ConstructTransaction {
    explicit _ConstructTransaction(vector &__v, size_type __n)
      : __v_(__v),  __pos_(__v.__end_), __new_end_(__v.__end_ + __n) {
#ifndef _LIBCPP_HAS_NO_ASAN
      __v_.__annotate_increase(__n);
#endif
    }
    ~_ConstructTransaction() {
      __v_.__end_ = __pos_;
#ifndef _LIBCPP_HAS_NO_ASAN
      if (__pos_ != __new_end_) {
        __v_.__annotate_shrink(__new_end_ - __v_.__begin_);
      }
#endif
    }

    vector &__v_;
    pointer __pos_;
    const_pointer const __new_end_;

  private:
    _ConstructTransaction(_ConstructTransaction const&) = delete;
    _ConstructTransaction& operator=(_ConstructTransaction const&) = delete;
	};

  template <class ..._Args>
  _LIBCPP_INLINE_VISIBILITY
  void __construct_one_at_end(_Args&& ...__args) {
    _ConstructTransaction __tx(*this, 1);
    __alloc_traits::construct(this->__alloc(), yjh_def::__to_raw_pointer(__tx.__pos_),
        _VSTD::forward<_Args>(__args)...);
    ++__tx.__pos_;
    /**
     * __tx 在进行析构的时候，会自动的调整 vector 的 __end_ 
     */
    }
};

// 具体的函数实现
#ifndef _LIBCPP_HAS_NO_DEDUCTION_GUIDES
template<class _InputIterator,
         class _Alloc = typename std::allocator<typename iterator_traits<_InputIterator>::value_type>,
         class = typename enable_if<__is_allocator<_Alloc>::value, void>::type
         >
vector(_InputIterator, _InputIterator)
  -> vector<typename iterator_traits<_InputIterator>::value_type, _Alloc>;

template<class _InputIterator,
         class _Alloc,
         class = typename enable_if<__is_allocator<_Alloc>::value, void>::type
         >
vector(_InputIterator, _InputIterator, _Alloc)
  -> vector<typename iterator_traits<_InputIterator>::value_type, _Alloc>;
#endif

// constructor of vector
template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n)
{
    #if _LIBCPP_DEBUF_LEVEL >= 2
        __get_db()->insert_c(this);
    #endif
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n);
    }
}

#if _LIBCPP_STD_VER > 11
template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const allocator_type& __a)
    : __base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n);
    }
}
#endif


template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const value_type& __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const value_type& __x, const allocator_type& __a)
    : __base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::vector(_InputIterator __first,
       typename enable_if
                    <
                        __is_input_iterator  <_InputIterator>::value &&
                         !__is_forward_iterator<_InputIterator>::value &&
                        is_constructible
                            <
                                value_type,
                                typename iterator_traits<_InputIterator>::reference
                        >::value,
                        _InputIterator
                    >::type __last)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
       typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                         !__is_forward_iterator<_InputIterator>::value &&
                         is_constructible<
                            value_type,
                            typename iterator_traits<_InputIterator>::reference>::value>::type*)
    : __base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
vector<_Tp, _Allocator>::vector(_ForwardIterator __first,
                typename enable_if
                            <
                                __is_forward_iterator<_ForwardIterator>::value &&
                                is_constructible
                                    <
                                        value_type,
                                        typename iterator_traits<_ForwardIterator>::reference
                                    >::value,
                                _ForwardIterator
                            >::type __last)
{
    size_type __n = static_cast<size_type>(yjh_def::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last, __n);
    }
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
vector<_Tp, _Allocator>::vector(_ForwardIterator __first, 
                                _ForwardIterator __last, const allocator_type& __a,
                                typename enable_if
                                        <
                                            __is_forward_iterator<_ForwardIterator>::value &&
                                            is_constructible
                                                <
                                                    value_type,
                                                    typename iterator_traits<_ForwardIterator>::reference
                                                >::value
                                        >::type*)
    : __base(__a)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last, __n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(const vector& __x)
    : __base(__alloc_traits::select_on_container_copy_construction(__x.__alloc()))
{
    size_type __n = __x.size();
    if (__n > 0)
    {
        /**
         * 分配空间  + 构造数据
         */
        __vallocate(__n);
        __construct_at_end(__x.__begin_, __x.__end_, __n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(const vector& __x, const allocator_type& __a)
    : __base(__a)
{
    size_type __n = __x.size();
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__x.__begin_, __x.__end_, __n);
    }
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>::vector(vector&& __x)
#if _LIBCPP_STD_VER > 14
        _NOEXCEPT
#else
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value)
#endif
    : __base(yjh_def::move(__x.__alloc()))
{
    this->__begin_ = __x.__begin_;
    this->__end_ = __x.__end_;
    this->__end_cap() = __x.__end_cap();
    __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr; // 输入的 vector 的所有的向量
    // 都设置为 nullptr
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>::vector(vector&& __x, const allocator_type& __a)
    : __base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    /**
     * 这里这样做的原因是什么？
     * 注意这里的移动赋值是进行内存空间的之间转移，将原本属于 __x 的内存空间交给了当前的类
     * 进行管理，这些内存是由 __x.__alloc()　进行有创建的。 如果 __a != __x.__alloc() 的
     * 话，那么有可能 __a 无法控制 __x.__alloc() 创建的内存空间，就会出错，所以需要查看
     * 两种迭代器是否相同
     * 在迭代器相同的情况下，可以直接进行内存的转移，否则的话，就只能一个一个元素进行拷贝了
     */
    if (__a == __x.__alloc())
    {
        this->__begin_ = __x.__begin_;
        this->__end_ = __x.__end_;
        this->__end_cap() = __x.__end_cap();
        __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr;
    }
    else
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__x.begin()), _Ip(__x.end()));
    }
}

// at
template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::reference
vector<_Tp, _Allocator>::at(size_type __n)
{
    if (__n >= size())
        this->__throw_out_of_range();
    return this->__begin_[__n];     // 简单粗暴，直接采用指针取下标的形式
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_reference
vector<_Tp, _Allocator>::at(size_type __n) const
{
    if (__n >= size())
        this->__throw_out_of_range();
    return this->__begin_[__n];
}

// operator[]
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::reference
vector<_Tp, _Allocator>::operator[](size_type __n) noexcept
{
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::const_reference
vector<_Tp, _Allocator>::operator[](size_type __n) const noexcept
{
    return this->__begin_[__n];
}

// begin
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::begin() _NOEXCEPT
{
    return __make_iter(this->__begin_);
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::const_iterator
vector<_Tp, _Allocator>::begin() const _NOEXCEPT
{
    return __make_iter(this->__begin_);
}

// end()
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::end() _NOEXCEPT
{
    return __make_iter(this->__end_);
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::const_iterator
vector<_Tp, _Allocator>::end() const _NOEXCEPT
{
    return __make_iter(this->__end_);
}

// reserve
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::reserve(size_type __n)
{
    if (__n > capacity())
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
        __swap_out_circular_buffer(__v);
    }
}

// shrink_to_fit
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::shrink_to_fit() noexcept
{
    /**
     * 现在已有的内存空间中，并不是所有的空间都用于 存储元素，还有部分的内存空间空闲没有使用
     * 把这部分多余的空间全部释放出来
     */
    if (capacity() > size())
    {
        #ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
        #endif
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(size(), size(), __a);
            // 初始的 __split_buffer 的 __begin_ 和 __end_都指向了分配的内存空间的末尾
            __swap_out_circular_buffer(__v);
        #ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch(...)
        {}
        #endif
    }
}

// __make_iter
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::__make_iter(pointer __p) _NOEXCEPT
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    return iterator(this, __p);
#else
    return iterator(__p);   // iterator = __wrap_iter<pointer>
#endif
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
typename vector<_Tp, _Allocator>::const_iterator
vector<_Tp, _Allocator>::__make_iter(const_pointer __p) const _NOEXCEPT
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    return const_iterator(this, __p);
#else
    return const_iterator(__p);
#endif
}

// insert
template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, const_reference __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())   // 还有空闲的空间可以使用
    {
        if (__p == this->__end_)    // 插入的位置在所有元素的后面
        {
            __construct_one_at_end(__x);
        }
        else
        {
            __move_range(__p, this->__end_, __p + 1); // 将 __p 开始的所有的元素向后面移动一位
            const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
            if (__p <= __xr && __xr < this->__end_)   // __xr 的地址在 __p 到 __end_ 之间
            /**
             * 而在 __p 到 __end_ 之间的元素全部都向后面移动了一个单位，那么 __xr 现在指向的元素就不是
             * 你本想进行赋值的那个元素了，你想要插入的那个元素现在在 __xr 的后面一位上面，所以，你要把
             * __xr + 1
             */
                ++__xr;
            *__p = *__xr;
        }
    }   
    else    // 没有空闲的空间可以使用，需要重新开辟空间
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.push_back(__x);
        __p = __swap_out_circular_buffer(__v, __p); // 这里另一个 __swap_out_circular_buffer
    }
    return __make_iter(__p);
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, value_type&& __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())   // 尾部还有空闲的空间
    {
        if (__p == this->__end_)    // 插入的位置为尾部
            __construct_one_at_end(yjh_def::move(__x));
        else 
        {
            __move_range(__p, this->__end_, __p + 1);
            *__p = yjh_def::move(__x);
        }
    }
    else    // 空间已经不够了重新分配空间
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), 
                __p - this->__begin_, __a);
        __v.push_back(yjh_def::move(__x));
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);  //返回被插入对象位置的迭代器
}
#endif

// __move_range
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__move_range(pointer __from_s, pointer __from_e, pointer __to)
{
    pointer __old_last = this->__end_;
    difference_type __n = __old_last - __to;
    {
      pointer __i = __from_s + __n;
      _ConstructTransaction __tx(*this, __from_e - __i);
      for (; __i < __from_e; ++__i, ++__tx.__pos_) {
          __alloc_traits::construct(this->__alloc(),
                                    yjh_def::__to_raw_pointer(__tx.__pos_),
                                    yjh_def::move(*__i));
      }
    }
    yjh_def::move_backward(__from_s, __from_s + __n, __old_last);
}

// max_size
template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::size_type
vector<_Tp, _Allocator>::max_size() const noexcept
{
    return yjh_def::min<size_type>(__alloc_traits::max_size(this->__alloc()),
                numeric_limits<difference_type>::max());
}

// assign
template <class _Tp, class _Allocator>
template <class _InputIterator>
typename enable_if
    <
        __is_input_iterator  <_InputIterator>::value &&
        !__is_forward_iterator<_InputIterator>::value &&
        is_constructible
            <
                _Tp,
                typename iterator_traits<_InputIterator>::reference
            >::value,
    void
    >::type
vector<_Tp, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
{
    clear();
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if
    <
        __is_forward_iterator<_ForwardIterator>::value &&
        is_constructible
            <
                _Tp,
                typename iterator_traits<_ForwardIterator>::reference
            >::value,
        void
    >::type
vector<_Tp, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __new_size = static_cast<size_type>(yjh_def::distance(__first, __last));
    if (__new_size <= capacity())
    {
        _ForwardIterator __mid = __last;
        bool __growing = false;     // 拷贝进来的数据比vector 现存的数据量要少
        if (__new_size > size())
        {
            __growing = true;   // 拷贝进来的数据量比 vector 现存的数据量要大
            __mid =  __first;   // 先拷贝前 size() 个，后面剩下的
            yjh_def::advance(__mid, size());
        }
        pointer __m = yjh_def::copy(__first, __mid, this->__begin_);
        if (__growing)
            __construct_at_end(__mid, __last, __new_size - size());
        else
            this->__destruct_at_end(__m);   // 赋值完成之后，vector 的末尾还有一段以前的老数据，这些数据需要析构掉
    }
    else    // 空间不够，重新分配空间，再赋值吧
    {
        __vdeallocate();
        __vallocate(__recommend(__new_size));
        __construct_at_end(__first, __last, __new_size);
    }
    __invalidate_all_iterators();
}


template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::assign(size_type __n, const_reference __u)
{
    if (__n <= capacity())
    {
        size_type __s = size();
        yjh_def::fill_n(this->__begin_, yjh_def::min(__n, __s), __u);
        if (__n > __s)
            __construct_at_end(__n - __s, __u);
        else
            this->__destruct_at_end(this->__begin_ + __n);
    }
    else
    {
        __vdeallocate();
        __vallocate(__recommend(static_cast<size_type>(__n)));
        __construct_at_end(__n, __u);
    }
    __invalidate_all_iterators();
}


template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>::vector(initializer_list<value_type> __il)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__il.size() > 0)
    {
        __vallocate(__il.size());
        __construct_at_end(__il.begin(), __il.end(), __il.size());
    }
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>::vector(initializer_list<value_type> __il, const allocator_type& __a)
    : __base(__a)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__insert_c(this);
#endif
    if (__il.size() > 0)
    {
        __vallocate(__il.size());
        __construct_at_end(__il.begin(), __il.end(), __il.size());
    }
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>&
vector<_Tp, _Allocator>::operator=(vector&& __x)
    _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value))
{
    __move_assign(__x, integral_constant<bool,
          __alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>&
vector<_Tp, _Allocator>::operator=(const vector& __x)
{
    if (this != &__x)
    {
        __base::__copy_assign_alloc(__x);
        assign(__x.__begin_, __x.__end_);
    }
    return *this;
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__move_assign(vector& __c, false_type)
    _NOEXCEPT_(__alloc_traits::is_always_equal::value)
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
vector<_Tp, _Allocator>::__move_assign(vector& __c, true_type)
    _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
{
    __vdeallocate();
    __base::__move_assign_alloc(__c); // this can throw
    this->__begin_ = __c.__begin_;
    this->__end_ = __c.__end_;
    this->__end_cap() = __c.__end_cap();
    __c.__begin_ = __c.__end_ = __c.__end_cap() = nullptr;
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->swap(this, &__c);
#endif
}

#endif  // !_LIBCPP_CXX03_LANG

template<class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__vallocate(size_type __n)
{
    if (__n > max_size())
        this->__throw_length_error();
    this->__begin_ = this->__end_ = __alloc_traits.allocate(this->__alloc(), __n);
    this->__end_cap() = this->__begin_ + __n;
    __annotate_new(0);
}

// __construct_at_end
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__construct_at_end(size_type __n)
{
    _ConstructTransaction __tx(*this, __n);
    for (; __tx.__pos_ != __tx.__new_end_; ++__tx.__pos_)
    {
        __alloc_traits.construct(this->__alloc(), yjh_def::__to_raw_pointer(__tx.__pos_));
    }
}

template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
{
    _ConstructTransaction __tx(*this, __n);
    for (; __tx.__pos_ != __tx.__new_end_; ++__tx.__pos_) {
        __alloc_traits::construct(this->__alloc(), yjh_def::__to_raw_pointer(__tx.__pos_), __x);
    }
}


template <class _Tp, class _Allocator>
template <class ..._Args>
#if _LIBCPP_STD_VER > 14
typename vector<_Tp, _Allocator>::reference
#else 
void
#endif
vector<_Tp, _Allocator>::emplace_back(_Args&&... _args)
{
    /**
     * 当前的存储数据的区域的尾部，还有开辟了但是还没有用的内存空间
     */
    if (this->__end_ < this->__end_cap())
    {
        __construct_one_at_end(yjh_def::forward<_Args>(__args)...);
    }
    else 
        __emplace_back_slow_path(yjh_def::forward<_Args>(__args)...);
    
    #if _LIBCPP_STD_VER > 14
        return this->back();
    #endif
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
template <class ... _Args>
void 
vector<_Tp, _Allocator>::__emplace_back_slow_path(_Args&& ... __args)
{
    /**
     * vector 插入新的元素，需要扩大空间。采用的策略如下
     * 使用 __split_buffer 建立一个新的内存区间，在这个区间的最后面添加这个元素
     * 将现有的vector 的所有的元素拷贝到新的内存空间的前面
     * 将 __split_buffer 的内存空间和当前的 vector 的空间进行交换
     * 完成插入的过程
     */
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
    //  // (__cap, __start_pos_, __alloc_)
    __alloc_traits::construct(  __a, 
                                yjh_def::__to_raw_pointer(__v.__end_), 
                                yjh_def::forward<_Args>(__args)...);
    __v.__end_ ++;
    __swap_out_circular_buffer(__v);    // 将 __split_buffer 的空间和当前的 vector 的空间进行交换
}

#endif

template <class _Tp, class _Allocator>
inline vector<_Tp, _Allocator>::size_type
/**
 * 为 vector 分配内存的大小提供一些建议
 */
vector<_Tp, _Allocator>::__recommend(size_type __new_size) const
{
    const size_type __ms = max_size();
    if (__new_size > __ms)
        this->_throw_length_error();
    const size_type __cap = capacity(); // 返回现有的可用的内存空间的大小
    if (__cap >= __ms / 2)  // 如果现有的空间大小超过了上限的一般，直接返回上限值
        return __ms;
    return yjh_def::max<size_type>(2 * __cap, __new_size);
}

// __swap_out_circular_buffer
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v)
{
    __annotate_delete();
    __alloc_traits::__construct_backward_with_exception_guarantees(
        this->__alloc(), this->__begin_, this->__end_, __v.__begin_); 
        // 注意， __v.__begin_ 的指针是以引用的方式进行传递的
        /**
         * 将 this->__begin_ 到 this->__end_ 为止的所有的元素，拷贝到 __v.__begin_ 开始的内存空间中
         */
    yjh_def::swap(this->__begin_, __v.__begin_);
    yjh_def::swap(this->__end_, __v.__end_);
    yjh_def::swap(this->__end_cap(), __v.__end_cap());
    __v.__first_ = __v.__begin_;
    __annotate_new(size());
    __invalidate_all_iterators();       // 只用于测试
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::pointer
vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p)
{
    /**
     * -------------------------------------------------
     * __v| 空的  |  有数据       |  空的
     * ----------|--------------|--------------------------
     *         __begin_        __end_
     */    
    __annotate_delete();
    pointer __r = __v.__begin_;
    /**
     * 把 __p 前面的元素按照顺序复制到 __v 的前面
     */
    __alloc_traits::__construct_backward_with_exception_guarantees(
        this->__alloc(), this->__begin_, __p, __v.__begin_);
    /**
     * 把 __p 后面的元素（包括自己）拷贝到 __v 的后面
     */
    __alloc_traits::__construct_forward_with_exception_guarantees(
        this->__alloc(), __p, this->__end_, __v.__end_);
    yjh_def::swap(this->__begin_, __v.__begin_);
    yjh_def::swap(this->__end_, __v.__end_);
    yjh_def::swap(this->__end_cap(), __v.__end_cap());
    __v.__first_ = __v.__begin_;    // 这一步干了什么？
    __annotate_new(size());
    __invalidate_all_iterators();
    return __r;
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
vector<_Tp, _Allocator>::__invalidate_all_iterators()
{
    // 保留
}

// push_back
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
vector<_Tp, _Allocator>::push_back(const_reference __x)
{
    if (this->__end_ != this->__end_cap())
        __construct_one_at_end(__x);
    else 
        __push_back_slow_path(__x);
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
vector<_Tp, _Allocator>::push_back(value_type&& __x)
{
    if (this->__end_ < this->__end_cap())
    {
        __construct_one_at_end(yjh_def::move(__x));
    }
    else
        __push_back_slow_path(yjh_def::move(__x));
}
#endif

template <class _Tp, class _Allocator>
template <class... _Args>
typename vector<_Tp, _Allocator>::iterator
/**
 * 在特定的位置构造生成
 */
vector<_Tp, _Allocator>::emplace(const_iterator __position, _Args&&... __args)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())   // 末尾有空闲的位置可以插入
    {
        if (__p == this->__end_)    // 如果插入的位置是 vector 的末尾
        {
            __construct_one_at_end(yjh_def::forward<_Args>(__args)...);
        }
        else
        {
            __temp_value<value_type, _Allocator> __tmp(this->__alloc(), _VSTD::forward<_Args>(__args)...);
            /**
             * __temp_value 中存储了一个内存对齐的内存空间用于临时存储 _Tp 类型的数据
             */
            __move_range(__p, this->__end_, __p + 1);   // 让出空间，将 __p 开始的所有的元素向后面移动一个单位
            *__p = yjh_def::move(__tmp.get());
        }
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        // 注意 __split_buffer::__begin_ 开始的位置
        __v.emplace_back(yjh_def::forward<_Args>(__args)...);
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __position)
{
    _LIBCPP_ASSERT(__position != end(),
        "vector::erase(iterator) called with a non-dereferenceable iterator");
    difference_type __ps = __position - cbegin();
    pointer __p = this->__begin_ + __ps;
    /**
     * 将 __p 后面的所有的元素往右边移动一位，挤掉了 __p 中的原有的元素，相当于删除了，
     * 最后面位置的元素因为向前面移动了移位，所以原位置的需要析构掉[空间并不需要回收]
     */
    this->__destruct_at_end(yjh_def::move(__p + 1, this->__end_, __p));
    this->__invalidate_iterators_past(__p-1);
    iterator __r = __make_iter(__p);
    return __r;
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
    _LIBCPP_ASSERT(__first <= __last, "vector::erase(first, last) called with invalid range");  
    pointer __p = this->__begin_ + (__first - begin());
    if (__first != __last)
    {
        this->__destruct_at_end(yjh_def::move(__p + (__last - __first)), this->__end_, __p);
        /**
         * 非常的巧妙
         * 一个步骤就完成了复杂的过程
         */
        this->__invalidate_iterators_past(_p - 1);
    }  
    iterator __r = __make_iter(__p);
    return __r;
}

// resize
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::resize(size_type __sz)
{
    size_type __cs = size();
    if (__cs < __sz)
        this->__append(__sz - __cs);
    else if (__cs > __sz)
        this->__destruct_at_end(this->__begin_ + __sz);
}

// swap
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::swap(vector& __x)
#if _LIBCPP_STD_VER >= 14
    _NOEXCEPT
#else
    _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                __is_nothrow_swappable<allocator_type>::value)
#endif
{
    _LIBCPP_ASSERT(__alloc_traits::propagate_on_container_swap::value ||
                   this->__alloc() == __x.__alloc(),
                   "vector::swap: Either propagate_on_container_swap must be true"
                   " or the allocators must compare equal");
    yjh_def::swap(this->__begin_, __x.__begin_);
    yjh_def::swap(this->__end_, __x.__end_);
    yjh_def::swap(this->__end_cap(), __x.__end_cap());
    __swap_allocator(this->__alloc(), __x.__alloc(),
        integral_constant<bool,__alloc_traits::propagate_on_container_swap::value>());
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->swap(this, &__x);
#endif  // _LIBCPP_DEBUG_LEVEL >= 2
}

// __append
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__append(size_type __n)
{
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n);  // 当然都采用默认构造函数
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n),
                        size(), __a);
        __v.__construct_at_end(__n);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__append(size_type __n, const_reference __x)
{
    /**
     * 使用默认值进行构造
     */
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n, __x);
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
        __v.__construct_at_end(__n, __x);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
inline 
void
vector<_Tp, _Allocator>::__invalidate_iterators_past(pointer __new_last)
{
    ((void)__new_last);         // ?????
}

template <class _Tp, class _Allocator>
template <class _Up>
void
#ifndef _LIBCPP_CXX03_LANG
vector<_Tp, _Allocator>::__push_back_slow_path(_Up&& __x)
#else
vector<_Tp, _Allocator>::__push_back_slow_path(_Up& __x)
#endif
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
    __alloc_traits::construct(__a, yjh_def::__to_raw_pointer(__v.__end_),
                    yjh_def::forward<_Up>(__x));
    __v.__end_ ++;
    __swap_out_circular_buffer(__v);
}

// __invariants
/**
 * 检测当前的 vector 是否存在一些不合法的情况，内部数据结构上的错误
 */
template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__invariants() const
{
    if (this->__begin_ == nullptr)
    {
        if (this->__end_ != nullptr || this->__end_cap() != nullptr)
            return false;
    }
    else
    {
        if (this->__begin_ > this->__end_)
            return false;
        if (this->__begin_ == this->__end_cap())
            return false;
        if (this->__end_ > this->__end_cap())
            return false;
    }
    return true;
}



// vector<bool>


}

#endif
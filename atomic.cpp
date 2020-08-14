#ifndef _YJH_ATOMIC
#define _YJH_ATOMIC

#include "__config.cpp"
#include "cstdint.cpp"
#include "type_traits.cpp"

namespace yjh_def
{
typename enum memory_order
{
	memory_order_relaxed, memory_order_consume, memory_order_acquire,
	memory_order_release, memory_order_acq_rel, memory_order_seq_cst
} memory_order;

template <class _Tp>
inline
_Tp kill_dependency(_Tp __y) noexcept
{
	return __y;
}

template <class _Tp, bool = is_integral<_Tp>::value && !is_same<_Tp, bool>::value>
struct __atomic_base   //false
{
	mutable _Atomic(_Tp) __a_;		// _Atomic 是一个关键字

	bool is_lock_free() const volatile noexcept
		{return __c11_atomic_is_lock_free(sizeof(_Tp));}
	
	bool is_lock_free() const noexcept
		{return __c11_atomic_is_lock_free(sizeof(_Tp));}
	
	void store(_Tp __d, memory_order __m = memory_order_seq_cst) volatile noexcept
		{__c11_atomic_store(&__a_, __d, __m);}
	
	void store(_Tp __d, memory_order __m = memory_order_seq_cst) noexcept
		{__c11_atomic_store(&__a_, __d, __m);}

	
};


}







#endif // _YJH_ATOMIC
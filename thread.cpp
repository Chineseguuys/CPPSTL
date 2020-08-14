#ifndef _LIBCPP_THREAD
#define _LIBCPP_THREAD

#include "__config.cpp"
#include "iosfwd.cpp"
#include "__functional_base.cpp"
#include "type_traits.cpp"
//#include "cstddef.cpp"
//#include "functional"
#include "memory.cpp"
#ifndef _LIBCPP_CXX03_LANG
#include "tuple.cpp"
#endif

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include "__undef_macros.cpp"

namespace yjh_def
{
template <class _Tp> class __thread_specific_ptr;
class _LIBCPP_TYPE_VIS __thread_struct;
class _LIBCPP_HIDDEN __thread_struct_imp;
class __assoc_sub_state;

_LIBCPP_FUNC_VIS __thread_specific_ptr<__thread_struct>& __thread_local_data();

class _LIBCPP_TYPE_VIS __thread_struct
{
	__thread_struct_imp* __p_;

	__thread_struct(const __thread_struct&);
	__thread_struct& operator=(const __thread_struct&);
public:
	__thread_struct();
	~__thread_struct();

	void notify_all_at_thread_exit(condition_variable*, mutex*);
	void __make_ready_at_thread_exit(__assoc_sub_state*);
};


};

#endif //__LIBCPP_THREAD
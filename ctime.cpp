#ifndef _LIBCPP_CTIME
#define _LIBCPP_CTIME


#include "__config.cpp"
#include <time.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

namespace yjh_def
{
using ::clock_t;
using ::size_t;
using ::time_t;
using ::tm;
#if _LIBCPP_STD_VER > 14 && defined(_LIBCPP_HAS_C11_FEATURES)
using ::timespec;
#endif
using ::clock;
using ::difftime;
using ::mktime;
using ::time;
#ifndef _LIBCPP_HAS_NO_THREAD_UNSAFE_C_FUNCTIONS
using ::asctime;
using ::ctime;
using ::gmtime;
using ::localtime;
#endif
using ::strftime;
#if _LIBCPP_STD_VER > 14 && defined(_LIBCPP_HAS_TIMESPEC_GET)
using ::timespec_get;
#endif
}




#endif //_LIBCPP_CTIME







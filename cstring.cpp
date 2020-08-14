#ifndef _YJH_CSTRING
#define _YJH_CSTRING

#include "__config.cpp"
#include <string.h>
/**
 * 直接将 C 语言标准库中的 string.h 中的部分函数拿来使用
 */
namespace yjh_def
{
using ::size_t;
using ::memcpy;
using ::memmove;
using ::strcpy;
using ::strncpy;
using ::strcat;
using ::strncat;
using ::memcmp;
using ::strcmp;
using ::strncmp;
using ::strcoll;
using ::strxfrm;

using ::memchr;

using ::strchr;

using ::strcspn;

using ::strpbrk;

using ::strrchr;

using ::strspn;

using ::strstr;

using ::strtok;
using ::memset;
using ::strerror;
using ::strlen;

}













#endif // _YJH_CSTRING
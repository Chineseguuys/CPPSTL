#ifndef _YJH_IOSFWD
#define _YJH_IOSFWD

#include "__config.cpp"
#include <wchar.h>
/**
 * 这里面定义了一系列的类
 * 没有具体的实现
 */
namespace yjh_def
{
class   ios_base;
template <class _CharT> struct char_traits;
template <class _Tp>    class allocator;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ios;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_streambuf;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_istream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ostream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_iostream;

template <class _CharT, class _Traits = char_traits<_CharT>,
            class _Allocator = allocator<_CharT> >
class basic_stringbuf;

template <class _CharT, class _Traits = char_traits<_CharT>,
            class _Allocator = allocator<_CharT> >
class basic_istringstream;

template <class _CharT, class _Traits = char_traits<_CharT>,
            class _Allocator = allocator<_CharT> >
class basic_ostringstream;

template <class _CharT, class _Traits = char_traits<_CharT>,
            class _Allocator = allocator<_CharT> >
class basic_stringstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_filebuf;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ifstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ofstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_fstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class istreambuf_iterator;

template <class _CharT, class _Traits = char_traits<_CharT> >
class ostreambuf_iterator;

typedef basic_ios<char>                     ios;
typedef basic_ios<wchar_t>                  wios;

typedef basic_streambuf<char>               streambuf;
typedef basic_istream<char>                 istream;
typedef basic_ostream<char>                 ostream;

typedef basic_stringbuf<char>               stringbuf;
typedef basic_istringstream<char>           istringstream;
typedef basic_ostringstream<char>           ostringstream;
typedef basic_stringstream<char>            stringstream;

typedef basic_filebuf<char>          filebuf;
typedef basic_ifstream<char>         ifstream;
typedef basic_ofstream<char>         ofstream;
typedef basic_fstream<char>          fstream;

typedef basic_streambuf<wchar_t>     wstreambuf;
typedef basic_istream<wchar_t>       wistream;
typedef basic_ostream<wchar_t>       wostream;
typedef basic_iostream<wchar_t>      wiostream;

typedef basic_stringbuf<wchar_t>     wstringbuf;
typedef basic_istringstream<wchar_t> wistringstream;
typedef basic_ostringstream<wchar_t> wostringstream;
typedef basic_stringstream<wchar_t>  wstringstream;

typedef basic_filebuf<wchar_t>       wfilebuf;
typedef basic_ifstream<wchar_t>      wifstream;
typedef basic_ofstream<wchar_t>      wofstream;
typedef basic_fstream<wchar_t>       wfstream;

/**   mbstate_t 的定义，目前不知道这个数据结构有什么类型
typedef struct _Mbstatet
{ // state of a multibyte translation
    unsigned long _Wchar;
    unsigned short _Byte, _State;
} _Mbstatet;

typedef _Mbstatet mbstate_t;
 */
template <class _State>             class fpos;
typedef fpos<mbstate_t>     streampos;
typedef fpos<mbstate_t>     wstreampos;

typedef long long streamoff;            // for char_traits in <string>

template <  class _CharT,
            class _Traits = char_traits<_CharT>,
            class _Allocator = allocator<_CharT> >
class basic_string;
typedef basic_string<char, char_traits<char>, allocator<char> > string;
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

// Include other forward declarations here
template <class _Tp, class _Alloc = allocator<_Tp>>
class _LIBCPP_TEMPLATE_VIS vector;

}



#endif
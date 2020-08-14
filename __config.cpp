
#ifndef _LIBCPP_CONFIG
#define _LIBCPP_CONFIG

// #define _NOEXCEPT noexcept

#if defined(_MSC_VER) && !defined(__clang__)
#  if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#    define _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER
#  endif
#endif

#ifndef _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER
#pragma GCC system_header
#endif

#ifdef __cplusplus

#ifdef __GNUC__
#  define _GNUC_VER (__GNUC__ * 100 + __GNUC_MINOR__)
// The _GNUC_VER_NEW macro better represents the new GCC versioning scheme
// introduced in GCC 5.0.
#  define _GNUC_VER_NEW (_GNUC_VER * 10 + __GNUC_PATCHLEVEL__)
#else
#  define _GNUC_VER 0
#  define _GNUC_VER_NEW 0
#endif

#define _LIBCPP_VERSION 10000

#ifndef _LIBCPP_ABI_VERSION
#  define _LIBCPP_ABI_VERSION 1
#endif

#ifndef __STDC_HOSTED__
#  define _LIBCPP_FREESTANDING
#endif

#ifndef _LIBCPP_STD_VER
#  if  __cplusplus <= 201103L
#    define _LIBCPP_STD_VER 11
#  elif __cplusplus <= 201402L
#    define _LIBCPP_STD_VER 14
#  elif __cplusplus <= 201703L
#    define _LIBCPP_STD_VER 17
#  else
#    define _LIBCPP_STD_VER 18  // current year, or date of c++2a ratification
#  endif
#endif  // _LIBCPP_STD_VER

#if defined(__ELF__)
#  define _LIBCPP_OBJECT_FORMAT_ELF   1
#elif defined(__MACH__)
#  define _LIBCPP_OBJECT_FORMAT_MACHO 1
#elif defined(_WIN32)
#  define _LIBCPP_OBJECT_FORMAT_COFF  1
#elif defined(__wasm__)
#  define _LIBCPP_OBJECT_FORMAT_WASM  1
#else
#  error Unknown object file format
#endif

#if defined(_LIBCPP_ABI_UNSTABLE) || _LIBCPP_ABI_VERSION >= 2
// Change short string representation so that string data starts at offset 0,
// improving its alignment in some cases.
#  define _LIBCPP_ABI_ALTERNATE_STRING_LAYOUT
// Fix deque iterator type in order to support incomplete types.
#  define _LIBCPP_ABI_INCOMPLETE_TYPES_IN_DEQUE
// Fix undefined behavior in how std::list stores its linked nodes.
#  define _LIBCPP_ABI_LIST_REMOVE_NODE_POINTER_UB
// Fix undefined behavior in  how __tree stores its end and parent nodes.
#  define _LIBCPP_ABI_TREE_REMOVE_NODE_POINTER_UB
// Fix undefined behavior in how __hash_table stores its pointer types.
#  define _LIBCPP_ABI_FIX_UNORDERED_NODE_POINTER_UB
#  define _LIBCPP_ABI_FORWARD_LIST_REMOVE_NODE_POINTER_UB
#  define _LIBCPP_ABI_FIX_UNORDERED_CONTAINER_SIZE_TYPE
// Don't use a nullptr_t simulation type in C++03 instead using C++11 nullptr
// provided under the alternate keyword __nullptr, which changes the mangling
// of nullptr_t. This option is ABI incompatible with GCC in C++03 mode.
#  define _LIBCPP_ABI_ALWAYS_USE_CXX11_NULLPTR
// Define the `pointer_safety` enum as a C++11 strongly typed enumeration
// instead of as a class simulating an enum. If this option is enabled
// `pointer_safety` and `get_pointer_safety()` will no longer be available
// in C++03.
#  define _LIBCPP_ABI_POINTER_SAFETY_ENUM_TYPE
// Define a key function for `bad_function_call` in the library, to centralize
// its vtable and typeinfo to libc++ rather than having all other libraries
// using that class define their own copies.
#  define _LIBCPP_ABI_BAD_FUNCTION_CALL_KEY_FUNCTION
// Enable optimized version of __do_get_(un)signed which avoids redundant copies.
#  define _LIBCPP_ABI_OPTIMIZED_LOCALE_NUM_GET
// Use the smallest possible integer type to represent the index of the variant.
// Previously libc++ used "unsigned int" exclusively.
#  define _LIBCPP_ABI_VARIANT_INDEX_TYPE_OPTIMIZATION
// Unstable attempt to provide a more optimized std::function
#  define _LIBCPP_ABI_OPTIMIZED_FUNCTION
// All the regex constants must be distinct and nonzero.
#  define _LIBCPP_ABI_REGEX_CONSTANTS_NONZERO
#elif _LIBCPP_ABI_VERSION == 1
#  if !defined(_LIBCPP_OBJECT_FORMAT_COFF)
// Enable compiling copies of now inline methods into the dylib to support
// applications compiled against older libraries. This is unnecessary with
// COFF dllexport semantics, since dllexport forces a non-inline definition
// of inline functions to be emitted anyway. Our own non-inline copy would
// conflict with the dllexport-emitted copy, so we disable it.
#    define _LIBCPP_DEPRECATED_ABI_LEGACY_LIBRARY_DEFINITIONS_FOR_INLINE_FUNCTIONS
#  endif
// Feature macros for disabling pre ABI v1 features. All of these options
// are deprecated.
#  if defined(__FreeBSD__)
#    define _LIBCPP_DEPRECATED_ABI_DISABLE_PAIR_TRIVIAL_COPY_CTOR
#  endif
#endif

#ifdef _LIBCPP_TRIVIAL_PAIR_COPY_CTOR
#error "_LIBCPP_TRIVIAL_PAIR_COPY_CTOR" is no longer supported. \
       use _LIBCPP_DEPRECATED_ABI_DISABLE_PAIR_TRIVIAL_COPY_CTOR instead
#endif

#define _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_X##_LIBCPP_Y
#define _LIBCPP_CONCAT(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y)

#ifndef _LIBCPP_ABI_NAMESPACE
# define _LIBCPP_ABI_NAMESPACE _LIBCPP_CONCAT(__,_LIBCPP_ABI_VERSION)
#endif

#if __cplusplus < 201103L
#define _LIBCPP_CXX03_LANG
#endif

#ifndef __has_attribute
#define __has_attribute(__x) 0
#endif

#ifndef __has_builtin
#define __has_builtin(__x) 0
#endif

#ifndef __has_extension
#define __has_extension(__x) 0
#endif

#ifndef __has_feature
#define __has_feature(__x) 0
#endif

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(__x) 0
#endif

// '__is_identifier' returns '0' if '__x' is a reserved identifier provided by
// the compiler and '1' otherwise.
#ifndef __is_identifier
#define __is_identifier(__x) 1
#endif

#ifndef __has_declspec_attribute
#define __has_declspec_attribute(__x) 0
#endif

#define __has_keyword(__x) !(__is_identifier(__x))

#ifndef __has_include
#define __has_include(...) 0
#endif

#if defined(__clang__)
#  define _LIBCPP_COMPILER_CLANG
#  ifndef __apple_build_version__
#    define _LIBCPP_CLANG_VER (__clang_major__ * 100 + __clang_minor__)
#  endif
#elif defined(__GNUC__)
#  define _LIBCPP_COMPILER_GCC
#elif defined(_MSC_VER)
#  define _LIBCPP_COMPILER_MSVC
#elif defined(__IBMCPP__)
#  define _LIBCPP_COMPILER_IBM
#endif

#if defined(_LIBCPP_COMPILER_GCC) && __cplusplus < 201103L
#error "libc++ does not support using GCC with C++03. Please enable C++11"
#endif

// FIXME: ABI detection should be done via compiler builtin macros. This
// is just a placeholder until Clang implements such macros. For now assume
// that Windows compilers pretending to be MSVC++ target the Microsoft ABI,
// and allow the user to explicitly specify the ABI to handle cases where this
// heuristic falls short.
#if defined(_LIBCPP_ABI_FORCE_ITANIUM) && defined(_LIBCPP_ABI_FORCE_MICROSOFT)
#  error "Only one of _LIBCPP_ABI_FORCE_ITANIUM and _LIBCPP_ABI_FORCE_MICROSOFT can be defined"
#elif defined(_LIBCPP_ABI_FORCE_ITANIUM)
#  define _LIBCPP_ABI_ITANIUM
#elif defined(_LIBCPP_ABI_FORCE_MICROSOFT)
#  define _LIBCPP_ABI_MICROSOFT
#else
#  if defined(_WIN32) && defined(_MSC_VER)
#    define _LIBCPP_ABI_MICROSOFT
#  else
#    define _LIBCPP_ABI_ITANIUM
#  endif
#endif

#if defined(_LIBCPP_ABI_MICROSOFT) && !defined(_LIBCPP_NO_VCRUNTIME)
# define _LIBCPP_ABI_VCRUNTIME
#endif

// Need to detect which libc we're using if we're on Linux.
#if defined(__linux__)
#  include <features.h>
#  if defined(__GLIBC_PREREQ)
#    define _LIBCPP_GLIBC_PREREQ(a, b) __GLIBC_PREREQ(a, b)
#  else
#    define _LIBCPP_GLIBC_PREREQ(a, b) 0
#  endif // defined(__GLIBC_PREREQ)
#endif // defined(__linux__)

#ifdef __LITTLE_ENDIAN__
#  if __LITTLE_ENDIAN__
#    define _LIBCPP_LITTLE_ENDIAN
#  endif  // __LITTLE_ENDIAN__
#endif  // __LITTLE_ENDIAN__

#ifdef __BIG_ENDIAN__
#  if __BIG_ENDIAN__
#    define _LIBCPP_BIG_ENDIAN
#  endif  // __BIG_ENDIAN__
#endif  // __BIG_ENDIAN__

#ifdef __BYTE_ORDER__
#  if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define _LIBCPP_LITTLE_ENDIAN
#  elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define _LIBCPP_BIG_ENDIAN
#  endif // __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#endif // __BYTE_ORDER__

#ifdef __FreeBSD__
#  include <sys/endian.h>
#  include <osreldate.h>
#  if _BYTE_ORDER == _LITTLE_ENDIAN
#    define _LIBCPP_LITTLE_ENDIAN
#  else  // _BYTE_ORDER == _LITTLE_ENDIAN
#    define _LIBCPP_BIG_ENDIAN
#  endif  // _BYTE_ORDER == _LITTLE_ENDIAN
#  ifndef __LONG_LONG_SUPPORTED
#    define _LIBCPP_HAS_NO_LONG_LONG
#  endif  // __LONG_LONG_SUPPORTED
#endif  // __FreeBSD__

#ifdef __NetBSD__
#  include <sys/endian.h>
#  if _BYTE_ORDER == _LITTLE_ENDIAN
#    define _LIBCPP_LITTLE_ENDIAN
#  else  // _BYTE_ORDER == _LITTLE_ENDIAN
#    define _LIBCPP_BIG_ENDIAN
#  endif  // _BYTE_ORDER == _LITTLE_ENDIAN
#  define _LIBCPP_HAS_QUICK_EXIT
#endif  // __NetBSD__

#if defined(_WIN32)
#  define _LIBCPP_WIN32API
#  define _LIBCPP_LITTLE_ENDIAN
#  define _LIBCPP_SHORT_WCHAR   1
// Both MinGW and native MSVC provide a "MSVC"-like environment
#  define _LIBCPP_MSVCRT_LIKE
// If mingw not explicitly detected, assume using MS C runtime only if
// a MS compatibility version is specified.
#  if defined(_MSC_VER) && !defined(__MINGW32__)
#    define _LIBCPP_MSVCRT // Using Microsoft's C Runtime library
#  endif
#  if (defined(_M_AMD64) || defined(__x86_64__)) || (defined(_M_ARM) || defined(__arm__))
#    define _LIBCPP_HAS_BITSCAN64
#  endif
#  define _LIBCPP_HAS_OPEN_WITH_WCHAR
#  if defined(_LIBCPP_MSVCRT)
#    define _LIBCPP_HAS_QUICK_EXIT
#  endif

// Some CRT APIs are unavailable to store apps
#  if defined(WINAPI_FAMILY)
#    include <winapifamily.h>
#    if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) &&                  \
        (!defined(WINAPI_PARTITION_SYSTEM) ||                                  \
         !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_SYSTEM))
#      define _LIBCPP_WINDOWS_STORE_APP
#    endif
#  endif
#endif // defined(_WIN32)

#ifdef __sun__
#  include <sys/isa_defs.h>
#  ifdef _LITTLE_ENDIAN
#    define _LIBCPP_LITTLE_ENDIAN
#  else
#    define _LIBCPP_BIG_ENDIAN
#  endif
#endif // __sun__

#if defined(__CloudABI__)
   // Certain architectures provide arc4random(). Prefer using
   // arc4random() over /dev/{u,}random to make it possible to obtain
   // random data even when using sandboxing mechanisms such as chroots,
   // Capsicum, etc.
#  define _LIBCPP_USING_ARC4_RANDOM
#elif defined(__Fuchsia__) || defined(__wasi__)
#  define _LIBCPP_USING_GETENTROPY
#elif defined(__native_client__)
   // NaCl's sandbox (which PNaCl also runs in) doesn't allow filesystem access,
   // including accesses to the special files under /dev. C++11's
   // std::random_device is instead exposed through a NaCl syscall.
#  define _LIBCPP_USING_NACL_RANDOM
#elif defined(_LIBCPP_WIN32API)
#  define _LIBCPP_USING_WIN32_RANDOM
#else
#  define _LIBCPP_USING_DEV_RANDOM
#endif

#if !defined(_LIBCPP_LITTLE_ENDIAN) && !defined(_LIBCPP_BIG_ENDIAN)
#  include <endian.h>
#  if __BYTE_ORDER == __LITTLE_ENDIAN
#    define _LIBCPP_LITTLE_ENDIAN
#  elif __BYTE_ORDER == __BIG_ENDIAN
#    define _LIBCPP_BIG_ENDIAN
#  else  // __BYTE_ORDER == __BIG_ENDIAN
#    error unable to determine endian
#  endif
#endif  // !defined(_LIBCPP_LITTLE_ENDIAN) && !defined(_LIBCPP_BIG_ENDIAN)

#if __has_attribute(__no_sanitize__) && !defined(_LIBCPP_COMPILER_GCC)
#  define _LIBCPP_NO_CFI __attribute__((__no_sanitize__("cfi")))
#else
#  define _LIBCPP_NO_CFI
#endif

#if __ISO_C_VISIBLE >= 2011 || __cplusplus >= 201103L
#  if defined(__FreeBSD__)
#    define _LIBCPP_HAS_QUICK_EXIT
#    define _LIBCPP_HAS_C11_FEATURES
#  elif defined(__Fuchsia__) || defined(__wasi__)
#    define _LIBCPP_HAS_QUICK_EXIT
#    define _LIBCPP_HAS_TIMESPEC_GET
#    define _LIBCPP_HAS_C11_FEATURES
#  elif defined(__linux__)
#    if !defined(_LIBCPP_HAS_MUSL_LIBC)
#      if _LIBCPP_GLIBC_PREREQ(2, 15) || defined(__BIONIC__)
#        define _LIBCPP_HAS_QUICK_EXIT
#      endif
#      if _LIBCPP_GLIBC_PREREQ(2, 17)
#        define _LIBCPP_HAS_C11_FEATURES
#        define _LIBCPP_HAS_TIMESPEC_GET
#      endif
#    else // defined(_LIBCPP_HAS_MUSL_LIBC)
#      define _LIBCPP_HAS_QUICK_EXIT
#      define _LIBCPP_HAS_TIMESPEC_GET
#      define _LIBCPP_HAS_C11_FEATURES
#    endif
#  endif // __linux__
#endif

#ifndef _LIBCPP_CXX03_LANG
# define _LIBCPP_ALIGNOF(_Tp) alignof(_Tp)
#elif defined(_LIBCPP_COMPILER_CLANG)
# define _LIBCPP_ALIGNOF(_Tp) _Alignof(_Tp)
#else
// This definition is potentially buggy, but it's only taken with GCC in C++03,
// which we barely support anyway. See llvm.org/PR39713
# define _LIBCPP_ALIGNOF(_Tp) __alignof(_Tp)
#endif

#define _LIBCPP_PREFERRED_ALIGNOF(_Tp) __alignof(_Tp)

#if defined(_LIBCPP_COMPILER_CLANG)

// _LIBCPP_ALTERNATE_STRING_LAYOUT is an old name for
// _LIBCPP_ABI_ALTERNATE_STRING_LAYOUT left here for backward compatibility.
#if (defined(__APPLE__) && !defined(__i386__) && !defined(__x86_64__) &&       \
     (!defined(__arm__) || __ARM_ARCH_7K__ >= 2)) ||                           \
    defined(_LIBCPP_ALTERNATE_STRING_LAYOUT)
#define _LIBCPP_ABI_ALTERNATE_STRING_LAYOUT
#endif

#if __has_feature(cxx_alignas)
#  define _ALIGNAS_TYPE(x) alignas(x)
#  define _ALIGNAS(x) alignas(x)
#else
#  define _ALIGNAS_TYPE(x) __attribute__((__aligned__(_LIBCPP_ALIGNOF(x))))
#  define _ALIGNAS(x) __attribute__((__aligned__(x)))
#endif

#if __cplusplus < 201103L
typedef __char16_t char16_t;
typedef __char32_t char32_t;
#endif

#if !(__has_feature(cxx_exceptions)) && !defined(_LIBCPP_NO_EXCEPTIONS)
#define _LIBCPP_NO_EXCEPTIONS
#endif

#if !(__has_feature(cxx_rtti)) && !defined(_LIBCPP_NO_RTTI)
#define _LIBCPP_NO_RTTI
#endif

#if !(__has_feature(cxx_strong_enums))
#define _LIBCPP_HAS_NO_STRONG_ENUMS
#endif

#if __has_feature(cxx_attributes)
#  define _LIBCPP_NORETURN [[noreturn]]
#else
#  define _LIBCPP_NORETURN __attribute__ ((noreturn))
#endif

#if !(__has_feature(cxx_lambdas))
#define _LIBCPP_HAS_NO_LAMBDAS
#endif

#if !(__has_feature(cxx_nullptr))
#  if (__has_extension(cxx_nullptr) || __has_keyword(__nullptr)) && defined(_LIBCPP_ABI_ALWAYS_USE_CXX11_NULLPTR)
#    define nullptr __nullptr
#  else
#    define _LIBCPP_HAS_NO_NULLPTR
#  endif
#endif

#if !(__has_feature(cxx_rvalue_references))
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

#if !(__has_feature(cxx_auto_type))
#define _LIBCPP_HAS_NO_AUTO_TYPE
#endif

#if !(__has_feature(cxx_variadic_templates))
#define _LIBCPP_HAS_NO_VARIADICS
#endif

// Objective-C++ features (opt-in)
#if __has_feature(objc_arc)
#define _LIBCPP_HAS_OBJC_ARC
#endif

#if __has_feature(objc_arc_weak)
#define _LIBCPP_HAS_OBJC_ARC_WEAK
#endif

#if !(__has_feature(cxx_relaxed_constexpr))
#define _LIBCPP_HAS_NO_CXX14_CONSTEXPR
#endif

#if !(__has_feature(cxx_variable_templates))
#define _LIBCPP_HAS_NO_VARIABLE_TEMPLATES
#endif

#if !(__has_feature(cxx_noexcept))
#define _LIBCPP_HAS_NO_NOEXCEPT
#endif

#if !defined(_LIBCPP_HAS_NO_ASAN) && !__has_feature(address_sanitizer)
#define _LIBCPP_HAS_NO_ASAN
#endif

// Allow for build-time disabling of unsigned integer sanitization
#if !defined(_LIBCPP_DISABLE_UBSAN_UNSIGNED_INTEGER_CHECK) && __has_attribute(no_sanitize)
#define _LIBCPP_DISABLE_UBSAN_UNSIGNED_INTEGER_CHECK __attribute__((__no_sanitize__("unsigned-integer-overflow")))
#endif

#if __has_builtin(__builtin_launder)
#define _LIBCPP_COMPILER_HAS_BUILTIN_LAUNDER
#endif

#if !__is_identifier(__has_unique_object_representations)
#define _LIBCPP_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#endif

#define _LIBCPP_ALWAYS_INLINE __attribute__ ((__always_inline__))

// Literal operators ""d and ""y are supported starting with LLVM Clang 8 and AppleClang 10.0.1
#if (defined(_LIBCPP_CLANG_VER) && _LIBCPP_CLANG_VER < 800) || \
    (defined(__apple_build_version__) && __apple_build_version__ < 10010000)
#define _LIBCPP_HAS_NO_CXX20_CHRONO_LITERALS
#endif

#define _LIBCPP_DISABLE_EXTENSION_WARNING __extension__

#elif defined(_LIBCPP_COMPILER_GCC)

#define _ALIGNAS(x) __attribute__((__aligned__(x)))
#define _ALIGNAS_TYPE(x) __attribute__((__aligned__(_LIBCPP_ALIGNOF(x))))

#define _LIBCPP_NORETURN __attribute__((noreturn))

#if !__EXCEPTIONS && !defined(_LIBCPP_NO_EXCEPTIONS)
#define _LIBCPP_NO_EXCEPTIONS
#endif

// Determine if GCC supports relaxed constexpr
#if !defined(__cpp_constexpr) || __cpp_constexpr < 201304L
#define _LIBCPP_HAS_NO_CXX14_CONSTEXPR
#endif

// GCC 5 supports variable templates
#if !defined(__cpp_variable_templates) || __cpp_variable_templates < 201304L
#define _LIBCPP_HAS_NO_VARIABLE_TEMPLATES
#endif

#if !defined(_LIBCPP_HAS_NO_ASAN) && !defined(__SANITIZE_ADDRESS__)
#define _LIBCPP_HAS_NO_ASAN
#endif

#if _GNUC_VER >= 700
#define _LIBCPP_COMPILER_HAS_BUILTIN_LAUNDER
#endif

#if _GNUC_VER >= 700
#define _LIBCPP_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#endif

#define _LIBCPP_ALWAYS_INLINE __attribute__ ((__always_inline__))

#define _LIBCPP_DISABLE_EXTENSION_WARNING __extension__

#elif defined(_LIBCPP_COMPILER_MSVC)

#define _LIBCPP_TOSTRING2(x) #x
#define _LIBCPP_TOSTRING(x) _LIBCPP_TOSTRING2(x)
#define _LIBCPP_WARNING(x) __pragma(message(__FILE__ "(" _LIBCPP_TOSTRING(__LINE__) ") : warning note: " x))

#if _MSC_VER < 1900
#error "MSVC versions prior to Visual Studio 2015 are not supported"
#endif

#define _LIBCPP_HAS_NO_CXX14_CONSTEXPR
#define _LIBCPP_HAS_NO_VARIABLE_TEMPLATES
#define __alignof__ __alignof
#define _LIBCPP_NORETURN __declspec(noreturn)
#define _ALIGNAS(x) __declspec(align(x))
#define _ALIGNAS_TYPE(x) alignas(x)

#define _LIBCPP_WEAK

#define _LIBCPP_HAS_NO_ASAN

#define _LIBCPP_ALWAYS_INLINE __forceinline

#define _LIBCPP_HAS_NO_VECTOR_EXTENSION

#define _LIBCPP_DISABLE_EXTENSION_WARNING

#elif defined(_LIBCPP_COMPILER_IBM)

#define _ALIGNAS(x) __attribute__((__aligned__(x)))
#define _ALIGNAS_TYPE(x) __attribute__((__aligned__(_LIBCPP_ALIGNOF(x))))
#define _ATTRIBUTE(x) __attribute__((x))
#define _LIBCPP_NORETURN __attribute__((noreturn))

#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_VARIABLE_TEMPLATES

#if defined(_AIX)
#define __MULTILOCALE_API
#endif

#define _LIBCPP_HAS_NO_ASAN

#define _LIBCPP_ALWAYS_INLINE __attribute__ ((__always_inline__))

#define _LIBCPP_HAS_NO_VECTOR_EXTENSION

#define _LIBCPP_DISABLE_EXTENSION_WARNING

#endif // _LIBCPP_COMPILER_[CLANG|GCC|MSVC|IBM]

#if defined(_LIBCPP_OBJECT_FORMAT_COFF)

#ifdef _DLL
#  define _LIBCPP_CRT_FUNC __declspec(dllimport)
#else
#  define _LIBCPP_CRT_FUNC
#endif

#if defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#  define _LIBCPP_DLL_VIS
#  define _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS
#  define _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS
#  define _LIBCPP_OVERRIDABLE_FUNC_VIS
#  define _LIBCPP_EXPORTED_FROM_ABI
#elif defined(_LIBCPP_BUILDING_LIBRARY)
#  define _LIBCPP_DLL_VIS __declspec(dllexport)
#  if defined(__MINGW32__)
#    define _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS _LIBCPP_DLL_VIS
#    define _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS
#  else
#    define _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS
#    define _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS _LIBCPP_DLL_VIS
#  endif
#  define _LIBCPP_OVERRIDABLE_FUNC_VIS _LIBCPP_DLL_VIS
#  define _LIBCPP_EXPORTED_FROM_ABI __declspec(dllexport)
#else
#  define _LIBCPP_DLL_VIS __declspec(dllimport)
#  define _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS _LIBCPP_DLL_VIS
#  define _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS
#  define _LIBCPP_OVERRIDABLE_FUNC_VIS
#  define _LIBCPP_EXPORTED_FROM_ABI __declspec(dllimport)
#endif

#define _LIBCPP_TYPE_VIS            _LIBCPP_DLL_VIS
#define _LIBCPP_FUNC_VIS            _LIBCPP_DLL_VIS
#define _LIBCPP_EXCEPTION_ABI       _LIBCPP_DLL_VIS
#define _LIBCPP_HIDDEN
#define _LIBCPP_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS
#define _LIBCPP_TEMPLATE_VIS
#define _LIBCPP_ENUM_VIS

#endif // defined(_LIBCPP_OBJECT_FORMAT_COFF)

#ifndef _LIBCPP_HIDDEN
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#    define _LIBCPP_HIDDEN __attribute__ ((__visibility__("hidden")))
#  else
#    define _LIBCPP_HIDDEN
#  endif
#endif

#ifndef _LIBCPP_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
// The inline should be removed once PR32114 is resolved
#    define _LIBCPP_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS inline _LIBCPP_HIDDEN
#  else
#    define _LIBCPP_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS
#  endif
#endif

#ifndef _LIBCPP_FUNC_VIS
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#    define _LIBCPP_FUNC_VIS __attribute__ ((__visibility__("default")))
#  else
#    define _LIBCPP_FUNC_VIS
#  endif
#endif

#ifndef _LIBCPP_TYPE_VIS
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#    define _LIBCPP_TYPE_VIS __attribute__ ((__visibility__("default")))
#  else
#    define _LIBCPP_TYPE_VIS
#  endif
#endif

#ifndef _LIBCPP_TEMPLATE_VIS
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#    if __has_attribute(__type_visibility__)
#      define _LIBCPP_TEMPLATE_VIS __attribute__ ((__type_visibility__("default")))
#    else
#      define _LIBCPP_TEMPLATE_VIS __attribute__ ((__visibility__("default")))
#    endif
#  else
#    define _LIBCPP_TEMPLATE_VIS
#  endif
#endif

#ifndef _LIBCPP_EXPORTED_FROM_ABI
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#    define _LIBCPP_EXPORTED_FROM_ABI __attribute__((__visibility__("default")))
#  else
#    define _LIBCPP_EXPORTED_FROM_ABI
#  endif
#endif

#ifndef _LIBCPP_OVERRIDABLE_FUNC_VIS
#define _LIBCPP_OVERRIDABLE_FUNC_VIS _LIBCPP_FUNC_VIS
#endif

#ifndef _LIBCPP_EXCEPTION_ABI
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS)
#    define _LIBCPP_EXCEPTION_ABI __attribute__ ((__visibility__("default")))
#  else
#    define _LIBCPP_EXCEPTION_ABI
#  endif
#endif

#ifndef _LIBCPP_ENUM_VIS
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS) && __has_attribute(__type_visibility__)
#    define _LIBCPP_ENUM_VIS __attribute__ ((__type_visibility__("default")))
#  else
#    define _LIBCPP_ENUM_VIS
#  endif
#endif

#ifndef _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS
#  if !defined(_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS) && __has_attribute(__type_visibility__)
#    define _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS __attribute__ ((__visibility__("default")))
#  else
#    define _LIBCPP_EXTERN_TEMPLATE_TYPE_VIS
#  endif
#endif

#ifndef _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS
#define _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS
#endif

#if __has_attribute(internal_linkage)
#  define _LIBCPP_INTERNAL_LINKAGE __attribute__ ((internal_linkage))
#else
#  define _LIBCPP_INTERNAL_LINKAGE _LIBCPP_ALWAYS_INLINE
#endif

#if __has_attribute(exclude_from_explicit_instantiation)
#  define _LIBCPP_EXCLUDE_FROM_EXPLICIT_INSTANTIATION __attribute__ ((__exclude_from_explicit_instantiation__))
#else
   // Try to approximate the effect of exclude_from_explicit_instantiation
   // (which is that entities are not assumed to be provided by explicit
   // template instantiations in the dylib) by always inlining those entities.
#  define _LIBCPP_EXCLUDE_FROM_EXPLICIT_INSTANTIATION _LIBCPP_ALWAYS_INLINE
#endif

#ifndef _LIBCPP_HIDE_FROM_ABI_PER_TU
#  ifndef _LIBCPP_HIDE_FROM_ABI_PER_TU_BY_DEFAULT
#    define _LIBCPP_HIDE_FROM_ABI_PER_TU 0
#  else
#    define _LIBCPP_HIDE_FROM_ABI_PER_TU 1
#  endif
#endif

#ifndef _LIBCPP_HAS_MERGED_TYPEINFO_NAMES_DEFAULT
# ifdef _LIBCPP_OBJECT_FORMAT_COFF // Windows binaries can't merge typeinfos.
# define _LIBCPP_HAS_MERGED_TYPEINFO_NAMES_DEFAULT 0
#else
// TODO: This isn't strictly correct on ELF platforms due to llvm.org/PR37398
// And we should consider defaulting to OFF.
# define _LIBCPP_HAS_MERGED_TYPEINFO_NAMES_DEFAULT 1
#endif
#endif

#ifndef _LIBCPP_HIDE_FROM_ABI
#  if _LIBCPP_HIDE_FROM_ABI_PER_TU
#    define _LIBCPP_HIDE_FROM_ABI _LIBCPP_HIDDEN _LIBCPP_INTERNAL_LINKAGE
#  else
#    define _LIBCPP_HIDE_FROM_ABI _LIBCPP_HIDDEN _LIBCPP_EXCLUDE_FROM_EXPLICIT_INSTANTIATION
#  endif
#endif

#ifdef _LIBCPP_BUILDING_LIBRARY
#  if _LIBCPP_ABI_VERSION > 1
#    define _LIBCPP_HIDE_FROM_ABI_AFTER_V1 _LIBCPP_HIDE_FROM_ABI
#  else
#    define _LIBCPP_HIDE_FROM_ABI_AFTER_V1
#  endif
#else
#  define _LIBCPP_HIDE_FROM_ABI_AFTER_V1 _LIBCPP_HIDE_FROM_ABI
#endif

// Just so we can migrate to the new macros gradually.
#define _LIBCPP_INLINE_VISIBILITY _LIBCPP_HIDE_FROM_ABI

// Inline namespaces are available in Clang/GCC/MSVC regardless of C++ dialect.
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std { inline namespace _LIBCPP_ABI_NAMESPACE {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD std::_LIBCPP_ABI_NAMESPACE
_LIBCPP_BEGIN_NAMESPACE_STD _LIBCPP_END_NAMESPACE_STD

#if _LIBCPP_STD_VER >= 17
#define _LIBCPP_BEGIN_NAMESPACE_FILESYSTEM \
  _LIBCPP_BEGIN_NAMESPACE_STD inline namespace __fs { namespace filesystem {
#else
#define _LIBCPP_BEGIN_NAMESPACE_FILESYSTEM \
  _LIBCPP_BEGIN_NAMESPACE_STD namespace __fs { namespace filesystem {
#endif

#define _LIBCPP_END_NAMESPACE_FILESYSTEM \
  _LIBCPP_END_NAMESPACE_STD } }

#define _VSTD_FS _VSTD::__fs::filesystem

#ifndef _LIBCPP_PREFERRED_OVERLOAD
#  if __has_attribute(__enable_if__)
#    define _LIBCPP_PREFERRED_OVERLOAD __attribute__ ((__enable_if__(true, "")))
#  endif
#endif

#ifndef _LIBCPP_HAS_NO_NOEXCEPT
#  define _NOEXCEPT noexcept
#  define _NOEXCEPT_(x) noexcept(x)
#else
#  define _NOEXCEPT throw()
#  define _NOEXCEPT_(x)
#endif

#ifdef _LIBCPP_HAS_NO_UNICODE_CHARS
typedef unsigned short char16_t;
typedef unsigned int   char32_t;
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS

#ifndef __SIZEOF_INT128__
#define _LIBCPP_HAS_NO_INT128
#endif

#ifdef _LIBCPP_CXX03_LANG
# define static_assert(...) _Static_assert(__VA_ARGS__)
# define decltype(...) __decltype(__VA_ARGS__)
#endif  // _LIBCPP_CXX03_LANG

#ifdef _LIBCPP_CXX03_LANG
#  define _LIBCPP_CONSTEXPR
#else
#  define _LIBCPP_CONSTEXPR constexpr
#endif

#ifdef _LIBCPP_CXX03_LANG
#  define _LIBCPP_DEFAULT {}
#else
#  define _LIBCPP_DEFAULT = default;
#endif

#ifdef _LIBCPP_CXX03_LANG
#  define _LIBCPP_EQUAL_DELETE
#else
#  define _LIBCPP_EQUAL_DELETE = delete
#endif

#ifdef __GNUC__
#  define _LIBCPP_NOALIAS __attribute__((__malloc__))
#else
#  define _LIBCPP_NOALIAS
#endif

#if __has_feature(cxx_explicit_conversions) || defined(__IBMCPP__) || \
    (!defined(_LIBCPP_CXX03_LANG) && defined(__GNUC__)) // All supported GCC versions
#  define _LIBCPP_EXPLICIT explicit
#else
#  define _LIBCPP_EXPLICIT
#endif

#if !__has_builtin(__builtin_operator_new) || !__has_builtin(__builtin_operator_delete)
#define _LIBCPP_HAS_NO_BUILTIN_OPERATOR_NEW_DELETE
#endif

#ifdef _LIBCPP_HAS_NO_STRONG_ENUMS
#  define _LIBCPP_DECLARE_STRONG_ENUM(x) struct _LIBCPP_TYPE_VIS x { enum __lx
#  define _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x) \
     __lx __v_; \
     _LIBCPP_INLINE_VISIBILITY x(__lx __v) : __v_(__v) {} \
     _LIBCPP_INLINE_VISIBILITY explicit x(int __v) : __v_(static_cast<__lx>(__v)) {} \
     _LIBCPP_INLINE_VISIBILITY operator int() const {return __v_;} \
     };
#else  // _LIBCPP_HAS_NO_STRONG_ENUMS
#  define _LIBCPP_DECLARE_STRONG_ENUM(x) enum class _LIBCPP_ENUM_VIS x
#  define _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x)
#endif  // _LIBCPP_HAS_NO_STRONG_ENUMS

#ifdef _LIBCPP_DEBUG
#  if _LIBCPP_DEBUG == 0
#    define _LIBCPP_DEBUG_LEVEL 1
#  elif _LIBCPP_DEBUG == 1
#    define _LIBCPP_DEBUG_LEVEL 2
#  else
#    error Supported values for _LIBCPP_DEBUG are 0 and 1
#  endif
#  if !defined(_LIBCPP_BUILDING_LIBRARY)
#    define _LIBCPP_EXTERN_TEMPLATE(...)
#  endif
#endif

#ifdef _LIBCPP_DISABLE_EXTERN_TEMPLATE
#define _LIBCPP_EXTERN_TEMPLATE(...)
#define _LIBCPP_EXTERN_TEMPLATE2(...)
#endif

#ifndef _LIBCPP_EXTERN_TEMPLATE
#define _LIBCPP_EXTERN_TEMPLATE(...) extern template __VA_ARGS__;
#endif

#ifndef _LIBCPP_EXTERN_TEMPLATE2
#define _LIBCPP_EXTERN_TEMPLATE2(...) extern template __VA_ARGS__;
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(_LIBCPP_MSVCRT_LIKE) || \
    defined(__sun__) || defined(__NetBSD__) || defined(__CloudABI__)
#define _LIBCPP_LOCALE__L_EXTENSIONS 1
#endif

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
// Most unix variants have catopen.  These are the specific ones that don't.
#  if !defined(__BIONIC__) && !defined(_NEWLIB_VERSION)
#    define _LIBCPP_HAS_CATOPEN 1
#  endif
#endif

#ifdef __FreeBSD__
#define _DECLARE_C99_LDBL_MATH 1
#endif

// If we are getting operator new from the MSVC CRT, then allocation overloads
// for align_val_t were added in 19.12, aka VS 2017 version 15.3.
#if defined(_LIBCPP_MSVCRT) && defined(_MSC_VER) && _MSC_VER < 1912
#  define _LIBCPP_HAS_NO_LIBRARY_ALIGNED_ALLOCATION
#elif defined(_LIBCPP_ABI_VCRUNTIME) && !defined(__cpp_aligned_new)
   // We're deferring to Microsoft's STL to provide aligned new et al. We don't
   // have it unless the language feature test macro is defined.
#  define _LIBCPP_HAS_NO_LIBRARY_ALIGNED_ALLOCATION
#endif

#if defined(__APPLE__)
#  if !defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && \
      defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#    define __MAC_OS_X_VERSION_MIN_REQUIRED __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#  endif
#endif // defined(__APPLE__)

#if !defined(_LIBCPP_HAS_NO_ALIGNED_ALLOCATION) && \
    (defined(_LIBCPP_HAS_NO_LIBRARY_ALIGNED_ALLOCATION) || \
    (!defined(__cpp_aligned_new) || __cpp_aligned_new < 201606))
#  define _LIBCPP_HAS_NO_ALIGNED_ALLOCATION
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
#define _LIBCPP_HAS_DEFAULTRUNELOCALE
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__sun__)
#define _LIBCPP_WCTYPE_IS_MASK
#endif

#if _LIBCPP_STD_VER <= 17 || !defined(__cpp_char8_t)
#define _LIBCPP_NO_HAS_CHAR8_T
#endif

// Deprecation macros.
//
// Deprecations warnings are always enabled, except when users explicitly opt-out
// by defining _LIBCPP_DISABLE_DEPRECATION_WARNINGS.
#if !defined(_LIBCPP_DISABLE_DEPRECATION_WARNINGS)
#  if __has_attribute(deprecated)
#    define _LIBCPP_DEPRECATED __attribute__ ((deprecated))
#  elif _LIBCPP_STD_VER > 11
#    define _LIBCPP_DEPRECATED [[deprecated]]
#  else
#    define _LIBCPP_DEPRECATED
#  endif
#else
#  define _LIBCPP_DEPRECATED
#endif

#if !defined(_LIBCPP_CXX03_LANG)
#  define _LIBCPP_DEPRECATED_IN_CXX11 _LIBCPP_DEPRECATED
#else
#  define _LIBCPP_DEPRECATED_IN_CXX11
#endif

#if _LIBCPP_STD_VER >= 14
#  define _LIBCPP_DEPRECATED_IN_CXX14 _LIBCPP_DEPRECATED
#else
#  define _LIBCPP_DEPRECATED_IN_CXX14
#endif

#if _LIBCPP_STD_VER >= 17
#  define _LIBCPP_DEPRECATED_IN_CXX17 _LIBCPP_DEPRECATED
#else
#  define _LIBCPP_DEPRECATED_IN_CXX17
#endif

// Macros to enter and leave a state where deprecation warnings are suppressed.
#if !defined(_LIBCPP_SUPPRESS_DEPRECATED_PUSH) && \
    (defined(_LIBCPP_COMPILER_CLANG) || defined(_LIBCPP_COMPILER_GCC))
#  define _LIBCPP_SUPPRESS_DEPRECATED_PUSH \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
#  define _LIBCPP_SUPPRESS_DEPRECATED_POP \
    _Pragma("GCC diagnostic pop")
#endif
#if !defined(_LIBCPP_SUPPRESS_DEPRECATED_PUSH)
#  define _LIBCPP_SUPPRESS_DEPRECATED_PUSH
#  define _LIBCPP_SUPPRESS_DEPRECATED_POP
#endif

#if _LIBCPP_STD_VER <= 11
#  define _LIBCPP_EXPLICIT_AFTER_CXX11
#else
#  define _LIBCPP_EXPLICIT_AFTER_CXX11 explicit
#endif

#if _LIBCPP_STD_VER > 11 && !defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#  define _LIBCPP_CONSTEXPR_AFTER_CXX11 constexpr
#else
#  define _LIBCPP_CONSTEXPR_AFTER_CXX11
#endif

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#  define _LIBCPP_CONSTEXPR_AFTER_CXX14 constexpr
#else
#  define _LIBCPP_CONSTEXPR_AFTER_CXX14
#endif

#if _LIBCPP_STD_VER > 17 && !defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#  define _LIBCPP_CONSTEXPR_AFTER_CXX17 constexpr
#else
#  define _LIBCPP_CONSTEXPR_AFTER_CXX17
#endif

// The _LIBCPP_NODISCARD_ATTRIBUTE should only be used to define other
// NODISCARD macros to the correct attribute.
#if __has_cpp_attribute(nodiscard) || defined(_LIBCPP_COMPILER_MSVC)
#  define _LIBCPP_NODISCARD_ATTRIBUTE [[nodiscard]]
#elif defined(_LIBCPP_COMPILER_CLANG) && !defined(_LIBCPP_CXX03_LANG)
#  define _LIBCPP_NODISCARD_ATTRIBUTE [[clang::warn_unused_result]]
#else
// We can't use GCC's [[gnu::warn_unused_result]] and
// __attribute__((warn_unused_result)), because GCC does not silence them via
// (void) cast.
#  define _LIBCPP_NODISCARD_ATTRIBUTE
#endif

// _LIBCPP_NODISCARD_EXT may be used to apply [[nodiscard]] to entities not
// specified as such as an extension.
#if defined(_LIBCPP_ENABLE_NODISCARD) && !defined(_LIBCPP_DISABLE_NODISCARD_EXT)
#  define _LIBCPP_NODISCARD_EXT _LIBCPP_NODISCARD_ATTRIBUTE
#else
#  define _LIBCPP_NODISCARD_EXT
#endif

#if !defined(_LIBCPP_DISABLE_NODISCARD_AFTER_CXX17) && \
    (_LIBCPP_STD_VER > 17 || defined(_LIBCPP_ENABLE_NODISCARD))
#  define _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_NODISCARD_ATTRIBUTE
#else
#  define _LIBCPP_NODISCARD_AFTER_CXX17
#endif

#if _LIBCPP_STD_VER > 14 && defined(__cpp_inline_variables) && (__cpp_inline_variables >= 201606L)
#  define _LIBCPP_INLINE_VAR inline
#else
#  define _LIBCPP_INLINE_VAR
#endif

#ifdef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#  define _LIBCPP_EXPLICIT_MOVE(x) _VSTD::move(x)
#else
#  define _LIBCPP_EXPLICIT_MOVE(x) (x)
#endif

#ifndef _LIBCPP_CONSTEXPR_IF_NODEBUG
#if defined(_LIBCPP_DEBUG) || defined(_LIBCPP_HAS_NO_CXX14_CONSTEXPR)
#define _LIBCPP_CONSTEXPR_IF_NODEBUG
#else
#define _LIBCPP_CONSTEXPR_IF_NODEBUG constexpr
#endif
#endif

#if __has_attribute(no_destroy)
#  define _LIBCPP_NO_DESTROY __attribute__((__no_destroy__))
#else
#  define _LIBCPP_NO_DESTROY
#endif

#ifndef _LIBCPP_HAS_NO_ASAN
_LIBCPP_FUNC_VIS extern "C" void __sanitizer_annotate_contiguous_container(
  const void *, const void *, const void *, const void *);
#endif

// Try to find out if RTTI is disabled.
// g++ and cl.exe have RTTI on by default and define a macro when it is.
// g++ only defines the macro in 4.3.2 and onwards.
#if !defined(_LIBCPP_NO_RTTI)
#  if defined(__GNUC__) && \
      ((__GNUC__ >= 5) || \
       (__GNUC__ == 4 && (__GNUC_MINOR__ >= 3 || __GNUC_PATCHLEVEL__ >= 2))) && \
      !defined(__GXX_RTTI)
#    define _LIBCPP_NO_RTTI
#  elif defined(_LIBCPP_COMPILER_MSVC) && !defined(_CPPRTTI)
#    define _LIBCPP_NO_RTTI
#  endif
#endif

#ifndef _LIBCPP_WEAK
#define _LIBCPP_WEAK __attribute__((__weak__))
#endif

// Thread API
#if !defined(_LIBCPP_HAS_NO_THREADS) && \
    !defined(_LIBCPP_HAS_THREAD_API_PTHREAD) && \
    !defined(_LIBCPP_HAS_THREAD_API_WIN32) && \
    !defined(_LIBCPP_HAS_THREAD_API_EXTERNAL)
#  if defined(__FreeBSD__) || \
      defined(__Fuchsia__) || \
      defined(__wasi__) || \
      defined(__NetBSD__) || \
      defined(__linux__) || \
      defined(__GNU__) || \
      defined(__APPLE__) || \
      defined(__CloudABI__) || \
      defined(__sun__) || \
      (defined(__MINGW32__) && __has_include(<pthread.h>))
#    define _LIBCPP_HAS_THREAD_API_PTHREAD
#  elif defined(_LIBCPP_WIN32API)
#    define _LIBCPP_HAS_THREAD_API_WIN32
#  else
#    error "No thread API"
#  endif // _LIBCPP_HAS_THREAD_API
#endif // _LIBCPP_HAS_NO_THREADS

#if defined(_LIBCPP_HAS_THREAD_API_PTHREAD)
#if defined(__ANDROID__) && __ANDROID_API__ >= 30
#define _LIBCPP_HAS_COND_CLOCKWAIT
#elif defined(_LIBCPP_GLIBC_PREREQ)
#if _LIBCPP_GLIBC_PREREQ(2, 30)
#define _LIBCPP_HAS_COND_CLOCKWAIT
#endif
#endif
#endif

#if defined(_LIBCPP_HAS_NO_THREADS) && defined(_LIBCPP_HAS_THREAD_API_PTHREAD)
#error _LIBCPP_HAS_THREAD_API_PTHREAD may only be defined when \
       _LIBCPP_HAS_NO_THREADS is not defined.
#endif

#if defined(_LIBCPP_HAS_NO_THREADS) && defined(_LIBCPP_HAS_THREAD_API_EXTERNAL)
#error _LIBCPP_HAS_THREAD_API_EXTERNAL may not be defined when \
       _LIBCPP_HAS_NO_THREADS is defined.
#endif

#if defined(_LIBCPP_HAS_NO_MONOTONIC_CLOCK) && !defined(_LIBCPP_HAS_NO_THREADS)
#error _LIBCPP_HAS_NO_MONOTONIC_CLOCK may only be defined when \
       _LIBCPP_HAS_NO_THREADS is defined.
#endif

#if defined(__STDCPP_THREADS__) && defined(_LIBCPP_HAS_NO_THREADS)
#error _LIBCPP_HAS_NO_THREADS cannot be set when __STDCPP_THREADS__ is set.
#endif

#if !defined(_LIBCPP_HAS_NO_THREADS) && !defined(__STDCPP_THREADS__)
#define __STDCPP_THREADS__ 1
#endif

// The glibc and Bionic implementation of pthreads implements
// pthread_mutex_destroy as nop for regular mutexes. Additionally, Win32
// mutexes have no destroy mechanism.
//
// This optimization can't be performed on Apple platforms, where
// pthread_mutex_destroy can allow the kernel to release resources.
// See https://llvm.org/D64298 for details.
//
// TODO(EricWF): Enable this optimization on Bionic after speaking to their
//               respective stakeholders.
#if (defined(_LIBCPP_HAS_THREAD_API_PTHREAD) && defined(__GLIBC__)) \
  || defined(_LIBCPP_HAS_THREAD_API_WIN32)
# define _LIBCPP_HAS_TRIVIAL_MUTEX_DESTRUCTION
#endif

// Destroying a condvar is a nop on Windows.
//
// This optimization can't be performed on Apple platforms, where
// pthread_cond_destroy can allow the kernel to release resources.
// See https://llvm.org/D64298 for details.
//
// TODO(EricWF): This is potentially true for some pthread implementations
// as well.
#if defined(_LIBCPP_HAS_THREAD_API_WIN32)
# define _LIBCPP_HAS_TRIVIAL_CONDVAR_DESTRUCTION
#endif

// Systems that use capability-based security (FreeBSD with Capsicum,
// Nuxi CloudABI) may only provide local filesystem access (using *at()).
// Functions like open(), rename(), unlink() and stat() should not be
// used, as they attempt to access the global filesystem namespace.
#ifdef __CloudABI__
#define _LIBCPP_HAS_NO_GLOBAL_FILESYSTEM_NAMESPACE
#endif

// CloudABI is intended for running networked services. Processes do not
// have standard input and output channels.
#ifdef __CloudABI__
#define _LIBCPP_HAS_NO_STDIN
#define _LIBCPP_HAS_NO_STDOUT
#endif

// Some systems do not provide gets() in their C library, for security reasons.
#ifndef _LIBCPP_C_HAS_NO_GETS
#  if defined(_LIBCPP_MSVCRT) || \
      (defined(__FreeBSD_version) && __FreeBSD_version >= 1300043)
#    define _LIBCPP_C_HAS_NO_GETS
#  endif
#endif

#if defined(__BIONIC__) || defined(__CloudABI__) ||                            \
    defined(__Fuchsia__) || defined(__wasi__) || defined(_LIBCPP_HAS_MUSL_LIBC)
#define _LIBCPP_PROVIDES_DEFAULT_RUNE_TABLE
#endif

// Thread-unsafe functions such as strtok() and localtime()
// are not available.
#ifdef __CloudABI__
#define _LIBCPP_HAS_NO_THREAD_UNSAFE_C_FUNCTIONS
#endif

#if __has_feature(cxx_atomic) || __has_extension(c_atomic) || __has_keyword(_Atomic)
#  define _LIBCPP_HAS_C_ATOMIC_IMP
#elif defined(_LIBCPP_COMPILER_GCC)
#  define _LIBCPP_HAS_GCC_ATOMIC_IMP
#endif

#if (!defined(_LIBCPP_HAS_C_ATOMIC_IMP) && \
     !defined(_LIBCPP_HAS_GCC_ATOMIC_IMP) && \
     !defined(_LIBCPP_HAS_EXTERNAL_ATOMIC_IMP)) \
     || defined(_LIBCPP_HAS_NO_THREADS)
#  define _LIBCPP_HAS_NO_ATOMIC_HEADER
#else
#  ifndef _LIBCPP_ATOMIC_FLAG_TYPE
#    define _LIBCPP_ATOMIC_FLAG_TYPE bool
#  endif
#  ifdef _LIBCPP_FREESTANDING
#    define _LIBCPP_ATOMIC_ONLY_USE_BUILTINS
#  endif
#endif

#ifndef _LIBCPP_DISABLE_UBSAN_UNSIGNED_INTEGER_CHECK
#define _LIBCPP_DISABLE_UBSAN_UNSIGNED_INTEGER_CHECK
#endif

#if defined(_LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS)
#  if defined(__clang__) && __has_attribute(acquire_capability)
// Work around the attribute handling in clang.  When both __declspec and
// __attribute__ are present, the processing goes awry preventing the definition
// of the types.
#    if !defined(_LIBCPP_OBJECT_FORMAT_COFF)
#      define _LIBCPP_HAS_THREAD_SAFETY_ANNOTATIONS
#    endif
#  endif
#endif

#if __has_attribute(require_constant_initialization)
#  define _LIBCPP_SAFE_STATIC __attribute__((__require_constant_initialization__))
#else
#  define _LIBCPP_SAFE_STATIC
#endif

#if !__has_builtin(__builtin_addressof) && _GNUC_VER < 700
#define _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF
#endif

#if !__has_builtin(__builtin_is_constant_evaluated) && _GNUC_VER < 900
#define _LIBCPP_HAS_NO_BUILTIN_IS_CONSTANT_EVALUATED
#endif

#if !defined(_LIBCPP_HAS_NO_OFF_T_FUNCTIONS)
#  if defined(_LIBCPP_MSVCRT) || defined(_NEWLIB_VERSION)
#    define _LIBCPP_HAS_NO_OFF_T_FUNCTIONS
#  endif
#endif

#if __has_attribute(diagnose_if) && !defined(_LIBCPP_DISABLE_ADDITIONAL_DIAGNOSTICS)
#  define _LIBCPP_DIAGNOSE_WARNING(...) \
     __attribute__((diagnose_if(__VA_ARGS__, "warning")))
#  define _LIBCPP_DIAGNOSE_ERROR(...) \
     __attribute__((diagnose_if(__VA_ARGS__, "error")))
#else
#  define _LIBCPP_DIAGNOSE_WARNING(...)
#  define _LIBCPP_DIAGNOSE_ERROR(...)
#endif

// Use a function like macro to imply that it must be followed by a semicolon
#if __cplusplus > 201402L && __has_cpp_attribute(fallthrough)
#  define _LIBCPP_FALLTHROUGH() [[fallthrough]]
#elif __has_cpp_attribute(clang::fallthrough)
#  define _LIBCPP_FALLTHROUGH() [[clang::fallthrough]]
#elif __has_attribute(fallthough) || _GNUC_VER >= 700
#  define _LIBCPP_FALLTHROUGH() __attribute__((__fallthrough__))
#else
#  define _LIBCPP_FALLTHROUGH() ((void)0)
#endif

#if __has_attribute(__nodebug__)
#define _LIBCPP_NODEBUG __attribute__((__nodebug__))
#else
#define _LIBCPP_NODEBUG
#endif

#ifndef _LIBCPP_NODEBUG_TYPE
#if __has_attribute(__nodebug__) && \
    (defined(_LIBCPP_CLANG_VER) && _LIBCPP_CLANG_VER >= 900)
#define _LIBCPP_NODEBUG_TYPE __attribute__((nodebug))
#else
#define _LIBCPP_NODEBUG_TYPE
#endif
#endif // !defined(_LIBCPP_NODEBUG_TYPE)

#if defined(_LIBCPP_ABI_MICROSOFT) && \
    (defined(_LIBCPP_COMPILER_MSVC) || __has_declspec_attribute(empty_bases))
#  define _LIBCPP_DECLSPEC_EMPTY_BASES __declspec(empty_bases)
#else
#  define _LIBCPP_DECLSPEC_EMPTY_BASES
#endif

#if defined(_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES)
#define _LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR
#define _LIBCPP_ENABLE_CXX17_REMOVED_UNEXPECTED_FUNCTIONS
#define _LIBCPP_ENABLE_CXX17_REMOVED_RANDOM_SHUFFLE
#define _LIBCPP_ENABLE_CXX17_REMOVED_BINDERS
#endif // _LIBCPP_ENABLE_CXX17_REMOVED_FEATURES

#if !defined(__cpp_deduction_guides) || __cpp_deduction_guides < 201611
#define _LIBCPP_HAS_NO_DEDUCTION_GUIDES
#endif

#if !__has_keyword(__is_aggregate) && (_GNUC_VER_NEW < 7001)
#define _LIBCPP_HAS_NO_IS_AGGREGATE
#endif

#if !defined(__cpp_coroutines) || __cpp_coroutines < 201703L
#define _LIBCPP_HAS_NO_COROUTINES
#endif

// FIXME: Correct this macro when either (A) a feature test macro for the
// spaceship operator is provided, or (B) a compiler provides a complete
// implementation.
#define _LIBCPP_HAS_NO_SPACESHIP_OPERATOR

// Decide whether to use availability macros.
#if !defined(_LIBCPP_BUILDING_LIBRARY) &&                                      \
    !defined(_LIBCPP_DISABLE_AVAILABILITY) &&                                  \
    __has_feature(attribute_availability_with_strict) &&                       \
    __has_feature(attribute_availability_in_templates) &&                      \
    __has_extension(pragma_clang_attribute_external_declaration)
#  ifdef __APPLE__
#    define _LIBCPP_USE_AVAILABILITY_APPLE
#  endif
#endif

// Define availability macros.
#if defined(_LIBCPP_USE_AVAILABILITY_APPLE)
#  define _LIBCPP_AVAILABILITY_SHARED_MUTEX                                    \
     __attribute__((availability(macosx,strict,introduced=10.12)))             \
     __attribute__((availability(ios,strict,introduced=10.0)))                 \
     __attribute__((availability(tvos,strict,introduced=10.0)))                \
     __attribute__((availability(watchos,strict,introduced=3.0)))
#  define _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS                             \
     __attribute__((availability(macosx,strict,introduced=10.14)))             \
     __attribute__((availability(ios,strict,introduced=12.0)))                 \
     __attribute__((availability(tvos,strict,introduced=12.0)))                \
     __attribute__((availability(watchos,strict,introduced=5.0)))
#  define _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS                              \
     _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#  define _LIBCPP_AVAILABILITY_BAD_ANY_CAST                                    \
     _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#  define _LIBCPP_AVAILABILITY_UNCAUGHT_EXCEPTIONS                             \
     __attribute__((availability(macosx,strict,introduced=10.12)))             \
     __attribute__((availability(ios,strict,introduced=10.0)))                 \
     __attribute__((availability(tvos,strict,introduced=10.0)))                \
     __attribute__((availability(watchos,strict,introduced=3.0)))
#  define _LIBCPP_AVAILABILITY_SIZED_NEW_DELETE                                \
     __attribute__((availability(macosx,strict,introduced=10.12)))             \
     __attribute__((availability(ios,strict,introduced=10.0)))                 \
     __attribute__((availability(tvos,strict,introduced=10.0)))                \
     __attribute__((availability(watchos,strict,introduced=3.0)))
#  define _LIBCPP_AVAILABILITY_FUTURE_ERROR                                    \
     __attribute__((availability(ios,strict,introduced=6.0)))
#  define _LIBCPP_AVAILABILITY_TYPEINFO_VTABLE                                 \
     __attribute__((availability(macosx,strict,introduced=10.9)))              \
     __attribute__((availability(ios,strict,introduced=7.0)))
#  define _LIBCPP_AVAILABILITY_LOCALE_CATEGORY                                 \
     __attribute__((availability(macosx,strict,introduced=10.9)))              \
     __attribute__((availability(ios,strict,introduced=7.0)))
#  define _LIBCPP_AVAILABILITY_ATOMIC_SHARED_PTR                               \
     __attribute__((availability(macosx,strict,introduced=10.9)))              \
     __attribute__((availability(ios,strict,introduced=7.0)))
#  define _LIBCPP_AVAILABILITY_FILESYSTEM                                      \
     __attribute__((availability(macosx,strict,introduced=10.15)))             \
     __attribute__((availability(ios,strict,introduced=13.0)))                 \
     __attribute__((availability(tvos,strict,introduced=13.0)))                \
     __attribute__((availability(watchos,strict,introduced=6.0)))
#  define _LIBCPP_AVAILABILITY_FILESYSTEM_PUSH                                 \
     _Pragma("clang attribute push(__attribute__((availability(macosx,strict,introduced=10.15))), apply_to=any(function,record))") \
     _Pragma("clang attribute push(__attribute__((availability(ios,strict,introduced=13.0))), apply_to=any(function,record))")     \
     _Pragma("clang attribute push(__attribute__((availability(tvos,strict,introduced=13.0))), apply_to=any(function,record))")    \
     _Pragma("clang attribute push(__attribute__((availability(watchos,strict,introduced=6.0))), apply_to=any(function,record))")
#  define _LIBCPP_AVAILABILITY_FILESYSTEM_POP                                  \
     _Pragma("clang attribute pop")                                            \
     _Pragma("clang attribute pop")                                            \
     _Pragma("clang attribute pop")                                            \
     _Pragma("clang attribute pop")
#else
#  define _LIBCPP_AVAILABILITY_SHARED_MUTEX
#  define _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS
#  define _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#  define _LIBCPP_AVAILABILITY_BAD_ANY_CAST
#  define _LIBCPP_AVAILABILITY_UNCAUGHT_EXCEPTIONS
#  define _LIBCPP_AVAILABILITY_SIZED_NEW_DELETE
#  define _LIBCPP_AVAILABILITY_FUTURE_ERROR
#  define _LIBCPP_AVAILABILITY_TYPEINFO_VTABLE
#  define _LIBCPP_AVAILABILITY_LOCALE_CATEGORY
#  define _LIBCPP_AVAILABILITY_ATOMIC_SHARED_PTR
#  define _LIBCPP_AVAILABILITY_FILESYSTEM
#  define _LIBCPP_AVAILABILITY_FILESYSTEM_PUSH
#  define _LIBCPP_AVAILABILITY_FILESYSTEM_POP
#endif

// Define availability that depends on _LIBCPP_NO_EXCEPTIONS.
#ifdef _LIBCPP_NO_EXCEPTIONS
#  define _LIBCPP_AVAILABILITY_FUTURE
#  define _LIBCPP_AVAILABILITY_THROW_BAD_ANY_CAST
#  define _LIBCPP_AVAILABILITY_THROW_BAD_OPTIONAL_ACCESS
#  define _LIBCPP_AVAILABILITY_THROW_BAD_VARIANT_ACCESS
#else
#  define _LIBCPP_AVAILABILITY_FUTURE                    _LIBCPP_AVAILABILITY_FUTURE_ERROR
#  define _LIBCPP_AVAILABILITY_THROW_BAD_ANY_CAST        _LIBCPP_AVAILABILITY_BAD_ANY_CAST
#  define _LIBCPP_AVAILABILITY_THROW_BAD_OPTIONAL_ACCESS _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#  define _LIBCPP_AVAILABILITY_THROW_BAD_VARIANT_ACCESS  _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS
#endif

// The stream API was dropped and re-added in the dylib shipped on macOS
// and iOS. We can only assume the dylib to provide these definitions for
// macosx >= 10.9 and ios >= 7.0. Otherwise, the definitions are available
// from the headers, but not from the dylib. Explicit instantiation
// declarations for streams exist conditionally to this; if we provide
// an explicit instantiation declaration and we try to deploy to a dylib
// that does not provide those symbols, we'll get a load-time error.
#if !defined(_LIBCPP_BUILDING_LIBRARY) &&                                      \
    ((defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) &&                \
      __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1090) ||                 \
     (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) &&               \
      __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ < 70000))
#  define _LIBCPP_DO_NOT_ASSUME_STREAMS_EXPLICIT_INSTANTIATION_IN_DYLIB
#endif

#if defined(_LIBCPP_COMPILER_IBM)
#define _LIBCPP_HAS_NO_PRAGMA_PUSH_POP_MACRO
#endif

#if defined(_LIBCPP_HAS_NO_PRAGMA_PUSH_POP_MACRO)
#  define _LIBCPP_PUSH_MACROS
#  define _LIBCPP_POP_MACROS
#else
  // Don't warn about macro conflicts when we can restore them at the
  // end of the header.
#  ifndef _LIBCPP_DISABLE_MACRO_CONFLICT_WARNINGS
#    define _LIBCPP_DISABLE_MACRO_CONFLICT_WARNINGS
#  endif
#  if defined(_LIBCPP_COMPILER_MSVC)
#    define _LIBCPP_PUSH_MACROS    \
       __pragma(push_macro("min")) \
       __pragma(push_macro("max"))
#    define _LIBCPP_POP_MACROS     \
       __pragma(pop_macro("min"))  \
       __pragma(pop_macro("max"))
#  else
#    define _LIBCPP_PUSH_MACROS        \
       _Pragma("push_macro(\"min\")")  \
       _Pragma("push_macro(\"max\")")
#    define _LIBCPP_POP_MACROS         \
       _Pragma("pop_macro(\"min\")")   \
       _Pragma("pop_macro(\"max\")")
#  endif
#endif // defined(_LIBCPP_HAS_NO_PRAGMA_PUSH_POP_MACRO)

#ifndef _LIBCPP_NO_AUTO_LINK
#  if defined(_LIBCPP_ABI_MICROSOFT) && !defined(_LIBCPP_BUILDING_LIBRARY)
#    if defined(_DLL)
#      pragma comment(lib, "c++.lib")
#    else
#      pragma comment(lib, "libc++.lib")
#    endif
#  endif // defined(_LIBCPP_ABI_MICROSOFT) && !defined(_LIBCPP_BUILDING_LIBRARY)
#endif // _LIBCPP_NO_AUTO_LINK

#define _LIBCPP_UNUSED_VAR(x) ((void)(x))

// Configures the fopen close-on-exec mode character, if any. This string will
// be appended to any mode string used by fstream for fopen/fdopen.
//
// Not all platforms support this, but it helps avoid fd-leaks on platforms that
// do.
#if defined(__BIONIC__)
#  define _LIBCPP_FOPEN_CLOEXEC_MODE "e"
#else
#  define _LIBCPP_FOPEN_CLOEXEC_MODE
#endif

#endif // __cplusplus

// something in __debug
#ifndef _LIBCPP_ASSERT
#define _LIBCPP_ASSERT   ((void)0)
#endif

#endif // _LIBCPP_CONFIG
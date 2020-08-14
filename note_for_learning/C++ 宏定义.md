# <center>C++ 的一些宏定义</center>

## 一些编译器内置的宏   
1. \_MSC_VER
> * \_MSC_VER 是 MSVC 编译器自身携带的一个宏，用于编译器为 MSVC 编译器。Microsoft Visual Studio 的 cl 编译器就是这样的编译器   

2. __cpluscplus   
> * 这个宏指定了编译器支持的 ```C++``` 的标准，它可能有下面的几个值  
> ```C++
> __cpluscplus < 201103L  // 最高支持 C++ 11 标准
> __cpluscplus < 201402L  // 最高支持 C++ 14 标准
> __cpluscplus < 201703L  // 最高支持 C++ 17 标准
> ```   
> * 在书写 ```C++``` 代码的时候，为了保证和编译器之间的兼容性，应该对不同的 __cpluscplus 分别进行不同的实现，当然如果代码没有使用什么新的特性，则可以忽略这个选项   
3. ```__GCC__```   
> * 这个宏定义了 GCC 编译器的主版本号
> * 与版本相关的还有下面的两个宏定义：   
>     + ```__GNUC_MINOR__``` : 次版本   
>     + ```__GNUC_PATCHLEVEL__``` : 修正版本号   
4. 可执行文件平台  
> * ```__ELF__``` : Linux 文件系统下面可执行文件的格式，按照 ELF 格式编写的文件有 .so  .a等   
> * ```__MACH__``` : Mach-0 是 IOS/MacOS 下的执行文件的格式  
> * ```__WIN32``` : windows 平台下 32 bits 或者 64bits 的目标文件格式 .exe .obj等
> * ```__wasm__``` : WebAssembly    
> * 如果上面这些都不是的话，那就说明你的编译器适用于其他的某种操作系统     

## 宏定义的一些说明   
1. ```##```   
```##``` 在预编译时期的使用用来连接两个宏定义。下面给其一个用法   
```C++
#define _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_X##_LIBCPP_Y
#define _LIBCPP_CONCAT(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y)

#ifndef _LIBCPP_ABI_NAMESPACE
# define _LIBCPP_ABI_NAMESPACE _LIBCPP_CONCAT(__,_LIBCPP_ABI_VERSION)
#endif
```   

## 编译器中一些类似函数的宏    
> __这一部分会在学习的过程中遇到新的在进行补充__
1. ```__has_feature()```   
> * ```__has_feature()```给定的参数特性被你的编译器和 C++ 标准库所支持的话，那么这个宏就会返回 1, 否则的话，就会返回 0   
```C++
#if defined(__has_feature(is_trivially_assignable))
template <class _Tp>	struct is_trivially_move_constructible   
    : public is_trivially_constructible<_Tp, typename add_rvalue_reference<_Tp>::value>
{};
```   
2. ```__has_builtin()```   
> * 这一个类函数的宏接受一个内建函数名称，内建伪函数的名称或者内建模板的名称。如果编译支持这些，则返回 1, 否则的话，返回 0   
```C++
#ifndef __has_builtin
    #define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_trap)
    __builtin_trap();
#else
    abort();
#endif
```     
3. ```__has_include()```   
> * 这个类函数宏接受一个头文件名字的字符串，如果这个头文件在包含路径中可以找到的话，那么就会返回 1 否则的话返回 0   
```C++
#if defined(__has_include)
#if __has_include("myinclude.h")
#include "myinclude.h"
#endif
#endif
```    

## 杂项     
1. ```#pragma GCC system_header```     
> * 从 ```#pragma GCC system_header``` 直到文件结束，之间的代码会被编译器视为系统头文件之中的代码，系统头文件中的代码往往不能完全的遵守```C```标准，所以头文件中的警告信息往往不显示<font color=#ff0000>(除非使用 ```#warning```)</font>显式的指明。    
> 

2. GNU C/C++ \_\_attribute\_\_ 用法      
> * GNUC的一大特色（却不被初学者所知）就是__attribute__机制。__attribute__可以设置函数属性（FunctionAttribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。   
> * \_\_attribute\_\_的语法格式为：   
>```C++
> __attribute__((attribute_list))
> ```
> * 其位置约束为位于声明的尾部， ' ; '的前面
> * \_\_attribute\_\_ 的三大属性        
> + 函数属性   
> 函数属性可以帮助开发者把一些特性添加到函数声明中，从而可以使编译器在错误检查方面的功能更强大。__attribute__机制也很容易同非GNU应用程序做到兼容之功效     
> 1. ```__attribute__ format```: 该__attribute__属性可以给被声明的函数加上类似printf或者scanf的特征，它可以使编译器检查函数声明和函数实际调用参数之间的格式化字符串是否匹配。该功能十分有用，尤其是处理一些很难发现的bug    
> ```__attribute__ (format(archetype, string_index, first-to-check))```       
> __format属性告诉编译器，按照printf, scanf, strftime或 strfmon 的参数表格式规则对该函数的参数进行检查。“archetype”指定是哪种风格；“string-index”指定传入函数的第几个参数是格式化字符串；“first-to-check”指定从函数的第几个参数开始按上述规则进行检查__     
```C++

extern void myprint(const char* format, ...) __attribute__((format(printf, 1, 2));

void test()
{
    myprint("i=%d\n",6);
    myprint("i=%s\n",6);
    myprint("i=%s\n","abc");
    myprint("%s,%d,%d\n",1,2);
}
```
运行 ```gcc –Wall –c attribute.c attribute```后，输出结果为：
```bash
attribute.c: In function `test':
attribute.c:7: warning: format argument is not a pointer (arg2)
attribute.c:9: warning: format argument is not a pointer (arg2)
attribute.c:9: warning: too few arguments forformat
```
> 2. ```__attribute__ noreturn``` : 该属性通知编译器函数从不返回值，当遇到类似函数需要返回值而却不可能运行到返回值处就已经退出来的情况，该属性可以避免出现错误信息

```C
extern void myexit();

int test(int n)
{
    if (n > 0)
    {
        myexit();
    }
    else
        return 0;
}
```
编译显示的输出信息为：
```bash
$gcc –Wall –c noreturn.c   
noreturn.c: In function `test':   
noreturn.c:12: warning: control reaches end of non-voidfunction
```
> + 变量属性     
> * 关键字__attribute__也可以对变量（variable）或结构体成员（structurefield）进行属性设置。    
> * 在使用__attribute__参数时，你也可以在参数的前后都加上“__”（两个下划线），例如，使用__aligned__而不是aligned，这样，你就可以在相应的头文件里使用它而不用关心头文件里是否有重名的宏定义      
> 1. ```aligned (alignment)``` : 该属性规定变量或结构体成员的最小的对齐格式，以字节为单位       
```C
int x __attribute__ ((aligned (16))) = 0;
/**
 * 编译器将以16字节（注意是字节byte不是位bit）对齐的方式分配一个变量
*/

struct foo { int x[2] __attribute__ ((aligned (8)));};
/**
 * 创建一个双字对齐的int对
*/

short array[3] __attribute__ ((aligned));
/**
 * 如上所述，你可以手动指定对齐的格式，同样，你也可以使用默认的对齐方式。如果aligned后面不紧跟一个指定的数字值，那么编译器将依据你的目标机器情况使用最大最有益的对齐方式
*/

union My_union
{
    unsigned char _data[3];
    struct __attribute__((__aligned__(8))) { } _align;
};
/*
    这个 union 只有三个 char 类型的数据，看似只占用了 3个字节的数据，但是使用 __aligned__
    强制将其扩充到 8 个字节，如果不指定这个 8 ,那么默认会扩展到 16 字节
*/

```       
> __Note: 更多的细节不在这里进行介绍了，具体的可以Google查阅相关的内容，\_\_attribute\_\_可以使用的参数类型有很多，在以后实际使用中碰到了再做添加__    


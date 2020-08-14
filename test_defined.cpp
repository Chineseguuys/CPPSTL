
#include <iostream>
#define out std::cout

int main()
{
    //out << _M_AMD64 << '\n';
    //out << __cplusplus << '\n';
    //out << __MINGW32__ << '\n';     // g++ gcc 
    //out << "__EXCEPTIONS\t" << __EXCEPTIONS << '\n';    // g++
    //out << "__clang_\t" << __clang__ << '\n';
    //out << "__GNUC__\t" << __GNUC__ << '\n';
    //out << "__GNUC_MINOR__\t"<< __GNUC_MINOR__ << '\n';
    //out << __GNUC_PATCHLEVEL__ << '\n';
    out << __STDC_HOSTED__ << '\n';
    return 0;
}
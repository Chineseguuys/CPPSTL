#include <iostream>


void test(const void* __key, size_t __len)
{
    const unsigned char* __data = static_cast<const unsigned char*>(__key);
    for (; __len > 4; __data += 4,  __len -= 4)
    {
        size_t __k = *(const size_t*)(__data);
        std::cout << __k << '\n';
    }
}


int main()
{
    union
    {
        unsigned long long __t;
        struct
        {
            size_t __a;
            size_t __b;
        };
    } __u;
    __u.__t = 1234567;
    test(&__u, sizeof(__u));
    return 0;
}
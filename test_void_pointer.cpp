#include <iostream>
#include <memory>
#include <type_traits>
#include <typeinfo>


int main()
{
    const std::type_info& res = typeid(std::allocator_traits<std::allocator<int> >::void_pointer);
    std::cout << res.name() << '\n';
    return 0;
}
// C++ program for illustration 
// of std::allocator() function 
#include <iostream> 
#include <memory> 

/**
 * stl 的 allocator 就是通过调用 operator new() 和 operator delete() 进行分配内存和释放内存的
 * 如果我们手动对 operator new() 进行了重载 添加了一个 stdout 的输出
 * operator delete() 没有进行重载
 */
/*
void* operator new(std::size_t sz)
{
	std::printf("global op new called, size = %zu\n", sz);
	void* ptr = std::malloc(sz);
	if(ptr)
		return ptr;
	else
		throw std::bad_alloc();
}
*/

//#define _ALLOCATOR_INT_
#define _ALLOCATOR_STRING_

#ifdef _ALLOCATOR_INT_

int main() 
{ 

	// allocator for integer values 
	std::allocator<int> myAllocator; 

	// allocate space for five ints 
	int* arr = myAllocator.allocate(5); 

	// construct arr[0] and arr[3] 
	myAllocator.construct(arr, 100); 
	arr[3] = 10; 
	std::cout<<std::oct<< arr <<std::dec<<std::endl;	//注意，在使用 std::oct 进行 8进制的显示之后，这种显示的格式在后面的所示的打印的程序当中都有效，如果希望在后面的打印中使用正常的 10进制的话，需要使用 std::dec 

	std::cout << arr[3] << std::endl; 
	std::cout << arr[0] << std::endl; 

	// deallocate space for five ints 
	myAllocator.deallocate(arr, 5); 

	return 0; 
} 

#endif

#ifdef _ALLOCATOR_STRING_

// C++ program for illustration 
// of std::allocator() function 
#include <iostream> 
#include <memory> 
#include <string> 

int main() 
{ 

	// allocator for integer values 
	std::allocator<std::string> myAllocator; 

	// allocate space for three strings 
	std::string* str = myAllocator.allocate(3); 

	// construct these 3 strings 
	myAllocator.construct(str, "Geeks"); 
	myAllocator.construct(str + 1, "for"); 
	myAllocator.construct(str + 2, "Geeks"); 

	std::cout << str[0] << str[1] << str[2]; 

	// destroy these 3 strings 
	myAllocator.destroy(str); 
	myAllocator.destroy(str + 1); 
	myAllocator.destroy(str + 2); 

	// deallocate space for 3 strings 
	myAllocator.deallocate(str, 3); 
} 

#endif

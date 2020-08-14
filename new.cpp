#ifndef _YJH_NEW
#define _YJH_NEW

#include "exception.cpp"


namespace yjh_def
{
class bad_alloc
	: public exception
{
public:
	bad_alloc() noexcept;
	virtual ~bad_alloc() noexcept;
	virtual const char* what() const noexcept;
};

class bad_array_new_length
	: public bad_alloc
{
public:
	bad_array_new_length() noexcept;
	virtual ~bad_array_new_length() noexcept;
	virtual const char* what() const noexcept;
};

void __throw_bad_alloc();

struct nothrow_t {};
extern const nothrow_t nothrow;
typedef void (*new_handler)();
new_handler set_new_handler(new_handler) noexcept;
new_handler get_new_handler() noexcept;

}

void* operator new(yjh_def::size_t __sz)
	throw(yjh_def::bad_alloc);

void* operator new(yjh_def::size_t, const yjh_def::nothrow_t&) noexcept;
void operator delete(void* __p) noexcept;
void operator delete(void* __p, const yjh_def::nothrow_t&) noexcept;

void* operator new[](yjh_def::size_t __sz)
	throw(yjh_def::bad_alloc);


void* operator new[](yjh_def::size_t __sz, const yjh_def::nothrow_t&) noexcept;
void operator delete[](void* __p) noexcept;
void operator delete[](void* __p, const yjh_def::nothrow_t&) noexcept;

inline void* operator new (yjh_def::size_t, void* __p) noexcept {return __p;}
inline void* operator new[](yjh_def::size_t, void* __p) noexcept {return __p;}
inline void operator delete (void*, void*) noexcept {}
inline void operator delete[] (void*, void*) noexcept {}


#endif
//#include <iostream>



#define _SELF_



#ifdef _SELF_

#include "memory.cpp"

int main()
{
	yjh_def::auto_ptr<int> int_ptr(new int(123));
	return 0;
}


#endif // _SELF

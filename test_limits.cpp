#include <iostream>
#include "limits.cpp"


int main(int argc, char* argv[])
{
	std::cout << yjh_def::numeric_limits<int>::digits << '\n';
	std::cout << yjh_def::numeric_limits<int>::digits10 << '\n';
	std::cout << yjh_def::numeric_limits<int>::min_exponent << '\n';
	return 0;
}
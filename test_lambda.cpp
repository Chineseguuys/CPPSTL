#include <iostream>



auto lambda_func(int __a, int __b) -> int { return __a * __b; }

auto lambda_func1 = [](int __a, int __b) -> int { return __a * __b; };

int main(int argc, char* argv[])
{
	std::cout << lambda_func(100, 12) << '\n';
	return 0;
}
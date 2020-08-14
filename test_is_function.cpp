#include <iostream>
#include <type_traits>

using namespace std;

double a_function_example(double floating_a, double floating_b)
{
	return floating_a + floating_b;
}

int main()
{
	cout<<boolalpha;
	cout<<is_function<int(int, double)>::value<<endl;
	return 0;
}
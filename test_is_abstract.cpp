#include <iostream>
#include <type_traits>

using namespace std;


class Abstract_A
{
	virtual void test() = 0;
};
class B
{
	private:
		int integer;
	public:
		B() : integer(100) {}
};

template <class _Tp>
char __test(_Tp (*value)[1])
{
	return 'a';
}

int main()
{
	int** integer_matrix = new int*[5];
	for(int index = 0; index < 5; ++index)
		integer_matrix[index] = new int[3];

	cout<<__test<int>(100)<<endl;

	for(int index = 0; index < 5; ++index)
		delete[] integer_matrix[index];
	delete[] integer_matrix;
	return 0;
}
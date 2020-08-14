#include <iostream>

using namespace std;

template <class _Tp>
struct data_storage
{
	public:
		void print() {cout<<"data_storage _Tp "<<endl;}
};

/**
 * 这里是上面的模板的一个偏特化的过程。
 * 值得注意的是，只有类的模板可以进行偏特化，模板函数是不可以进行偏特化的，只可以进行全特化处理
 */
template <class _Tp>
struct data_storage<_Tp*>
{
	public:
		void print(){cout<<"data_storage _Tp* "<<endl;}
};


int main(int argc, char** argv)
{
	data_storage<int*> object_data_storage1;
	data_storage<int> object_data_storage12;
	object_data_storage1.print();
	object_data_storage12.print();
	return 0;
}
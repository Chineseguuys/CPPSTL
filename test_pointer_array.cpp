#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	int integer_vec[5] = {1,11,111,1111,11111};
	int* iter = int*(integer_vec);
	cout<<*iter<<endl;
	cout<<*(iter + 1)<<endl;
	return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
#include <string>
 

#ifdef _MOVE_ITERATOR_
int main()
{
	std::vector<std::string> v{"this", "is", "an", "example"};
 
	std::cout << "Old contents of the vector: ";
	for (auto& s : v)
		std::cout << '"' << s << "\" ";
 
	typedef std::vector<std::string>::iterator iter_t;
	std::string concat = std::accumulate(
							 std::move_iterator<iter_t>(v.begin()),
							 std::move_iterator<iter_t>(v.end()),
							 std::string());  // 可用 std::make_move_iterator 简化
 
	std::cout << "\nConcatenated as string: " << concat << '\n'
			  << "New contents of the vector: ";
	for (auto& s : v)
		std::cout << '"' << s << "\" ";
	std::cout << '\n';

	return 0;
}

/**
Old contents of the vector: "this" "is" "an" "example"
Concatenated as string: thisisanexample
New contents of the vector: "" "" "" ""
*/

#endif

using namespace std;
int main(int argc, char** argv)
{
	int integer_num = 100;
	int&& integer_a = static_cast<int&&>(integer_num);
	int integer_b = std::move(integer_a);
	cout<<integer_num<<endl;
	cout<<integer_a<<endl;
	cout<<integer_b<<endl;
	return 0;
}
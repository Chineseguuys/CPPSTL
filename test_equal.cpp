#include "algorithm.cpp"
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> integer_vec1 {1,2,3,4,5};
    std::vector<int> integer_vec2 {1,2,3};
    std::cout << std::boolalpha;
    std::cout << yjh_def::equal(integer_vec1.begin(), integer_vec1.end(), integer_vec2.begin());
    return 0;
}
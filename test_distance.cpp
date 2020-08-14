#include <iostream>
#include <iterator>

using namespace std;


int main()
{
    int integer_vector[5] = {1,2,3,4,5};
    ptrdiff_t dist = distance(integer_vector, integer_vector + 3);
    cout<<"dist "<<dist<<endl; // result = 3
    return 0;
}
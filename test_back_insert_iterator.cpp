#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

#define _INSERT_

#ifdef _BACK_INSERT_
int main(int argc, char** argv)
{
    vector<int> integer_vec {1,2,3,4,5};
    back_insert_iterator<vector<int> > back_iter_integer_vec(integer_vec);
    back_iter_integer_vec = 6;
    back_iter_integer_vec = 7;
    for_each(integer_vec.begin(), integer_vec.end(), [](int& num)->void{cout<<num<<" ";});
    return 0;
}
#endif

#ifdef _INSERT_
int main(int argc, char** argv)
{
    vector<int> integer_vec {1,2,3,4,5};
    vector<int>::iterator iter = integer_vec.begin();
    iter += 3;
    insert_iterator<vector<int> > insert_iter_integer_vec(integer_vec, iter);
    for(int n : {1,2,3,4})
        insert_iter_integer_vec = 2*n + 10;
    for_each(integer_vec.begin(), integer_vec.end(), [](int& num)->void{cout<<num<<" ";});
    return 0;
}
#endif
#define _SELF_




#ifdef _SELF_
#include "tuple.cpp"
#include <stdio.h>
int main(int argc, char** argv)
{
    yjh_def::tuple<int, int, double> three_list(100,123, 3.1415f);
    int res = yjh_def::get<1>(three_list);
    printf("%d\n", res);
    return 0;
}


#endif
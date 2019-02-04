
#include <iostream>

#include "../SArray.h"



int main()
{
    SArray<unsigned> arr;

    for (unsigned i = 0; i < 1000000; ++i)
        arr.push_back(i);

    for (unsigned i = 0; i < 1000000; ++i)
        if (arr[i] != i)
            return 1;
    
    return 0;
}



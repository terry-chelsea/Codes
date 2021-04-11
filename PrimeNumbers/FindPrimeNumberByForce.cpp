#include "FindPrimeNumberByForce.h"
#include <cmath>
#include <iostream>

unsigned long long
FindPrimeNumberByForce::findPrimeNumberCount(unsigned long long start, unsigned long long end)
{
    int count = 0;
    auto cur = start > 1 ? start : 2;
    while (cur < end) {
        if (IsPrimeNumber(cur)){
            count ++;
        }
        ++ cur;
    }

    return count;
}

bool
FindPrimeNumberByForce::IsPrimeNumber(unsigned long long value)
{
//    auto sqrt_value = std::sqrt(value);
    for (unsigned long long i = 2; i * i <= value; ++ i)
    {
        if (value % i == 0)
            return false;
    }
    return true;
}
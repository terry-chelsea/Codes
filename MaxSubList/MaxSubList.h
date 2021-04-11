#include <tuple>

#ifndef __CPP_MaxSubList_H_
#define __CPP_MaxSubList_H_

using Func = bool(int);
// given a filter of elements, find the biggest subarray.
// find the start and end position.
class MaxSubList
{
    public:
        virtual std::tuple<int, int, int> MaxSum(int *input, int size, Func f) = 0;
};

#endif
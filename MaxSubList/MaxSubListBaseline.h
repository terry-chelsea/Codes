#include "MaxSubList.h"

#ifndef __CPP_MaxSubListBaseline_H_
#define __CPP_MaxSubListBaseline_H_

// baseline, in three level loop, find every possible range and compute sum of the range.
// find the biggest one.
class MaxSubListBaseline
{
    public:
        virtual std::tuple<int, int, int> MaxSum(int *input, int size, Func);
};

#endif

#include "MaxSubList.h"

#ifndef __CPP_MaxSubListByForce_H_
#define __CPP_MaxSubListByForce_H_

// find the result in two level of loop.
class MaxSubListByForce
{
    public:
        virtual std::tuple<int, int, int> MaxSum(int *input, int size, Func);
};

#endif
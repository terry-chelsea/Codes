#include "MaxSubList.h"
#include <tuple>

#ifndef __CPP_MaxSubListDP_H_
#define __CPP_MaxSubListDP_H_

class MaxSubListDP
{
    public:
        virtual std::tuple<int, int, int> MaxSum(int *input, int size, Func);
};

#endif
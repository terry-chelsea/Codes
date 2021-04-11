#include "MaxSubListBaseline.h"

std::tuple<int, int, int>
MaxSubListBaseline::MaxSum(int *input, int size, Func f)
{
    int max = 0, start = 0, end = 0;
    for (int i = 0; i < size; ++ i)
    {
        for (int j = i; j < size; ++ j)
        {
            bool satisfied = false;
            int sum = 0;
            for (int k = i; k <= j; ++ k)
            {
                satisfied |= f(input[k]);
                sum += input[k];
            }
            if (satisfied && sum > max) {
                max = sum;
                start = i;
                end = j;
            }
        }
    }

    return std::make_tuple<>(start, end, max);
}
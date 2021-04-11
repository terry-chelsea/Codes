#include "MaxSubListByForce.h"

std::tuple<int, int, int>
MaxSubListByForce::MaxSum(int *input, int size, Func f)
{
    int maxSum = 0;
    int start = 0, end = 0;
    // the first loop, keep the start value.
    for (int i = 0; i < size; ++ i) {
        int sum = 0;
        bool satisfied = false;
        // the second loop, compute the biggest subarray(from i to end) which contains the satisfied elements.
        // once one element satisfied, the subarray can be compared.
        for (int j = i; j < size; ++ j) {
            sum += input[j];
            satisfied |= f(input[j]);
            if (sum > maxSum && satisfied) {
                maxSum = sum;
                start = i;
                end = j;
            }
        }
    }

    return std::make_tuple<>(start, end, maxSum);
}
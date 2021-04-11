#include "MaxSubListDP.h"
#include <algorithm>

std::tuple<int, int, int>
MaxSubListDP::MaxSum(int *input, int size, Func f)
{
    int maxSum = 0, start = 0, end = 0;
    int startBefore = 0;    // the start elements of every valid subarray.
    int satisfiedStart = 0;    // the start elements of every valid subarray that contains satisfied elements.
    /**
     * keep the biggest sum of subarray which end with i
     * maxSumBefore[i] = std::max(maxSumBefore[i - 1] + input[i], input[i]);
     * do not need array because we can compare the biggest directly.
     */
    int maxSumBefore = 0;
    /**
     * keep the biggest sum of subarray which end with i and contains at least one satisfied elements.
     * maxSumSatisfiedBefore[i] = maxSumBefore[i]   if input[i] satisfied f.
     * maxSumSatisfiedBefore[i] = maxSumSatisfiedBefore[i - 1] + input[i]  if input[i] not satisfied and contains satisfied elements before i.
     * if input[i] not satisfied and no satisfied elements before, do nothing.
     */
    int maxSumSatisfiedBefore = 0;
    bool hasSatisfied = false;
    for (int i = 0; i < size; ++ i)
    {
        bool satisfied = f(input[i]);
        hasSatisfied |= satisfied;
        maxSumBefore = maxSumBefore + input[i];

        if (maxSumBefore < input[i]) {
            maxSumBefore = input[i];
            startBefore = i;
        }
        if (satisfied) {
            maxSumSatisfiedBefore = maxSumBefore;
            satisfiedStart = startBefore;
        } else if (hasSatisfied) {
            maxSumSatisfiedBefore = maxSumSatisfiedBefore + input[i];
        }

        if (maxSumSatisfiedBefore > maxSum) {
            maxSum = maxSumSatisfiedBefore;
            end = i;
            start = satisfiedStart;
        }
    }

    return std::make_tuple<>(start, end, maxSum);
}

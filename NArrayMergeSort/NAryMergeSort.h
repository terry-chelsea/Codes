#include <memory>

#ifndef __CPP_NAryMergeSort_H_
#define __CPP_NAryMergeSort_H_

// merge sort N arrays while it is sorted already.
class NAryMergeSort
{
    public:
        virtual std::shared_ptr<int> mergeSort(int* input[], int, int) = 0;
};

#endif

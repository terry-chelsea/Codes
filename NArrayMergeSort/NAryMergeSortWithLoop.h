#include "NAryMergeSort.h"

#ifndef __CPP_NAryMergeSortWithLoop_H_
#define __CPP_NAryMergeSortWithLoop_H_

// merge sort by find the biggest value in loop from an array..
class NAryMergeSortWithLoop : public NAryMergeSort
{
    public:
        virtual std::shared_ptr<int> mergeSort(int* input[], int m, int n);
};

#endif
#include "NAryMergeSort.h"

#ifndef __CPP_NAryMergeSortWithHeap_H_
#define __CPP_NAryMergeSortWithHeap_H_

// create a heap and pop + insert from the heap in order.
class NAryMergeSortWithHeap : public NAryMergeSort
{
    public:
        virtual std::shared_ptr<int> mergeSort(int* input[], int m, int n);
};

#endif
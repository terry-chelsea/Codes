#include "NAryMergeSort.h"

#ifndef __CPP_NAryMergeSortByForce_H_
#define __CPP_NAryMergeSortByForce_H_

// combine all numbers and do quick sort on the combined array.
class NAryMergeSortByForce : public NAryMergeSort
{
    public :
        virtual std::shared_ptr<int> mergeSort(int* input[], int m, int n);
};

#endif

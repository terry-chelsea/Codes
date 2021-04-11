#include "FindPrimeNumber.h"

#ifndef __CPP_FindPrimeNumberByMark_H_
#define __CPP_FindPrimeNumberByMark_H_

class FindPrimeNumberByMark : public FindPrimeNumber
{
    public:
        unsigned long long findPrimeNumberCount(unsigned long long start, unsigned long long end);

    private:
        bool getBit(int *bitmap, int pos);
        void setBit(int *bitmap, int pos);
};

#endif
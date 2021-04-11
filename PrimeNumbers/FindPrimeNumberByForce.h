#include "FindPrimeNumber.h"

#ifndef __CPP_FindPrimeNumberByForce_H_
#define __CPP_FindPrimeNumberByForce_H_

// find prime numbers by force, it is a N*N loop to find evert prime number.
class FindPrimeNumberByForce : public FindPrimeNumber
{
    public:
        unsigned long long findPrimeNumberCount(unsigned long long start, unsigned long long end);

    private:
        bool IsPrimeNumber(unsigned long long);
};

#endif
#include "FindPrimeNumberByMark.h"
#include <vector>
#include <iostream>

unsigned long long
FindPrimeNumberByMark::findPrimeNumberCount(unsigned long long start, unsigned long long end)
{
    int bitmap_size = (end >> 5) + 1;
    // bitmap store whether value of the index is a prime, 1 stand for non-prime. 
    auto bitmap = new int[bitmap_size];
    // store all prime numbers. it will be used to mark other non-prime number.
    std::vector<unsigned long long> primes;
    // initialize state, every bit is zero assume all numbers is not-prime.
    memset(bitmap, bitmap_size, 0);
    // init 2 and 3 is prime number. the init value is 00000011.
    bitmap[0] = 3;
    for (unsigned long long i = 2; i < end; ++ i)
    {
        auto isPrime = !getBit(bitmap, i);
        if (isPrime) {
            primes.push_back(i);
        }
        // for every number in prime code, multiply current number, the result is not a prime.
        for (auto primeValue : primes) {
            auto value = primeValue * i;
            if (value <= end) {
                setBit(bitmap, primeValue * i);  // mark non-prime numbers.
            } else {
                break;
            }
            if (i % primeValue == 0) break;  // avoid mark more than one time for one number.
        }
    }

    return primes.size();
}

bool
FindPrimeNumberByMark::getBit(int *bitmap, int pos)
{
    int bit = bitmap[pos / 32];
    return bit & (1 << (pos % 32));
}

void
FindPrimeNumberByMark::setBit(int *bitmap, int pos)
{
    int *bit = bitmap + (pos / 32);
    *bit |= (1 << (pos % 32));
}
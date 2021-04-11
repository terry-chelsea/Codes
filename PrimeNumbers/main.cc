#include <iostream>
#include "FindPrimeNumberByForce.h"
#include "FindPrimeNumberByMark.h"
using namespace std;

void runTest(std::shared_ptr<FindPrimeNumber> handler, unsigned long long start, unsigned long long end)
{
    auto count = handler->findPrimeNumberCount(start, end);
    std::cout << "There are " << count << " prime numbers between " << start << " and "<< end << std::endl;
}

int main(int argc, char* args[])
{
    runTest(std::make_shared<FindPrimeNumberByForce>(), 0, 47565632);

//    runTest(std::make_shared<FindPrimeNumberByMark>(), 0, 47565632);
    return 0;
}
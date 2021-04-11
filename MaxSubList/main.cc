#include "MaxSubListByForce.h"
#include "MaxSubListDP.h"
#include "MaxSubListBaseline.h"
#include <random>
#include <iostream>
#include <chrono>

bool test(int v)
{
    return v == 100;
}

bool TestCase(int size)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::default_random_engine e(start.time_since_epoch().count());
    int *input = new int[size];
    bool satisfied = false;
    for (int i = 0; i < size; )
    {
        int v = e() % 1000 - e() % 500;
        input[i++] = v;
    }
    auto byForce = std::make_shared<MaxSubListByForce>();
    auto byDp = std::make_shared<MaxSubListDP>();
    auto baseline = std::make_shared<MaxSubListBaseline>();

    auto byBase = baseline->MaxSum(input, size, test);
    auto byForceMax = byForce->MaxSum(input, size, test);
    auto byDpMax = byDp->MaxSum(input, size, test);

    std::cout << "[" << std::get<2>(byForceMax) << "," << std::get<2>(byDpMax) << "]" << std::endl;
    bool result = true;
    if (byDpMax != byForceMax) {
        std::cerr << "----------failed by compare baseline and force--------------" << std::endl;
        for (int i =0 ; i < size; ++ i) {
            std::cout << input[i] << ",";
        }
        std::cout << std::endl;
        std::cout << "ByForce  = [" << std::get<0>(byForceMax) << ", " << std::get<1>(byForceMax) << ", " << std::get<2>(byForceMax) 
                << "]" << std::endl;
        std::cout << "ByDP     = [" << std::get<0>(byDpMax) << ", " << std::get<1>(byDpMax) << ", " << std::get<2>(byDpMax) << "]"
                << std::endl;
        result = false;
    }

    delete[] input;
    return result;
}

int main(int argc, char *argv[])
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // int SIZE = 150;
    std::default_random_engine e(start.time_since_epoch().count());
    for (int i = 0; i < 50000; ++ i) {
        TestCase(e() % 10000 + 20);
    }
}
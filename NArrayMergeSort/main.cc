#include "NAryMergeSortByForce.h"
#include "NAryMergeSortWithHeap.h"
#include "NAryMergeSortWithLoop.h"
#include "Heap.h"
#include <random>
#include <iostream>
#include <vector>
#include <chrono>

class Test
{
    public:
    // Test()
    // {
    //     std::cout << "construct" << std::endl;
    // }

    // Test(const Test & t)
    // {
    //     std::cout << "copy construct" << std::endl;
    // }

    // Test(Test && t)
    // {
    //     std::cout << "move construct" << std::endl;
    // }

    // ~Test()
    // {
    //     std::cout << "destruct" << std::endl;
    // }

    virtual void run()
    {
        std::cout << "base run" << std::endl;
    }
};

class DeriveTest : public Test
{
    void run()
    {
        std::cout << "derive run" << std::endl;
    }
};

class DDeriveTest : public DeriveTest
{
    // virtual void run()
    // {
    //     std::cout << "derive derive run" << std::endl;
    // }
};

typedef void(*Func)(void);
void test_vector()
{
    Test t1;
    DeriveTest  t2;
    DDeriveTest t3;

    std::cout << "test size = " << sizeof(t1) << ", derive size = " << sizeof(t2) << ", dd size " << sizeof(t3) << std::endl;
//    tests.emplace_back(std::move(a));
    Func f = (Func) *((long *) *(long *) &t3);
    f();

}

std::shared_ptr<int>
run(std::shared_ptr<NAryMergeSort> sorter, int **input, int m, int n)
{
    std::chrono::steady_clock::time_point s1 = std::chrono::steady_clock::now();
    auto result = sorter->mergeSort(input, m, n);
    std::chrono::steady_clock::time_point f1 = std::chrono::steady_clock::now();
    auto gap1 = std::chrono::duration_cast<std::chrono::milliseconds>(f1 - s1).count();
    std::cout << "sort cost : " << gap1 << std::endl;

    // for (int i = 0; i < m * n; ++ i) {
    //     std::cout << result.get()[i] << ", ";
    // }
    // std::cout << std::endl;
    return result;
}

int main(int argc, char *argv[])
{
    std::default_random_engine e;
    const int M = 10;
    const int N = 900000;
//    test_vector();
    int** input = new int*[M];

    for (int i = 0; i < M; ++ i) {
        input[i] = new int[N];
        for (int j = 0; j < N; ++ j) {
            input[i][j] = e() % 1000000;
        }
        std::sort(input[i], input[i] + N, std::greater<int>());
    }

    auto loopSorter = std::make_shared<NAryMergeSortWithLoop>();
    auto result1 = run(loopSorter, input, M, N);

    auto heapSorter = std::make_shared<NAryMergeSortWithHeap>();
    auto result2 = run(heapSorter, input, M, N);

    auto quickSorter = std::make_shared<NAryMergeSortByForce>();
    auto result3 = run(quickSorter, input, M, N);

    for (int i = 0; i < M * N; ++ i)
    {
        int value1 = result1.get()[i];
        int value2 = result2.get()[i];
        int value3 = result3.get()[i];
        if (value1 != value2 || value1 != value3) {
            std::cout << "error" << std::endl;
            return -1;
        }
    }
}
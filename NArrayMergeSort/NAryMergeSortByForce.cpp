#include "NAryMergeSortByForce.h"
#include <algorithm>
#include <functional>

std::shared_ptr<int>
NAryMergeSortByForce::mergeSort(int* input[], int m, int n)
{
    std::shared_ptr<int> array(new int[m * n](), std::default_delete<int[]>());
    int *array_ptr = array.get();
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n ; ++ j) {
            array_ptr[i * n + j] = input[i][j];
        }
    }

    std::sort(array_ptr, array_ptr + m * n, std::greater<int>());

    return array;
}
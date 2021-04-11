#include "NAryMergeSortWithLoop.h"

// find index of the biggest value in the array, nexts[i] < 0 means array[i] is invalid.
// return -1 if no valid values in array.
int
findValue(int *array, int *nexts, int size)
{
    int i = 0;
    while(i < size && nexts[i] < 0) i ++;
    if (i == size) return -1;
    
    int pos = i++;
    for (; i < size; ++ i)
    {
        if (nexts[i] >= 0 && array[i] > array[pos]) {
            pos = i;
        }
    }

    return pos;
}

std::shared_ptr<int>
NAryMergeSortWithLoop::mergeSort(int **input, int m, int n)
{
    std::shared_ptr<int> array(new int[m * n](), std::default_delete<int[]>());
    int *array_ptr = array.get();
    int *sort_array = new int[m];    // store the values to compared, one value from one input array.
    int *nexts = new int[m];        // the next index of one array.
    for (int i = 0; i < m; ++ i)
    {
        sort_array[i] = input[i][0];
        nexts[i] = 0;
    }

    int count = 0;
    int index = 0;
    while ((index = findValue(sort_array, nexts, m)) >= 0)
    {
        array_ptr[count ++] = sort_array[index];
        nexts[index] ++;
        if (nexts[index] >= n) {
            nexts[index] = -1;
        } else {
            sort_array[index] = input[index][nexts[index]];
        }
    }

    delete[] sort_array;
    delete[] nexts;
    return array;
}

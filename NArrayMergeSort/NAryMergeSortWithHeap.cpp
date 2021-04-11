#include "NAryMergeSortWithHeap.h"
#include "Heap.h"

std::shared_ptr<int>
NAryMergeSortWithHeap::mergeSort(int **input, int m, int n)
{
    std::shared_ptr<int> array(new int[m * n](), std::default_delete<int[]>());
    int *array_ptr = array.get();
    Heap heap(m);
    for (int i = 0; i < m; ++ i)
    {
        Item item = {input[i][0], i, 0};
        heap.Insert(item);
    }

    int count = 0;
    Item&& result = heap.Pop();
    while (result.value > 0)
    {
        array_ptr[count ++] = result.value;
        int next = result.n + 1;
        while (next < n && input[result.m][next] == input[result.m][next - 1]) {
            array_ptr[count ++] = result.value;
            ++ next;
        }
        if (next < n) {
            Item tmp = {input[result.m][next], result.m, next};
            heap.Insert(tmp);
        }
        result = heap.Pop();
    }

    return array;
}

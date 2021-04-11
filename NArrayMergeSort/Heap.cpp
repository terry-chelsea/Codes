#include "Heap.h"
#include <iostream>

// from down to top, only case current node and its parent.
void
Heap::Adjust()
{
    int pos = size;
    while (pos > 0 && heap[pos].value > heap[(pos - 1) >> 1].value) {
        Item temp = heap[pos];
        heap[pos] = heap[(pos - 1) >> 1];
        heap[(pos - 1) >> 1] = temp;
        pos = (pos - 1) >> 1;
    }
}

// from top to down, only case the bigger child and the parent.
void
Heap::ReHeap()
{
    int pos = 0;
    while(true)
    {
        int leftPos = (pos << 1) + 1;
        int rightPos = (pos << 1) + 2;
        if (leftPos > size) break;
        int maxPos = (rightPos > size || heap[rightPos].value < heap[leftPos].value) ? leftPos : rightPos;        
        if (heap[maxPos].value > heap[pos].value) {
            Item temp = heap[pos];
            heap[pos] = heap[maxPos];
            heap[maxPos] = temp;
            pos = maxPos;
        } else {
            break;
        }
    }
}

Item
Heap::Pop()
{
    if (0 == size) {
        return {-1, -1};
    }

    Item value = heap[0];
    heap[0] = heap[size - 1];
    size --;
    ReHeap();

    return value;
}

bool
Heap::Insert(const Item& v)
{
    if (size == capacity)
    {
        std::cerr << "Heap is full, pop it first." << std::endl;
        return false;
    }

    heap[size] = v;
    Adjust();
    size ++;
    return true;
}

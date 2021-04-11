
#ifndef __CPP_Heap_H_
#define __CPP_Heap_H_

struct Item
{
    int value;
    int m;
    int n;
};

// TODO: implement it with a template class.
class Heap
{
    public:
        Heap(int n)
            :heap(new Item[n]),
            capacity(n),
            size(0)
        {
        }

        ~Heap()
        {
            delete[] heap;
        }

        Item Pop();

        bool Insert(const Item& v);

    private:
        Item *heap;
        int capacity;
        int size;

        // adjust the heap when a new value added to be tail.
        void Adjust();
        // adjust the heap when a value is moved from the head.
        void ReHeap();
};

#endif

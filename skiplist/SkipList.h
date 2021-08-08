#ifndef __TEST_SKIP_LIST_H_
#define __TEST_SKIP_LIST_H_

#include <algorithm>
#include <random>

class SkipList
{
    private:
        struct Node
        {
            int value;
            int count;
            int levels;
            Node **nexts;

            Node(int value, int levels);
            ~Node();
        };

        void FindLessThanNode(int value, Node **);
        int RandomHeight();

        Node *m_head;
        static const int MAX_LEVEL = 10;
        int m_size;
        int m_max_height;
        int m_max_random;

        std::uniform_int_distribution<unsigned> m_random_range;
        std::default_random_engine m_random_engine;
    public:
        SkipList();

        ~SkipList();

        bool Add(int value);

        bool Contains(int value);

        bool Remove(int value);

        void Print();

        bool Empty()
        {
            return m_head->nexts[0] == NULL;
        }

        int Size()
        {
            return m_size;
        }
};

#endif

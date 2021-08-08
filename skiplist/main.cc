#include <iostream>
#include <random>
#include <set>
#include <unordered_set>
#include <thread>
#include "SkipList.h"
#include "../task_monitor/TaskMonitor.h"

class RandomGenerator
{
    public :
        RandomGenerator(int start, int end)
            :m_random_range(start, end)
        {
            m_random_engine.seed(time(0));
        }

        int operator()()
        {
            return m_random_range(m_random_engine);
        }

    private:
        std::uniform_int_distribution<unsigned> m_random_range;
        std::default_random_engine m_random_engine;
};

void testSet(RandomGenerator random, int adds, int search, int deletes)
{
    int inserted = 0, existed = 0, deleted = 0;
    std::set<int> valueSet;
    for (int i = 0; i < adds; ++ i)
    {
        auto iter = valueSet.insert(random());
        inserted += (iter.second ? 1 : 0);
    }

    for (int i = 0 ; i < search; ++ i)
    {
        bool exists = valueSet.find(random()) != valueSet.end();
        existed += exists ? 1 : 0;
    }

    for (int i = 0 ; i < deletes; ++ i)
    {
        auto count = valueSet.erase(random());
        deleted += count;
    }

    std::cout << "Insert " << inserted << ", Find " << existed << ", Remove " << deleted << ", Last " << valueSet.size() << std::endl;
}

class TestSetTask : public Task
{
    public:
        void operator()()
        {
            RandomGenerator random(0, 1000000);
            testSet(random, 100000, 100000, 100000);
        }

        std::string toString()
        {
            return "test set operation";
        }
};

void testUnorderedSet(RandomGenerator random, int adds, int search, int deletes)
{
    int inserted = 0, existed = 0, deleted = 0;
    std::unordered_set<int> valueSet;
    for (int i = 0; i < adds; ++ i)
    {
        auto iter = valueSet.insert(random());
        inserted += (iter.second ? 1 : 0);
    }

    for (int i = 0 ; i < search; ++ i)
    {
        bool exists = valueSet.find(random()) != valueSet.end();
        existed += exists ? 1 : 0;
    }

    for (int i = 0 ; i < deletes; ++ i)
    {
        auto count = valueSet.erase(random());
        deleted += count;
    }

    std::cout << "Insert " << inserted << ", Find " << existed << ", Remove " << deleted << ", Last " << valueSet.size() << std::endl;
}

class TestUnorderedSetTask : public Task
{
    public:
        void operator()()
        {
            RandomGenerator random(0, 1000000);
            testUnorderedSet(random, 100000, 100000, 100000);
        }

        std::string toString()
        {
            return "test unordered set operation";
        }
};

void testSkipList(RandomGenerator random, int adds, int search, int deletes)
{
    int inserted = 0, existed = 0, deleted = 0;
    SkipList sl;
    for (int i = 0; i < adds; ++ i)
    {
        bool exists = sl.Add(random());
        inserted += exists ? 1 : 0;
    }


    for (int i = 0 ; i < search; ++ i)
    {
        bool exists = sl.Contains(random());
        existed += exists ? 1 : 0;
    }

    for (int i = 0 ; i < deletes; ++ i)
    {
        bool exists = sl.Remove(random());
        deleted += exists ? 1 : 0;
    }

    std::cout << "Insert " << inserted << ", Find " << existed << ", Remove " << deleted << ", Last " << sl.Size() << std::endl;
//    sl.Print();
}

class TestSkipListTask : public Task
{
    public:
        void operator()()
        {
            RandomGenerator random(0, 1000000);
            testSkipList(random, 100000, 100000, 100000);
        }

        std::string toString()
        {
            return "test skiplist operation";
        }
};

int main()
{

    RandomGenerator random(0, 1000000);
    std::vector<int> values;
    SkipList sl;
    for (int i = 0; i < 1000; ++ i)
    {
        int value = random();
        values.push_back(value);
        bool contains = sl.Add(value);
        // if (contains)
        // {
        //     std::cout << "Contains " << value << std::endl;
        // }
    }
//    sl.Print();

    for (auto iter = values.begin(); iter != values.end(); ++ iter)
    {
        bool contains = sl.Contains(*iter);
        if (!contains)
        {
            std::cout << "Not found : " << *iter << std::endl;
        }
    }

    for (int i = 0; i < 1000; ++ i)
    {
        int value = random();
        bool contains = sl.Remove(value);
        // if (!contains)
        // {
        //     std::cout << "Not Contains : " << value << std::endl;
        // }
    }

//    sl.Print();

    TestSetTask setTask;
    TestSkipListTask skiplistTask;
    TaskMonitor monitor_set(&setTask);
    monitor_set.Monitor();
//    std::this_thread::sleep_for(std::chrono::seconds(3));
    TaskMonitor monitor_skiplist(&skiplistTask);
    monitor_skiplist.Monitor();

    TestUnorderedSetTask unorderedSetTask;
    TaskMonitor monitor_unordered(&unorderedSetTask);
    monitor_unordered.Monitor();
    return 0;
}
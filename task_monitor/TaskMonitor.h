#ifndef __H_TASK_MONITOR_
#define __H_TASK_MONITOR_
#include <chrono>
#include <iostream>
#include <string>

class Task
{
    public:
        virtual void operator()() = 0;

        virtual std::string toString() = 0;
};

class TaskMonitor
{
    private:
        Task *m_task;

    public:
        TaskMonitor(Task *task)
            :m_task(task)
        {}

        void Monitor()
        {
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            (*m_task)();
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            auto cost = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Task " << m_task->toString() << ", cost " << cost << " millseconds" << std::endl;
        }
};

#endif
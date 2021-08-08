#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "../task_monitor/TaskMonitor.h"
#define TIMES 100000
#define WIDTH 16
std::random_device rd;

std::string random_string()
{
     std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

     std::mt19937 generator(rd());

     std::shuffle(str.begin(), str.end(), generator);

     return str.substr(0, WIDTH);
}

class CompareTextTask : public Task
{
    public:
        void operator()()
        {
            int equalsCount = 0;
            for (int i = 0; i < m_elements_.size(); ++ i)
            {
                for (int j = i; j < m_elements_.size(); ++ j)
                {
                    const std::string& value1 = m_elements_[i];
                    const std::string& value2 = m_elements_[j];
                    if (value1 == value2)
                    {
                        equalsCount ++;
                    }
                }
            }

            std::cout << "Equals count = " << equalsCount << std::endl;
        }

        std::string toString()
        {
            return "Compare Text";
        }

        const std::vector<std::string>& m_elements_;

        CompareTextTask(const std::vector<std::string>& elements)
        :m_elements_(elements)
        {}
};

class CompareTextWithCallback : public Task
{
    public:
        using Callback = std::function<bool (const std::string&, const std::string&)>;
        void operator()()
        {
            int equalsCount = 0;
            for (int i = 0; i < m_elements_.size(); ++ i)
            {
                for (int j = i; j < m_elements_.size(); ++ j)
                {
                    if (m_function_(m_elements_[i], m_elements_[j]))
                    {
                        equalsCount ++;
                    }
                }
            }

            std::cout << "Equals count = " << equalsCount << std::endl;
        }

        std::string toString()
        {
            return "Compare Text with callback";
        }

        std::vector<std::string> m_elements_;
        Callback m_function_;

        CompareTextWithCallback(const std::vector<std::string>& elements, Callback cb)
        :m_elements_(elements),
        m_function_(cb)
        {}
};

bool EqualsText(const std::string& first, const std::string& second)
{
    return first == second;
}

int main()
{
    std::vector<std::string> elements;
    elements.reserve(TIMES);
    for (int i = 0; i < TIMES; ++ i)
    {
        elements.push_back(std::move(random_string()));
    }

    CompareTextTask textCmp(elements);
    CompareTextWithCallback textCmpWithCb(elements, EqualsText);

    {
        TaskMonitor monitor1(&textCmp);
        monitor1.Monitor();
    }

    {
        TaskMonitor monitor2(&textCmpWithCb);
        monitor2.Monitor();
    }
}
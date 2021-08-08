#include <iostream>
#include <random>
#include "SkipList.h"

SkipList::Node::Node(int value, int levels)
{
    this->value = value;
    this->count = 1;
    this->levels = levels;
    this->nexts = new Node*[levels];
    memset(this->nexts, 0, sizeof(Node *) * levels);
}

SkipList::Node::~Node()
{
    delete[] this->nexts;
    levels = -1;
}

SkipList::SkipList()
    : m_max_height(MAX_LEVEL),
    m_max_random(4),
    m_random_range(0, m_max_random - 1)
{
    m_head = new Node(0, MAX_LEVEL);
    m_random_engine.seed(time(0));
    m_size = 0;
}

SkipList::~SkipList()
{
    Node *cur = m_head;
    Node *next = cur->nexts[0];
    while (next != NULL)
    {
        delete cur;
        cur = next;
        next = cur->nexts[0];
    }
    delete cur;
}

void
SkipList::FindLessThanNode(int value, Node **previous)
{
    int curLevel = MAX_LEVEL - 1;
    Node *cur = m_head;
    while (curLevel >= 0)
    {
        Node *next = cur->nexts[curLevel];
        if (next == NULL || next->value >= value)
        {
            previous[curLevel] = cur;
            curLevel --;
            continue;
        }
        cur = next;
    }
}

bool SkipList::Add(int value)
{
    Node *previous[MAX_LEVEL] = {NULL};
    FindLessThanNode(value, previous);
    // check exists.
    if (previous[0]->nexts[0] != NULL && value == previous[0]->nexts[0]->value)
    {
        previous[0]->nexts[0]->count ++;
        return false;
    }

    int level = RandomHeight();
    Node *node = new Node(value, level);
    for (int i = 0; i < level; ++ i)
    {
        Node *prev = previous[i];
        Node *next = prev->nexts[i];
        node->nexts[i] = next;
        prev->nexts[i] = node;
    }
    m_size ++;

    return true;
}

bool SkipList::Contains(int value)
{
    Node *previous[MAX_LEVEL] = {NULL};
    FindLessThanNode(value, previous);
    return (previous[0]->nexts[0] != NULL && value == previous[0]->nexts[0]->value);
}

bool SkipList::Remove(int value)
{
    Node *previous[MAX_LEVEL] = {NULL};
    FindLessThanNode(value, previous);
    if (previous[0]->nexts[0] == NULL || value != previous[0]->nexts[0]->value)
    {
        return false;
    }
    Node *node = previous[0]->nexts[0];

    for (int i = 0; i < node->levels; ++ i)
    {
        Node *next = node->nexts[i];
        previous[i]->nexts[i] = next;
    }
    m_size --;

    delete node;
    return true;
}

void SkipList::Print()
{
    for (int i = MAX_LEVEL - 1; i >= 0; -- i)
    {
        std::cout << "Level " << i << " : [";
        Node *head = m_head->nexts[i];
        Node *cur = head;
        int count = 0;
        while (cur != NULL)
        {
            // if (cur != head)
            // {
            //     std::cout << ", ";
            // }
            // std::cout << cur->value;
            cur = cur->nexts[i];
            ++ count;
        }
        std::cout << "]" << ", Size = " << count << std::endl;
    }
}

int SkipList::RandomHeight() {
  int height = 1;
  while (height < MAX_LEVEL && (m_random_range(m_random_engine) == 0))
  {
    height++;
  }
  assert(height > 0);
  return height;
}

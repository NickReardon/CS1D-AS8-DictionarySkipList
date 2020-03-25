/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #8	: Skip Lists
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 03 / 25 / 20
 *****************************************************************************/
#ifndef SKIPLIST_H
#define SKIPLIST_H 

#include <iostream>
#include <vector>
#include"Except.h"


template <typename NodeValue>
struct SkipNode
{
    int key;
    NodeValue value;

    std::vector<SkipNode*> next;

    SkipNode(int newKey, const NodeValue& newValue, int level) : key(newKey), value(newValue)
    {
        for (int i = 0; i < level; ++i)
        {
            next.emplace_back(nullptr);
        }
    }
};


template <typename value>
class SkipListTemplate
{
private:
    SkipNode* head;
    SkipNode* tail;

    float probability;
    int maxLevel;

    int randomLevel();

    int nodeLevel(const std::vector<SkipNode*>& value);

    SkipNode* makeNode(int newKey, NodeValue newValue, int level);


protected:


public:
    SkipList();
    ~SkipList();

    void print();

    SkipNode* find(int searchKey);

    void insert(int searchKey, const NodeValue& newValue);

    void erase(int searchKey);

};


#endif SKIPLIST_H

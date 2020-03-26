/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #8	: Skip Lists
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 03 / 25 / 20
 *****************************************************************************/
#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>


class SkipList
{

private:

	struct Node
	{
		int key;
		std::string value;

		std::vector<Node*> next;

		Node(int k, const std::string& v, int level) :
			key(k), value(v), next(level, nullptr)
		{
		}
	};

	Node* head;
	Node* tail;

	int currentSize;

	float probability;
	int maxLevel;


	int randomLevel() const
	{
		int newLevel = 1;
		while ( ( (double)std::rand() / RAND_MAX) < probability && (newLevel < maxLevel) )
		{
			newLevel++;
		}
		return newLevel;
	}


	static int nodeLevel(const Node* v)
	{
		return v->next.size();
	}


	static Node* makeNode(int key, std::string val, int level)
	{
		return new Node(key, val, level);
	}

	Node* lower_bound(int searchKey) const
	{
		Node* node = head;

		for (unsigned int i = nodeLevel(head); i-- > 0;)
		{
			while (node->next[i]->key < searchKey)
			{
				node = node->next[i];
			}
		}
		return node->next[0];
	}


	std::vector<SkipList::Node*> getPreviousNodes(int searchKey) const
	{
		std::vector<Node*> result(nodeLevel(head), nullptr);
		Node* node = head;

		for (unsigned int i = nodeLevel(head); i-- > 0;)
		{
			while (node->next[i]->key < searchKey)
			{
				node = node->next[i];
			}
			result[i] = node;
		}
		return result;
	}


protected:


public:
	SkipList(float newProbability = 0.5f, int newMaxLevel = 16)
	{
		probability = newProbability;
		maxLevel = newMaxLevel;

		std::srand(time(0));

		int headKey = std::numeric_limits<int>::min();
		head = new Node(headKey, "head", maxLevel);

		int tailKey = std::numeric_limits<int>::max();
		tail = new Node(tailKey, "tail", maxLevel);

		std::fill(head->next.begin(), head->next.end(), tail);
	}


	~SkipList()
	{
		Node* node = head;
		while (node->next[0])
		{
			Node* temp = node;
			node = node->next[0];
			delete temp;
		}
		delete node;
	}


	void print() const
	{


		Node* list = head->next[0];

		std::cout << "\n----------\n";
		std::cout << std::left;
		while (list != tail)
		{
			std::cout << "value: " << std::setw(20) << list->value
				<< "key: " << std::setw(10) << list->key
				<< "level: " << std::setw(10) << nodeLevel(list);

			for (int i = 0; i < nodeLevel(list); i++)
			{
				std::cout << "[]";
			}

			list = list->next[0];


			std::cout << "\n";
		}
		std::cout << "\n----------\n";

	}


	void printLevels() const
	{
		std::cout << "\n----------\n";

		Node* list;
		for (int i = maxLevel - 1; i >= 0; i--)
		{
			list = head->next[i];

			std::cout << "level: " << std::setw(10) << i << '\n';

			while (list != tail)
			{
				std::cout << std::string(10, ' ') << "value: " << std::setw(30) << list->value
					<< "key: " << std::setw(10) << list->key;

				list = list->next[i];


				std::cout << "\n";
			}
		}
		std::cout << "\n----------\n";
	}


	std::string* find(int searchKey) const
 	{
		std::string* result = nullptr;
		if (auto node = lower_bound(searchKey))
		{
			if (node->key == searchKey && node != tail)
			{
				result = &(node->value);
			}
		}
		return result;
	}



	void insert(int searchKey, const std::string& newValue)
	{
		std::vector<Node*> prevNodes = getPreviousNodes(searchKey);

		int newNodeLevel = randomLevel();
		Node* newNode = makeNode(searchKey, newValue, newNodeLevel);

		for (int i = 0; i < newNodeLevel; ++i)
		{
			newNode->next[i] = prevNodes[i]->next[i];
			prevNodes[i]->next[i] = newNode;
		}

		currentSize++;
	}


	void erase(int searchKey)
	{
		std::vector<Node*> prevNodes = getPreviousNodes(searchKey);

		Node* node = prevNodes[0]->next[0];
		if (node->key != searchKey || node == tail)
		{
			return;
		}

		for (size_t i = 0; i < nodeLevel(node); ++i)
		{
			prevNodes[i]->next[i] = node->next[i];
		}
		delete node;

		currentSize--;

	}


	bool empty() const
	{
		return (currentSize == 0);
	}


	int size() const
	{
		return currentSize;
	}


};





#endif // !_SKIPLIST_H_
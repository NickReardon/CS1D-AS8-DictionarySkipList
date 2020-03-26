/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #8	: Skip Lists
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 03 / 25 / 20
 *****************************************************************************/


#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include"Except.h"


class Skip_list {
public:
    Skip_list() :
        probability(0.5),
        maxLevel(16)
    {

        std::srand(time(0));

        int headKey = std::numeric_limits<int>::min();
        head = new Node(headKey, "head", maxLevel);

        int nilKey = std::numeric_limits<int>::max();
        tail = new Node(nilKey, "tail", maxLevel);

        std::fill(head->forward.begin(), head->forward.end(), tail);
    }
    ~Skip_list() {
        auto node = head;
        while (node->forward[0]) {
            auto tmp = node;
            node = node->forward[0];
            delete tmp;
        }
        delete node;
    }

    // non-modifying member functions

    /*
    It prints the key, value, level
    of each node of the skip list.

    Prints two nodes per line.
    */
    void print() const {


        Node* list = head->forward[0];

        std::cout << "{\n";
        std::cout << std::left;
        while (list != tail) 
        {
            std::cout << "value: " << std::setw(30) << list->value
                << "key: " << std::setw(10) << list->key
                << "level: " << std::setw(10) << nodeLevel(list);

            for (int i = 0; i < nodeLevel(list); i++)
            {
                std::cout << "[]";
            }

            list = list->forward[0];


            std::cout << "\n";
        }
        std::cout << "\n}\n";

    }

    /*
    It searches the skip list and
    returns the element corresponding
    to the searchKey; otherwise it returns
    failure, in the form of null pointer.
    */
    std::string* find(int searchKey) const {
        std::string* res{};
        if (auto x = lower_bound(searchKey)) {
            if (x->key == searchKey && x != tail) {
                res = &(x->value);
            }
        }
        return res;
    }

    // modifying member functions

    /*
    It searches the skip list for elements
    with seachKey, if there is an element
    with that key its value is reassigned to the
    newValue, otherwise it creates and splices
    a new node, of random level.
    */
    void insert(int searchKey, const std::string& newValue) 
    {
        auto preds = predecessors(searchKey);

        //{//reassign value if node exists and return
        //    auto next = preds[0]->forward[0];
        //    if (next->key == searchKey && next != tail) 
        //    {
        //        next->value = newValue;
        //        return;
        //    }
        //}

        // create new node
        const int newNodeLevel = randomLevel();
        auto newNodePtr = makeNode(searchKey, newValue, newNodeLevel);

        // connect pointers of predecessors and new node to respective successors
        for (int i = 0; i < newNodeLevel; ++i) {
            newNodePtr->forward[i] = preds[i]->forward[i];
            preds[i]->forward[i] = newNodePtr;
        }
    }
    /*
    It deletes the element containing
    searchKey, if it exists.
    */
    void erase(int searchKey) {
        auto preds = predecessors(searchKey);

        //check if the node exists
        auto node = preds[0]->forward[0];
        if (node->key != searchKey || node == tail) {
            return;
        }

        // update pointers and delete node 
        for (size_t i = 0; i < nodeLevel(node); ++i) {
            preds[i]->forward[i] = node->forward[i];
        }
        delete node;
    }

    bool empty() const
    {
        return (currentSize == 0);
    }

    bool size() const
    {
        return currentSize;
    }

private:

    struct Node {
        int key;
        std::string value;

        // pointers to successor nodes
        std::vector<Node*> forward;

        Node(int k, const std::string& v, int level) :
            key(k), value(v), forward(level, nullptr)
        {}
    };

    // Generates node levels in the range [1, maxLevel).    
    int randomLevel() const {
        int v = 1;
        while (((double)std::rand() / RAND_MAX) < probability &&
            v < maxLevel) {
            v++;
        }
        return v;
    }

    //Returns number of incoming and outgoing pointers
    static int nodeLevel(const Node* v) {
        return v->forward.size();
    }

    //creates a node on the heap and returns a pointer to it.   
    static Node* makeNode(int key, std::string val, int level) {
        return new Node(key, val, level);
    }
    // Returns the first node for which node->key < searchKey is false  
    Node* lower_bound(int searchKey) const {
        Node* x = head;

        for (unsigned int i = nodeLevel(head); i-- > 0;) {
            while (x->forward[i]->key < searchKey) {
                x = x->forward[i];
            }
        }
        return x->forward[0];
    }

    /*
    * Returns a collection of Pointers to Nodes
    * result[i] hold the last node of level i+1 for which result[i]->key < searchKey is true
    */
    std::vector<Skip_list::Node*> predecessors(int searchKey) const {
        std::vector<Node*> result(nodeLevel(head), nullptr);
        Node* x = head;

        for (unsigned int i = nodeLevel(head); i-- > 0;) {
            while (x->forward[i]->key < searchKey) {
                x = x->forward[i];
            }
            result[i] = x;
        }
        return result;
    }

    // data members 

    int currentSize;

    const float probability;
    const int maxLevel;
    Node* head; // pointer to first node
    Node* tail;  // last node
};






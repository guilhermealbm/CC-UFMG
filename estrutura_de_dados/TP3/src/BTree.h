#ifndef BTree_H
#define BTree_H

#include "node.h"
#include <iostream>

class BTree {
private:
    Node *_raiz;
public:
    BTree();
    ~BTree();
    void insert_cell(Cell cell);
    void printPreorder();
    char find_cell(std::string key);
};

#endif
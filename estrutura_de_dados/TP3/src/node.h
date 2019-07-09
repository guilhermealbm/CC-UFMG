#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

struct Cell{
    std::string key;
    char letter;
};

class Node {
private:
    Node *_left;
    Node *_right;
    Cell _cell;
public:
    Node();
    ~Node();
    void insert_cell(Cell cell, unsigned int index);
    char find_cell(std::string key, unsigned int index);
    void printPreorder(Node *node);
};

#endif

#include "BTree.h"
#include "node.h"

BTree::BTree(){
  this->_raiz = new Node();
}

BTree::~BTree(){
  if (this->_raiz != nullptr)
    delete this->_raiz;
}

void BTree::insert_cell(Cell cell){
  this->_raiz->insert_cell(cell, 0);
}

char BTree::find_cell(std::string key){
  return this->_raiz->find_cell(key, 0);
}

void BTree::printPreorder(){
  this->_raiz->printPreorder(this->_raiz);
}
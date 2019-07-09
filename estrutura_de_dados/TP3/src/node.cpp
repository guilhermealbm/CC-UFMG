#include "node.h"

Node::Node(){
  this->_cell = {" ", ' '}; //Cria node com célula vazia. Se necessário, a célulal será substituída no método insert_cell.
  this->_left = nullptr;
  this->_right = nullptr;
}

Node::~Node(){
  if (this->_left != nullptr)
    delete this->_left;
  if (this->_right != nullptr)
    delete this->_right;
}

void Node::insert_cell(Cell cell, unsigned int index){
  if(index == cell.key.size()){ //Se chegou até o nível correto na trie, atribui a célula correta ao node.
    this->_cell = cell;
    return;
  }
  
  /* Caminha para a esquerda se a posição do código for um '.' e para a direita se o caractere for '-' 
  Se o node ainda não existe, deve ser criado para que a célula seja inserida na posição correta.
  O método faz chamadas recursivas aumentando o valor do índice, ou seja, chama a si próprio 
  "descendo" na árvore até encontrar a posição correta para a célula
  */

  else if (cell.key[index] == '.'){
    if (this->_left == nullptr)
      this->_left = new Node();
    this->_left->insert_cell(cell, index+1);
  }else{
    if (this->_right == nullptr)
      this->_right = new Node();
    this->_right->insert_cell(cell, index+1);
  }
}

char Node::find_cell(std::string key, unsigned int index){
  if(index == key.size()) //Se chegou até o nível correto na trie, retorna a letra correspondente ao código em questão.
    return this->_cell.letter;
  else if(key[index] == '.') //Faz chamadas recursivar a fim de "descer" na árvore até encontrar o código buscado.
    return this->_left->find_cell(key, index+1);
  else
    return this->_right->find_cell(key, index+1);
}

void Node::printPreorder(Node *node){ 
  if (node == nullptr)
    return;

  if(node->_cell.letter != ' ')
    std::cout << node->_cell.letter << " " << node->_cell.key << std::endl; 
    
  printPreorder(node->_left);  
  printPreorder(node->_right); 
}
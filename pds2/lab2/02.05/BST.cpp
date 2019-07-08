#include "BST.h"
#include "node.h"


BST::BST(){
  this->_raiz = nullptr;
  this->_num_elementos_inseridos = 0;
}
BST::~BST(){
  if (this->_raiz != nullptr)
    delete this->_raiz;
}

void BST::inserir_elemento(int elemento){
  if (this->_raiz == nullptr) {
    this->_raiz = new Node(elemento);
    this->_num_elementos_inseridos++;
  } else if (!this->_raiz->existe_elemento(elemento)) {
    this->_raiz->inserir_elemento(elemento);
    this->_num_elementos_inseridos++;
  }
}

bool BST::existe_elemento(int elemento){
  if (this->_raiz == nullptr) {
    return false;
  }
  return this->_raiz->existe_elemento(elemento);
}

ListaEncadeada BST::pre_ordem(){
    
  ListaEncadeada lista;
  this->_raiz->pre_ordem_aux(lista); //metodo auxiliar
  return lista;
  
}

ListaEncadeada BST::em_ordem(){

  ListaEncadeada lista;
  this->_raiz->em_ordem_aux(lista); //metodo auxiliar
  return lista;

}

ListaEncadeada BST::pos_ordem(){
    
  ListaEncadeada lista;
  this->_raiz->pos_ordem_aux(lista); //metodo auxiliar
  return lista;

}

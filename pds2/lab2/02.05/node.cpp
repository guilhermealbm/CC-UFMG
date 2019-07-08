#include "node.h"
#include <iostream>

Node::Node(int valor){
  this->_elemento = valor;
  this->_esquerda = nullptr;
  this->_direita = nullptr;
}

Node::~Node(){
  if (this->_esquerda != nullptr)
    delete this->_esquerda;
  if (this->_direita != nullptr)
    delete this->_direita;
}

void Node::inserir_elemento(int elemento){
  if (elemento < this->_elemento) {
    if (this->_esquerda == nullptr) {
      this->_esquerda = new Node(elemento);
    } else {
      this->_esquerda->inserir_elemento(elemento);
    }
  } else if (elemento > this->_elemento) {
    if (this->_direita == nullptr) {
      this->_direita = new Node(elemento);
    } else {
      this->_direita->inserir_elemento(elemento);
    }
  }
}

bool Node::existe_elemento(int elemento){
  if (this->_elemento == elemento) {
   return true;
  } else if (elemento < this->_elemento) {
   if (this->_esquerda == nullptr) {
     return false;
   } else {
     return this->_esquerda->existe_elemento(elemento);
   }
  } else {
   if (this->_direita == nullptr) {
     return false;
   } else {
     return this->_direita->existe_elemento(elemento);
   }
 }
}

ListaEncadeada Node::pre_ordem(){
  ListaEncadeada lista;
  this->pre_ordem_aux(lista); //metodo auxiliar
  return lista;
}

void Node::pre_ordem_aux(ListaEncadeada &lista){
  lista.insere_elemento(this->_elemento);
  if (this->_esquerda!=nullptr) {
    this->_esquerda->pre_ordem_aux(lista);
  }
  if (this->_direita!=nullptr) {
    this->_direita->pre_ordem_aux(lista);
  }
}

ListaEncadeada Node::em_ordem(){
  ListaEncadeada lista;
  this->em_ordem_aux(lista); //metodo auxiliar
  return lista;
}

void Node::em_ordem_aux(ListaEncadeada &lista){
  if (this->_esquerda!=nullptr) {
    this->_esquerda->em_ordem_aux(lista);
  }
  lista.insere_elemento(this->_elemento);
  if (this->_direita!=nullptr) {
    this->_direita->em_ordem_aux(lista);
  }
}

ListaEncadeada Node::pos_ordem(){
  ListaEncadeada lista;
  this->pos_ordem_aux(lista); //metodo auxiliar
  return lista;
}


void Node::pos_ordem_aux(ListaEncadeada &lista){
  if (this->_esquerda!=nullptr) {
    this->_esquerda->pos_ordem_aux(lista);
  }
  if (this->_direita!=nullptr) {
    this->_direita->pos_ordem_aux(lista);
  }
  lista.insere_elemento(this->_elemento);
}

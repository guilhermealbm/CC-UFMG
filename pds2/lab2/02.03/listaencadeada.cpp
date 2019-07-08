#include "listaencadeada.h"
#include <iostream>

ListaEncadeada::ListaEncadeada() {
  this->_inicio = nullptr;
  this->_fim = nullptr;
  this->_num_elementos_inseridos = 0;
}

ListaEncadeada::~ListaEncadeada() {
  node_t *anterior = nullptr;
  node_t *proximo = this->_inicio;
  while (proximo != nullptr) {
    anterior = proximo;
    proximo = proximo->proximo;
    delete anterior;
  }
}

void ListaEncadeada::insere_elemento(int elemento) {
    node_t *novo = new node_t();
    novo->elemento = elemento;
    novo->proximo = nullptr;
    novo->anterior = nullptr;
    if (this->_inicio == nullptr) {
        this->_inicio = novo;
        this->_fim = novo;
    } else {
        this->_fim->proximo = novo;
        novo->anterior = this->_fim;
        this->_fim = novo;
    }
    this->_num_elementos_inseridos++;
}

void ListaEncadeada::insere_primeiro(int elemento) {
  node_t *novo = new node_t();
  novo->elemento = elemento;
  novo->proximo = this->_inicio;
  novo->anterior = nullptr;


    this->_inicio = novo;

  this->_num_elementos_inseridos++;
}

int ListaEncadeada::get_iesimo(int posicao){
    node_t *atual = this->_inicio;
    int i = 0;

    while (atual != nullptr){
        if(i == posicao){
            return (atual->elemento);
        }
        i++;
        atual = atual->proximo;
    }
    return -1; //Elemento não existe
}

void ListaEncadeada::remover_elemento() {
    node_t *atual = this->_fim;
    this->_fim = atual->anterior;
    this->_num_elementos_inseridos--;
}

void ListaEncadeada::remover_primeiro(){
    node_t *atual = this->_inicio;
    this->_inicio = atual->proximo;
    this->_num_elementos_inseridos--;
    delete atual;
}

void ListaEncadeada::remover_iesimo(int i) { //É capaz de remover, inclusive, o primeiro e o último elemento
  if (i >= this->_num_elementos_inseridos) {
    return;
  }
  node_t *atual = this->_inicio;
  for (int j = 0; j < i; j++)
    atual = atual->proximo;
  if (atual->proximo != nullptr)
    atual->proximo->anterior = atual->anterior;
  if (atual->anterior != nullptr)
    atual->anterior->proximo = atual->proximo;
  if (i == 0)
    this->_inicio = atual->proximo;
  if (i == this->_num_elementos_inseridos - 1)
    this->_fim = atual->anterior;
  this->_num_elementos_inseridos--;
  delete atual;
}

void ListaEncadeada::inserir_iesimo(int elemento, int posicao){
    if(posicao == 0){
        insere_primeiro(elemento);
        return;
    }else if(posicao == this->_num_elementos_inseridos-1){
        insere_elemento(elemento);
        return;
    }else{

        node_t *novo = new node_t();
        novo->elemento = elemento;
        novo->proximo = nullptr;
        novo->anterior = nullptr;

        node_t *atual = this->_inicio;
        for (int j = 0; j < posicao-1; j++)
            atual = atual->proximo;

        novo->anterior = atual;
        novo->proximo = atual->proximo;
        atual->proximo = novo;
        atual->proximo->anterior = novo;


        this->_num_elementos_inseridos++;
    }
}

int ListaEncadeada::tamanho(){
    return (this->_num_elementos_inseridos);
}

void ListaEncadeada::remove_consecutivos(){
    node_t *atual = this->_inicio;

    int i = 0;
    while (atual->proximo != nullptr) {
      this->imprimir();
      if (atual->elemento == atual->proximo->elemento) {
          this->remover_iesimo(i+1);
          i--;
      }else{
        atual = atual->proximo;
      }
      i++;
    }

}

int ListaEncadeada::k_esimo(bool direcao, int k){
  if (direcao) {
    node_t *atual = this->_inicio;
    for (int i = 0; i < k; i++) {
      atual = atual->proximo;
    }
    return atual->elemento;
  }else{
    node_t *atual = this->_fim;
    for (int i = k; i > 0; i--) {
      atual = atual->anterior;
    }
    return atual->elemento;
  }
}

void ListaEncadeada::imprimir() {
  node_t *atual = this->_inicio;
  while (atual != nullptr) {
    std::cout << atual->elemento << " ";
    atual = atual->proximo;
  }
  std::cout << std::endl;
}

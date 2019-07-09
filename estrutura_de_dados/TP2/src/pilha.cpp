#include "pilha.h"
#include <iostream>
#include <stdexcept>

Pilha::Pilha(int size): size(size) {
    this->vetor = new int[size];
    this->top = 0;
}

Pilha::~Pilha() {
    delete this->vetor;
}

int Pilha::nElements() {
    return this->top;
}

void Pilha::push(int element) {
    if (!(this->top == this->size)){
        this->vetor[this->top] = element;
        this->top++;
        return;
    }

    std::cout << "Erro. Pilha cheia." << std::endl;
}

int Pilha::pop() {
    if (!(this->top == 0)){
        this->top--;
        return this->vetor[this->top];
    }
    
    std::cout << "Erro. Pilha Vazia." << std::endl;
    return -1;
}
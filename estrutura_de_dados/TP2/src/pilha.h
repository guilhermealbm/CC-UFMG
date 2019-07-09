#ifndef PILHA_H
#define PILHA_H

//Implementa a estrutura de dados pilha.
//Sera usada para o QuickSort não recursivo.

class Pilha {
private:
    const int size;
    int* vetor;
    int top;

public:
    Pilha(int size); //Construtor
    ~Pilha(); //Destrutor
    void push(int element); //Insere elemento
    int pop(); //Remove elemento
    int nElements(); //Retorna o número de elementos da pilha
};

#endif
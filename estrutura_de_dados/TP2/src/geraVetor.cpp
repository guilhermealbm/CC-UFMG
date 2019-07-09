#include "geraVetor.h"
#include <cstdlib>

void GeraVetor::aleatorio(int* vetor, int n){
    for (int i = 0; i < n; i++)
        vetor[i] = rand() % n;
}

void GeraVetor::crescente(int* vetor, int n){
    for (int i = 0; i < n; i++)
        vetor[i] = i;
}

void GeraVetor::decrescente(int* vetor, int n){
    for (int i = n; i > 0; i--)
        vetor[n-i] = i;
}

int* GeraVetor::clonaVetor(int* vetor, int n){
    int* copy = new int[n];
    for (int i = 0; i < n; i++)
        copy[i] = vetor[i];

    return copy;
    
}
#ifndef GERAVETOR_H
#define GERAVETOR_H

class GeraVetor {
private:
    // Disallow creating an instance of this object
    GeraVetor(){};    
public:
    static void aleatorio(int* vetor, int n); //Gera vetor aleatório. Ex: [6, 4, 3, 5]
    static void crescente(int* vetor, int n); //Gera vetor crescente. Ex: [0, 1, 2, 3]
    static void decrescente(int* vetor, int n); //Gera vetor decrescente. Ex: [9, 8, 7, 6]
    static int* clonaVetor(int* vetor, int n); //Retorna o vetor passado como parâmetro (clona o vetor)
};

#endif
#include "quicksort.h"
#include "pilha.h"

//Implementa a versão não recusriva do QuickSort. As chamadas recursivas são trocadas pela utilização da estrutura de dados Pilha (stack)
stats QuickSort::naoRecursivo(int* vetor, int n){
    stats resultado = {0, 0};
    Pilha pilhaLeft(n);
    Pilha pilhaRight(n);
    int left = 0, right = n-1, i, j;

    //Empilha o primeiro e o ultimo elemento nas suas respectivas pilhas.
    pilhaLeft.push(0);
    pilhaRight.push(n-1);

    do{
        if(right > left){
            int pivo = vetor[(left + right) / 2];
            //Particiona o vetor
            QuickSort::particao(left, right, &i, &j, vetor, pivo, resultado);
            //Empilha analogamente às chamadas recursivas das outras implementações
            if((j-left)>(right-i)){
                pilhaLeft.push(left);
                pilhaRight.push(j);
                left=i;
            }else{
                pilhaLeft.push(i);
                pilhaRight.push(right);
                right=j;
            }
        //Desempilha se necessário
        }else{
            left = pilhaLeft.pop();
            right = pilhaRight.pop();
        }
    } while (!pilhaLeft.nElements() == 0);

    return resultado;
    
}
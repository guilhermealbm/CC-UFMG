#include "quicksort.h"
#include "iostream"

//Implementa o quicksort com inserção.
stats QuickSort::insercao(int* vetor, int left, int right, int cut){
    //Declara a struct resultado, que é responsável por armazenas numero de comparações e número de movimentações.
    stats resultado = {0, 0};
    int i = 0, j = 0;

    //Se a condição for satisfeita, o método chamado fará a comparação do restante do array pelo método inserção de ordenação.
    if (right - left + 1 <= cut){
        QuickSort::insere(vetor, left, right, resultado);
        return resultado;
    }

    //Obtem o pivo pelo método da mediana
    int pivo = medianaDeTres(vetor[left], vetor[(left + right) / 2], vetor[right], resultado);

    //Particiona o Vetor
    QuickSort::particao(left, right, &i, &j, vetor,pivo, resultado);
    //Chama recursivamente o próprio método, a depender do estado atual do vetor
    if (left < j) resultado += QuickSort::insercao(vetor, left, j, cut);
    if (right > i) resultado += QuickSort::insercao(vetor, i, right, cut);

    return resultado;

}

//Compara e insere os valores com base no insertion sort
void QuickSort::insere(int* vetor, int left, int right, stats& resultado){
    for (int i = left + 1; i <= right; i++) {
        int current = vetor[i];
        int j = i-1;
        
        while(j >= left) {
            resultado.comparisons++;
            //Encontra o índice correto e insere o elemento.
            if (vetor[j] > current) {
                resultado.moviments++;
                vetor[j + 1] = vetor[j];
                j--;
            } else break;
        }
        vetor[j + 1] = current;
        resultado.moviments++;
    }
}
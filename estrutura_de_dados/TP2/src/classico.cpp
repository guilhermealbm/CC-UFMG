#include "quicksort.h"

//Particiona o array em duas metades, a depender do pivo x escolhido.
void QuickSort::particao(int left, int right,int *i, int *j, int* vetor, int x, stats& resultado){
	int w;
	*i = left; *j = right;
	do{
        //Anda com o contador i da esquerda para a direita até o pivo
		while (x > vetor[*i]){(*i)++; resultado.comparisons++;}
        //Anda com o contador i da direita para a esquerda até o pivo
		while (x < vetor[*j]){(*j)--; resultado.comparisons++;}
        resultado.comparisons +=2; //Comparações que resultaram em false no while.
		if (*i <= *j){
            //Faz a troca (swap) afim de ordenar o vetor em questão.
			w = vetor[*i]; vetor[*i] = vetor[*j]; vetor[*j] = w;
            resultado.moviments += 3;
			(*i)++; (*j)--;
		}
	} while (*i <= *j);
}

//Calcula a mediana de três números quaisquer. Utilizado no QuickSort com pivo mediana de tres.
int QuickSort::medianaDeTres(int first, int middle, int last, stats& resultado){
    resultado.comparisons += 2;
    if (first >= middle) {
        if (last >= first) 
            return first;
        resultado.comparisons++;
        if (middle >= last) 
            return middle;

        return last;
    } else {
        if(last >= middle)
            return middle;
        resultado.comparisons++;
        if(first >= last)
            return first;

        return last;
    }
}

//Executa a variação mais eficiente, para a maior parte dos casos, do algoritmo de ordenação QuickSort
stats QuickSort::classico(int left, int right, int* vetor, TipoClassico tipo){
    int pivo;
    //Declara a struct resultado, que é responsável por armazenas numero de comparações e número de movimentações.
    stats resultado = {0, 0};
    //Escolhe de qual maneira o pivo deve ser encontrado, a depender dos parametros passados na CLI (Linha de comando)
    if(tipo == CLASSICO)
	    pivo = vetor[(left + right) / 2];
    else if(tipo == MEDIANA_DE_TRES)
        pivo = QuickSort::medianaDeTres(vetor[left], vetor[(left + right) / 2], vetor[right], resultado);
    else
        pivo = vetor[left];

    int i, j;
    //Particiona o vetor
	QuickSort::particao(left, right, &i, &j, vetor, pivo, resultado);
    //Chama recursivamente o próprio método, a depender do estado atual do vetor
	if (left < j) resultado += classico(left, j, vetor, tipo);
	if (i < right) resultado += classico(i, right, vetor, tipo);

    return resultado;

}
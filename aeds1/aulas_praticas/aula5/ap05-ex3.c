#include <stdio.h>

#define MAX 100

int main(){

	int tamanho, i;
	int vetor[MAX];
	printf("Entre com o tamanho do vetor\n");
	scanf("%d", &tamanho);

	for (i = 0; i < tamanho; ++i){
		printf("Entre com o valor a ser armazenado\n");
		scanf("%d", &vetor[i]);
	}

	for (i = tamanho-1; i >= 0; --i){
		printf("%d \n", vetor[i]);
	}

	return 0;
}
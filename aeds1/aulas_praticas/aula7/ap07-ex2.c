#include <stdio.h>

int main(){

	int n[10], i, posicao;
	int menor = 10000000;

	for (i = 0; i < 10; ++i){
		printf("Entre com o elemento %d do vetor \n", i+1);
		scanf("%d", &n[i]);
		if (n[i] < menor){
			menor = n[i];
			posicao = i+1;
		}
	}

	printf("O menor elemento do vetor está na posição %d e é o elemento %d \n", posicao, menor);

	return 0;
}
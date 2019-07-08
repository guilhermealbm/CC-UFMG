#include <stdio.h>

#define MAX_Linhas 12
#define MAX_Colunas 12

int main(){

	int matrizA[MAX_Linhas][MAX_Colunas], matrizB[MAX_Linhas][MAX_Colunas], matrizResult[MAX_Linhas][MAX_Colunas];

	int linhas, colunas, i, j;
	printf("Entre com o tamanho de linhas e de colunas da matriz\n");
	scanf("%d %d", &linhas, &colunas);

	for (i = 0; i < linhas; ++i){
		for (j = 0; j < colunas; ++j){
			printf("Entre com um valor para a posição da matriz A\n");
			scanf("%d", &matrizA[i][j]);
		}
		 
	}

	for (i = 0; i < linhas; ++i){
		for (j = 0; j < colunas; ++j){
			printf("Entre com um valor para a posição da matriz B\n");
			scanf("%d", &matrizB[i][j]);
		}
		 
	}

	for (i = 0; i < linhas; ++i){
		for (j = 0; j < colunas; ++j){
			matrizResult[i][j] =  matrizA[i][j] + matrizB[i][j];
			printf("%d ", matrizResult[i][j]);
		}
		printf("\n");
		 
	}


	return 0;
}
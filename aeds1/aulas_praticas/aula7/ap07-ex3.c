#include <stdio.h>
#include <stdlib.h>

#define LIN 10
#define COL 10
//LIN e COL devem ser iguais.

int main (){

	int mat[LIN][COL], i, j, somatorio = 0;
	float media;
	for (i = 0; i < LIN; ++i){
		for (j = 0; j < COL; ++j){
			printf("Entre com o valor da linha %d coluna %d \n", i+1, j+1);
			scanf("%d", &mat[i][j]);
			if (i == j){
				somatorio += mat[i][j];
			}
		}
	}
	media = somatorio/LIN;
	printf("A media da diagonal principal será de: %f \n", media);

	return 0;
}
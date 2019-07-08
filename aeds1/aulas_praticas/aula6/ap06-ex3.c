#include <stdio.h>

#define linhasA 2
#define colunasA 3
#define linhasB 3
#define colunasB 3

int main(){

	float a[linhasA][colunasA], b[linhasB][colunasB], c[linhasA][colunasB];

	if (colunasA != linhasB){
		printf("Impossível multiplicar as matrizes\n");
	}else{
		int i, j;
		for (i = 0; i < linhasA; ++i){
			for (j = 0; j < colunasA; ++j){
				printf("Digite o valor A[%d][%d] para a matriz A\n", i+1, j+1);
				scanf("%f", &a[i][j]);
			}
		}

		for (i = 0; i < linhasB; ++i){
			for (j = 0; j < colunasB; ++j){
				printf("Digite o valor B[%d][%d] para a matriz B\n", i+1, j+1);
				scanf("%f", &b[i][j]);
			}
		}

		int k;
		for (i = 0; i < linhasA; ++i){
			for (j = 0; j < colunasB; ++j){
				c[i][j] = 0;
				for (k = 0; k < colunasA; k++){ //ou linhas de B
					c[i][j] += a[i][k] * b[k][j];
				}
			}

		}

		for (i = 0; i < linhasA; ++i){
			for (j = 0; j < colunasB; ++j){
				printf("%f", c[i][j]);
			}
			printf("\n");
		}
	}



	return 0;
}
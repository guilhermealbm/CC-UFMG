#include <stdio.h>
#include <stdlib.h>

int ** leValores (int **mat, int linhas, int colunas){

	int i, j;
	for (i = 0; i < linhas; ++i){
		for (j = 0; j < colunas; ++j){
			printf("Entre com o valor da linha %d coluna %d \n", i+1, j+1);
			scanf("%d", &mat[i][j]);
		}
	}

	return mat;

}

int** alocaMatriz(int linhas, int colunas){

	int **mat, i;

	mat = (int**)malloc (linhas * sizeof (int*));
	for (i = 0; i < linhas; ++i){
		mat[i] = (int*) malloc (colunas * sizeof (int));
	}

	return mat;
}

void liberaMemoriaMat (int **mat, int linhas, int colunas){

	int i;

	for (i = 0; i < linhas; ++i){
		free(mat[i]);
	}

	free(mat);

}

int** multiplicaMatriz(int **a, int **b, int linhasA, int colunasB, int colunasA){

	int **c, i, j, k;

	c = alocaMatriz(linhasA, colunasB);

	for (i = 0; i < linhasA; ++i){
		for (j = 0; j < colunasB; ++j){
			c[i][j] = 0;
			for (k = 0; k < colunasA; k++){ //ou linhas de B
				c[i][j] += a[i][k] * b[k][j];
			}
		}

	}

	return c;
}

void imprimeMatriz (int **mat, int linhas, int colunas){
	int i, j;

	for (i = 0; i < linhas; ++i){
		for (j= 0; j < colunas; ++j){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}

}

int main(){

	int **result, **a, **b, i, j, k, linhasA, colunasA, linhasB, colunasB;

	printf("Entre com o numero de linhas de A, colunas de A, linhas de B e colunas de B, respectivamente\n");
	scanf("%d %d %d %d", &linhasA, &colunasA, &linhasB, &colunasB);

	if (colunasA != linhasB){
		printf("Impossível multiplicar matrizes\n");
	}else{
		a = alocaMatriz(linhasA, colunasA);
		b = alocaMatriz(linhasB, colunasB);

		a = leValores(a, linhasA, colunasA);
		b = leValores(b, linhasB, colunasB);

		result = multiplicaMatriz(a, b, linhasA, colunasB, colunasA);

		imprimeMatriz(a, linhasA, colunasA);
		printf("\n");
		imprimeMatriz(b, linhasB, colunasB);
		printf("\n");
		imprimeMatriz(result, linhasA, colunasB);


		liberaMemoriaMat(a, linhasA, colunasA);
		liberaMemoriaMat(b, linhasB, colunasB);
		liberaMemoriaMat(result, linhasA, colunasB);

	}

	return 0;
}
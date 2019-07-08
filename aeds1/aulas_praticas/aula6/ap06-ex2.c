#include <stdio.h>

#define N 3

void vetormatriz(double v[], double A[][N]){
	int i, j, total = 0;
	for (i = 0; i < N; ++i){
		for (j = 0; j < N; j++){
			A[i][j] = v[total];
			printf("%lf ", A[i][j]);
			total++;
		}
		printf("\n");
	}

}

int main(){

	double vetorNN[N*N], matrizN[N][N];
	int i;

	for (i = 0; i < N*N; ++i){
		scanf("%lf", &vetorNN[i]);
	}

	vetormatriz(vetorNN, matrizN);


	return 0;
}
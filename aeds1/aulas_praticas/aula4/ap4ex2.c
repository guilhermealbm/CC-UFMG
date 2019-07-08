#include <stdio.h>

int eImpar (int numero){
	if (numero % 2 == 0)
		return 0;
	else
		return 1;
}

int main (){

	int numeroMax, i;

	printf("Entre com o número final da sequência\n");
	scanf("%d", &numeroMax);
	int qteImp = 0;

	for (i = 1; i <= numeroMax; ++i){
		if (eImpar(i)){
			printf("%d ", i);
			qteImp++;
		}
		if (qteImp % 10 == 0)	
			printf("\n");
	}
	printf("\n");

	return 0;
}
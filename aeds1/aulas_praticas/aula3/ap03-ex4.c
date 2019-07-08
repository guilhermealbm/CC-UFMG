#include <stdio.h>

int MDC (int a, int b){

	while(b != 0){
		int restoAB = a % b;
		a = b;
		b = restoAB;
	}

	int resultadoMDC = a;

	return(resultadoMDC);

}

int main(){

	int a, b;
	char c;
	do{

		printf("Entre com o valor de A e o valor de B\n");
		scanf("%d %d", &a, &b);

		printf("O valor do MDC será: %d\n", MDC(a,b));

		printf("Continua? (S/N) ");
		fflush(stdin);
		__fpurge(stdin);
		c = getchar(); //getche no windows...
		printf("\n");

	}while ((c == 'S') || (c == 's')); 

}
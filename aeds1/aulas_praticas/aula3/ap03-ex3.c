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
	printf("Entre com o valor de A e o valor de B\n");
	scanf("%d %d", &a, &b);

	printf("O valor do MDC será: %d\n", MDC(a,b));

}
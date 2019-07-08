#include <stdio.h>

int main(){


	int a, b;
	printf("Entre com o valor de A e o valor de B\n");
	scanf("%d %d", &a, &b);

	while(b != 0){
		int restoAB = a % b;
		a = b;
		b = restoAB;
	}

	printf("O mdc será igual a: %d \n", a);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){


	int x;
	short int y;
	unsigned char a;

	//a) Usando a função potência (pow), calcule este maior valor para cada tipo e imprima em seguida

	x = pow(2, 31) -1;	
	y = pow(2, 15) -1;
	a = pow(2, 8) -1;

	printf("X = %d\n", x);
	printf("Y = %d\n", y);
	printf("A = %d\n", a);

	//b) Em seguida, você deverá somar 1 ao valor e novamente imprimir para ver o que acontece.

	x += 1;	
	y += 1;
	a += 1;

	printf("X = %d\n", x);
	printf("Y = %d\n", y);
	printf("A = %d\n", a);

	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	float a, b, c;
	printf("Entre com os valores de a, b e c\n");
	scanf("%f %f %f", &a, &b, &c);

	float delta = pow(b, 2) - 4 * a * c;

	/*Parte extra (futuramente): depois de implementado e testado, acrescente um teste condicional (if) que só calcula as raízes se o valor de delta for maior ou igual a zero. Caso contrário, imprima a mensagem “a equação não possui raízes reais”.*/

	if(delta < 0){
		printf("Não existem raízes reais \n");
	}else{
		float raiz1, raiz2;
		if(delta == 0){
			raiz1 = (-b + sqrt((pow(b,2))-4 * a * c))/2*a;
			printf("Raíz Única: %f\n",raiz1);
		}else{
			raiz1 = (-b + sqrt((pow(b,2))-4 * a * c))/2*a;
			printf("Raíz 1: %f\n",raiz1);
			raiz2 = (-b - sqrt((pow(b,2))-4 * a * c))/2*a;
			printf("Raíz 2: %f\n",raiz2);
		}
	}
	
	return 0;

}

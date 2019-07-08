#include <stdio.h>
#include <stdlib.h>

int main (){

	int ano;
	printf("Entre com o ano\n");
	scanf("%d", &ano);

	if (((ano % 100 != 0) && (ano % 4 == 0)) || (ano%400 == 0)){
		printf("O ano %d é bissexto\n", ano);
	}else{
	printf("O ano %d não é bissexto\n", ano);
	}

	return 0;
}
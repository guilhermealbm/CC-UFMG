#include <stdio.h>

int main (){


	int num=0;

	printf("Digite o número de linhas do triângulo de Floyd desejado.\n");

	int erro = 0;

	do{
		if (erro == 1)		{
			printf("Entrada inválida. Digite um número maior ou igual a 1.\n");
		}
		scanf("%d", &num);
		erro = 1;
	}while (num <1);

	int i;
	int j;
	int algTriang = 1;

	for (i = 0; i <= num; ++i){
		for (j = 0; j <= i; ++j){
			printf("%d ", algTriang);
			algTriang++;
		}
		printf("\n");
	}

	return 0;
}
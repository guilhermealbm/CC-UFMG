#include <stdio.h>

int main(){

	float vetorFloat[7];
	int i;

	for (i = 0; i < 7; ++i){
		printf("Entre com o valor\n");
		scanf("%f", &vetorFloat[i]);
	}

	for (i = 0; i < 7; ++i){
		printf("%f \n", vetorFloat[i]);
	}


	//Imprimirá os valores armazenados nos indices
	//0, 2, 4, 6
	for (i = 0; i < 7; i+=2){
		printf("%f \n", vetorFloat[i]);
	}


	return 0;
}
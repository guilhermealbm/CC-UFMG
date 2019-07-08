#include <stdio.h>

int main(){

	int i;
	int vetorInt[10];

	for (i = 0; i < 10; ++i){
		printf("Entre com o valor\n");
		scanf("%d", &vetorInt[i]);
	}
	for (i = 0; i < 10; ++i){
		printf("%d \n", vetorInt[i]);
	}

	return 0;
}
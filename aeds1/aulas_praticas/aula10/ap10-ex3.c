#include <stdio.h>

void calculaBinario (int x){
	if (x == 1 || x == 0){
		printf("%d", x);
		return;
	}else{
		calculaBinario(x/2);
		printf("%d", x%2);
	}
}

int main(){
	int valor;
	printf("Entre com o valor\n");
	scanf("%d", &valor);
	calculaBinario(valor);
	printf("\n");

	return 0;
}
#include <stdio.h>

void acker(int valor){

	if(valor == 1){
		printf("%d\n", valor);
		return;
	}else if (valor % 2 == 0){ //par
		printf("%d\n", valor);
		acker(valor/2);
	}else{ //impar
		printf("%d\n", valor);
		acker(3 * valor + 1);
	}

}

int main(){
	int valor;
	printf("Entre com o valor\n");
	scanf("%d", &valor);
	acker(valor);

	return 0;
}
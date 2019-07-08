#include <stdio.h>

float valorDiario (float valeAlimentacao, float transporte, float metrosquad){

	if (metrosquad<10){
		return (metrosquad*10  + valeAlimentacao + (transporte*2));
	}else if (metrosquad < 20){
		return (metrosquad*11.5  + valeAlimentacao + (transporte*2));
	}else{
		return (metrosquad*13  + valeAlimentacao + (transporte*2));
	}
}

int main (){

	float valeAlimentacao, transporte, metrosquad;
	int pedreiros = 0, i = 0;

	printf("Entre com a quantidade de pedreiros que deseja calcular o valor a ser pago\n");
	scanf("%d", &pedreiros);

	for (i = 0; i < pedreiros; ++i){

		printf("Entre com o valor do vale alimentação, do vale transporte e a quantidade de metros quadrados\n");
		scanf("%f %f %f", &valeAlimentacao, &transporte, &metrosquad);
		float valorPed = valorDiario(valeAlimentacao, transporte, metrosquad);
		printf("O pedreiro deve receber %f \n", valorPed);

	}

	return 0;
}
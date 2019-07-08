#include <stdio.h>
#include <stdlib.h>

int main (){

	float altura, peso;
	printf("Entre com o seu peso e a sua altura respectivamente\n");
	scanf("%f %f", &peso, &altura);

	float imc = (peso/(altura*altura));

	if(altura < 1 || peso < 30 || altura > 2.5 || peso > 300){ //Valores validos médios para a população incluindo crianças.
		printf("Impossível calcular IMC - valores inválidos\n");
		}else if (imc < 17){
			printf("Você tem IMC igual a %f, o que significa que está muito abaixo do peso\n", imc);
		}else if(imc >= 17 && imc < 18.5){
			printf("Você tem IMC igual a %f, o que significa que está abaixo do peso\n", imc);
		}else if(imc >=18.5 && imc < 25){
			printf("Você tem IMC igual a %f, o que significa que está com o peso normal\n", imc);
		}else if(imc >=25 && imc < 30){
			printf("Você tem IMC igual a %f, o que significa que está acima do peso\n", imc);
		}else if(imc >=30 && imc < 35){
			printf("Você tem IMC igual a %f, o que significa que está com obesidade I\n", imc);
		}else if(imc >=35 && imc < 40){
			printf("Você tem IMC igual a %f, o que significa que está com obesidade II (severa)\n", imc);
		}else{
			printf("Você tem IMC igual a %f, o que significa que está com obesidade III (mórbida)\n", imc);
		}


	return 0;
}
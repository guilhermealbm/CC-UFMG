#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	float d,p,s,t;

	/*
	d = 500; //deposito inicial
	//após o primeiro mês
	p = d + 0.01*d;
	//após o segundo mês
	s = p + 0.01*p;
	//após o terceiro mês
	t = s + 0.01*s; */

	// Qual será o valor da conta após três meses? 
	// R: 515,15

	//É possível refazer o programa usando apenas a variável d?
	//Sim, conforme feito abaixo:

	d = 500 * pow((1+0.01), 3); //formula de juros compostos
	printf("Valor da conta = %.2f\n", d);
	
	return 0;

}

#include <stdio.h>
#include <stdlib.h>

int main(){


	float nota1, nota2, nota3;
	int cred1, cred2, cred3;
	int valor1, valor2, valor3; //valor atribuido a cada conceito entre 0 e 5

	printf("Entre com o valor das 3 notas \n");
	scanf("%f %f %f", &nota1, &nota2, &nota3);

	printf("Entre com a quantidade de créditos de cada matéria\n");
	scanf("%d %d %d", &cred1, &cred2, &cred3);

	if (nota1 > 100 || nota1 < 0 || nota2 > 100 || nota2 < 0 || nota3 > 100 || nota3 < 0){
		printf("Impossível calcular o RSG. Valores de notas inválidos.\n");
	}else if (cred1 > 6 || cred1 < 2 || cred2 > 6 || cred2 < 2 || cred3 > 6 || cred3 <2){
		printf("Impossível calcular o RSG. Valores de créditos inválidos\n");
		}else{

			/*Existe um jeito mais elegante de se resolver esse problema, 
			utilizando estruturas de repeticao e vetores, contudo, 
			para treinar as estruturas condicionais na linguagem C, resolvi fazer da seguinte maneira: */

			//valor conceito da nota 1
			if (nota1 <= 100 && nota1 >= 90){
				valor1 = 5;
			}else if(nota1 < 90 && nota1 >= 80){
				valor1 = 4;
				}else if(nota1 < 80 && nota1 >= 70){
					valor1 = 3;
					}else if(nota1 < 70 && nota1 >= 60){
						valor1 = 2;
						}else if(nota1 < 60 && nota1 >= 40){
							valor1 = 1;
							}else{
								valor1 = 0;
							}

			//valor conceito da nota 2
			if (nota2 <= 100 && nota2 >= 90){
				valor2 = 5;
			}else if(nota2 < 90 && nota2 >= 80){
				valor2 = 4;
				}else if(nota2 < 80 && nota2 >= 70){
					valor2 = 3;
					}else if(nota2 < 70 && nota2 >= 60){
						valor2 = 2;
						}else if(nota2 < 60 && nota2 >= 40){
							valor2 = 1;
							}else{
								valor2 = 0;
							}

			//valor conceito da nota 3
			if (nota3 <= 100 && nota3 >= 90){
				valor3 = 5;
			}else if(nota3 < 90 && nota3 >= 80){
				valor3 = 4;
				}else if(nota3 < 80 && nota3 >= 70){
					valor3 = 3;
					}else if(nota3 < 70 && nota3 >= 60){
						valor3 = 2;
						}else if(nota3 < 60 && nota3 >= 40){
							valor3 = 1;
							}else{
								valor3 = 0;
							}

			//Fim da conversão de valores de notas para conceitos

			//Cálculo do RSG:
			float rsg = (valor3*cred3+valor2*cred2+valor1*cred1)/(cred3+cred2+cred1);
			char conceitorsg;

			//calculo do conceito do RSG

			if (rsg <= 5 && rsg > 4){
				conceitorsg = 'A';
			}else if(rsg <= 4 && rsg > 3){
				conceitorsg = 'B';
				}else if(rsg <= 3 && rsg > 2){
					conceitorsg = 'C';
					}else if(rsg <= 2 && rsg > 1){
						conceitorsg = 'D';
						}else if(rsg <= 1 && rsg > 0){
							conceitorsg = 'E';
							}else{
								conceitorsg = 'F';
							}

			printf("O valor do RSG é %f, que equivale a um conceito %c\n", rsg, conceitorsg);

		}
	
	return 0;
}
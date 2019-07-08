#include <stdio.h>
#include <stdlib.h>
#define TAM_VET 4


// declaracao do modelo data
struct data{
	int dia, mes, ano;
};


// declaracao do modelo funcionario
struct aluno{
	char nome[50];
	double mediaFinal;
	struct data nascimento;
};


int main(){
int i;
// declaracao e inicialização do vetor de estruturas vet

	struct aluno faculdade[TAM_VET];

	for (int i = 0; i < TAM_VET; ++i){

		printf("Nome:\n");
		gets(faculdade[i].nome);
		printf("Media Final:\n");
		scanf("%lf", &faculdade[i].mediaFinal);
		getchar(); // Limpa o buffer de teclado
		printf("Data de nascimento (separada por espacos)\n");
		scanf("%d %d %d", &faculdade[i].nascimento.dia, &faculdade[i].nascimento.mes, &faculdade[i].nascimento.ano);
		getchar(); // Limpa o buffer de teclado
		
	}

	puts("Imprimindo os dados.\n");
	for(i=0; i<TAM_VET; i++){

		puts(faculdade[i].nome);
		printf("Media Final: %.2f", faculdade[i].mediaFinal);
		printf("\n%d/%d/%d\n\n", faculdade[i].nascimento.dia,faculdade[i].nascimento.mes,faculdade[i].nascimento.ano );

	}
	return (0);
}
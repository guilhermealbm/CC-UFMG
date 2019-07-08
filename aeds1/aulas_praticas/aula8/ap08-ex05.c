#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pessoa{

	char nome[50];
	int idade;
	double peso;
	double altura;

}individuo;

int main (int argc, char *argv[]){

	individuo vetorCadastro[MAX];

	int nPessoas, i;

	printf("Quantas pessoas serão cadastradas?\n");
	scanf("%d", &nPessoas);

	for (i = 0; i < nPessoas; ++i){
		printf("Nome:\n");
		__fpurge (stdin);
		fgets(vetorCadastro[i].nome, 50, stdin);
		printf("Idade\n");
		scanf("%d", &vetorCadastro[i].idade);
		printf("Peso\n");
		scanf("%lf", &vetorCadastro[i].peso);
		printf("Altura\n");
		scanf("%lf", &vetorCadastro[i].altura);

	}

	for (i = 0; i < nPessoas; ++i){
		printf("\nNome: %s", vetorCadastro[i].nome);
		printf("Idade: %d\n", vetorCadastro[i].idade);
		printf("Peso: %lf\n", vetorCadastro[i].peso);
		printf("Altura: %lf\n", vetorCadastro[i].altura);
	}
}
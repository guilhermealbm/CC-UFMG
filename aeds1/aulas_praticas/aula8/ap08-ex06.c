#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pessoa{

	char nome[50];
	int idade;
	double peso;
	double altura;

}individuo;

individuo nova_pessoa(){

	individuo p;

	printf("Nome:\n");
	__fpurge (stdin);
	fgets(p.nome, 50, stdin);
	printf("Idade\n");
	scanf("%d", &p.idade);
	printf("Peso\n");
	scanf("%lf", &p.peso);
	printf("Altura\n");
	scanf("%lf", &p.altura);


	return p;
}

int main (int argc, char *argv[]){

	individuo vetorCadastro[MAX];

	int nPessoas, i;

	printf("Quantas pessoas serão cadastradas?\n");
	scanf("%d", &nPessoas);

	for (i = 0; i < nPessoas; ++i){
		vetorCadastro[i]=nova_pessoa();
	}

	for (i = 0; i < nPessoas; ++i){
		printf("\nNome: %s", vetorCadastro[i].nome);
		printf("Idade: %d\n", vetorCadastro[i].idade);
		printf("Peso: %lf\n", vetorCadastro[i].peso);
		printf("Altura: %lf\n", vetorCadastro[i].altura);
	}
}
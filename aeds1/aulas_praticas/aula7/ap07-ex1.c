#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, *vet, somatorio;
	printf("Entre com a quantidade de alunos\n");
	scanf("%d", &n);

	vet = (int *) malloc (n * sizeof(int));
	int i;
	float media;

	if (vet){
		for (i = 0; i < n; ++i){
			printf("Entre com a idade do aluno %d\n", i+1);
			scanf("%d", &vet[n]);
			somatorio += vet[n];
		}
		media = somatorio / n;
		printf("Média das idades: %f \n", media);
	}else{
		printf("Não foi possível alocar a memória solicitada\n");
	}

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h> // necessário para algumas operações com arquivos
#include <string.h> // necessário para strtok()
#include <ctype.h>

#define MAX 80 // maximo de caracteres a serem lidos

char opcao_menu(){
	system("clear");
	printf(" (L)istar notas\n");
	printf(" (I)nserir novo aluno\n");
	printf(" (F)im\n");
	printf("> ");
	return (toupper(getchar()));
}

void listar_notas(){
	int num,notas;
	float n1,n2,media;
	char *nome;
	char buf[MAX];
	FILE *arq;
	arq = fopen("dados.txt","r");

	if (arq == NULL){
		printf("Erro ao abrir arquivo\n");
		return;
	}

	printf("\n");
	printf("NUM | NOME | N1 | N2\n");
	printf("----+----------------------+------+------\n");
	notas = 0;
	media = 0;
	fgets(buf,MAX,arq);
	while (!feof(arq)){
		num = atoi(strtok(buf,","));
		nome = strtok(NULL,",");
		n1 = atof(strtok(NULL,","));
		n2 = atof(strtok(NULL,","));
		printf("%03d | %-20s | %4.1f |%4.1f\n",num,nome,n1,n2);
		notas = notas + 2;
		media = media + n1 + n2;
		fgets(buf,MAX,arq);
	}

	printf("----+----------------------+------+------\n");
	media = media/notas;
	printf("Media das notas = %4.1f\n",media);
	fclose(arq);
}

void novoAluno(){
	FILE *arq1;
	arq1 = fopen("dados.txt", "a");
	int numero;
	char nome[50];
	float nota, media;
	printf("Entre com o numero\n");
	scanf("%d", &numero);
	__fpurge(stdin);
	printf("Entre com o nome\n");
	fgets(nome, 50, stdin);
	printf("Entre com a nota\n");
	scanf("%f,", &nota);
	printf("Entre com a média\n");
	scanf("%f,", &media);
	nome[strlen(nome)-1] = '\0'; //gambs
	fprintf(arq1, "%d,%s,%f,%f\n", numero, nome, nota, media);
	fclose(arq1);

}

int main(int args, char * arg[]){
	char op;

	do{
		op = opcao_menu();
		if (op == 'L')
			listar_notas();
		if (op == 'I')
			novoAluno();
		printf("\n");
		__fpurge(stdin);
		getchar();
	}
	while (op != 'F');

	return 0;

}
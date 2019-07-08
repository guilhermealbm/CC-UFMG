#include <stdio.h>

#define LEN 50
#define CID 15
#define EST 3
#define TAM_CEP 10


struct endereco {
	char rua[LEN];
	char cidade[CID];
	char estado[EST];
	char cep[TAM_CEP];
};


struct endereco obtem_endereco(void){
	struct endereco ender;
	printf("\t Entre rua: ");
	gets(ender.rua);
	printf("\t Entre cidade: ");
	gets(ender.cidade);
	printf("\t Entre estado: ");
	gets(ender.estado);
	printf("\t Entre CEP: ");
	gets(ender.cep);
	return ender;
}


void imprime_endereco(struct endereco ender){
	printf("\t %s\n", ender.rua);
	printf("\t %s\n", ender.cidade);
	printf("\t %s\n", ender.estado);
	printf("\t %s\n", ender.cep);
}


void main(void){
	struct endereco residencia;
	printf("Entre seu endereco residencial:\n");
	residencia = obtem_endereco();
	printf("\nSeu endereco eh:\n");
	imprime_endereco(residencia);
}
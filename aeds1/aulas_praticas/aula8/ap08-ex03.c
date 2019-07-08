#include <stdio.h>
#include <string.h>

struct tipo_endereco{
	char rua [50];
	int numero;
	char bairro [20];
	char cidade [30];
	char sigla_estado [3];
	long int CEP;
};

struct ficha_pessoal{
	char nome [50];
	long int telefone;
	struct tipo_endereco endereco;
};

main (void){
	struct ficha_pessoal ficha;
	strcpy (ficha.nome,"Luiz Osvaldo Silva");
	ficha.telefone=4921234;
	strcpy (ficha.endereco.rua,"Rua das Flores");
	ficha.endereco.numero=10;
	strcpy (ficha.endereco.bairro,"Cidade Velha");
	strcpy (ficha.endereco.cidade,"Belo Horizonte");
	strcpy (ficha.endereco.sigla_estado,"MG");
	ficha.endereco.CEP=31340230;
	/* INSIRA AQUI AS LINHAS PARA IMPRIMIR O QUE FOI COPIADO PARA A STRUCT FICHA PESSOAL */

	printf("Nome: %s\n", ficha.nome);
	printf("Telefone: %li\n", ficha.telefone);
	printf("Rua: %s\n", ficha.endereco.rua);
	printf("Número: %d\n", ficha.endereco.numero);
	printf("Bairro: %s\n", ficha.endereco.bairro);
	printf("Cidade: %s\n", ficha.endereco.cidade);
	printf("Estado: %s\n", ficha.endereco.sigla_estado);



	/* FIM DA AREA DE IMPRESSAO */
	return 0;
}
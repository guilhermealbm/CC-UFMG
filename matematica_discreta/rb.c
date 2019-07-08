/*

TP - Matemática Discreta - 2018/1 
Aluno: Guilherme de Abreu Lima Buitrago Miranda
Matrícula: 2018054788
Relações Binárias

*/

#include <stdio.h>
#include <stdlib.h>

/*

Algumas funções para facilitar o trabalho com matrizes dinâmicas.
Como as relações binárias do TP formam apenas matrizes quadradas, nenhuma função pede as colunas da matriz como parâmetro

*/

int** alocaMatriz(int linhas){

	int **mat, i;

	mat = (int**)calloc (linhas, sizeof (int*));
	for (i = 0; i < linhas; ++i){
		mat[i] = (int*) calloc (linhas, sizeof (int));
	}

	return mat;
}

void liberaMemoriaMat (int **mat, int linhas){

	int i;

	for (i = 0; i < linhas; ++i){
		free(mat[i]);
	}

	free(mat);

}

int* leElementos (int *nElementos){
	int i, *vet;

	scanf("%d", &*nElementos);

	vet = (int*)calloc(*nElementos, sizeof(int));

	for (i = 0; i < *nElementos; ++i)
		scanf("%d", &vet[i]);

    return vet;
}

int** lePares (int nElementos, int *vet){

	int i;

	int **mat = alocaMatriz(nElementos);
	int origem, destino, linha, coluna;

	//marcador de final de arquivo = EOF

	while (scanf("%d %d", &origem, &destino) != EOF){

			for (i = 0; i < nElementos; ++i){
				if (vet[i] == origem)
					linha = i;
				if (vet[i] == destino)
					coluna = i;

			}
			mat[linha][coluna] = 1;
	}

	return mat;

}

void reflexividade (int *reflexiva, int *irreflexiva, int **mat, int nElementos, int *vetElementos){

	int *faltantesReflex = NULL, *faltantesIrreflex = NULL, i, tamanhoVetReflex = 0, tamanhoVetIrreflex = 0;

	//reflexiva = Toda diagonal principal = 1
	//irreflexiva = Toda diagonal principal = 0

	for (i = 0; i < nElementos; ++i){
		if (mat[i][i] != 1){
			*reflexiva = 0;


			faltantesReflex = (int*)realloc(faltantesReflex, (tamanhoVetReflex+1)*sizeof(int));
			faltantesReflex[tamanhoVetReflex] = vetElementos[i]; //adiciona o elemento faltante para que a relação seja T
			tamanhoVetReflex += 1;

		}else{ //mat[i][i] != 0
			*irreflexiva = 0;

			faltantesIrreflex = (int*) realloc(faltantesIrreflex, (tamanhoVetIrreflex+1)*sizeof(int));
			faltantesIrreflex[tamanhoVetIrreflex] = vetElementos[i];
			tamanhoVetIrreflex += 1;
		}
	}

	if (*reflexiva){
		printf("1. Reflexiva: V\n");
	}else{
		printf("1. Reflexiva: F\n   ");
		for (i = 0; i < tamanhoVetReflex; ++i){
			printf("(%d,%d); ", faltantesReflex[i], faltantesReflex[i]);
		}
		printf("\n");
	}

	if (*irreflexiva){
		printf("2. Irreflexiva: V\n");
	}else{
		printf("2. Irreflexiva: F\n   ");
		for (i = 0; i < tamanhoVetIrreflex; ++i){
			printf("(%d,%d); ", faltantesIrreflex[i], faltantesIrreflex[i]);
		}
		printf("\n");
	}


}

void simetria (int *simetrica, int *anti_simetrica, int **mat, int nElementos, int *vetElementos){

	int *faltantesSimetrica = NULL, *faltantesAnti = NULL, i, j, tamanhoVetSim = 0, tamanhoVetAnti = 0;

	for (i = 0; i < nElementos; ++i){
		for (j = 0; j < i; ++j){ //j < i analisa apenas parte acima da diagonal principal

			if (mat[i][j] == 1 && mat[j][i] == 0){
				*simetrica = 0;

				faltantesSimetrica = (int*)realloc(faltantesSimetrica, (tamanhoVetSim+2)*sizeof(int));
				faltantesSimetrica[tamanhoVetSim] = vetElementos[j];
				faltantesSimetrica[tamanhoVetSim+1] = vetElementos[i];
				tamanhoVetSim += 2;

			}

			if (mat[j][i] == 1 && mat[i][j] == 0){

				*simetrica = 0;

				faltantesSimetrica = (int*)realloc(faltantesSimetrica, (tamanhoVetSim+2)*sizeof(int));
				faltantesSimetrica[tamanhoVetSim] = vetElementos[i];
				faltantesSimetrica[tamanhoVetSim+1] = vetElementos[j];
				tamanhoVetSim += 2;

			}

			if (mat[i][j] == 1 && mat[j][i] == 1){
				*anti_simetrica = 0;

				faltantesAnti = (int*)realloc(faltantesAnti, (tamanhoVetAnti+2)*sizeof(int));
				faltantesAnti[tamanhoVetAnti] = vetElementos[i];
				faltantesAnti[tamanhoVetAnti+1] = vetElementos[j];
				tamanhoVetAnti += 2;

			}

		}
	}

	if(*simetrica){
		printf("3. Simetrica: V\n");
	}else{
		printf("3. Simetrica: F\n   ");
		for (i = 0; i < tamanhoVetSim; i += 2){
			printf("(%d,%d); ", faltantesSimetrica[i], faltantesSimetrica[i+1]);
		}
		printf("\n");
	}

	if (*anti_simetrica){
		printf("4. Anti-simetrica: V\n");
	}else{
		printf("4. Anti-simetrica: F\n   ");
		for (i = 0; i < tamanhoVetAnti; i += 2){
			printf("(%d,%d) e (%d, %d); ", faltantesAnti[i], faltantesAnti[i+1], faltantesAnti[i+1], faltantesAnti[i]);
		}
		printf("\n");
	}

}

int** transitividade (int *transitivo, int **mat, int nElementos, int *vetElementos){

	//Solução inspirada no algoritmo de Floyd-Warshall

	int** matTrans = alocaMatriz(nElementos);

	int i, j, k, *faltantesTrans = NULL, tamanhoVetTrans = 0;

	//clonando matriz
	for (i = 0; i < nElementos; ++i){
		for (j = 0; j < nElementos; j++){
			matTrans[i][j] = mat[i][j];
		}
	}


	for (i = 0; i < nElementos; ++i){
		for (j = 0; j < nElementos; ++j){
			for (k = 0; k < nElementos; ++k){
				if (matTrans[j][i] == 1 && matTrans[i][k] == 1 && matTrans[j][k] == 0){
					*transitivo = 0;
					matTrans[j][k] = 1;

					faltantesTrans = (int*)realloc(faltantesTrans, (tamanhoVetTrans+3)*sizeof(int));
					faltantesTrans[tamanhoVetTrans] = vetElementos[i];
					faltantesTrans[tamanhoVetTrans+1] = vetElementos[j];
					faltantesTrans[tamanhoVetTrans+2] = vetElementos[k];
					tamanhoVetTrans += 3;

				}
			}
		}
	}

	if (*transitivo){
		printf("6. Transitiva: V\n");
	}else{
		printf("6. Transitiva: F\n   ");
		for (i = 0; i < tamanhoVetTrans; i += 3){
			printf("(%d,%d); ", faltantesTrans[i+1], faltantesTrans[i+2]);
		}
		printf("\n");
	}

	return matTrans;
}

void fechoReflexivo (int nElementos, int *vetElementos, int **mat){

	int i, j;
	printf("Fecho reflexivo da relacao = {");

	for (i = 0; i < nElementos; ++i){
		for (j = 0; j < nElementos; ++j){
			if (mat[i][j] == 1){
				printf("(%d, %d); ", vetElementos[i], vetElementos[j]);
			}else{
				if (i == j){	
					printf("(%d, %d); ", vetElementos[i], vetElementos[i]);
				}
			}
		}
	}

	printf("}\n");

}

void fechoSimetrico (int nElementos, int *vetElementos, int **mat){

	int i, j;

	printf("Fecho simetrico da relacao = {");
	for (i = 0; i < nElementos; ++i){
		for (j = 0; j < nElementos; ++j){

			if (mat[i][j] == 1){
				printf("(%d, %d); ", vetElementos[i], vetElementos[j]);
				if(mat[j][i] == 0){
					printf("(%d, %d); ", vetElementos[j], vetElementos[i]);
				}
			}

		}
	}

	printf("}\n");

}

void fechoTransitivo(int nElementos, int *vetElementos, int **mat){

	int i, j;

	printf("Fecho transitivo da relacao = {");
	for (i = 0; i < nElementos; ++i){
		for (j = 0; j < nElementos; ++j){

			if (mat[i][j] == 1){
				printf("(%d, %d); ", vetElementos[i], vetElementos[j]);
			}

		}
	}

	printf("}\n");

}


int main(){

	int i, nElementos = 0;

	int *vet = leElementos(&nElementos);
	int **matId = lePares(nElementos, vet);

	printf("Propriedades\n");

	int reflexiva = 1, irreflexiva = 1; //reflexiva e irreflexiva por default
	reflexividade(&reflexiva, &irreflexiva, matId, nElementos, vet);

	int simetrica = 1, anti_simetrica = 1;
	simetria(&simetrica, &anti_simetrica, matId, nElementos, vet);

	if (irreflexiva && anti_simetrica){
		printf("5. Assimetrica: V\n");
	}else{
		printf("5. Assimetrica: F\n");
	}

	int transitivo = 1;
	int **matTrans = transitividade (&transitivo, matId, nElementos, vet);

	//Uma relação R é uma relação de equivalência se e somente se R é reflexiva, simétrica e transitiva.

	if (reflexiva && simetrica && transitivo)
		printf("Relacao de equivalencia: V\n");
	else
		printf("Relacao de equivalencia: F\n");
	

	//Uma relação R é uma relação de ordem parcial se e somente se R é reflexiva, anti-simétrica e transitiva.

	if (reflexiva && anti_simetrica && transitivo)
		printf("Relacao de ordem parcial: V\n");
	else
		printf("Relacao de ordem parcial: F\n");

	if(!reflexiva)
		fechoReflexivo(nElementos, vet, matId);

	if (!simetrica)
		fechoSimetrico(nElementos, vet, matId);

	if(!transitivo)
		fechoTransitivo(nElementos, vet, matTrans);

	

	liberaMemoriaMat(matId, nElementos);
	liberaMemoriaMat(matTrans, nElementos);


	return 0;
}
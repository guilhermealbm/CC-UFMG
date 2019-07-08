#include <stdio.h>

int aprovadoFrequencia (int qteAulas, int qtePresenca){

		if (qtePresenca < (qteAulas * 0.75))
			return 0;
		else
			return 1;

}

char conceito (int nota){
	if (nota >= 90){
		return 'A';
	}else if (nota >= 80){
		return 'B';
	}else if (nota >= 70){
		return 'C';
	}else if (nota >= 60){
		return 'D';
	}else if (nota >= 40){
		return 'E';
	}else{
		return 'F';
	}
}

int main(){

	int numeroDisc, i;

	printf("Entre com o número de disciplinas que o aluno cursou\n");
	scanf("%d", &numeroDisc);

	for (i = 1; i <= numeroDisc; ++i){

		int numeroAulas, numeroPresenca;
		float nota;
		printf("Entre com o número de aulas lecionadas, o númeo de presença e a nota do aluno\n");
		scanf("%d %d %f", &numeroAulas, &numeroPresenca, &nota);

		if (aprovadoFrequencia(numeroAulas, numeroPresenca)){
			if (nota >= 60){
				printf("O aluno foi aprovado na disciplina %d com conceito %c \n", i, conceito(nota));
			}else{
				printf("O aluno foi reprovado na disciplina %d com conceito %c \n", i, conceito(nota));
			}
		}else{
			printf("O aluno foi reprovado por frequência, seu conceito é I (infrequente)\n");
		}

	}

	return 0;
}
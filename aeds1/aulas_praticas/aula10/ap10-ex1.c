#include <stdio.h>

void pgeo(float inicial, float razao, int numeroTermos){

	if (!numeroTermos)
		return;
	else{
		printf("%f\n", inicial);
		pgeo(inicial * razao, razao, numeroTermos-1);
	}

}

int main(){
	float inicial, razao;
	int numeroTermos;
	printf("Entre com o termo inicial, a razão da PG e o número de termos a serem gerados respectivamente\n");
	scanf("%f %f %d", &inicial, &razao, &numeroTermos);
	pgeo(inicial, razao, numeroTermos);
	return 0;
}
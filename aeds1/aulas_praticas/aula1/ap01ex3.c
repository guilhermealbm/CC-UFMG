#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){


	int a, b, c;
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);
	float s = (a + b + c)/2;

	printf("Área = %f\n", sqrt(s * (s - a) * (s - b) * (s -c)));

	return 0;

}

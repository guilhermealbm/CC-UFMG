#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	float a = 1.5, e = 1.2, f = 4.3, v1, v2, v3;
	int  b = 4, c = 2, d = 3;

	v1 = (a*(c+d))/(b*(e+f));
	v2 = (pow(a, (b+c))/(e+f)) +d;
	v3 = (-b + sqrt((pow(b,2))-4 * a * c))/2*a;

	printf("V1 = %f\n",v1);
	printf("V2 = %f\n",v2);
	printf("V3 = %f\n",v3);
	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float bigger(float vet[])
{
	float bigger = vet[0];

	for(int i=1; i<10; i++)
	{
		if(vet[i] > bigger)
			bigger = vet[i];
	}

	return bigger;
}

float smaller(float vet[])
{
	float smaller = vet[0];

	for(int i=1; i<10; i++)
	{
		if(vet[i] < smaller)
			smaller = vet[i];
	}

	return smaller;
}


int main()
{
	float vet[10];

	/* generate values */
	for(int i=0; i<10; i++)
		vet[i] = i;


	printf("Bigger: %f\n", bigger(vet));
	printf("Smaller: %f\n", smaller(vet));

	return 0;
}
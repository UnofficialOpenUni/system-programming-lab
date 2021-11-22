#include <stdio.h>
#include "data.h"

main()
{
	printf("\nCelsius - Fahrenheit rates:\n");

	int fahr=LOWER;
	float celsius;
	
	printf("\n-----------------------------");
	printf("\n%8s \t %11s\n", "Celsius:", "Fahrenheit:");
	for (; fahr<=UPPER; fahr+=STEP)
	{
		celsius = (5.0/9.0)*(fahr-32);
		printf("%7.1f \t %11d\n", celsius, fahr);
	}
	printf("-----------------------------\n\n");
}

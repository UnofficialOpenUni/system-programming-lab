#include <stdio.h>
#include "data.h"

/*
main: prints a table of temperture conversions of fahrenheit to celsius going 
from 300 down to 0.
*/
main ()
{
	int fahr;
	float celsius;
	
	printf("\n%11s \t %8s\n", "Fahrenheit:", "Celsius:");
	printf("\n--------------------------\n");
	for (fahr=UPPER; fahr>=0; fahr-=STEP)
	{
		celsius = 5.0/9.0*(fahr-32);
		printf("%11d \t %7.1f\n", fahr, celsius);
	}
	printf("--------------------------\n");
	
	return 0;
}

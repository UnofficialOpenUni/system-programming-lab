#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP 20

float convertToCel(int fahr);

int main (void)
{
	int fahr;
	
	printf("\n%11s\t%8s\n", "Fahrenheit:", "Celsius:");
	printf("----------------------------\n");
	for (fahr=LOWER; fahr<=UPPER; fahr+=STEP)
		printf("%11d\t%7.1f\n", fahr, convertToCel(fahr));
	printf("----------------------------\n");
	
	return 0;
}

float convertToCel(int fahr)
{
	return (5.0/9.0 * (fahr-32));
}

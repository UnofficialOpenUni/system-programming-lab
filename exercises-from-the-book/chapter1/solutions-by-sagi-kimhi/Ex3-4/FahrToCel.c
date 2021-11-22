#include <stdio.h>
#include "data.h"

/*
The main method which prints a table of all the values from 0-300 fahrenheits
in celsius
*/
main()
{
	printf("\nFahrenheit - Celsius rates:\n");
	printf("---------------------------\n");

	int fahr=LOWER;
	float celsius;
	printf("\n%11s \t %8s\n", "Fharenheit:", "Celsius:");
	while (fahr<=UPPER)
	{
		celsius = (5.0/9.0)*(fahr-32);
		printf("%11d \t %7.1f\n", fahr, celsius);
		fahr += STEP;
	}
	printf("---------------------------\n\n");
}

/*
This method uses a formula to convert the fahrenheits given as 
parameter to return its rate in celsius.
@param fahr The fharenheits to convert to celsius
@return A float representing the rate of the given fahrenhites in celsius
*/
/*
float toCelsius(float fahr)
{
	return ((5.0/9.0)*(fahr-32.0));
}


This method uses a formula to convert the celsius rate given as 
parameter to farenheits.
@param celsius The celsius rate to convert to fahrenheits
@return An int representing the given celsius rate in fahrenheits

int toFahr(float celsius)
{
	return ((int)(9.0 * celsius / 5.0 + 32));
}
*/

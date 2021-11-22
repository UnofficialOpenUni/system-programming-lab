#include <stdio.h>

unsigned short bitcount(unsigned x);

int main(void)
{
	
	unsigned x, expected, actual;
	
	printf("\nTest #1 of function bitcount(x):\n---------------------------------------\n");
	x = 0x3b8289af;
	expected = 16;
	actual = bitcount(x);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
		
		
	printf("\nTest #2 of function bitcount(x):\n---------------------------------------\n");
	x = 0x15a;
	expected = 5;
	actual = bitcount(x);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
	
	
	printf("\nTest #3 of function bitcount(x):\n---------------------------------------\n");
	x = 0x211289f;
	expected = 11;
	actual = bitcount(x);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
		
		
	printf("\nTest #4 of function bitcount(x):\n---------------------------------------\n");
	x = 0x1;
	expected = 1;
	actual = bitcount(x);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
		
		
	printf("\nTest #5 of function bitcount(x):\n---------------------------------------\n");
	x = 0x2;
	expected = 1;
	actual = bitcount(x);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
		
		
	printf("\nTest #6 of function bitcount(x):\n---------------------------------------\n");
	x = 0;
	expected = 0;
	actual = bitcount(x);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
	
	

	return 0;
}

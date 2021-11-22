#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);

int main(void)
{
	
	unsigned x, y, expected, actual;
	int p, n;
	
	printf("\nTesting function setbits(x, p, n, y):\n---------------------------------------\n");
	x = 0xd79d;
	y = 0xd712;
	p = 12;
	n = 5;
	expected = 0xd91d;
	actual = setbits(x, p, n, y);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
		
		
	printf("\nTesting function invert(x, p, n):\n---------------------------------------\n");
	x = 0xd79d;
	p=10;
	n=6;
	expected = 0xd46d;
	actual = invert(x, p, n);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
	
	
	printf("\nTesting function rightrot(x, n):\n---------------------------------------\n");
	x = 0xc144d79d;
	n=7;
	expected = 0x3b8289af;
	actual = rightrot(x, n);
	if (actual==expected)
		printf("Success!\nExpected: %u\nActual: %u\nGGs mate!\n\n", expected, actual);
	else
		printf("Fail!\nExpected: %u\nActual: %u\nbig oof... :(\n\n", expected, actual);
	
	
	
	
	return 0;
}



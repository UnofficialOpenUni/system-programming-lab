#include <stdio.h>
#include "data.h"

int htoi(char s[]);

int main (void)
{
	char test1[] = "0x89";
	char test2[] = "0X6E2";
	char test3[] = "0x6e2";
	char test4[] = "0X17A0F6";
	char test5[] = "0x17a0f6";
	char test6[] = "0XPPPPPP";
	char test7[] = "0xphlphp";
	char test8[] = "0X17a0f6";
	
	printf("\n***test1*** \nshould be: %d \nactual: %d\n", 0x89, htoi(test1));
	printf("\n***test2*** \nshould be: %d \nactual: %d\n", 0X6E2, htoi(test2));
	printf("\n***test3*** \nshould be: %d \nactual: %d\n", 0x6e2, htoi(test3));
	printf("\n***test4*** \nshould be: %d \nactual: %d\n", 0X17A0F6, htoi(test4));
	printf("\n***test5*** \nshould be: %d \nactual: %d\n", 0x17a0f6, htoi(test5));
	printf("\n***test6*** \nshould be: %d \nactual: %d\n", 0, htoi(test6));
	printf("\n***test7*** \nshould be: %d \nactual: %d\n", 0, htoi(test7));
	printf("\n***test8*** \nshould be: %d \nactual: %d\n", 0x1706, htoi(test8));
	
	return 0;
}



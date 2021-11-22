#include <stdio.h>
#define LENGTH 1200
#define LENGTH2 130
#define LENGTH3 127
#define LENGTH4 1015

int main(void)
{
	int i;
	
	for (i=0; i<(LENGTH); ++i)
		printf("l");
	printf("\n");
	for (i=0; i<(LENGTH2); ++i)
		printf("a");
	printf("\n");
	for (i=0; i<(LENGTH3); ++i)
		printf("b");
	printf("\n");
	for (i=0; i<(LENGTH4); ++i)
		printf("c");
	printf("\n");
	
	return 0;
}

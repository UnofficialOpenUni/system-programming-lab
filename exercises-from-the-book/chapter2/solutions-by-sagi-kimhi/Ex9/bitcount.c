#include <stdio.h>

unsigned short bitcount(unsigned x)
{
	short i;
	for (i=0; x!=0; i++)
		x &= x-1;
	
	return i;
}

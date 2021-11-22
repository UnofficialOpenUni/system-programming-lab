#include <stdio.h>
#include <float.h>
#include <limits.h>


int main (void)
{
	
	printf("\n");
	printf("Signed char: [%d to %d]\n", ~((unsigned char)~0>>1), (unsigned char)~0>>1);
	printf("Unsgined char: [0 to %u]\n", (unsigned char)~0);
	
	printf("Signed short: [%d to %d]\n", ~((unsigned short)~0>>1), (unsigned short)~0>>1);
	printf("Unsgined short: [0 to %u]\n", (unsigned short)~0);
	
	printf("Signed int: [%d to %d]\n", ~((unsigned int)~0>>1), (unsigned int)~0>>1);
	printf("Unsgined int: [0 to %u]\n", (unsigned int)~0);
	
	printf("Signed long: [%ld to %ld]\n", ~((unsigned long)~0>>1), (unsigned long)~0>>1);
	printf("Unsgined long: [0 to %lu]\n", (unsigned long)~0);
	
    printf("Float[%g to %g]\n", FLT_MIN, FLT_MAX);

    printf("Double[%g to %g]\n", DBL_MIN, DBL_MAX);

    return 0;
}

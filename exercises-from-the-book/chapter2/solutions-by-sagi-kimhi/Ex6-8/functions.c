#include <stdio.h>

#define UNSIGNED_BITS bitsInUnsigned()

unsigned short bitsInUnsigned(void);
unsigned setbits(unsigned x, int p, int n, unsigned y);

unsigned short bitsInUnsigned(void)
{
	unsigned short i;
	unsigned x;
	x = ~0;
	for (i=0; x!=0; ++i)
		x >>= 1;
	
	return i;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned tempx, tempy;
	tempx = (~(~(~0<<n)<<(p-n))) & x;
	tempy = (~(~0<<n) & y)<<(p-n);
	
	return (tempx | tempy);
}

unsigned invert(unsigned x, int p, int n)
{
	unsigned y;
	y = x;
	y = ~(y >> (p-n));
	
	return setbits(x, p, n, y);
}

unsigned rightrot(unsigned x, int n)
{
	unsigned temp;
	n = (n<UNSIGNED_BITS) ? n: n % UNSIGNED_BITS;
	temp = x << (UNSIGNED_BITS - n);
	x >>= n;
	
	return (x | temp);
}

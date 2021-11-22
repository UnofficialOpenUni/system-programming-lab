#include <stdio.h>

int any (char s1[], char s2[]);

int main (void)
{
	char s1[] = "Ssgi Haily Kimhi";
	char s2[] = "   Haily  ";
	int loc;
	
	printf("%d\n", EOF);
	if ((loc= any(s1, s2))<0)
		printf("\nstring s1 does not contain any letters from string s2\n");
	else
		printf("\nstring s1 contains a letter from s2 at location %d\n", loc);
	
	
	return 0;
}

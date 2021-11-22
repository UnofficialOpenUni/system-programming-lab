#include <stdio.h>

void squeeze (char s1[], char s2[]);

int main (void)
{
	char s1[] = "Sagi Haily Kimhi";
	char s2[] = "   Haily  ";
	printf("\n%s\n", s1);
	squeeze(s1, s2);
	printf("\n%s\n", s1);
	
	
	return 0;
}

void squeeze (char s1[], char s2[])
{
	int i, k, j;
	for (i=k=0; s1[i]!='\0'; ++i)
	{
		for (j=0; s2[j]!='\0' && s1[i]!=s2[j]; ++j)
			;
		if (s2[j]=='\0')
			s1[k++]=s1[i];
	}
	s1[k]='\0';
}

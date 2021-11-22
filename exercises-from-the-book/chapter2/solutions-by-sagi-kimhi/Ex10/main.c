#include <stdio.h>

int lower(int c);

int main(void)
{
	int i, c;
	char s[] = "THIS IS A TEST FOR THE FUNCTION LOWER(INT C), IF THIS APPEARS IN NON CAPITAL LETTERS IT MEANS THAT THE FUNCTION WORKS JUST FINE! :)";
	
	for (i=0; (c=s[i])!='\0'; i++)
		s[i]=lower(c);
	
	printf("%s\n", s); 
	
	
	return 0;
}

#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 81
#define TO 45 /* the ascii value of the character '-' */

void contract(char s1[], char s2[]);

int main() 
{
	char s1[MAX_LENGTH], s2[MAX_LENGTH];
	
	fgets(s1, MAX_LENGTH, stdin);
	printf("\nYour input was: \n%s\n", s1);
	contract(s1, s2);
	printf("\nThe shortened string is: \n%s\n", s2);
	
	return 0;
}

void contract(char s1[], char s2[])
{
	int i, j, k;
	
	if (s1==NULL)
		return ;
	for (i=j=k=0; s1[i]!='\0'; ++i)
	{
		if (isalnum(s1[i]))
			for (k=i; isalnum(s1[k+1]) && s1[k]+1==s1[k+1]; ++k)
					;
		if (k>i)
		{
			if ((k-i)>1)
			{
				s2[j++]=s1[i];
				s2[j++]=TO;
				s2[j++]=s1[(i=k)];
				continue;
			}
			else /* this else is not necessary but was added for readability */
				s2[j++]=s1[i++];
		}
			s2[j++]=s1[i];
	}
	s2[j]='\0';
}

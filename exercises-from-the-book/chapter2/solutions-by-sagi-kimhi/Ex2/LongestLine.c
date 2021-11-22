#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
	int length, max;
	char line[MAXLINE], tempLine[MAXLINE];
	char longest[MAXLINE];
	
	max=0;
	while ((length=getLine(line, MAXLINE))>0)
	{
		while (length==MAXLINE-1)
			length+=getLine(tempLine, MAXLINE);
		if (length>max)
		{
			max=length;
			copy(longest, line);
		}
	}
	if (max>0)
		printf("\nThe longest line is: %d characters long.\n%s\n", max, longest);
	
	
	return 0;
}

/*
	read a line into array s[] and return its length.
*/
int getLine(char s[], int lim)
{
	char c;
	int i;
	
	/* -----The solution for Exc 2 of Chap2----- */
	for (i=0; (i<lim-1) ? ((c=getchar())!=EOF) ? (c!='\n'): 0: 0; ++i)
	{
		s[i]=c;
	}
	/* -----The solution for Exc 2 of Chap2----- */
	if (c=='\n')
	{
		s[i]=c;
		s[i+1]='\0';
		return i;
	}
	s[i]='\0';
	return i;
}

/*
	copy 'from' into 'to'.
*/
void copy(char to[], char from[])
{
	int i;
	
	i=0;
	while ((to[i]=from[i])!='\0')
		++i;
}

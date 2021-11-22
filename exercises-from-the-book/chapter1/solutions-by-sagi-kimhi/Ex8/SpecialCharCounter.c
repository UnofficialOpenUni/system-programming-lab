#include <stdio.h>

int main()
{
	char c;
	int blanks, tabs, nlines;
	blanks=tabs=nlines=0;
	
	while ((c=getchar())!=EOF)
	{
		switch (c)
		{
			case ' ': ++blanks; break;
			case '\t': ++tabs; break;
			case '\n': ++nlines; break;
		}
	}
	printf("\nBlanks: %d\nTabs: %d\nNew Lines: %d\n\n", blanks, tabs, nlines);
		
		return 0;
}

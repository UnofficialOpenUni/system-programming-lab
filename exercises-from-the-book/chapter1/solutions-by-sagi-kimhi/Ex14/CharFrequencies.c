#include <stdio.h>

#define MAX_CHARS 128

int main(void)
{
	int characters[MAX_CHARS];
	char c;
	int i, j, diffChars, maxCount;
	diffChars=maxCount=0;
	
	/*
		Initialize the array of characters to the value of 0.
	*/
	for (i=0; i<MAX_CHARS; ++i)
		characters[i]=0;
		
	/*
		scan the text, for each character scanned, add 1 count to its possision in characters[]
		array, and for each new character scanned also add 1 count to diffChar.
	*/
	while ((c=getchar())!=EOF)
	{
		i=c; 
		if (i<MAX_CHARS && i>=0) 
		{ 
			if (!characters[i]) 
				++diffChars;
			++characters[i];
			maxCount = (maxCount<characters[i]) ? characters[i]: maxCount;
		}
	}

	/*
		Print the histogram:
	*/
	for (i=maxCount; i; --i)
	{
		printf("\n%2d|", i);
		for (j=0; j<MAX_CHARS; ++j)
		{
			if (characters[j])
			{
				if (characters[j]>=i)
					printf("%3c", '#');
				else
					printf("%3c", ' ');
			}
		}
	}
	
	/*
		Print the histogram's footer:
	*/
	printf("\n%3c", '+');
	for (i=diffChars; i; --i)
	{
		printf("---");
	}
	
	printf("\n%3c", ' ');
	for (i=0; i<MAX_CHARS; ++i)
		if (characters[i])
			switch (i)
			{
				case '\t': printf("%2s%1c", "\\", 't'); break;
				case '\n': printf("%2s%1c", "\\", 'n'); break;
				default: printf("%3c", i);
			}
	printf("\n\n");
	
	
	return 0;
}




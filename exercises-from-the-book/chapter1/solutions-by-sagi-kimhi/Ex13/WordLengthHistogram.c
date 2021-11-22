#include <stdio.h>
#define MAX_WORDS 10
#define MAX_LENGTH 15

int main()
{
	char c;
	int lengths[MAX_WORDS]={0};
	int i, inspace=0, words=0, longestWord=0;
	
	do
	{
		while ((c=getchar())!=EOF && c!=' ' && c!='\t' && c!='\n')
		{
			++lengths[words];
			inspace=0;
		}
		longestWord = (longestWord<lengths[words]) ? lengths[words]: longestWord;
		if (inspace==0)
		{
			++words;
			inspace=1;
		}
	}
	while(words<MAX_WORDS && c!=EOF);
	
	
	while (longestWord>0)
	{
		printf("\n%2d|", longestWord);
		
		for (i=0; i<words; ++i)
		{
			if (lengths[i]>=longestWord)
				printf("%4c", '#');
			else
				printf("%4c", ' ');
		}
		--longestWord;
	}
	printf("\n%3c", '+');
	for (i=0; i<words; ++i)
		printf("----");
		
	printf("\n%3c", ' ');
	for (i=0; i<words; ++i)
		printf("%4d", i+1);
	printf("\n");
	
	return 0;
}

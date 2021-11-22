#include <stdio.h>
#include <stdbool.h>

int main()
{
	char c;
	bool blank=false;
	
	printf("\n");
	while ((c=getchar())!=EOF)
	{
		if (c!=' ')
		{
			putchar(c);
			blank=false;
		}
		else if (!blank)
		{
			putchar(c);
			blank=true;
		}
	}
	printf("\n");
	return 0;
}

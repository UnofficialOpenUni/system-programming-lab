#include <stdio.h>

int main(void)
{
	char c;
	
	printf("%d\n", (c=getchar())!=EOF);
	
	while ((c=getchar())!=EOF)
		;
	
	printf("%d\n", c!=EOF);

	return 0;
}

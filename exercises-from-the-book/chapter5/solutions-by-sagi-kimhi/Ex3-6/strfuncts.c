#include <stdio.h>
#include <ctype.h>

#define MAXLEN 100

char *strcat(char *s, char *t)
{
	char *p = s;
	if (*p)				/* if we're not pointing to the null character */
		while (*++p);	/* go on untill reching the null character */
	while ((*p++ = *t++)); /* copy t to s until null char is reached and copied */
	return s;
}

char *strncat(char *s, char *t, int n)
{
	char *p = s;
	if (*p)				/* if we're not pointing to the null character */
		while (*++p);	/* go on untill reching the null character */
	while ((*p = *t++) && n--) /* copy t to s until null char is reached and copied */
		p++;
	if (*p)
		*p = '\0';
	return s;
}

char *strncpy(char *s, char *t, int n)
{
	char *p = s;
	while (*p && n--) {
		if (*t)
			*p++ = *t++;
		else
			*p++ = '\0';
		}
	if (*p)
		*p = '\0';
	return s;
}

int strncmp(char *s, char *t, int n)
{
	if (!n || (!*s && !*t))
		return 0;
	return (*s<*t) ? -1: (*s>*t) ? 1: strncmp(s+1, t+1, n-1);
}

int main(int argc, char *argv[])
{
	
	char s1[MAXLEN], s2[MAXLEN];
	int func, arg, resume=1, strend(char *s, char *t);
	
	while (resume-- > 0) {
		int i, c;

		printf("\nType a string for s1:\n");
		for (i=0; (c = getchar()) != '\n'; ++i) {
			if (c == EOF)
				return -1;
			*(s1+i) = c;
		}
		*(s1+i) = '\0';
		printf("Type a string for s2:\n");
		for (i=0; (c = getchar()) != '\n'; ++i) {
			if (c == EOF)
				return -1;
			*(s2+i) = c;
		}
		*(s2+i) = '\0';
		printf("Enter an int representing the function from the list which you wish to test:\n");
		printf("1. strcat(char *s, char *t)\n2. strncat(char *s, char *t, int n)\n");
		printf("3. strncpy(char *s, char *t, int n)\n4. strncmp(char *s, char *t, int n)\n");
		printf("5. int strend(char *s, char *t)\n");
		scanf("%d", &func);
		switch (func) {
		case 1:
			printf("s1 was: %s\ns2 was: %s\n\n", s1, s2);
			strcat(s1, s2);
			printf("s1: %s\ns2: %s\n", s1, s2);
			break;
		case 2:
			printf("Please enter provide an argument - int n:\n");
			scanf("%d", &arg);
			printf("s1 was: %s\ns2 was: %s\n\n", s1, s2);
			strncat(s1, s2, arg);
			printf("s1: %s\ns2: %s\n", s1, s2);
			break;
		case 3:
			printf("Please enter provide an argument - int n:\n");
			scanf("%d", &arg);
			printf("s1 was: %s\ns2 was: %s\n\n", s1, s2);
			strncpy(s1, s2, arg);
			printf("s1: %s\ns2: %s\n", s1, s2);
			break;
		case 4:
			printf("Please enter provide an argument - int n:\n");
			scanf("%d", &arg);
			printf("s1 was: %s\ns2 was: %s\n\n", s1, s2);
			printf("Result is: %d\n", strncmp(s1, s2, arg));
			break;
		case 5:
			printf("s1 was: %s\ns2 was: %s\n\n", s1, s2);
			printf("Result is: %d\n", strend(s1, s2));
			break;
		default:
			printf("Error: Invalid function - %d\n", func);
		}
		printf("If you wish to run another test, type 1, otherwise type 0\n");
		scanf("%d", &resume);
		while ((c=getchar()) != '\n' && c != EOF);
		if (resume>9) {
			printf("Error: Invalid request - %c", c);
			resume = 0;
		}
	}

	return 0;
}


static int strendgo(char *s, char *t)
{
	if (!*t && !*s)
		return 1;
	if (*s == *t)
		return strendgo(s+1, t+1);
	return -1;
}

int strend(char *s, char *t)
{
	int sLength, tLength;
	for (sLength=0; *(s+sLength); sLength++);
	for (tLength=0; *(t+tLength); tLength++);
	if (sLength<tLength || !sLength || !tLength)
		return -1;
	return strendgo(s+(sLength-tLength), t);
}
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char *s);
void itoa(int n, char *s);

int main()
{
    char s[200];

    itoa(INT_MIN, s);

    printf("%d is converted to %s.\n", INT_MIN, s);

    return 0;
}

void itoa(int n, char *s)
{
    unsigned int nAbs;
    char *p = s, isNegative=0;
    if (n<0)
        isNegative = 1;
    nAbs = (isNegative) ? -n: n;
    do {
        (*p++) = (nAbs%10) + '0';
    }while ((nAbs /= 10) > 0);
    if (isNegative)
        (*p++) = '-';
    (*p) = '\0';
    reverse(s);
}

void reverse(char *s)
{
    char *p, c;
    p = s;
    while (*p!='\0')
        p++;
    while (s<--p) {
        c = *s;
        *s++ = *p;
        *p = c;
    }
}
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char *s);
void itoa(int n, char *s);
void itob(int n, char *s, int b);

int main()
{
    char s[200];

    itob(INT_MAX, s, 16);

    printf("%d is converted to %s.\n", INT_MAX, s);

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

void itob(int n, char *s, int b)
{
    unsigned int nAbs;
    char *p = s, isNegative=0;
    if (n<0)
        isNegative = 1;
    nAbs = (isNegative) ? -n: n;
    do {
        (*p++) = ((nAbs%b)>9) ?  nAbs%b + '7': nAbs%b + '0';
    }while ((nAbs /= b) > 0);
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
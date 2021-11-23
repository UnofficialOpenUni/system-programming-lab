#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* get the next integer from the input into *pn */
int getInt(int *pn)
{
    int c, sign;

    while (isspace(c=getch()));
    if ((!isdigit(c) && c != '-' && c != '+') || c == EOF) {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1: 1;
    if (c == '+' || c == '-')
        c = getch();
    if (isdigit(c)) 
        for (*pn = 0; isdigit(c); c = getch())
            *pn = 10 * *pn + (c - '0');
    else {
        ungetch(c);
        return 0;
    }
    *pn *= sign;
    return c;
}

int getFloat(double *pn)
{
    int c, power = 0, sign;
    c = getInt(&power);
    if (c == EOF)
        return 0;
    sign = (power >= 0) ? 1: -1;
    *pn = sign * power;
    if (c == '.')
        c = getch();
    if (!isdigit(c))
        return 0;
    for (power = 1; isdigit(c); c = getch(), power *= 10)
        *pn = 10 * *pn + (c - '0');
    *pn = sign * *pn/power;
    return c;
}

int getDecimalCount(double f)
{
    int i=0, temp;
    f = (f<0) ? -f: f;
    temp = (int)f;
    f -= temp;
    while (f<0.99 && f>0.1) {
        temp = (int)(f *= 10);
        f -= temp;
        i++;
    }
    return i;
}

int main(int argc, char *argv[])
{
    double f;
    int count;
    getFloat(&f);
    count = getDecimalCount(f);
    printf("%.*f\n", count, f);

    return 0;
}
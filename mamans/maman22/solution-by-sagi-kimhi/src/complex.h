#ifndef _COMPLEX_H
#define _COMPLEX_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LEN 101 /* including the null character '\0' */
#define MAX_CMD_LEN 14 /* longest valid commend */
#define MIN_CMD_LEN 4

#ifndef _COMPLEX_
#define _COMPLEX_
typedef struct complex {
    float real;
    float img;
} complex;
#endif

int read_comp(complex *var, float real, float img);
int print_comp(complex *var);
complex *add_comp(complex *var, complex *var2);
complex *sub_comp(complex *var, complex *var2);
complex *mult_comp_real(complex *var, float real);
complex *mult_comp_img(complex *var, float img);
complex *mult_comp_comp(complex *var, complex *var2);
float abs_comp(complex *var);
int stop(void);


#endif

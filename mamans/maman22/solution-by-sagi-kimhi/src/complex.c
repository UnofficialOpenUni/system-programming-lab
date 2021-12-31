#include "complex.h"

int read_comp(complex *var, float real, float img)
{
    if (!var)
        return 0;
    var->real = real;
    var->img = img;
    return 1;
}

int print_comp(complex *var)
{
    if (!var)
        return 0;
    printf("result:\t%0.3f + (%0.3f)i\n", var->real, var->img);
    return 1;
}

complex *add_comp(complex *var, complex *var2)
{
    complex *temp=NULL;
    if (!var || !var2)
        return NULL;
    if (!(temp = (complex *) malloc(sizeof(complex))))
        return NULL;
    temp->real = (var->real + var2->real);
    temp->img = (var->img + var2->img);
    return temp;
}

complex *sub_comp(complex *var, complex *var2)
{
    complex *temp;
    if (!var || !var2)
        return NULL;
    if (!(temp = (complex *) malloc(sizeof(complex))))
        return NULL;
    temp->real = (var->real - var2->real);
    temp->img = (var->img - var2->img);
    return temp;
}

complex *mult_comp_real(complex *var, float real)
{
    complex *temp;
    if (!var)
        return NULL;
    if (!(temp = (complex *) malloc(sizeof(complex))))
        return NULL;
    temp->real = var->real * real;
    temp->img = var->img * real;
    return temp;
}

complex *mult_comp_img(complex *var, float img)
{
    complex *temp;
    if (!var)
        return NULL;
    if (!(temp = (complex *) malloc(sizeof(complex))))
        return NULL;
    temp->real = (-1)*(img * var->img);
    temp->img = (img * var->real);
    return temp;
}

complex *mult_comp_comp(complex *var, complex *var2)
{
    complex *temp;
    if (!var || !var2)
        return NULL;
    if (!(temp = (complex *) malloc(sizeof(complex))))
        return NULL;
    temp->real = ((var->real*var2->real)-(var->img*var2->img));
    temp->img = ((var->real*var2->img)+(var->img*var2->real));
    return temp;
}

float abs_comp(complex *var)
{
    float abs;
    if (!var)
        return 0;
    abs = (float)(sqrt((pow(var->real,2)+pow(var->img,2))));
    return abs;
}

int stop(void)
{
    exit(EXIT_SUCCESS);
}



#include "data.h"
void printMatrix(int matrix[N][N])
{
    int i, j;
    printf("\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        putchar('\n');
    }
}

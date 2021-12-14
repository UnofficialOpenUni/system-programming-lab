#include "data.h"
int main()
{
  magic();
  return 0;
}

void magic()
{
  int matrix[N][N] = {{0}};
  if (parseInput(matrix))
  {
    printMatrix(matrix);
    isBasicMagicBox(matrix) ? printf("\nYES! it is a Simple Magic Box! :)") : printf("\nit is NOT! a Basic Magic Box :(");
  }
}

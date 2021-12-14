#include "data.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int parseInput(int matrix[N][N])
{
  int i = 0, j = 0, k = 0;
  int c = 0, numericValue = 0;
  Bool isParsing = False;
  char *num;
  num = (char *)calloc(8, sizeof(int));
  while ((c = getchar()) != EOF)
  {
    if (j + 1 > SIZE)
      return handleInputError(tooManyNumbers);

    if (isdigit(c) || (!isParsing && c == '-'))
    {
      if (!isParsing)
        isParsing = True;

      num[k] = c;
      k++;
    }

    else if (isspace(c) && isParsing)
    {
      numericValue = atoi(num);
      memset(num, 0, k);
      if (j > 0 && j % N == 0)
        i++;
      matrix[i][j % N] = numericValue;
      j++;

      isParsing = False;
      c = k = numericValue = 0;
    }

    else if (c == '.')
      return handleInputError(notAnInteger);
    else if (!isspace(c) && !isdigit(c))
      return handleInputError(generalInputError);
  }

  if (c == EOF && isParsing == True && j == SIZE - 1)
  {
    numericValue = atoi(num);
    free(num);
    matrix[i][j % N] = numericValue;
    j++;
  }

  return j < SIZE ? handleInputError(notEnoughNumbers) : True;
}

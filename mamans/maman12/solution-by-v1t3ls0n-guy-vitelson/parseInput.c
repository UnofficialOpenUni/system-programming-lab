#include "data.h"
#include <stdio.h>
#include <ctype.h>

int parseInput(int matrix[N][N])
{
  int i = 0, j = 0, num;
  char c;
  while (scanf("%d%c", &num, &c) >= 1)
  {

    if (j > SIZE - 1)
      return handleInputError(tooManyNumbers);
    else if (c == '.')
      return handleInputError(notAnInteger);
    else if (!isspace(c))
      return handleInputError(generalInputError);

    else
    {
      if (j > 0 && j % N == 0)
        i++;
      matrix[i][j % N] = num;
      j++;
    }
  }

  if (!isspace(c) || (!isdigit(num) && !isspace(num)))
    return handleInputError(generalInputError);

  return j < SIZE ? handleInputError(notEnoughNumbers) : True;
}

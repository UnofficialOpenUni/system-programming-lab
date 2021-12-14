#include "data.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int parseInput(int matrix[N][N])
{
  int i = 0, j = 0, num;
  char c;
  char *str = NULL;
  str = (char *)calloc(SIZE, sizeof(int));

  while (scanf("%d%c", &num, &c) > 0)
  {
    if (c == '.')
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

  scanf("%s", str);
  if (strlen(str) > 0)
    return handleInputError(generalInputError);

  if (j > SIZE)
    return handleInputError(tooManyNumbers);
  else if (j < SIZE)
    return handleInputError(notEnoughNumbers);

  return True;
}

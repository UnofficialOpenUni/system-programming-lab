#include "data.h"

Bool isBasicMagicBox(int matrix[N][N])
{
  int xSum, ySum, ltrCrossSum, rtlCrossSum;
  int i, j;
  xSum = ySum = ltrCrossSum = rtlCrossSum = 0;
  for (i = 0; i < N; i++)
  {
    if (xSum == ySum)
    {
      if (i > 0 && xSum != MAX_SUM)
        return False;

      else if (i == 0)
        rtlCrossSum += matrix[N - 1][N - 1];
      else
        rtlCrossSum += matrix[N - 1 - i][N - 1 - i];

      ltrCrossSum += matrix[i][i];
      xSum = ySum = 0;
    }
    else
      return False;

    for (j = 0; j < N; j++)
    {

      if (!verify(matrix[i][j]))
        return False;

      xSum += matrix[i][j];
      ySum += matrix[j][i];
    }
  }

  if (ltrCrossSum != rtlCrossSum || rtlCrossSum != MAX_SUM)
    return False;

  return True;
}

Bool verify(int c)
{
  if (c < 1 || c > SIZE || c >= MAX_SUM)
    return False;

  return checkForDuplicateValues(c);
}

Bool checkForDuplicateValues(int c)
{
  static int valuesTable[MAX_SUM] = {0};
  valuesTable[c]++;
  if (valuesTable[c] > 1)
    return False;
  else
    return True;
}

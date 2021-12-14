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
        return printFailureReason(notEqualToMagicSum);

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
    return printFailureReason(notEqualToMagicSum);

  return True;
}

Bool verify(int c)
{
  if (c < 1 || c > SIZE)
    return printFailureReason(numberOutOfRange);
  else if (c >= MAX_SUM)
    return printFailureReason(biggerThanMagicSum);

  return checkForDuplicates(c);
}

Bool checkForDuplicates(int c)
{
  static int valuesTable[MAX_SUM] = {0};
  valuesTable[c]++;
  if (valuesTable[c] > 1)
    return printFailureReason(duplicateNumber);
  else
    return True;
}

Bool printFailureReason(Failure err)
{
  switch (err)
  {
  case numberOutOfRange:
    printf("\nValue of single number crossed accepted range, which is between %d - %d, ", N, SIZE);
    break;
  case duplicateNumber:
    printf("\nDuplicate number value was found, ");
    break;
  case biggerThanMagicSum:
    printf("\nSingle number was found to be bigger than the expected sum, ");
    break;

  case notEqualToMagicSum:
    printf("\nCalculated sum was found not equal to expected magic sum, ");
    break;

  default:
    break;
  }
  printf("Therefore, ");
  return False;
}
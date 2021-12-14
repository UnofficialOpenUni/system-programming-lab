#include <stdio.h>
#define N 5
#define SIZE N *N
#define MAX_SUM ((N * (SIZE + 1)) / 2)

typedef enum
{
  False,
  True
} Bool;

typedef enum
{
  generalInputError = -4,
  tooManyNumbers = -5,
  notEnoughNumbers = -6,
  notAnInteger = -7

} Error;

typedef enum
{
  numberOutOfRange = 101,
  duplicateNumber = 102,
  biggerThanMagicSum = 103,
  notEqualToMagicSum = 104
} Failure;

int parseInput(int matrix[N][N]);
int parseInputScanf(int matrix[N][N]);
Bool verify(int c);
Bool isBasicMagicBox(int matrix[N][N]);
Bool handleInputError(Error err);
Bool printFailureReason(Failure err);
Bool checkForDuplicates(int c);
void printMatrix(int matrix[N][N]);
void magic();
int main();

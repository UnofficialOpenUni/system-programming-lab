#include "../magic.h"


/****************************************************
*					SET FUNCTIONS:					*
****************************************************/
/*	setSquare: Reads integers from the input and sets them as members of the square
	in left to right order, returns 1 on success, or prints an error and halts on failure. */
int setSquare(Square square)
{
	int row, col, count;
	row=col=count=0; 
	while (scanf("%d", &square[row][col]) == 1) { 
		if (++count > MAX_MEMBERS) 
				printInputError(VALUE_OVERFLOW);
		if (++col < N)
			continue;
		col = 0;
		++row;
	}

	if (!feof(stdin))
		printInputError(INVALID_INPUT_VALUE);
	else if (count != MAX_MEMBERS)
		printInputError(VALUE_UNDERFLOW);
	return 1;
}

/*	setSquareSums: Calcualtes and sets all the sums of the pointed to SquareSums struct to the
	aprropriate sums of the square given as argument. No operation will occure for a null pointer. */
void setSquareSums(Square square, SquareSums *sums)
{
	if (sums != NULL) {
		int i;
		resetSums(sums);
		for (i = 0; i < N; i++) {
			sums->rowSum[i] = getRowSum(square, i);
			sums->colSum[i] = getColSum(square, i);
		}
		sums->leftDiagonal = getLeftDiagSum(square);
		sums->rightDiagonal = getRightDiagSum(square);
	}
}

/*	resetSums: sets all the members of the pointed to SquareSums structure to 0.
	No operation will occure for a null pointer argument. */
void resetSums(SquareSums *sums)
{
	if (sums != NULL) {
		memset(sums->rowSum, 0, sizeof(sums->rowSum));
		memset(sums->colSum, 0, sizeof(sums->colSum));
		sums->leftDiagonal = sums->rightDiagonal = 0;
	}
}

/****************************************************
*					GET FUNCTIONS:					*
****************************************************/
/*	getRowSum: Calculates and returns the sum the specified row within the square.
	returns the constant INT_MIN if the row argument is out of the square's bounds. */
int getRowSum(Square square, int row)
{
	if (row<N) {
		int i, sum;
		for (i = sum = 0; i < N; i++)
			sum += square[row][i];
		return sum;
	}
	return INT_MIN;
}

/*	getColSum: Calculates and returns the sum the specified column within the square.
	returns the constant INT_MIN if the col argument is out of the square's bounds. */
int getColSum(Square square, int col)
{
	if (col < N) {
		int i, sum;
		for (i = sum = 0; i < N; i++)
			sum += square[i][col];
		return sum;
	}
	return INT_MIN;
}

/*	getLeftDiagSum: Calculates and returns the sum of members within the 
	square's left diagonal line. */
int getLeftDiagSum(Square square)
{
	int i, sum;
	for (i = sum = 0; i < N; i++)
		sum += square[i][i];
	return sum;
}

/*	getRightDiagSum: Calculates and returns the sum of members within the 
	square's right diagonal line. */
int getRightDiagSum(Square square)
{
	int sum = 0, limit = N;
	while (--limit >= 0)
		sum += square[limit][limit];
	return sum;
}

#include "../magic.h"

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

/****************************************************
*					SET FUNCTIONS:					*
****************************************************/
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

static InputFlag setSquareRec(Square square, int row,  int col, int count);

/*	setSquare: Reads integers from the input and sets them as members of the square
	in left to right order, and returns the aprropriate InputFlag on success/failure */
int setSquare(Square square)
{
	InputFlag flag = setSquareRec(square, 0, 0, 0);
	if (flag == VALID_INPUT) 
		return flag;
	printInputError(flag);	/* print user input related error message */
	exit(flag);
}
/****************************************************
*				STATIC FUNCTIONS:					*
****************************************************/
/*	setSquareRec: A static recursive function to be used by the setSquare function.
	returns an aprropriate InputFlag type for both success or failure. */
static InputFlag setSquareRec(Square square, int row,  int col, int count)
{
	int member;
	if (scanf("%d", &member) == 1) { /* saves the returned char and checks if an int was succesfully fetched */
		if (count++ >= MAX_MEMBERS) 
				return VALUE_OVERFLOW;
		if (col >= N) {	
			col = 0;
			row++;
		}
		square[row][col] = member;
		return (!feof(stdin)) ? setSquareRec(square, row, col+1, count): /* recursive call - set the next column */
		(count == MAX_MEMBERS) ? VALID_INPUT: VALUE_UNDERFLOW;
	}
	return (!feof(stdin)) ? INVALID_INPUT_VALUE:
	(count == MAX_MEMBERS) ? VALID_INPUT: VALUE_UNDERFLOW;
}
#include "../magic.h"


/****************************************************
*				USER INTERFACE FUNCTIONS:			*
****************************************************/
/* printUserIntroMessage: prints a detailed user introduction message to the program. */
void printUserIntroMessage(void)
{
	printf("\n******************************** Hello And Welcome! ********************************\n");
	printf("This program checks whether or not a square is a basic magic square\n");
	printf("In order to continue, please provide %d integers representing your square\n", MAX_MEMBERS);
	printf("from left to right order, where the first integer is the integer on the first row\n");
	printf("and column and the last integer is the integer on the last row and column.\n");
	printf("You can enter your values in any way you'd like to, each value in a seperate row,\n");
	printf("all values on the same row, or any other way.\n\n");
	printf("In order to begin the validation, please provide the values...\n");
	printf("*************************************************************************************\n\n");
}

/* printSquare: prints a pretty Square representation */
void printSquare(Square square)
{
	/* find the longest variable in the matrix */
	int row, col, minTemp, maxTemp;
	uint8_t longestVar=1, longestPosVar = 1, longestNegVar = 2;
	for (row=minTemp=maxTemp=0; row<N; row++)
		for (col=0; col<N; col++) {
			maxTemp = (square[row][col] > maxTemp) ? square[row][col]: maxTemp;
			minTemp = (square[row][col] < minTemp) ? square[row][col]: minTemp;
		}
	for (; (maxTemp/=10); longestPosVar++);
	for (; (minTemp/=10); longestNegVar++);
	longestVar = (longestPosVar > longestNegVar) ? longestPosVar: longestNegVar;

	/* print the matrix with dynamic spacing based on the size of the longest variable */
	printf("\n\n");
	for (row = 0; row < N; row++) {
		printf("%-*c", longestVar, '|');
		for (col = 0; col < N; col++)
			printf("%-*d %-*c", longestVar, square[row][col], longestVar, '|');
		printf("\n\n");
	}
	printf("\n");
}

/* printInputError: prints an appropriate error message based on the InputFlag argument */
void printInputError(InputFlag inFlag)
{
	switch (inFlag) {
	case INVALID_INPUT_VALUE:
		printf("\nError: an incorrect input type was recieved.\nPlease use integers only!\n\n");
		exit(INVALID_INPUT_VALUE);
	case VALUE_OVERFLOW:
		printf("\nError: Too many values were entered.\nPlease enter exactly %d values!\n\n", MAX_MEMBERS);
		exit(VALUE_OVERFLOW);
	case VALUE_UNDERFLOW:
		printf("\nError: You did not provide enough values.\n");
		printf("Please make sure you are providing exactly %d values!\n\n", MAX_MEMBERS);
		exit(VALUE_UNDERFLOW);
	}
}

/* printIfMagic: prints out a friendly message announcing a magic square */
void printIfMagic(uint8_t _magicFlag)
{
	if (!_magicFlag)
		printf("Congrats!\nThis square is a basic magic square with a constant sum of: %d\n\n", CONSTANT_SUM);
	else {
		printf("Well, it is a square... But it sure ain't a magical one...\n");
		printf("This is due to the following reasons:\n");
		if (_magicFlag & INVALID_MAGIC_MEMBER)
			printf("\t# You have provided a value that is not within the scope of {1...N^2}.\n");
		if (_magicFlag & MULTI_MEMBER_APPEARANCE)
			printf("\t# Some values (1 or more) have multiple appearances.\n");
		if (_magicFlag & INVALID_MAGIC_LINEAR_SUM)
			printf("\t# The square has one or more rows/columns with an invalid sum.\n \
		all sums should be equal to: %d.\n", CONSTANT_SUM);
		if (_magicFlag & INVALID_MAGIC_DIAGONAL_SUM)
			printf("\t# The square has one or more diagonals with an invalid sum.\n \
		all sums should be equal to: %d.\n", CONSTANT_SUM);
	}
}

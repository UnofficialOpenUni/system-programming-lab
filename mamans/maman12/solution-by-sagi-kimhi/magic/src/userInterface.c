/*
*	This source file contains all the user interaction related functions including
*	handling of output - printing an intro message, a matrix, error messages, etc.
*	and also some handling of input - the getInt function which converts a set of
*	characters from the input representing an integer - into an actual integer value.
*/
#include "../magic.h"

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

/* printSquare: prints a pretty matrix representation of the Square argument */
void printSquare(Square square)
{
	int row, col;
	printf("\n");
	for (row = 0; row < N; row++) {
		printf("%-5c", '|');
		for (col = 0; col < N; col++)
			printf("%-5d", square[row][col]);
		printf("%-c\n", '|');
	}
	printf("\n");
}

/* printIfMagic: prints out a friendly message announcing a magic square */
void printIfMagic(int isMagic, MagicFlag flag)
{
	if (isMagic)
		printf("Congrats!\nThis square is a basic magic square with a constant sum of: %d\n\n", CONSTANT_SUM);
	else {
		printf("Well, it is a square... But it sure ain't a magical one...\n");
		printf("This is due to the following reasons:\n");
		if (flag._invalid_magic_member)
			printf("\t* You have provided a value that is not within the scope of {1...N^2}.\n");
		if (flag._multiple_member_appearances)
			printf("\t* Some values (1 or more) have multiple appearances.\n");
		if (flag._invalid_magic_sums)
			printf("\t* The individual sums of rows, columns, and diagonals are not all equal to %d.\n", CONSTANT_SUM);
	}
}

/* printInputError: prints an appropriate error message based on the InputFlag argument */
void printInputError(InputFlag flag)
{
	switch (flag) {
	case INVALID_INPUT_VALUE:
		printf("\nError: an incorrect input type was recieved.\nPlease use integers only!\n\n");
		break;
	case VALUE_OVERFLOW:
		printf("\nError: Too many values were entered.\nPlease enter exactly %d values!\n\n", MAX_MEMBERS);
		break;
	case VALUE_UNDERFLOW:
		printf("\nError: You did not provide enough values.\n");
		printf("Please make sure you are providing exactly %d values!\n\n", MAX_MEMBERS);
		break;
	default:
		break;
	}
}
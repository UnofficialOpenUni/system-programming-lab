/*
*	This source file contains all the user interaction related functions including
*	handling of output - printing an intro message, a matrix, error messages, etc.
*	and also some handling of input - the getInt function which converts a set of
*	characters from the input representing an integer - into an actual integer value.
*/
#include "magic.h"

#define CharToDigit(c) ((c) - '0')

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
		printf("|");
		for (col = 0; col < N; col++)
			printf("%8d\t", square[row][col]);
		printf("|\n\n");
	}
	printf("\n");
}

/* printSquareType: prints whether or not a square is a basic magic square - based on the argument */
void printSquareType(MagicSquareFlag flag)
{
	if (flag == BASIC_MAGIC_SQUARE)
		printf("Congrats!\nThis square is a basic magic square with a constant sum of: %d\n\n", CONSTANT_SUM);
	else {
		printf("Well it is a square...\nBut it sure ain't a magical one... ");
		printf("You may want to reconsider your input :-)\n\n");
	}
}

/* printInputError: prints an appropriate error message based on the InputFlag argument */
void printInputError(InputFlag inFlag)
{
	switch (inFlag) {
	case INVALID_INPUT_VALUE:
		printf("Error: an incorrect input type was recieved.\nPlease use integers only!\n\n");
		break;
	case VALUE_OVERFLOW:
		printf("Error: Too many values were entered.\nPlease enter exactly %d values!\n\n", MAX_MEMBERS);
		break;
	case VALUE_UNDERFLOW:
		printf("Error: You did not provide enough values.\n");
		printf("Please make sure you are providing exactly %d values!\n\n", MAX_MEMBERS);
		break;
	default:
		break;
	}
}

/* 	printProgramFailureMsg: prints a general program error message describing a failure 
	in the program and what could have caused the failure - this failure is not input related  */
void printProgramFailureMsg(void)
{
	printf("Error: the program has failed due to an unknown reason.\n");
	printf("This is non-related to the user's input and is usually caused due to:\n");
	printf("\t- A change done to the main function - misusing a function.\n");
	printf("\t- A null pointer argument sent to one of the functions.\n");
	printf("\t- Not enough space available to construct a new MagicSquare or");
	printf("magicMember hash-table structure.\n");
	printf("We sincerely appologize for the inconvenience, please report this error to get further\n");
	printf("help and find a possible fix to the problem...\t:-(\n\n");
}

/* 	getInt: gets an integer from a string of input and converts it to an actual int type and saves
	the converted value into the pointer argument. 
	Returns the latest non digit character encountered upon success, or 0 upon failure.
	Either way, the latest nondigit charcter is pushed back to the input by the ungetc function. */
int getInt(int *pn)
{
    int c, sign;
    while (isspace(c=getchar()))	/* skips spaces */
		;
    if (!isdigit(c) && c != '-' && c != '+' && c != EOF) {
        ungetc(c, stdin);
		return 0;
    }
    sign = (c == '-') ? -1: 1;	/* sets the aprropriate sign of the int */
    if (c == '+' || c == '-')
        c = getchar();
    if (isdigit(c)) 
        for (*pn = 0; isdigit(c); c = getchar())
            *pn = 10 * *pn + CharToDigit(c);		/* The convertion operation */
    else {
		ungetc(c, stdin);	
		return 0;
    }
    *pn *= sign;
    return ungetc(c, stdin);
}
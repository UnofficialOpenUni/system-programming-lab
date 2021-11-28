#include "magic.h"

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

void printSquareType(MagicSquareFlag flag)
{
	if (flag == BASIC_MAGIC_SQUARE)
		printf("Congrats!\nThis square is a basic magic square with a constant sum of: %d\n\n", CONSTANT_SUM);
	else
		printf("Well it is a square...\nBut it ain't a magical one... Try again :-)\n\n");
}

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
		printf("The input is valid\n");
		break;
	}
}

int getInt(int *pn)
{
    int c, sign;
    while (isspace(c=getchar()))
		;
    if (!isdigit(c) && c != '-' && c != '+' && c != EOF) {
        ungetc(c, stdin);
		return 0;
    }
    sign = (c == '-') ? -1: 1;
    if (c == '+' || c == '-')
        c = getchar();
    if (isdigit(c)) 
        for (*pn = 0; isdigit(c); c = getchar())
            *pn = 10 * *pn + (c - '0');
    else {
		ungetc(c, stdin);
		return 0;
    }
    *pn *= sign;
    return ungetc(c, stdin);
}
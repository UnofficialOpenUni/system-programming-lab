#ifndef _MAGIC_H
#define _MAGIC_H 1
/****************************************************
*					LIBRARY INCLUDES:				*
****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/****************************************************
*					CONSTANT DEFINES:				*
****************************************************/
#ifndef N
#define N 9							/* Defines the dimention for an NxN sized square */
#endif
#define MAX_MEMBERS \
	((N)*(N))						/* Max amount of members in an NxN sized square */
#define CONSTANT_SUM \
	((N)*(MAX_MEMBERS+1)/2)			/* The formula for a magic square's constant sum */
#define FAILURE -1

/****************************************************
*					MACRO DEFINES:					*
****************************************************/
#define ValidMagicSum(SUM) \
	((SUM) == CONSTANT_SUM)			/* validates if a sum is a valid magic sum */
#define ValidMagicMember(X) \
	((X) > 0 && (X) <= MAX_MEMBERS)	/* validates if a value is a valid magic member */

/****************************************************
*					TYPEDEFS :						*
****************************************************/
typedef unsigned char uint8_t;		/* Wasn't sure if we're allowed to use stdint.h for this maman */

typedef int Square[N][N];			/* An NxN sized 2d int array */

typedef struct squareSums {			/* A structure to store */
	int rowSum[N];					/* the row sums, */
	int colSum[N];					/* column sums */
	int leftDiagonal;				/* and diagonal sums */
	int rightDiagonal;				/* of a Square type */
} SquareSums;

typedef struct magicMember {		/* struct for members */
	int value;						/* with a value and a count */
	unsigned int count;				/* for validation of magic members */
} MagicTable[MAX_MEMBERS];			/* within a Square type matrix*/

typedef enum _InputFlags {
	INVALID_INPUT_VALUE, 			/* Describes various */
	VALUE_OVERFLOW, 				/* input error flags */
	VALUE_UNDERFLOW
} InputFlag;

enum _BitMagicFlags {
	VALID = 0x0u, 						/* 0 */
	INVALID_MAGIC_MEMBER = 0x1u,		/* 1 */	/* Constant values used for */
	MULTI_MEMBER_APPEARANCE = 0x2u,		/* 2 */	/* bit operations to represent*/
	INVALID_MAGIC_LINEAR_SUM = 0x4u,	/* 4 */	/* various Magic square flags*/
	INVALID_MAGIC_DIAGONAL_SUM = 0x8u	/* 8 */
};

/****************************************************
*			MAGIC VALIDATION FUNCTIONS :			*
****************************************************/
/* validateMagicSquare: Validates whther or not a square is a basic magic square.
Returns a uint8_t value set with appropriate _BitMagicFlags (see typdef) */
uint8_t validateMagicSquare(Square square);

/* validateMagicMembers: Validates if a square contains valid magic members.
Returns a uint8_t value set with aprropriate _BitMagicFlags (see typdef) */
uint8_t validateMagicMembers(Square square);

/* validateMagicSums: Checks if the sums of the square's rows, columns and diagonals are all
equal to CONSTANT_SUM, and returns a uint8_t value set with aprropriate _BitMagicFlags. */
uint8_t validateMagicSums(Square square);

/****************************************************
*				MAGIC TABLE FUNCTIONS :				*
****************************************************/
/* setMemTable: sets the appropriate count for all of the square's members that
count as valid magic members (members with a value between 1...N^2) */
uint8_t setMemTable(Square square, MagicTable tab);

/* addToTable: adds one count to a member with the value of "val", if "val" is not a
valid magic member's value, no operation is done. */
int addToTable(MagicTable tab, int val);

/* resetMemTable: initializes a MagicTable with sorted member values of 1...N^2 and counts of 0 */
void resetMemTable(MagicTable table);

/* getKey: Returns an index to a magic member's value in a MagicTable.
Returns FAILURE if the value is not a valid magic member's value. */
int getKey(int val);

/****************************************************
*				SQUARE SET FUNCTIONS :				*
****************************************************/
/* setSquare: Reads integers from the input and sets them as members of the square
in left to right order, returns 1 on success, or prints an error and halts on failure. */
int setSquare(Square square);

/* setSquareSums: Calcualtes and sets all the sums of the pointed to SquareSums struct to the
aprropriate sums of the square given as argument. No operation will occure for a null pointer. */
void setSquareSums(Square square, SquareSums *sums);

/* resetSums: sets all the members of the pointed to SquareSums structure to 0.
No operation will occure for a null pointer argument. */
void resetSums(SquareSums *sums);

/****************************************************
*				SQUARE GET FUNCTIONS :				*
****************************************************/
/* getRowSum: Calculates and returns the sum the specified row within the square.
returns the constant INT_MIN if the row argument is out of the square's bounds. */
int getRowSum(Square square, int row);

/* getColSum: Calculates and returns the sum the specified column within the square.
returns the constant INT_MIN if the col argument is out of the square's bounds. */
int getColSum(Square square, int col);

/* getLeftDiagSum: Calculates and returns the sum of members within the 
square's left diagonal line. */
int getLeftDiagSum(Square square);

/* getRightDiagSum: Calculates and returns the sum of members within the 
square's right diagonal line. */
int getRightDiagSum(Square square);

/****************************************************
*			USER INTERFACE FUNCTIONS:				*
****************************************************/
void printUserIntroMessage(void);			/* prints a pretty introduction message to the program. */
void printSquare(Square square);			/* prints a pretty Square representation */
void printIfMagic(uint8_t magicFlag);		/* prints an appropriate error message based on the InputFlag argument */
void printInputError(InputFlag inputFlag);	/* prints out a friendly message announcing a magic square */

#endif

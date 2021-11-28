/****************************************************
*				INCLUDES AND DEFINES :				*
****************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 5
#define MAX_MEMBERS ((N)*(N))
#define CONSTANT_SUM ((N) * (MAX_MEMBERS + 1)/2)
#define IsConstSum(sum) ((sum) == CONSTANT_SUM)
#define ValidMagicMember(x) ((x) > 0 && (x) <= MAX_MEMBERS)
#define FAILURE -1

/****************************************************
*					TYPEDEFS :						*
****************************************************/
typedef enum InputFlags { 
	INVALID_INPUT_VALUE = INT_MIN, 
	VALUE_OVERFLOW, 
	VALUE_UNDERFLOW, 
	VALID_INPUT = 1
} InputFlag;

typedef enum magicSquareFlags { 
	STANDARD_SQUARE,
	BASIC_MAGIC_SQUARE
} MagicSquareFlag;

typedef int Square[N][N];

typedef struct squareSums {
	int rowSum[N];
	int colSum[N];
	int leftDiagonal;
	int rightDiagonal;
} SquareSums;

typedef struct magicMember {
	int value;
	unsigned int count;
} MagicMember, MemTable[MAX_MEMBERS];

typedef struct basicMagicSquare {
	Square square;
	SquareSums sums;
	MemTable memberTable;
} MagicSquare;


/****************************************************
*					GET FUNCTIONS :					*
****************************************************/
int getNewMagicSquare(MagicSquareFlag *squareFlag);
int getRowSum(Square square, int row);
int getColSum(Square square, int col);
int getRightDiagSum(Square square);
int getLeftDiagSum(Square square);
int memLookup(int val, MemTable tab);
int getKey(int val);

/****************************************************
*					SET FUNCTIONS :					*
****************************************************/
InputFlag setSquare(Square square);
int setMemTable(MagicSquare *magicSquare, MemTable tab);
int removeFromTable(int val, MemTable tab);
int addToTable(int val, MemTable tab);
void resetMemTable(MemTable table);
void setSquareSums(SquareSums *sums, Square square);
void resetSums(SquareSums *sums);

/****************************************************
*				VALIDATION FUNCTIONS :				*
****************************************************/
MagicSquareFlag isMagicSquare(MagicSquare *magicSquare);
int validMagicMembers(MemTable tab);
int validMagicSums(SquareSums sums);

/****************************************************
*					USER INTERFACE :				*
****************************************************/
void printUserIntroMessage(void);
void printSquare(Square square);
void printSquareType(MagicSquareFlag flag);
void printInputError(InputFlag inputFlag);
void printProgramFailureMsg(void);
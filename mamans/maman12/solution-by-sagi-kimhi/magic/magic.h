/****************************************************
*				INCLUDES AND DEFINES :				*
****************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 3
#define MAX_MEMBERS ((N)*(N))
#define CONSTANT_SUM ((N) * (MAX_MEMBERS + 1)/2)
#define IsConstSum(sum) ((sum) == CONSTANT_SUM)
#define ValidMagicMember(x) ((x) > 0 && (x) <= MAX_MEMBERS)
#define FAILURE -1

/****************************************************
*					TYPEDEFS :					*
****************************************************/
typedef enum InputFlags { 
	INVALID_INPUT_VALUE = INT_MIN, 
	VALUE_OVERFLOW, 
	VALUE_UNDERFLOW, 
	VALID_INPUT = 1
} InputFlag;

typedef enum magicSquareFlags { 
	STANDARD_SQUARE = 0,
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
} Member, *MemTable;

typedef struct basicMagicSquare {
	Square square;
	SquareSums sums;
	MemTable memberTable;
} MagicSquare;

/****************************************************
*				DE/CONSTRUCTOR FUNCTIONS :			*
****************************************************/
MagicSquare *newMagicSquare(void);
Member *newMemTable(void);

/****************************************************
*					GET FUNCTIONS :					*
****************************************************/
MagicSquareFlag getNewMagicSquare(void);
int getRowSum(Square square, int row);
int getColSum(Square square, int col);
int getLeftDiagSum(Square square);
int getRightDiagSum(Square square);
int getKey(int val);
int getInt(int *pn);

/****************************************************
*					SET FUNCTIONS :					*
****************************************************/
InputFlag setSquare(Square square);
void setSquareSums(SquareSums *sums, Square square);
void resetSums(SquareSums *sums);
int updateMemTable(MagicSquare *magicSquare, MemTable tab);
int resetMemTable(MemTable table);
int addToTable(int val, MemTable tab);
int removeFromTable(int val, MemTable tab);

/****************************************************
*				VALIDATION FUNCTIONS :				*
****************************************************/
MagicSquareFlag isMagicSquare(MagicSquare *magicSquare);
int validMagicMembers(MemTable tab);
int validMagicSums(SquareSums sums);

int memLookup(int val, MemTable tab);

/****************************************************
*					USER INTERFACE :				*
****************************************************/
void printUserIntroMessage(void);
void printSquare(Square square);
void printSquareType(MagicSquareFlag flag);
void printInputError(InputFlag inputFlag);
void printProgramFailureMsg(void);
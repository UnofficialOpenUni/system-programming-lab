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
#define IsConstSum(SUM) ((SUM) == CONSTANT_SUM)
#define ValidMagicMember(X) ((X) > 0 && (X) <= MAX_MEMBERS)
#define FAILURE -1

/****************************************************
*					TYPEDEFS :						*
****************************************************/
typedef enum _InputFlags { 
	VALID_INPUT = 1,
	INVALID_INPUT_VALUE, 
	VALUE_OVERFLOW, 
	VALUE_UNDERFLOW
} InputFlag;

typedef struct _MagicFlags {
	unsigned int _multiple_member_appearances: 1;
	unsigned int _invalid_magic_member: 1;
	unsigned int _invalid_magic_sums: 1;
} MagicFlag;

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
} Member, MemTable[MAX_MEMBERS];


/****************************************************
*					GET FUNCTIONS :					*
****************************************************/
int getNewMagicSquare(void);
int getRowSum(Square square, int row);
int getColSum(Square square, int col);
int getLeftDiagSum(Square square);
int getRightDiagSum(Square square);
int getMemCount(int val, MemTable tab);
int getKey(int val);

/****************************************************
*					SET FUNCTIONS :					*
****************************************************/
int setSquare(Square square);
int setMemTable(Square square, MemTable tab);
int removeFromTable(int val, MemTable tab);
int addToTable(int val, MemTable tab);
void resetMemTable(MemTable table);
void setSquareSums(Square square, SquareSums *sums);
void resetSums(SquareSums *sums);

/****************************************************
*				VALIDATION FUNCTIONS :				*
****************************************************/
int isMagicSquare(Square square, MagicFlag *flags);
int validMagicMembers(MemTable tab);
int validMagicSums(Square square);

/****************************************************
*					USER INTERFACE :				*
****************************************************/
void printUserIntroMessage(void);
void printSquare(Square square);
void printIfMagic(int isMagic, MagicFlag flag);
void printInputError(InputFlag inputFlag);

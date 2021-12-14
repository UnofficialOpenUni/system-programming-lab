/****************************************************
*				INCLUDES AND DEFINES :				*
****************************************************/
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>

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

enum MagicFlags {
	INVALID_MAGIC_MEMBER = 0x1u, /* 1 */
	MULTI_MEMBER_APPEARANCE = 0x2u, /* 2 */
	INVALID_MAGIC_LINEAR_SUM = 0x4u, /* 4 */
	INVALID_MAGIC_DIAGONAL_SUM = 0x8u /* 8 */
};

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
uint8_t scanNewMagicSquare(void);
int getRowSum(Square square, int row);
int getColSum(Square square, int col);
int getLeftDiagSum(Square square);
int getRightDiagSum(Square square);
int getKey(int val);

/****************************************************
*					SET FUNCTIONS :					*
****************************************************/
int setSquare(Square square);
void setMemTable(Square square, MemTable tab);
void addToTable(int val, MemTable tab);
void resetMemTable(MemTable table);
void setSquareSums(Square square, SquareSums *sums);
void resetSums(SquareSums *sums);

/****************************************************
*				VALIDATION FUNCTIONS :				*
****************************************************/
uint8_t isMagicSquare(Square square);
uint8_t validMagicMembers(Square square);
uint8_t validMagicSums(Square square);

/****************************************************
*					USER INTERFACE :				*
****************************************************/
void printUserIntroMessage(void);
void printSquare(Square square);
void printIfMagic(uint8_t magicFlag);
void printInputError(InputFlag inputFlag);
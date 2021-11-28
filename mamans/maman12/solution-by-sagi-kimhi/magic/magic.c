#include "magic.h"

int main(int argc, char  *argv[])
{
	MagicSquareFlag magicSquareFlag;
	printUserIntroMessage();
	magicSquareFlag = getNewMagicSquare();
	if (magicSquareFlag != FAILURE)
		printSquareType(magicSquareFlag);
	
	return 0;
}

/****************************************************
*					DE/CONSTRUCTORS:				*
****************************************************/
/*	*newMagicSquare: allocates memory for a new MagicSquare struct pointer, 
	initializes it's members and returns a pointer to its address. returns NULL upon failure. */
MagicSquare *newMagicSquare(void)
{
	MagicSquare *newMagicSquare = (MagicSquare *) malloc(sizeof(MagicSquare));
	MemTable temp = newMemTable();

	if (newMagicSquare != NULL && temp != NULL) {
		memset(newMagicSquare->square, 0, sizeof(Square));
		resetSums(&newMagicSquare->sums);
		newMagicSquare->memberTable = temp;
		return newMagicSquare;
	}
	free(newMagicSquare);
	free(temp);
	return NULL;
}

/*	*newMemTable: allocates memory for a new magicMember hash table with size of MAX_MEMBERS, 
	initializes it's members and returns a pointer to its address. returns NULL upon failure. */
MemTable newMemTable(void)
{
	MemTable newTab = malloc(MAX_MEMBERS * sizeof(Member));
	
	if (newTab != NULL) {
		int member;
		for (member = 1; ValidMagicMember(member); member++) {
			newTab[getKey(member)].value = member;
			newTab[getKey(member)].count = 0;
		}
		return newTab;
	}
	return NULL;
}

/****************************************************
*					GET FUNCTIONS:					*
****************************************************/
/*	getNewMagicSquare: Creates, fills and prints a square from an input of integers.
	returns a MagicSquareFlag upon success, or the failure upon FAILURE.
	If the failure was due to invalid user input, an aprropriate message will be printed. */
MagicSquareFlag getNewMagicSquare(void)
{
	MagicSquare *magicSquare = newMagicSquare();
	if (magicSquare != NULL) {
		InputFlag inputFlag = setSquare(magicSquare->square);
		if (inputFlag == VALID_INPUT) {
			printSquare(magicSquare->square);
			return isMagicSquare(magicSquare);
		}
		printInputError(inputFlag);
	}
	return FAILURE;
}

/****************************************************
*				VALIDATION FUNCTIONS:				*
****************************************************/
/*	isMagicSquare: Validates whther or not a pointer to a MagicSquare struct points to a valid
	magic square and returns the aprropriate MagicSquareFlag. returns FAILURE for a null pointer. */
MagicSquareFlag isMagicSquare(MagicSquare *magicSquare)
{
	if (updateMemTable(magicSquare, magicSquare->memberTable) == FAILURE) 
		return FAILURE;
	if(validMagicMembers(magicSquare->memberTable)) {
		setSquareSums(&magicSquare->sums, magicSquare->square);
		if (validMagicSums(magicSquare->sums))
			return BASIC_MAGIC_SQUARE;
	}
	return STANDARD_SQUARE;
}

/*	validMagicMembers: Validates whether or not a pointer to a magicMember hash table
	points to a table with valid magic members and returns 1 if it does, otherwise, returns 0. */
int validMagicMembers(MemTable table)
{
	int magicMember;
	for (magicMember = 1; ValidMagicMember(magicMember); magicMember++)
		if (memLookup(magicMember, table) != 1)
			return 0;
	return 1;
}

/*	validMagicSums: returns 1 if the members of the SquareSum struct contain valid magic square
	sums, otherwise, returns 0. */
int validMagicSums(SquareSums sums)
{
	int ind = N;
	while (ind++ < N)
		if (!IsConstSum(sums.colSum[ind]) || !IsConstSum(sums.rowSum[ind]))
			return 0;
	return (IsConstSum(sums.rightDiagonal) && IsConstSum(sums.leftDiagonal));
}

/****************************************************
*				HASH TABLE FUNCTIONS:				*
****************************************************/
int updateMemTable(MagicSquare *magicSquare, MemTable table)
{
	if (magicSquare != NULL) {
		int row, col;
		for (row = 0; row < N; row++)
			for (col = 0; col < N; col++)
				addToTable(magicSquare->square[row][col], table);
		return 1;
	}
	return FAILURE;
}

int addToTable(int val, MemTable table)
{
	if (memLookup(val, table) != FAILURE)
		return ++table[getKey(val)].count;
	return FAILURE;
}

int removeFromTable(int val, MemTable table)
{
	if (memLookup(val, table) > 0) 
		return --table[getKey(val)].count;
	return FAILURE;
}

int memLookup(int val, MemTable table)
{
	int ind;
	if (table != NULL && (ind = getKey(val)) != FAILURE)
		return table[ind].count;
	return FAILURE;
}

int getKey(int val)
{
	return (ValidMagicMember(val)) ? val-1: FAILURE;
}
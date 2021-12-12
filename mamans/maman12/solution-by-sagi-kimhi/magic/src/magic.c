/*	
*	This is a basic magic square validation program.
*	The program scans integers from a given input in a left to right order.
*	These will be set as the members of a square matrix to be tested as a magic square, 
*	The integers in the input should be passed by the order of the desired matrice's rows,
*	in a left to right order, where each of the integers are seperated from one another
*	by one or more whitespace characters. The scan stops when EOF is reached.
*	
*	If the input contains an invalid number of integers (more or less than N^2), 
*	and/or a non integer character (excluding '+' and/or '-'), the program will halt
*	and print out an appropriate error message describing the error occurred.
*	
*	Otherwise, if the input is valid, then the new square matrix will be printed out,
*	along with a message mentioning whether or not the square is a magic square.
*	
*	************* The description of the main algorithm is as follows: **************
*
*	Print out a user introduction message to the program;
*	Scan and set the integers from the input into a square matrix;
*	if (the input was invalid)
*		stop the program and print an appropriate error message;
*	else
*		Print out the new matrix;
*		Print whether or not it is a valid magic square;
*
*	**********************************************************************************
*	Written by: Sagi Kimhi
*	Date: 27/11/21
*/
#include "../magic.h"


int main(int argc, char *argv[])
{
	printUserIntroMessage();
	getNewMagicSquare();
	
	return 0;
}

/****************************************************
*					GET FUNCTIONS:					*
****************************************************/
/*	getNewMagicSquare: Creates, a square from an input of integers, prints it,
	and validates whether or not it's a basic magic square. */
int getNewMagicSquare(void)
{
	Square magicSquare;
	MagicFlag flag;
	setSquare(magicSquare);
	printSquare(magicSquare);
	memset(&flag, 0, sizeof(MagicFlag));
	printIfMagic(isMagicSquare(magicSquare, &flag), flag);
	return 1;
}

/****************************************************
*				VALIDATION FUNCTIONS:				*
****************************************************/
/*	isMagicSquare: Validates whther or not a square is a basic magic square.
	returns 1 if it is, otherwise, toggles the appropriate MagicFlags and returns 0 */
int isMagicSquare(Square square, MagicFlag *flag)
{
	MemTable magicMemberTable;
	unsigned int result = 0;
	if ((result |= flag->_invalid_magic_member = !setMemTable(square, magicMemberTable))) {
		flag->_invalid_magic_sums = !validMagicSums(square);
		return 0;
	}
	result |= (flag->_multiple_member_appearances = !validMagicMembers(magicMemberTable));
	result |= (flag->_invalid_magic_sums = !validMagicSums(square));
	return (!result);
}

/*	validMagicMembers: Validates whether or not a pointer to a magicMember hash table
	points to a table with valid magic members and returns 1 if it does, otherwise, returns 0. */
int validMagicMembers(MemTable table)
{
	int magicMember;
	for (magicMember = 1; ValidMagicMember(magicMember); magicMember++)
		if (getMemCount(magicMember, table) != 1)
			return 0;
	return 1;
}

/*	validMagicSums: returns 1 if the members of the SquareSum struct contain valid magic square
	sums, otherwise, returns 0. */
int validMagicSums(Square square)
{
	int ind = 0;
	SquareSums sums;
	setSquareSums(square, &sums);
	while (ind++ < N)
		if (!IsConstSum(sums.colSum[ind]) || !IsConstSum(sums.rowSum[ind]))
			return 0;
	return (IsConstSum(sums.rightDiagonal) && IsConstSum(sums.leftDiagonal));
}

/****************************************************
*				HASH TABLE FUNCTIONS:				*
****************************************************/
/* 	updateMemTable: Updates the count of the MemTable's members in accordance to the
	values set in the magicSquare's square's matrix. Returns 1 on success or FAILURE upon failure. 
	Use the resetMemTable function upfront if the table was not previously reset. */
int setMemTable(Square square, MemTable table)
{
	int row, col;
	resetMemTable(table);
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (addToTable(square[row][col], table) == FAILURE)
				return 0;
	return 1;
}
/*	resetMemTable: sets the member values of a MemTable to 1...N^2 and their count to 0.
	No operation occures, and FAILURE is returned for a null MemTable argument. */
void resetMemTable(MemTable table)
{
	int member;
	for (member = 1; ValidMagicMember(member); member++) {
		table[getKey(member)].value = member;
		table[getKey(member)].count = 0;
	}
}

/*	addToTable: adds a count to the MemTable's aprropriate magicMember and returns it.
	Returns FAILURE upon failure. */
int addToTable(int val, MemTable table)
{
	if (getMemCount(val, table) != FAILURE)
		return ++table[getKey(val)].count;
	return FAILURE;
}

/*	removeFromTable: decrease a count from the MemTable's aprropriate 
	magicMember and returns it. Returns FAILURE upon failure. */
int removeFromTable(int val, MemTable table)
{
	if (getMemCount(val, table) > 0) 
		return --table[getKey(val)].count;
	return FAILURE;
}

/* 	getMemCount: Returns the count of the MemTable's magicMember with the value sent as argument. 
	Returns FAILURE for a null pointer or for an invalid magicMember value argument. */
int getMemCount(int val, MemTable table)
{
	int ind;
	if (table != NULL && (ind = getKey(val)) != FAILURE)
		return table[ind].count;
	return FAILURE;
}

/* 	getKey: Returns a key representing an appropriate index to a magicMember in a MemTable
	with the value of the argument. Returns FAILURE if the value is not a valid magic member value. */
int getKey(int val)
{
	return (ValidMagicMember(val)) ? val-1: FAILURE;
}
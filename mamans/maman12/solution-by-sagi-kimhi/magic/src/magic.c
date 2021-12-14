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


int main(int argc, char  *argv[])
{
	printUserIntroMessage();
	printIfMagic(scanNewMagicSquare());
	
	return 0;
}

/****************************************************
*					GET FUNCTIONS:					*
****************************************************/
/*	scanNewMagicSquare: Creates, fills and prints a square from an input of integers.
	returns a MagicSquareFlag upon success, or the FAILURE constant upon failure.
	an aprropriate message is printed upon failure, describing the reason. */
uint8_t scanNewMagicSquare(void)
{
	Square magicSquare;
	setSquare(magicSquare);
	printSquare(magicSquare);
	return isMagicSquare(magicSquare);
}

/****************************************************
*				VALIDATION FUNCTIONS:				*
****************************************************/
/*	isMagicSquare: Validates whther or not a square is a basic magic square.
	returns 1 if it is, otherwise, toggles the appropriate MagicFlags and returns 0 */
uint8_t isMagicSquare(Square square)
{
	uint8_t _magicFlags = 0;
	_magicFlags |= validMagicMembers(square);
	_magicFlags |= validMagicSums(square);
	return _magicFlags;
}

/*	validMagicMembers: Validates whether or not a pointer to a magicMember hash table
	points to a table with valid magic members and returns 1 if it does, otherwise, returns 0. */
uint8_t validMagicMembers(Square square)
{
	MemTable table;
	int member, ind;
	uint8_t _flags = 0;
	setMemTable(square, table);
	for (member = 1; (ind=getKey(member)) !=FAILURE ; member++) {
		if (table[ind].count == 1)
			continue;
		_flags |= (!table[ind].count) ? INVALID_MAGIC_MEMBER: MULTI_MEMBER_APPEARANCE;
	}
	return _flags;
}

/*	validMagicSums: returns 1 if the members of the SquareSum struct contain valid magic square
	sums, otherwise, returns 0. */
uint8_t validMagicSums(Square square)
{
	int ind;
	SquareSums sums;
	uint8_t _flags = 0;
	setSquareSums(square, &sums);
	for (ind = 0; ind < N; ind++) {
		if (!IsConstSum(sums.colSum[ind]) || !IsConstSum(sums.rowSum[ind])) {
			_flags |= INVALID_MAGIC_LINEAR_SUM;
			break;
		}
	}
	if (!IsConstSum(sums.rightDiagonal) || !IsConstSum(sums.leftDiagonal))
		_flags |= INVALID_MAGIC_DIAGONAL_SUM;
	return _flags;
}

/****************************************************
*				HASH TABLE FUNCTIONS:				*
****************************************************/
/* 	getKey: Returns a key representing an appropriate index to a magicMember in a MemTable
	with the value of the argument. Returns FAILURE if the value is not a valid magic member value. */
int getKey(int val)
{
	return (ValidMagicMember(val)) ? val-1: FAILURE;
}

/* 	updateMemTable: Updates the count of the MemTable's members in accordance to the
	values set in the magicSquare's square's matrix. Returns 1 on success or FAILURE upon failure. 
	Use the resetMemTable function upfront if the table was not previously reset. */
void setMemTable(Square square, MemTable table)
{
	int row, col;
	resetMemTable(table);
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			addToTable(square[row][col], table);
}

/*	resetMemTable: sets the member values of a MemTable to 1...N^2 and their count to 0.
	No operation occures, and FAILURE is returned for a null MemTable argument. */
void resetMemTable(MemTable table)
{
	int member, ind;
	for (member = 1; (ind = getKey(member)) != FAILURE; member++) {
		table[ind].value = member;
		table[ind].count = 0;
	}
}

/*	addToTable: adds a count to the MemTable's aprropriate magicMember and returns it.
	Returns FAILURE upon failure. */
void addToTable(int val, MemTable table)
{
	int ind;
	if ((ind = getKey(val)) != FAILURE)
		++table[ind].count;
}

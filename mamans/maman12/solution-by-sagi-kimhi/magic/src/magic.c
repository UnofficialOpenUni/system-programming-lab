/*	
*	This is a basic magic square validation program.
*	The program scans integers from a given input in a left to right order.
*	These will be set as the members of a square matrix to be validated as a basic magic square, 
*	The integers in the input should be passed by the order of the desired matrice's rows,
*	in a left to right order, where each of the integers are seperated from one another
*	by one or more whitespace characters, or a + or - sign, followed by the next integer.
*	The scan stops when EOF is reached.
*	
*	If the input contains an invalid number of integers (more or less than N^2), 
*	or a non integer character, the program will halt and print out an error message
*	describing the error occurred.
*	
*	Otherwise, if the input is valid, then the new square matrix will be printed out,
*	along with a message describing whether or not the square is a magic square.
*	
*	************* The description of the main algorithm is as follows: **************
*
*	Print out a user introduction message to the program;
*	Scan and set the integers from the input into a square matrix;
*	if (the input is invalid at any point)
*		print an appropriate error message and halt;
*	else
*		Print out the new matrix;
*		validate whther or not it is a magic Square.
*		print out the result of the validation.
*
*	**********************************************************************************
*	Written by: Sagi Kimhi - 206504227
*/
#include "../magic.h"


int main(int argc, char  *argv[])
{
	Square magicSquare;
	printUserIntroMessage();
	setSquare(magicSquare);			/* This function also halts upon input error. */
	printSquare(magicSquare);
	validateMagicSquare(magicSquare);
	
	return 0;
}


/****************************************************
*				VALIDATION FUNCTIONS:				*
****************************************************/
/*	validateMagicSquare: Validates whther or not a square is a basic magic square.
	returns a uint8_t value set with appropriate _BitMagicFlags (see typdef)  */
uint8_t validateMagicSquare(Square square)
{
	uint8_t _magicFlags = VALID;
	_magicFlags |= validateMagicMembers(square);	/* turn on bit flags returned by function */
	_magicFlags |= validateMagicSums(square);		/* turn on bit flags returned by function */
	printIfMagic(_magicFlags);

	return _magicFlags;
}

/*	validateMagicMembers: Validates if a square contains valid magic members.
	Returns a uint8_t value set with aprropriate _BitMagicFlags (see typdef) */
uint8_t validateMagicMembers(Square square)
{
	MagicTable magicMemberTable;
	return setMemTable(square, magicMemberTable);
}

/*	validateMagicSums: Checks if the sums of the square's rows, columns and diagonals are all
	equal to CONSTANT_SUM, and returns a uint8_t value set with aprropriate _BitMagicFlags. */
uint8_t validateMagicSums(Square square)
{
	int ind;
	SquareSums sums;
	uint8_t _bitFlags = VALID;
	setSquareSums(square, &sums);	/* calculate and set the sums in a SquareSums struct */
	if (!ValidMagicSum(sums.rightDiagonal) || !ValidMagicSum(sums.leftDiagonal))
		_bitFlags |= INVALID_MAGIC_DIAGONAL_SUM;
	for (ind = 0; ind < N; ind++) {
		if (!ValidMagicSum(sums.colSum[ind]) || !ValidMagicSum(sums.rowSum[ind])) {
			_bitFlags |= INVALID_MAGIC_LINEAR_SUM;
			break;
		}
	}
	return _bitFlags;
}

/****************************************************
*				MAGIC TABLE FUNCTIONS:				*
****************************************************/
/* 	setMemTable: sets appropriate count for all of the square's members that
	count as valid magic members (members with a value between 1...N^2).
	Returns _BitMagicFlags set with flags appropriate to the encountered square members */
uint8_t setMemTable(Square square, MagicTable table)
{
	int row, col, temp;
	uint8_t _bitFlags = VALID;
	resetMemTable(table);
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if ((temp = addToTable(table, square[row][col])) != 1)
				_bitFlags |= (temp) ? MULTI_MEMBER_APPEARANCE: INVALID_MAGIC_MEMBER;
	return _bitFlags;
}

/*	resetMemTable: initializes a MagicTable with sorted member values of 1...N^2 and counts of 0 */
void resetMemTable(MagicTable table)
{
	int member, ind;
	for (member = 1; (ind = getKey(member)) != FAILURE; member++) {
		table[ind].value = member;
		table[ind].count = 0;
	}
}

/*	addToTable: adds one count to a member with the value of "val", if "val" is not a
	valid magic member's value, no operation is done. */
int addToTable(MagicTable table, int val)
{
	int ind;
	if ((ind = getKey(val)) != FAILURE)
		return ++table[ind].count;
	return 0;
}

/* 	getKey: Returns an index to a magic member's value in a MagicTable.
	Returns FAILURE if the value is not a valid magic member's value. */
int getKey(int val)
{
	return (ValidMagicMember(val)) ? val-1: FAILURE;
}

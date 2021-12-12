#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genMagicSquare(void);
int genOddMagic(int **matrix, int row, int col, int curr, int lim);
int genEvenMagic(int **matrix, int row, int col, int curr, int lim, int direction);

int main(int argc, char *argv[])
{
	char newFile;
	printf("\n******************************** ATTENTION - READ FIRST! ********************************\n");
	printf("The program currently only works for *ODD* magic squares!\n");
	printf("the only valid *EVEN* magic square it can currently generate is of order 4\n");
	printf("please feel free to update this code and fix this, i'm too tired to do so atm... :P\n");
	printf("have fun :)\n");
	printf("******************************** ATTENTION - READ FIRST! ********************************\n\n");
	printf("Would you like to export the results to a new file in this directory?\n");
	printf("type y/n: ");
	if (scanf("%c", &newFile)==1)
		switch (newFile) {
		case 'y':
			freopen("GenFile.txt", "w", stdout);
			break;
		case 'n':
			break;
		default:
			fprintf(stderr, "\nMagicSquareGen: Invalid character was given as input: %c\n", newFile);
			return -1;
		}
		while (genMagicSquare()==1);

	return 0;
}

void printMatrix(int **matrix, int lim)
{
	int row, col;
	printf("\n");
	for (row = 0; row < lim; row++) {
		for (col = 0; col < lim; col++)
			printf("%-5d", matrix[row][col]);
		if (row != lim-1)
			printf("\n");
	}
	printf("\n");
}

int genMagicSquare(void)
{
	int n, i;
	n = 0;
	printf("\nEnter an integer representing the order of the desired magic cube:\n");
	if (scanf("%d", &n) == 1) {

		int **matrix = (int**) malloc(n*sizeof(int));
		for (i=0; i<n; i++)
			matrix[i] = (int*) malloc(n*sizeof(int));
		for (i=0; i<n; i++)
			memset(matrix[i], 0, n*sizeof(int));

		if (n%2 == 1)
			genOddMagic(matrix, 0, n/2, 1, n);
		else
			genEvenMagic(matrix, 0, 0, 1, n, 1);

		printMatrix(matrix, n);
		for (i=0; i<n; i++)
			free(matrix[i]);
		free(matrix);
		return 1;
	}
	return 0;
}

/* This function works :) */
int genOddMagic(int **matrix, int row, int col, int curr, int lim)
{
	if (curr > (lim*lim))
		return 1;
	if (row > lim-1)
		row -= lim;
	if (row < 0)
		row = lim-1;
	if (col > lim-1)
		col = 0;
	if (col<0)
		col = lim-1;
	if (matrix[row][col]) 
			return genOddMagic(matrix, row+2, col-1, curr, lim);
	matrix[row][col] = curr;
	return genOddMagic(matrix, row-1, col+1, curr+1, lim);
}

/* NEEDS A FIX - only works if lim == 4, feel free to correct this im tired and don't
	really care too much */
int genEvenMagic(int **matrix, int row, int col, int curr, int lim, int direction)
{
	if (direction) {
		if (col >= lim) 
			return genEvenMagic(matrix, row+1, 0, curr, lim, direction);
		if ((row == col || row == lim-1-col))
			matrix[row][col] = curr;
		if (row == lim-1 && col == lim-1)
			return genEvenMagic(matrix, row, col, 1, lim, 0);
		return genEvenMagic(matrix, row, col+1, curr+1, lim, direction);
	}
	else
	{
		if (row < 0)
			return 0;
		if (!row && !col)
			return 1;
		if (col < 0)
			return genEvenMagic(matrix, row-1, lim-1, curr, lim, direction);
		if (!matrix[row][col])
			matrix[row][col] = curr;
		return genEvenMagic(matrix, row, col-1, curr+1, lim, direction);
	}
}

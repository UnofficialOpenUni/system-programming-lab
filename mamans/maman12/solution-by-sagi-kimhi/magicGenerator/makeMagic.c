#include "../magic/magic.h"
#include <string.h>

int makeMagic(void);
int makeOddMagic(int **matrix, int row, int col, int curr, int lim);
int makeEvenMagic(int **matrix, int row, int col, int curr, int lim, int direct);

int main(int argc, char *argv[])
{
	while (!feof(stdin))
		makeMagic();

	return 0;
}

void printMagic(int **matrix, int lim)
{
	int row, col;
	printf("\n");
	for (row = 0; row < lim; row++) {
		/* printf("|"); */
		for (col = 0; col < lim; col++)
			printf("%6d", matrix[row][col]);
		/* printf("      |\n\n"); */
		printf("\n\n");
	}
	printf("\n");
}

int makeMagic(void)
{
	int n, res, i;
	res = n = 0;
	printf("enter an integer representing the order of the desired magic cube:\n");
	if (scanf("%d", &n) == 1) {
		int **matrix = (int**) malloc(n*sizeof(int));
		for (i=0; i<n; i++)
			matrix[i] = (int*) malloc(n*sizeof(int));
		for (i=0; i<n; i++)
			memset(matrix[i], 0, n*sizeof(int));
		if (n%2 == 1)
			res = makeOddMagic(matrix, 0, n/2, 1, n);
		else
			res = makeEvenMagic(matrix, 0, 0, 1, n, 1);
		if (res) {
			printMagic(matrix, n);
			for (i=0; i<n; i++)
				free(matrix[i]);
			free(matrix);
			return 1;
		}
		return 0;
	}
	return FAILURE;
}

int makeOddMagic(int **matrix, int row, int col, int curr, int lim)
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
			return makeOddMagic(matrix, row+2, col-1, curr, lim);
	matrix[row][col] = curr;
	return makeOddMagic(matrix, row-1, col+1, curr+1, lim);
}

int makeEvenMagic(int **matrix, int row, int col, int curr, int lim, int direct)
{
	if (direct) {
		if (col >= lim) 
			return makeEvenMagic(matrix, row+1, 0, curr, lim, direct);
		if ((row == col || row == lim-1-col))
			matrix[row][col] = curr;
		if (row == lim-1 && col == lim-1)
			return makeEvenMagic(matrix, row, col, 1, lim, 0);
		return makeEvenMagic(matrix, row, col+1, curr+1, lim, direct);
	}
	else
	{
		if (row < 0)
			return 0;
		if (!row && !col)
			return 1;
		if (col < 0)
			return makeEvenMagic(matrix, row-1, lim-1, curr, lim, direct);
		if (!matrix[row][col])
			matrix[row][col] = curr;
		return makeEvenMagic(matrix, row, col-1, curr+1, lim, direct);
	}
}

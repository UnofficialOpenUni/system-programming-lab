#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 101				/* The character limitation for a line of input */
#define STACK_SIZE (MAX_LINE_LENGTH/2)	/* The stack size for pushOrPop()'s static stack */
#define FAILURE -1					/* can be returned by a function to represent failure */
#define INIT_PUSHORPOP -2			/* argument for pushOrPop() to reinitialize its static stack and stack index */
#define INCREASE_CNT 1				/* used by isSpecialLine() to represent a special line with an open bracket */
#define DECREASE_CNT -1				/* used by isSpecialLine() to represent a special line with a close bracket */


/*	getLine(): save the next line of input onto the array given as argument */
short getLine(char line[]);
/*	validate(): prints whether or not the parentheses/brackets in the array given as argument are balanced.
	this method keeps a static counter to keep track of the balance of all the lines that were tested
	since the begining of the program.
	returns whether or not all of the lines combined that went through validation from the begining of the
	program are balanced - 1 if they are, 0 if they aren't.
	special lines will not make the text unbalanced although they count as unbalanced as an individual line. */
short validate(char line[]);
/*	pushOrPop(): 
	keeps 2 static variables of type "short" of a stack and its current index.
	in order to clear the stack and index, send INIT_PUSHORPOP (-2) as an argument.
	for any other character argument, the function pushes "opening" brackets into the stack,
	or pops them out of the stack if the character argument is the aprropriate
	"closing" bracket for the latests pushed bracket character. 
	if the character argument is not a bracket, no push nor pop action will occure.
	returns: the value of the index of its stack. FAILURE is returned upon
	failure of push or pop actions due to mismatching bracket types. */
short pushOrPop(short c);


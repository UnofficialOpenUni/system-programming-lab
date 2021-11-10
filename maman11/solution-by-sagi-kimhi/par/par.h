#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 101				/* The character limitation for a line of input */
#define STACK_SIZE (MAX_LINE_LENGTH/2)	/* The stack size for pushorpop()'s static stack */
#define FAILURE -1						/* The returned value for a failed push or pop attempt */
#define INIT_PUSHORPOP -2				/* argument for pushorpop() to reinitialize its static stack and stack index */
#define INCREASE 1						/* defined in order to provide better code readability */
#define DECREASE -1						/* defined in order to provide better code readability */



/*	pushorpop: 
	keeps 2 static variables of type "short" of a stack and its current index.
	in order to clear the stack and index, send INIT_PUSHORPOP (-2) as an argument.
	for any other character argument, the function pushes "opening" brackets into the stack,
	or pops them out of the stack if the character argument is the aprropriate
	"closing" bracket for the latests pushed bracket character. 
	if the character argument is not a bracket, no push nor pop action will occure.
	returns: the value of the index of its stack. FAILURE is returned upon
	failure of push or pop actions due to mismatching bracket types.
*/
short pushorpop(short c);
/*	getline: save the next line of input onto the array given as argument */
short getline(char line[]);
/* validates whether or not the string given as argument is a valid line or not */
short validate(char line[]);
short isspecialline(char line[]);
short isbalancedline(char line[]);


#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 101				/* The character limitation for a line of input */
#define STACK_SIZE (MAX_LINE_LENGTH/2)	/* The stack size for matchBrackets()'s static stack */
#define BALANCED 1						/* Represents a balanced line/input */
#define NOT_BALANCED 0					/* Represents an unbalanced line/input */
#define INCREASE_CNT 1					/* used by isSpecialLine() to indicate of a special line with an open bracket */
#define DECREASE_CNT -1					/* used by isSpecialLine() to indicate of a special line with a close bracket */
#define FAILURE -1						/* can be returned by a function to indicate failure of function exectution*/
#define INIT_MATCH_BRACKETS -2			/* argument for matchBrackets() to reinitialize its stack and stack index */


/****************************************************
*				FUNCTION PROTOTYPES:				*
****************************************************/
/*	scanAndValidateInput(): gets the next line of input, and validates it. returns 1 on success.
	upon reaching EOF, the function prints the global balance of the text and returns 0. */
short scanAndValidateInput();
/*	validate(): validates proper nesting of brackets/parentheses within the character string argument 
	and prints the result. the function also keeps track of the global balance of all of the previous
	strings it had scanned since the initialization of the program by using a static variable.
	returns BALANCED or NOT_BALANCED - based on its current global balance variable */
short validate(char line[]);


/****************************************************
*			UI-RELATED FUNCTION PROTOTYPES:			*
****************************************************/
void printWelcomeMessage(); 				/* Prints a predefined user welcome message */
void printInput(char line[]);				/* Prints the user's input - recieved as argument */
void printLineBalance(short isBalanced);	/* Prints whether or not a line is balanced - based on the argument */
void printGlobalBalance(short isBalanced);	/* Prints whether or not whole input is balanced - based on the argument */

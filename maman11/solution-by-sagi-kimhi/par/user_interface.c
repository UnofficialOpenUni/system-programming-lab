#include "par.h"

/****************************************************
*		USER-INTERFACE RELATED FUNCTIONS:			*
****************************************************/

/* printWelcomeMessage(): Prints a predefined user welcome message */
void printWelcomeMessage()
{
	printf("\n******************************** Hello And Welcome! ********************************\n");
	printf("This is a text validation program.\n");
	printf("The program's function is to validate proper nesting of brackets within a given input\n");
	printf("If you are using this program from CMD or Terminal, you can stop this program at any point\n");
	printf("by using the keyboard combination Ctrl+Z for Windows CMD or Ctrl+D for Terminal\n");
	printf("This program can validate an infinite number of lines. Yet, the length of each seperate line\n");
	printf("must be no longer than a 100 characters, or else, only the first 100 will be scanned.\n\n");
	printf("In order to begin the validation, please provide a line of input...\n");
	printf("*************************************************************************************\n\n");
}

/* printInput(): Prints the user's input - recieved as argument */
void printInput(char line[])
{
	static unsigned int lineNum;
	printf("\n%22s%5d: %s\n", "Input for line number ",  ++lineNum, line);
}

/* printLineBalance(): Prints whether or not a line is balanced - based on the argument */
void printLineBalance(short isBalanced)
{
	printf("This line is %s\n", (isBalanced) ? "balanced": "*NOT* balanced");
}

/* printGlobalBalance(): Prints whether or not whole input is balanced - based on the argument */
void printGlobalBalance(short isBalanced)
{
	printf("\n\n********************** RESULT **********************\n\n");
	printf("\tThe entire file/input was %s", (isBalanced) ? "balanced": "NOT balanced");
	printf("\n\n****************************************************\n\n");
}

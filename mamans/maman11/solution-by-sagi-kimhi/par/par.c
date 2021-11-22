/*	
	This program scans each line of a given input, prints it,
	and validates whether or not this line has proper nesting of brackets 
	while also taking special lines, strings and comments into consideration 
	(special line are lines with only white space and the char { or }).
	After reaching the end of the input, the program will then print whether or
	not the complete textfile/input as a whole had proper nesting of brackets.
	
	Worth to mention:
	Special lines do not count as "valid" as an individual seperate line, yet, 
	if the brackets nested properly throughout the input, 
	they will not affect the validity  of the input as a whole.
	
	Description of input:
	The input can be spread over any number of lines, yet
	each line must be no longer than 100 characters including the
	newline ('\n') character at the end of the line, or else, only
	the first 100 characters of the line will be printed and
	go through the validation process.
	
	
	The description of the algorithm is as follows:
	
	print input instructions;
	while (there is another line of input - save it) {
		print the input, validate the line, and print the result
	}
	print whether or not the input as a whole is balanced/valid;
*/
#include "par.h"

int main()
{									
	printWelcomeMessage();
	while (scanAndValidateInput());
	
	return 0;
}

/****************************************************
*				OTHER FUNCTIONS:					*
****************************************************/

/*	scanAndValidateInput(): gets the next line of input, and validates it. returns 1 on success.
	upon reaching EOF, the function prints the global balance of the text and returns 0. */
short scanAndValidateInput()
{
	static char line[MAX_LINE_LENGTH];
	static short globalBalance = BALANCED;	/* boolean indicator of the balance of the entire input */
	
	if (fgets(line, MAX_LINE_LENGTH, stdin)!=NULL) {
		line[strcspn(line, "\n")] = '\0';	/* removes any newline characters from the array */
		printInput(line);
		globalBalance = validate(line); /* validate it and update the input's global balance */
		
		return 1;
	}
	printGlobalBalance(globalBalance);
	return 0;
}

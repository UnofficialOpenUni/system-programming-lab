/*	
	This program scans each line of a given input, prints it,
	and validates whether or not this line has proper nesting of brackets 
	while also taking special lines, strings and comments into consideration.
	After reaching the end of the input, the program will then print whether or
	not the complete textfile/input as a whole had proper nesting of brackets.
	special lines do not count as "valid" as individual seperate lines, yet, 
	if nested properly throughout the input, they will not affect the validity 
	of the input as a whole.
	
	Description of input:
	The input can be spread over any number of lines, yet
	each line must be no longer than 100 characters including the
	newline ('\n') character at the end of the line, or else, only
	the first 100 characters of the line will be printed and
	go through the validation process.
	
	
	The description of the algorithm and it's output is as follows:
	
	print input instructions;
	while (there is another line of input) {
		save it and print it;
		check and print whether or not the line is balanced/valid.
	}
	print whether or not the input as a whole is balanced/valid;
*/
#include "par.h"

int main()
{
	char *line=NULL;				/* A pointer to the next line of input */
	short balanced=1;				/* boolean indicator of the balance of the entire input */
										
	printf("Hello! Please enter your code below in order to perform a parentheses balance test:\n");
	while ((line=getLine())!=NULL) {	/* sets a pointer to the next line of input */
		balanced = validate(line);	/* validate it and save the returned value into "balanced" */
	}
	printf("\n\nThe entire file/input is %s.\n", (balanced) ? "balanced": "NOT balanced");
	
	return balanced;
}


/*	getLine(): saves a line of input into a static character array.
	returns a pointer to the array on success or a NULL pointer upon reaching EOF if no new characters
	were added to the array.
*/
char *getLine()
{
	static char line[MAX_LINE_LENGTH];		/* the array which the next line of input will be saved to */
	if (fgets(line, MAX_LINE_LENGTH, stdin)!=NULL) {
		line[strcspn(line, "\n")] = '\0';	/* remove any newline characters from the array */
		return line;
	}
	return NULL;
}

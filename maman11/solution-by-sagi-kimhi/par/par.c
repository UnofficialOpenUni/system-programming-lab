/*	
	This program scans each line on a given input, prints it,
	and validates whether or not this line has proper nesting of brackets, 
	while also taking special lines, strings and comments into consideration.
	After reaching the end of the input, the program will print whether or
	not the whole text had proper nesting of brackets.
	special lines do not count as "valid" as an individual line, yet, 
	if nested properly throughout the input, they will not affect the validity 
	of the input as a whole.
	
	Description of input:
	The input can spread over any number of lines, yet
	each line must be no longer than 100 characters including the
	newline ('\n') character at the end of the line.
	
	The description of the algorithm and output is as follows:
	
	print input instructions;
	while (there is another line of input) {
		save it into an array and print it;
		check and print whether or not the line is balanced
	}
	print whether or not the input as a whole is balanced;
*/
#include "par.h"

int main()
{
	char line[MAX_LINE_LENGTH];		/* the array which the next line of input will be saved to */
	short balanced=1;				/* boolean indicator of the balance of the entire input */
										
	printf("Hello! Please enter your code below in order to perform a parentheses balance test:\n");
	while (getline(line)) {			/* while there is another line of input */
		balanced = validate(line);	/* validate it and save the returned value into "balanced" */
	}
	printf("\n\nThe entire file/input is %s.\n", (balanced) ? "balanced": "NOT balanced");
	
	return 0;
}

/*	getline: saves a line of input into a character array given as argument.
	returns 1 on success or 0 upon reaching EOF.
*/
short getline(char line[])
{
	if (fgets(line, MAX_LINE_LENGTH, stdin)!=NULL) {
		line[strcspn(line, "\n")] = '\0';	/* remove any newline characters from the array */
		return 1;
	}
	return 0;
}

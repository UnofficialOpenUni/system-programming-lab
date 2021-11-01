/*	
	This file contains the main function which scans and tests each seperate line 
	from a file or from raw input for imbalances of parentheses and brackets.
	if the parentheses/brackets are contained within a string or a comment,
	the program will ignore their existence. 
	
	This file also contains some, but not all, of the different methods
	used by the main function to test the given input.
	
	The other various methods and constants that used for the different tests 
	can be found within the "parstack.c" file or within the "stackdata.h" header.
*/

/* header declaration section */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stackdata.h"
/* end of header declaration section */

/* constants declaration section */
#define MAX_LINE_LENGTH 101 		/* max amount of characters for each seperate line */
#define INCREASE 1					/* defined in order to provide better code readability */
#define DECREASE -1					/* defined in order to provide better code readability */
enum text_states {OUT, IN_STRING, IN_COMM};			/* defines different text states */
/* end of constant declaration section */

/* method declaration section */
int testline(char line[], int line_num, int is_a_special_line);
int isspecialline(char line[]);
int isbalancedline(char line[]);
int pushorpop(char c, int stack[], int stack_index);
/* end method declaration section */



/* -------------- CODE OF THE VARIOUS METHODS BEGINS HERE -------------- */


/*	
	The main function of the program - scans each seperate line of input and
	prints whether or not the parantheses in it are balanced. The number of characters
	for each line must not exceed the count of 100, or else, only the first 100 will be scanned.
	After all the lines are tested the method prints whether or not the whole
	input is balanced while also taking special lines (lines that only contain a single
	opening or closing curly bracket) into consideration. 
*/
int main()
{
	char line[MAX_LINE_LENGTH];
	int special_line_bracket_cnt, line_num, special, balanced;
	
	special_line_bracket_cnt=line_num=0;
	balanced=1;
	printf("Hello! Please enter your code below in order to perform a parentheses balance test:\n");
	while ((fgets(line, MAX_LINE_LENGTH, stdin))!=NULL)
	{
		++line_num;
		line[strcspn(line, "\n")] = '\0';
		if ((special = isspecialline(line)) && special_line_bracket_cnt>=0)
			special_line_bracket_cnt += special;
		if ((!testline(line, line_num, special)) ? (!special) ? 1: 0: 0)
			balanced=0;
	}
	balanced = (!special_line_bracket_cnt) ? balanced: 0;
	printf("\n\nThe text file in its whole is %s.\n", (balanced) ? "balanced": "NOT balanced");
	
	return 0;
}

/*
	This method requires 3 arguments - 1) the string to be tested, 2) the line number of 
	the string within the input, and 3) an int representing whether or not the line 
	is a special line. The method prints the input, tests its balance, and prints whether
	it is balanced or not.
	This method does not tell the difference between a special line and an ordinary line
	and therefore this must be pretested and given as an argument.
*/
int testline(char line[], int line_num, int special)
{
	printf("\n%21s%3d: %s\n", "input for line number ",  line_num, line);
	printf("this line is ");
	if ((!special) && isbalancedline(line))
	{
		printf("balanced.\n");
		return 1;
	}
	printf("NOT balanced.\n");
	return 0;
	
}

/*
	This methods checks if the parentheses/brackets of the character array given 
	as argument are balanced - returns true if it's balanced, false otherwise.
	This method does not tell the difference between a special line and an ordinary line.
*/
int isbalancedline(char line[])
{
	int stack[STACK_SIZE];
	int i, state, stack_index;
	
	state = OUT;
	initstack(stack);
	for (i=stack_index=0; stack_index>STACK_FAILURE && line[i]!='\0'; ++i)
	{
		if (isalnum(line[i]))
			continue;
			
		switch (state)
		{
			case OUT:
				if (line[i]=='\"')
					state = IN_STRING;
				else if (line[i]=='/' && line[i+1]=='*')
				{
					state = IN_COMM;
					++i;
				}
				else
					stack_index = pushorpop(line[i], stack, stack_index);
				break;
				
			case IN_STRING:
				if (line[i]=='\"')
					state = OUT;
				break;
				
			case IN_COMM:
				if (line[i]=='*' && line[i+1]=='/')
				{
					state = OUT;
					++i;
				}
				break;
		}
	}
	return (state == OUT && isempty(stack_index));
}


/*
	Recieves an array of characters as parameter and tests it to see whether 
	or not the array represents what is called a "special line" or not.
	if the array represents a special line, the value of the constants
	INCREASE OR DECREASE will be returned in order to increase or decrease a count
	of open or brackets in the global file, either way both values count as "true".
	otherwise, if the line is not considered special, the value of 0 will be returned.
*/
int isspecialline(char line[])
{
	int i, temp;
	
	i=0;
	while (line[i]!='\0' && isspace(line[i]))
		++i;
	if ((temp=line[i++]) == '{' || temp == '}')
	{
		while (line[i]!='\0' && isspace(line[i]))
			++i;
		if (line[i]=='\0')
		{
			if (temp=='{')
				return INCREASE;
			else
				return DECREASE;
		}
	}
	return 0;
}

/*
	recieves 3 arguements - 1) a character, 2) an int array representing a 
	stack of parentheses and/or brackets, and 3) an index of the latest 
	character that is saved in the stack + 1.(would be 0 if no characters were saved yet).
	the method then attempts to push or pop a character to or from the stack 
	(depends if its an open or closing parentheses/bracket) and returns the new index.
	if no action was taken, the index that was given as argument will be returned.
	
	for a better understanding check out "parstack.c" and "stackdata.h" files.
*/
int pushorpop(char c, int stack[], int stack_index)
{
	if (c=='{' || c=='[' || c=='(')
		return push(c, stack, stack_index);
	if (c=='}' || c==']' || c==')')
	{
		switch (c)
	{
		case '}': c='{'; break;
		case ')': c='('; break;
		case ']': c='['; break;
	}
		return pop(c, stack, stack_index);
	}
	return stack_index;
}

/* ---------------------- CODE ENDS HERE ---------------------- */

/*	
	This file contains one global/public function - validate(char[line]), as well as two additional static functions used
	the global function in order to validate proper nesting of brackets within one or numerous lines of string. 
*/

/* ----------------------------------INCLUDES, PROTOTYPES AND CONSTANTS SECTION---------------------------------- */
#include "par.h"

/*	isspecialline: checks if the string given as argument is a "special line".
	returns 0 if the line is not special.
	if the line is special it will return INCREASE_CNT for an opening bracket and DECREASE_CNT for a closing bracket. */
static short isspecialline(char line[]);
/*	isbalancedline: checks if the parentheses/brackets within the string given as argument are
	properly nested (line is balanced) or not (line is not balanced).
	returns 1 if the string is balanced or 0 if it isn't. */
static short isbalancedline(char line[]);

enum text_states {OUT, IN_STRING, IN_COMM};	/* defines different states essential for testing the balance of the text */
/* -------------------------------END OF INCLUDES, PROTOTYPES AND CONSTANTS SECTION------------------------------- */


/* -----------------------------------------FUNCTION DEFININTIONS SECTION----------------------------------------- */
/*	validate: prints whether or not the parentheses/brackets in the string given as argument are balanced.
	this method keeps a static counter to keep track of the balance of all the lines that were tested
	since the begining of the program.
	returns whether or not all of the lines combined that went through validation from the begining of the
	program are balanced - 1 if they are, 0 if they aren't.
	special lines will not make the text unbalanced although they count as unbalanced as an individual line. */
short validate(char line[])
{
	static int line_num, special_brack_cnt; /* keeps track of line number and opening/closing brackets in special lines */
	short special; 							/* temporary variable to save the returned value from isspecialline() */
	printf("\n%21s%4d: %s\n", "input for line number ",  ++line_num, line);
	printf("this line is ");
	if ((special=isspecialline(line))) { /* checks if the its a special line and saves the returned value into "special" */
		if (special_brack_cnt!=FAILURE) /* if none of previous tested lines has damaged the balance of the whole input */
			special_brack_cnt += special;
		printf("*NOT* balanced.");
	}
	else if (isbalancedline(line)) 
			printf("balanced.");
	else {							/* if the line is both not special and not balanced */
		special_brack_cnt=FAILURE; /* then the whole input can no longer be seen as balanced */
		printf("*NOT* balanced.");
	}
	return (!special_brack_cnt); /* if the count is 0 - all open brackets had a matching closing bracket */
	
}

/*	isbalancedline: checks if the parentheses/brackets within the string given as argument are
	properly nested (line is balanced) or not (line is not balanced).
	returns 1 if the string is balanced or 0 if it isn't. */
static short isbalancedline(char line[])
{
	static short state;	/*	keeps track of the different states of this and previous lines - static since comments may
							persist throughout numerous lines */
	short stack_index;	/* will save the returned value from pushorpop() which represents it's current stack index */
	short i;
	
	stack_index=pushorpop(INIT_PUSHORPOP); /* reinitialize the stack of pushorpop before scaning the new line */
	for (i=stack_index=0; line[i]!='\0'; ++i) {
		if (isalnum(line[i]) || isspace(line[i]))	/* alphanumeric and whitespace characters are not relevant to the */
			continue;								/* balance of the text, therefore move on to the next character */
		switch (state) {
			case OUT:				/* if outside of any string or comment */
				if (line[i]=='\"')
					state = IN_STRING;
				else if (line[i]=='/' && line[i+1]=='*') {
					state = IN_COMM;
					++i;
				}
				else	/* if the begining of a string or comment was not encountered */
					stack_index = pushorpop(line[i]); /* then the current character may be a bracket - pushorpop() tests it */
				break;
				
			case IN_STRING:			/* check for a character that breaks out of the string */
				if (line[i]=='\"')
					state = OUT;
				break;
				
			case IN_COMM:			/* check for a set of charactes that breaks out of the comment */
				if (line[i]=='*' && line[i+1]=='/') {
					state = OUT;
					++i;
				}
				break;
		}
	}
	return (!stack_index);	/* if the index is 0 - then stack is empty, which means any bracket that existed was 
								properly nested and therefore popped out of the stack eventually */
}

/*	isspecialline: checks if the string given as argument is a "special line".
	returns 0 if the line is not special.
	if the line is special it will return INCREASE_CNT for an opening bracket and DECREASE_CNT for a closing bracket.
	A line is considered to be "special" if it only contains a single bracket - '{' or '}', and no other 
	additional characters that aren't considered as "white space". */
static short isspecialline(char line[])
{
	int i, temp;
	
	i=0;
	while (line[i]!='\0' && isspace(line[i])) /* skip all whitespaces until a character or end of line are reached */
		++i;
	if ((temp=line[i++]) == '{' || temp == '}') {	/* if reached a bracket of the correct type */
		while (line[i]!='\0' && isspace(line[i]))	/* keep scanning for non whitespace characters */
			++i;
		if (line[i]=='\0') {	/* if we've reached the end of the line, then no additional non whitespace character exist */
			if (temp=='{')
				return INCREASE_CNT;	/* if the bracket was an open bracket, return an indication to increase 1 count */
			else
				return DECREASE_CNT;	/* if it was a closing bracket, return an indication to decrease 1 count */
		}
	}
	return 0; /* if no brackets were found then the line is not a special line */
}

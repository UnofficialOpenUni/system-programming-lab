/****************************************************************************************************
*																									*
*	This file was seperated from the main file and fucntion of par.c to provide usage of static		*
*	functions that should not be accesible to an ordinary user of this program in order to prevent	*
*	misuses of those functions that may result in unexpected/undefined behavior of the program.		*
*																									*
****************************************************************************************************/

#include "par.h"

/****************************************************
*			STATIC FUNCTION PROTOTYPES:				*
****************************************************/

/*	isSpecialLine(): checks if the string given as argument is a "special line". returns 0 if the line is not special.
	if the line is special it will return INCREASE_CNT for an opening bracket and DECREASE_CNT for a closing bracket. */
static short isSpecialLine(char line[]);
/*	isBalancedLine(): checks if the parentheses/brackets within the string given as argument are properly nested.
	returns BALANCED if they are, and NOT_BALANCED if they aren't */
static short isBalancedLine(char line[], int *state);
/*	matchBrackets(): send a character argument with the value of INIT_MATCH_BRACKETS to empty the function's stack.
	This function checks whether or not the character argument is a paranthese/bracket, and by making use of
	a stack model, matches corrosponding opening and closing brackets/parentheses. make sure to empty the stack
	before every first use. the balance argument is set to BALANCED if the stack is empty, otherwise, UNBALANCED */
static void matchBrackets(char c, short *balance);
/* initStack(): A static function to be used by matchBrackets() to re/initialize its stack */
static void initStack(short stack[]);
/* push(): push a character into the stack	*/
static void push(char c, short stack[], short *stackIndex);
/* pop(): pop a character out of the stack */
static void pop(char c, short stack[], short *stackIndex);


enum TextStates {OUT, IN_STRING, IN_COMMENT};	/* defines different states essential for testing the balance of the text */


/****************************************************
*					FUNCTIONS:						*
****************************************************/

/*	validate(): validates proper nesting of brackets/parentheses within the character string argument 
	and prints the result. the function also keeps track of the global balance of all of the previous
	strings it had scanned since the initialization of the program by using a static variable.
	returns BALANCED or NOT_BALANCED - based on its current global balance variable */
short validate(char line[])
{
	static int specialBrackCnt, state;			/* keeps track of opening/closing brackets in special lines and state */
	short special; 								/* temporary variable to save the returned value from isSpecialLine() */
	
	if (state == OUT && (special = isSpecialLine(line))) {
		if (specialBrackCnt != FAILURE)
			specialBrackCnt += special;
		printLineBalance(NOT_BALANCED);
	}
	else if (isBalancedLine(line, &state))
			printLineBalance(BALANCED);
	else {										/* if the line is both not special and not balanced */
		specialBrackCnt = FAILURE; 				/* then the whole input can no longer be seen as balanced/valid */
		printLineBalance(NOT_BALANCED);
	}
	return (specialBrackCnt == 0) ? BALANCED: NOT_BALANCED; /* if the count is 0 - all open brackets had matching closing brackets */
	
}

/****************************************************
*				STATIC FUNCTIONS:					*
****************************************************/

/*	isSpecialLine(): checks if the string given as argument is a "special line". returns 0 if the line is not special.
	if the line is special it will return INCREASE_CNT for an opening bracket and DECREASE_CNT for a closing bracket. */
static short isSpecialLine(char line[])
{
	int temp, i = 0;
	
	while (line[i] != '\0' && isspace(line[i])) /* skip all whitespaces until a character or end of string are reached */
		++i;
	if ((temp = line[i++]) == '{' || temp == '}') {		/* saving the non-whitespace char into temp, and checking if its a bracket */
		while (line[i]!='\0' && isspace(line[i]))		/* keep skipping whitespaces */
			++i;
		if (line[i] == '\0') {			/* if we've reached the end of the line, then no additional non whitespace character exist */
			if (temp=='{')
				return INCREASE_CNT;
			else
				return DECREASE_CNT;
		}
	}
	return 0; /* if no brackets were found then the line is not a special line */
}


/*	isBalancedLine(): checks if the parentheses/brackets within the string given as argument are properly nested.
	returns BALANCED if they are, and NOT_BALANCED if they aren't */
static short isBalancedLine(char line[], int *state)
{
	short i, bracketBalance = BALANCED;						/* represents the balance of brackets in the line */
	matchBrackets(INIT_MATCH_BRACKETS, &bracketBalance); 	/* reinitializes the stack of matchBrackets() */
	
	for (i = 0; line[i] != '\0'; ++i) {
		if (isalnum(line[i]) || isspace(line[i]))	/* alphanumeric and whitespace characters are not relevant to the */
			continue;								/* balance of the text, therefore we move on to the next character */
			
		switch (*state) {
			case OUT:
				if (line[i] == '\"')
					(*state) = IN_STRING;
				else if (line[i] == '/' && line[i+1] == '*') {
					(*state) = IN_COMMENT;
					++i;
				}
				else
					matchBrackets(line[i], &bracketBalance); /* the current character may be a bracket - matchBrackets() tests it */
				break;
				
			case IN_STRING:
				if (line[i] == '\"')
					(*state) = OUT;
				break;
				
			case IN_COMMENT:
				if (line[i] == '*' && line[i+1] == '/') {
					(*state) = OUT;
					++i;
				}
				break;
		}
	}
	if ((*state) == IN_STRING)	/* Strings may only last 1 line by definition of this maman */
		(*state) = OUT; 
	return (bracketBalance);
}


/****************************************************
*				BRACKET STACK MODULE:				*
****************************************************/

/*	matchBrackets(): To empty the function's stack, send a character argument with the value of INIT_MATCH_BRACKETS.
	This function checks whether or not the character argument is a paranthese/bracket, and by making use of
	a stack model, matches corrosponding opening and closing brackets/parentheses. make sure to empty the stack
	before every first use. the balance argument is set to BALANCED if the stack is empty, otherwise, UNBALANCED */
static void matchBrackets(char c, short *balance)
{
	static short stack[STACK_SIZE], stackIndex; /* A stack to keep track of matching opening/closing bracket types. */
	
	if (c == INIT_MATCH_BRACKETS) {				/* reinitializes the stack for a new use of the function */
		initStack(stack);
		stackIndex = 0;
	}
	else if (stackIndex != FAILURE) {			/* if no previous push or pop attempts resulted in failure */
		if (c == '{' || c == '[' || c == '(') 
			push(c, stack, &stackIndex);
		else if (c == '}' || c == ']' || c == ')') {
			switch (c) {					
				case '}': c='{'; break;
				case ')': c='('; break;
				case ']': c='['; break;
			}
			pop(c, stack, &stackIndex);
		}
	}
	(*balance) = (!stackIndex) ? BALANCED: NOT_BALANCED;
}

/* 	initStack(): sets all stack values to 0. */
static void initStack(short stack[])
{
	int i;
	for (i = 0; i<STACK_SIZE; stack[i++] = 0);
}

/*	pop(): Attempts to pop a bracket out of the stack with the condition that the  
	bracket given as argument will be equal to the last bracket in the stack.
	stackIndex is set to FAILURE upon, well... you can probably guess... */
static void pop(char c, short stack[], short *stackIndex)
{
	if ((*stackIndex)<=STACK_SIZE && (*stackIndex)>0 && c==stack[(*stackIndex)-1])
		stack[--(*stackIndex)] = 0;
	else
		(*stackIndex) = FAILURE;
}

/*	push(): Attempts to push a bracket into the stack at a certain index.
	stackIndex will be set to FAILURE if the attempt had failed for any reason */
static void push(char c, short stack[], short *stackIndex)
{
	if ((*stackIndex)<STACK_SIZE)
		stack[(*stackIndex)++] = c;
	else
		(*stackIndex) = FAILURE;
}

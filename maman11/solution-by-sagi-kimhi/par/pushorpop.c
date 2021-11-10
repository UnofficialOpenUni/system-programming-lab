/* ----------------------------------INCLUDES, PROTOTYPES AND CONSTANTS SECTION---------------------------------- */
#include "par.h"

/* initstack: A static function to be used by pushorpop() to re/initialize its stack */
static void initstack(short stack[]);
/*	push: A static function to be used by pushorpop() to push a character
	onto its stack.	*/
static short push(char c, short stack[], short stack_index);
/*	pop: A static function to be used by pushorpop() to pop a character
	out of the stack. */
static short pop(char c, short stack[], short stack_index);
/* -------------------------------END OF INCLUDES, PROTOTYPES AND CONSTANTS SECTION------------------------------- */

/* -----------------------------------------FUNCTION DEFININTIONS SECTION----------------------------------------- */
/*	pushorpop: 
	keeps 2 static variables of type "short" of a stack and its current index.
	in order to clear the stack and index, send INIT_PUSHORPOP (-2) as an argument.
	for any other character argument, the function pushes "opening" brackets into its stack,
	or pops them out of its stack if the character argument is the aprropriate type of "closing" bracket 
	for the latests pushed bracket character. 
	if the character argument is not a bracket, no push nor pop action will occure.
	returns: the value of the index of its stack. the value of 0 indicates that the stack is empty.
	the value FAILURE (-1) is returned upon failure of push or pop actions due to mismatching bracket types. */
short pushorpop(short c)
{
	static short stack[STACK_SIZE], stack_index; /* A stack to keep track of matching opening/closing bracket types. */
	if (c==INIT_PUSHORPOP) {		/* reinitializes the stack if the given character equals to INIT_PUSHORPOP (-2) */
		initstack(stack);			/* which represents a reinitialization request for this function */
		return (stack_index=0);
	}
	else if (stack_index!=FAILURE) {	/* if no previous push or pop attempts resulted in failure since initialization */
		if (c=='{' || c=='[' || c=='(')
			return (stack_index=push(c, stack, stack_index));	/* opening brackets are pushed into the stack */
		if (c=='}' || c==']' || c==')') {
			switch (c) {					/* closing brackets are transformed into they're matching opening bracket */
				case '}': c='{'; break;		/* in preparation for the pop action since they must be equal to the latest */
				case ')': c='('; break;		/* pushed character in order for a pop action to be taken */
				case ']': c='['; break;
			}
			return (stack_index=pop(c, stack, stack_index));	/* attempts to pop the matching pair out of the stack */
		}
	}
	return stack_index;
}

/* initstack: A static function to be used by pushorpop() to re/initialize its stack */
static void initstack(short stack[])
{
	int i;
	for (i=0; i<STACK_SIZE; ++i)
		stack[i]=0;
}

/*
	Attempts to pop a character from the stack with the condition that the character given as argument 
	will be equal to the latest character that was pushed into the stack. 
	if the attempt fails, the defined value FAILURE is returned. */
static short pop(char c, short stack[], short stack_index)
{
	if (stack_index<=STACK_SIZE && c==stack[stack_index-1]) {
		stack[--stack_index]=0;
		return stack_index;
	}
	return FAILURE;
}

/*
	Attempts to push a character into the stack at a certain index.
	returns the new index if the character was successfuly pushed, or FAILURE the stack index is already larger than
	or equal to the max stack size (STACK_SIZE) */
static short push(char c, short stack[], short stack_index)
{
	if (stack_index<STACK_SIZE)
	{
		stack[stack_index++]=c;
		return stack_index;
	}
	return FAILURE;
}

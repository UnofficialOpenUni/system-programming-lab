#include "par.h"

/* initstack: A static function to be used by pushorpop() to re/initialize its stack */
static void initstack(short stack[]);
/*	push: A static function to be used by pushorpop() to push a character
	onto its stack.	*/
static short push(char c, short stack[], short stack_index);
/*	pop: A static function to be used by pushorpop() to pop a character
	out of the stack.
*/
static short pop(char c, short stack[], short stack_index);

/*
	recieves 3 arguements - 1) a character, 2) an int array representing a 
	stack of parentheses and/or brackets, and 3) an index of the latest 
	character that is saved in the stack + 1.(would be 0 if no characters were saved yet).
	the method then attempts to push or pop a character to or from the stack 
	(depends if its an open or closing parentheses/bracket) and returns the new index.
	if no action was taken, the index that was given as argument will be returned.
	
	for a better understanding check out "parstack.c" and "stackdata.h" files.
*/
short pushorpop(short c)
{
	static short stack[STACK_SIZE], stack_index;
	if (c==INIT_PUSHORPOP) {
		initstack(stack);
		stack_index=0;
		return stack_index;
	}
	else if (stack_index!=FAILURE) {
		if (c=='{' || c=='[' || c=='(')
			return (stack_index=push(c, stack, stack_index));
		if (c=='}' || c==']' || c==')') {
			switch (c) {
				case '}': c='{'; break;
				case ')': c='('; break;
				case ']': c='['; break;
			}
			return (stack_index=pop(c, stack, stack_index));
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
	Attempts to pop a character from the stack with the condition that the 
	character given as argument will be equal to the latest int that
	was pushed into the stack. 
	if the attempt fails, the constant value FAILURE is returned.
*/
static short pop(char c, short stack[], short stack_index)
{
	if (stack_index>0 && stack_index<=STACK_SIZE && c==stack[stack_index-1]) {
		stack[--stack_index]=0;
		return stack_index;
	}
	return FAILURE;
}

/*
	Attempts to push a character into the stack at a certain index.
	all 3 - the character, stack, and index, must be given as arguments.
	the stack size must be equal to the constant STACK_SIZE or the method WILL cause
	problems! - Returns the new index if the attempt succeeds or the value
	of FAILURE if the attempt fails (some conditions were not met).
*/
static short push(char c, short stack[], short stack_index)
{
	if (stack_index<STACK_SIZE && stack[stack_index]==0)
	{
		stack[stack_index++]=c;
		return stack_index;
	}
	return FAILURE;
}

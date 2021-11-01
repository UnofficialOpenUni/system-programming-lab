#include <stdio.h>
#include "stackdata.h"

/*
	Recives an int array as a parameter and sets all of its saved values to 0.
	the given array must be set beforehand to the constant value of STACK_SIZE!!\
	this method does not have any safety tests and WILL cause problems if not used
	appropriately.
*/
void initstack(int stack[])
{
	int i;
	
	for (i=0; i<STACK_SIZE; ++i)
		stack[i]=0;
}

/*
	Attempts to pop a character from the stack with the condition that the 
	character given as argument will be equal to the latest int that
	was pushed into the stack. 
	if the attempt fails, the constant value STACK_FAILURE is returned.
*/
int pop(char c, int stack[], int stack_index)
{
	if (stack_index>0 && stack_index<=STACK_SIZE && c==stack[stack_index-1])
	{
		stack[--stack_index]=0;
		return stack_index;
	}
	return STACK_FAILURE;
}

/*
	Attempts to push a character into the stack at a certain index.
	all 3 - the character, stack, and index, must be given as arguments.
	the stack size must be equal to the constant STACK_SIZE or the method WILL cause
	problems! - Returns the new index if the attempt succeeds or the value
	of STACK_FAILURE if the attempt fails (some conditions were not met).
*/
int push(char c, int stack[], int stack_index)
{
	if (stack_index<STACK_SIZE && stack[stack_index]==0)
	{
		stack[stack_index++]=c;
		return stack_index;
	}
	return STACK_FAILURE;
}

/* Returns true if the index given as arguement equals to 0, false otherwise.*/
int isempty(int stack_index)
{
	return (stack_index==0);
}

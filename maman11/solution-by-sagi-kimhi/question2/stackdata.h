
#define STACK_SIZE 50 /*the stack size to be initiated to safely use the functions declared in this file*/
#define STACK_FAILURE -1 /* The returned value for a failed push or pop attempt */

/*
	declarations of the methods from file "parstack.c"
*/
void initstack(int stack[]);
int push(char c, int stack[], int stack_index);
int pop(char c, int stack[], int stack_index);
int isempty(int stack_index);


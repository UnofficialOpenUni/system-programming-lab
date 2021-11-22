#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100
#define RESULT_FAILED 0
#define RESULT_SUCCESS 1
#define RESULT_SPECIAL_OPEN 2
#define RESULT_SPECIAL_CLOSE 3

short scanAndValidateLines();
short validate(char*);
short isSpecialLine(char*);
void push(char**,char);
char pop(char**);


int main()
{
    while(scanAndValidateLines());
    return 1;
}

short scanAndValidateLines()
{
    static short textBalanced = 1; 
    char line[MAX_LINE_LENGTH]; /* The line of code sent by the user. */
    int specialCharCount = 0; /* Checkes for the amount of curly brackets, if there is an anequal amount of opening/closings, the code is not balanced */
    short result; /* Gets the result from the validate function */
    if (fgets(line, MAX_LINE_LENGTH, stdin)) /* Get a line of code as an input */ 
    {
        printf("Line input: %s\n", line);
        result = validate(line);
        switch(result) /* Check the result state */
        {
            case RESULT_FAILED:
                printf("This line is not valid!\n");
                textBalanced = 0;
                break;
            case RESULT_SUCCESS:
                printf("This line is valid\n");
                break;
            case RESULT_SPECIAL_OPEN:
                printf("This line is not valid. but might not affect the text balance\n");
                specialCharCount++;
                break;
            case RESULT_SPECIAL_CLOSE:
                printf("This line is not valid. but might not affect the text balance\n");
                specialCharCount--;
                break;
        }
        return 1; /* Should continue to next line */
    }
    if(specialCharCount != 0) textBalanced=0; /* An anequal amount of closing/opening curly brackets */
    if(textBalanced){
        printf("The full text is balanced.\n");}
    else
        printf("The full text is not balanced\n");
    return 0;
}

short validate(char *line)
{
    static short stateInComment = 0;
    short stateInQuote = 0;
    char curr;
    char* stack = (char*)malloc(sizeof(char)*(MAX_LINE_LENGTH+1)); /* Create a stack, size of max line +1 for an empty char, flag for empty stack */
    char par;
    push(&stack,'\0'); /* Stack empty flag */
    if(strchr(line, '{')) /* Check if only a curly bracket in this line */
    {
        if(isSpecialLine(line))
        return RESULT_SPECIAL_OPEN;
    }
        if(strchr(line, '}')) /* Ditto */
    {
        if(isSpecialLine(line))
        return RESULT_SPECIAL_CLOSE;
    }
    while((curr=*line++)!='\0')
    {
        if(curr=='"') /* Checks if code is in quotes */
        {
            stateInQuote = !stateInQuote;
        }
        if(stateInQuote) continue;
        if(curr=='/' && *line=='*') /* Is this a comment start? */
            stateInComment = 1;
        if(curr=='*' && *line=='/') /* Is this a comment end? */
            stateInComment = 0;    
        if(stateInComment) continue; 
        switch (curr)
        {
        case '(':
        case '[':
        case '{':
            push(&stack, curr); /* Insert an opening bracket to the stack */
            break;
        case ')':
            par=pop(&stack); /* Remove an opening bracket from stack, and validate it is the correct one */
            if(par!='(') return RESULT_FAILED;
            break;
        case ']':
            par=pop(&stack);
            if(par!='[') return RESULT_FAILED;
            break;
        case '}':
            par=pop(&stack);
            if(par!='{') return RESULT_FAILED;
            break;
        }
    }
    if(*stack == '\0') /* Stack is empty at the end, validate seccussful */
        return RESULT_SUCCESS;
    return RESULT_FAILED;
}

/* Checks if the line contains only of empty spaces and a single curly bracket */
short isSpecialLine(char *line)
{
    char *point = line;
    char curr;
    short specialFound = 0;
    while((curr=*point++)!='\0')
    {
        if(!isspace(curr))
        {
            if(specialFound || !(curr == '{' || curr == '}')) return 0;
            specialFound = 1;
        }
    }
    return 1;
}

void push(char **stack, char c)
{
    (*stack)++; /* Increment the stack */
    **stack=c;
}

char pop(char **stack)
{
    char c = **stack;
    (*stack)--; /* Decrement the stack */
    return c;
}


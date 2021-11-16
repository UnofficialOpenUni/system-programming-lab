#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 81 	/* maximum length allowed for a line of input including the last null character */
#define ASCII_TO 45 	/* the ascii value of the character '-' */

/* 	printUserInstructionMessage(): Prints a friendly message to the user, explaining the 
	functionality of the program and requesting a line of input. */
void printUserInstructionMessage();
/*	contract(): Shortens a consecutive series of 3 or more alphanumeric characters within the string
	of characters in s1, and saves the shortened string version into s2. */
void contract(char s1[], char s2[]);


int main() 
{
	char userInput[MAX_LENGTH]; 		/* (s1) The array which in which the input will be saved to */
	char shortenedOutput[MAX_LENGTH];	/* (s2) The array to which contract will save the shortened string */
	
	printUserInstructionMessage();
	fgets(userInput, MAX_LENGTH, stdin);
	contract(userInput, shortenedOutput);
	printf("\nYour input was: \n%s\n", userInput);
	printf("\nThe shortened string is: \n%s\n", shortenedOutput);
	
	return 0;
}

/****************************************************
*				FUNCTION DEFINITIONS:				*
****************************************************/

/* 	printUserInstructionMessage(): Prints a friendly message to the user, explaining the 
	functionality of the program and requesting a line of input. */
void printUserInstructionMessage()
{
	printf("\n********************** Hello And Welcome! **********************\n");
	printf("This program is meant to help you shorten consecutive series\n");
	printf("of 3 or more alphanumeric characters within a line of string.\n");
	printf("Please make sure that your line of input is no longer than 80 characters.\n");
	printf("If it is longer, then only the first 80 will be scanned and shortened.\n\n");
	printf("as an example, the input abcdef12345 will be shortened to a-f1-5 \n\n");
	printf("In order to begin, please provide a line of input...\n");
	printf("*******************************************************************\n\n");
}

/*	contract(): Shortens a consecutive series of 3 or more alphanumeric characters within the string
	of characters in s1, and saves the shortened string version into s2. */
void contract(char s1[], char s2[])
{
	int i, j, k;
	
	for (i=j=k=0; s1[i]!='\0'; ++i) {
		if (isalnum(s1[i]))
			for (k=i; isalnum(s1[k+1]) && s1[k]+1==s1[k+1]; ++k); /* set k to the index of the last alphanumeric character in a serie */
		if (k>i) {
			if ((k-i)>1) {		/* the serie is at least 3 characters long (s1[i],s1[i+1],s1[k]) */
				s2[j++]=s1[i];
				s2[j++]=ASCII_TO;
				s2[j++]=s1[(i=k)];
				continue;
			}
			s2[j++]=s1[i++];
		}
		s2[j++]=s1[i];
	}
	s2[j]='\0';
}

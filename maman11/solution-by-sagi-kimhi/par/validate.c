#include "par.h"

enum text_states {OUT, IN_STRING, IN_COMM};			/* defines different text states */

/*
	This method requires 2 arguments - 1) the string to be tested, 2) an int representing whether or not the line 
	is a special line. The method prints the input, tests its balance, and prints whether
	it is balanced or not.
	This method does not tell the difference between a special line and an ordinary line
	and therefore this must be pretested and given as an argument.
*/
short validate(char line[])
{
	static int line_num, special_brack_cnt;
	short special;
	printf("\n%21s%4d: %s\n", "input for line number ",  ++line_num, line);
	printf("this line is ");
	if ((special=isspecialline(line))){
		if (special_brack_cnt!=FAILURE)
			special_brack_cnt += special;
		printf("*NOT* balanced.");
	}
	else if (isbalancedline(line))
			printf("balanced.");
	else {
		special_brack_cnt=FAILURE;
		printf("*NOT* balanced.");
	}
	return (!special_brack_cnt) ? 1: 0;
	
}

/*
	This methods checks if the parentheses/brackets of the character array given 
	as argument are balanced - returns true if it's balanced, false otherwise.
	This method does not tell the difference between a special line and an ordinary line.
*/
short isbalancedline(char line[])
{
	static int state;
	short i, stack_index;
	
	stack_index=pushorpop(INIT_PUSHORPOP);
	for (i=stack_index=0; line[i]!='\0'; ++i) {
		if (isalnum(line[i]))
			continue;
		switch (state) {
			case OUT:
				if (line[i]=='\"')
					state = IN_STRING;
				else if (line[i]=='/' && line[i+1]=='*') {
					state = IN_COMM;
					++i;
				}
				else
					stack_index = pushorpop(line[i]);
				break;
				
			case IN_STRING:
				if (line[i]=='\"')
					state = OUT;
				break;
				
			case IN_COMM:
				if (line[i]=='*' && line[i+1]=='/') {
					state = OUT;
					++i;
				}
				break;
		}
	}
	return (!stack_index);
}

/*
	Recieves an array of characters as parameter and tests it to see whether 
	or not the array represents what is called a "special line" or not.
	if the array represents a special line, the value of the constants
	INCREASE OR DECREASE will be returned in order to increase or decrease a count
	of open or brackets in the global file, either way both values count as "true".
	otherwise, if the line is not considered special, the value of 0 will be returned.
*/
short isspecialline(char line[])
{
	int i, temp;
	
	i=0;
	while (line[i]!='\0' && isspace(line[i]))
		++i;
	if ((temp=line[i++]) == '{' || temp == '}') {
		while (line[i]!='\0' && isspace(line[i]))
			++i;
		if (line[i]=='\0') {
			if (temp=='{')
				return INCREASE;
			else
				return DECREASE;
		}
	}
	return 0;
}

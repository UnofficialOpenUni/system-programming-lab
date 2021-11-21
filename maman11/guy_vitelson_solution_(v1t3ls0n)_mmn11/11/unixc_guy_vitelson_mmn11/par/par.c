/* 
    par.c
    
    ### Program Description ###
    The program gets from the use lines of text (that suppose to be c code that contains brackets), the program
    evaluate of the brackets within each line user enter are valid by the C language syntax, the program then notify
    the user if the line of code he just entered is valid or not, and in the end of the input (when user exit or input from file if over),
    the program write if the whole text user have entered is valid (globally) or not.
    In the global evaluation of the user input at the end of the program, the program will treat special cases of invalid lines single 
    that contained single open or closing curly brackets and whitespace characters only, the program will check if all of those special lines
    of brackets are balanced by checking if for any special line with open curly bracket there is a corresponding special line holding closing curly bracket.

    Author: Guy Vitelson
    Date: 21/11/2021
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 101
#define ASCII_NEW_LINE 10
#define ASCII_EMPTY_SPACE 32
#define ASCII_DOUBLE_QUOTES 34
#define ASCII_ASTERISK 42
#define ASCII_FORWARD_SLASH 47
#define ASCII_OPENING_SQUARE_BRACKETS 91
#define ASCII_CLOSING_SQUARE_BRACKETS 93
#define ASCII_OPENING_CURLY_BRACES 123
#define ASCII_CLOSING_CURLY_BRACES 125
#define ASCII_OPENING_ROUND_BRACKETS 40
#define ASCII_CLOSING_ROUND_BRACKETS 41
typedef enum
{
    isOut = 3,
    inComment = 4,
    inString = 5,
    newLine = 6,
    inMultiLineComment = 7,
    preFalse = -2

} State;

typedef enum
{
    False,
    True,
} Bool;

/* @ Function: isOpeningBracket 
   @ Arguments: the function gets c argument that is an integer that suppose to hold a value ascii character
   @ Desciption: The function checks if the value its argument is sort of an opened bracket { [ ( valid in C and return True or False typedef variable
*/
Bool isOpeningBracket(int c);

/* @ Function: isClosingBracket
   @ Arguments: the function gets c argument that is an integer that suppose to hold a value ascii character
   @ Desciption: The function checks if the value its argument is sort of an closed bracket } ] ) valid in C and return True or False typedef variable
*/
Bool isClosingBracket(int c);

/* @ Function: areBracketsOfSameTypeButInverse
   @ Arguments: the function gets 2 integer arguments, each of them suppose to hold ascii value of a character, the first one 
   supposed to be a opening bracket of some sort and the second argument supposed to be a closed bracket of some sort.
   @ Desciption: The function checks if its 2 arguments are brackets of the same type and that the first argument is an opened bracket and 
   the second argument is the closed version of that bracket.
*/
Bool areBracketsOfSameTypeButInverse(int o, int c);

/* @ Function: evalBracketSequence
   @ Arguments: The function gets 3 argument, first is an array of open brackets characters, the second is an array of closed brackets
   characters, the third argument is the length of both arrays, the arrays suppose to have the same length.
   @ Desciption: the function checks whether the brackets in the opened and closed brackets arrays representing a valid sequence of opening
   and closing brackets sequence of characters in C language. for exampel opened array containing {[( and closed array containing )]} 
   will return True because the closed brackets array holds the corresponding closed versions of brackets in the right order.

   The way the function work is by the logic that the first character in the opened brackets array will have its corresponding closed version
   at the end of the closed brackets array, then the next character in the opened array will have its corresponding version in the closed array
   at the location of 1 character previous to the last character array and so forth.

   The function loops over the 2 arrays, on the closing array it is iterating from end to start and on the opened brackets
   array it iterates from begining to the end, on every iteration of the while loop it compares if the current brackets on both arrays are
   the same type of brackets but with reversed direction using the areBracketsOfSameTypeButInverse function the first time
   a pair of brackets in those arrays do not match the function returns False and end the function.
*/
Bool evalBracketSequence(char opening[MAX_LINE_LENGTH / 2], char closing[MAX_LINE_LENGTH / 2], int length);

/* @ Function: evalSingleLine
   @ Arguments: The function gets 2 argument, first is a string of opening or closing brackets, the second argument is the length of that array.
   @ Desciption: The function evaluates if the sequence of brackets it gets representing valid sequence of opening and closing brackets in 
   C language, the function return True or False typedef variables correspondingly.
*/
Bool evalSingleLine(char brackets[MAX_LINE_LENGTH], int length);

/* @ Function: handleState
   * A state is a concept represent our current "mode" in the evalution proccess, we are in different mode of validating
   brackets on each line depending if we are currently inside a comment or inside a string or inside a multiline comment 
   or if now we encountered new line character input and we need to evaluate this line now.
   
   @ Arguments: The first argument function gets represents the state we are currently in, the next argument (current) represents 
   the current character value we got from the user input, the next argument (prev) represent the last character input we got from user,
   the next argument (commentStrCharCount) is a number which represent the number of characters currently been counted inside 
   a comment expression in caset we are inside a comment.The function returns us the updated value of the state we are in as a typedef
   State variable .
   @ Desctiption: The function evaluate what value our current state must have after taking into account our previous state and the last
   character input we got from the user.

*/
State handleState(State prevState, int current, int prev, int commentStrCharCount);

/* @ Function: getTextAndAnalyzeFully
   @ Arguments: the function get not arguments.
   @ Desctiption: The function start listening to input from user and evaluates brackets in each line of text user entered 
   the moment the user entering a new line and print the result each time (each line). At the end of the input the function
   evaluates if the whole text is globally valid or not.
*/
void getTextAndAnalyzeFully();

/* @ Function: printCurrentLineResult
   @ Arguments: the function gets one argument that is of typedef Bool and it represents the validity value (true or false) of the current line.
   @ Desctiption: The function prints message of valid or not valid to user in a visual nice way. 
*/
void printCurrentLineResult(Bool result);

/* @ Function: evalTextGlobally
   @ Arguments: The first argument needs to represent the global result value we currently have while we still inside
    getTextAndAnalyzeFully function which we are about to exit now, next argument is the current brackets string we saved
    from current line, next argument is the last character we got from user input, next 2 arguments are the closed and opened bracket 
    counts from all special case lines.
    @ Desctiption: The function evaluate globally if all of users input is valid or not and then prints the result.
*/
void evalTextGlobally(Bool lastResult, char bracketsOfLastLine[MAX_LINE_LENGTH], int lastChar, int closedCount, int openCount);

int main()
{
    printf("~ In this program each line of your code will be evaluated seperately,\nand result will show up immediately as you press enter to start a new line.\nAt the end of you input you will see the evaluation result for the whole text you've entered.\nThe global result takes count of special lines with correct open or closed curly braces.\n");
    printf("\n\n *** ~ START NOW (Insert Text Please) ~ ***\n\n\n\n");
    getTextAndAnalyzeFully();
    return 0;
}
void getTextAndAnalyzeFully()
{
    Bool globalResult = True;
    Bool singleLineResult = True;
    Bool isPossiblySpecialLine = True;
    State currentState = isOut;
    char brackets[MAX_LINE_LENGTH] = {0};
    int preDetermentResult = -1;
    int j;
    int c, prevChar;
    int lonelyOpenBracetsCount, lonelyCloseBracetsCount, commentStrCharCount;
    c = j = commentStrCharCount = prevChar = lonelyCloseBracetsCount = lonelyOpenBracetsCount = 0;
    printf("The Line (First line) You Entered is:\n");
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        if (isspace(c) != 0 && c != ASCII_NEW_LINE)
            c = ASCII_EMPTY_SPACE;

        currentState = handleState(currentState, c, prevChar, commentStrCharCount);

        switch (currentState)
        {
        case preFalse:
        {
            isPossiblySpecialLine = False;
            preDetermentResult = False;
            break;
        }

        case inComment:
        {
            commentStrCharCount++;
            preDetermentResult = True;
            break;
        }
        case inMultiLineComment:
        {
            commentStrCharCount++;
            preDetermentResult = True;
            break;
        }
        case inString:
        {
            preDetermentResult = True;
            break;
        }

        case isOut:
        {
            if (isOpeningBracket(c) || isClosingBracket(c) || c == ASCII_EMPTY_SPACE)
            {
                if (c != ASCII_EMPTY_SPACE)
                {
                    brackets[j] = c;
                    j++;
                }
            }
            else
                isPossiblySpecialLine = False;

            commentStrCharCount = 0;
            preDetermentResult = -1;
            break;
        }

        case newLine:
        {
            if (preDetermentResult != -1)
                singleLineResult = preDetermentResult;
            else
                singleLineResult = evalSingleLine(brackets, j);

            if (globalResult)
            {
                /*
                    If global result have not been set to false yet by first case of line being not valid and not special one
                    at the same time - then we are checking if this non valid line is special one,
                    if this line is special in a valid way, we updated count of open/closed lonely brackets on special lines.
                    the first time current line is not special and not valid or special lines balance breaks, 
                    we set global result to false and never enter this if block again.
                */

                if (!singleLineResult && isPossiblySpecialLine)
                {
                    if (brackets[0] == ASCII_OPENING_CURLY_BRACES)
                        lonelyOpenBracetsCount++;
                    else
                        lonelyCloseBracetsCount++;

                    if (lonelyCloseBracetsCount > lonelyOpenBracetsCount)
                        globalResult = False;
                }
            }
            printCurrentLineResult(singleLineResult);

            /* Now we reset all variables we need for next line input evaluation */
            memset(brackets, 0, j);
            currentState = isOut;
            singleLineResult = True;
            preDetermentResult = -1;
            j = prevChar = 0;
            isPossiblySpecialLine = True;

            /*
               Just before we make another iteration of this while loop which means user necesserly inserted
               some character otherwise c would be EOF and we will exit the loop, 
               we need to print this message for the next line user will complete inserting upfront and after we printed if current line is valid or not,  
             */
            printf("The Line You Entered is:\n");
        }
            /* saving the real last character user have inserted for later evaluation by handleState, current char will be saved
            into c variable the moment we enter this while loop
            */
        }
        prevChar = c;
    }

    evalTextGlobally(globalResult, brackets, prevChar, lonelyCloseBracetsCount, lonelyOpenBracetsCount);
}

void evalTextGlobally(Bool lastResult, char bracketsOfLastLine[MAX_LINE_LENGTH], int lastChar, int closedCount, int openCount)
{
    Bool lastSingleLineResult = True;
    if (lastChar != ASCII_NEW_LINE)
    {
        lastSingleLineResult = evalSingleLine(bracketsOfLastLine, strlen(bracketsOfLastLine));
        printCurrentLineResult(lastSingleLineResult);
    }

    if (lastResult && !lastSingleLineResult && strlen(bracketsOfLastLine) == 1)
    {

        if (lastChar == ASCII_CLOSING_CURLY_BRACES)
            closedCount++;
        else if (lastChar == ASCII_OPENING_CURLY_BRACES)
            lastResult = False;
    }

    if (closedCount != openCount)
        lastResult = False;

    if (lastResult)
        printf("\n*** Text is Globally Valid :) ***\n\n");
    else
        printf("\n*** Text is Not Globally Valid! ): ***\n\n");
}

void printCurrentLineResult(Bool result)
{
    if (result == True)
        printf("\n*** Valid :) ***\n");
    else
        printf("\n*** Not Valid! :( ***\n");

    printf("\n##################################################  \n\n\n");
}

State handleState(State prevState, int current, int prev, int commentStrCharCount)
{
    State state = prevState;
    state = state == inMultiLineComment ? inComment : state;

    switch (current)
    {
    case ASCII_DOUBLE_QUOTES:
    {
        if (state == inComment)
            break;
        else
        {
            if (state == inString)
                state = isOut;
            else if (state == isOut)
                state = inString;
            break;
        }
    }

    case ASCII_FORWARD_SLASH:
    {
        if (state == inString)
            break;
        else
        {

            if (prev == ASCII_ASTERISK)
            {

                if (state == inComment && commentStrCharCount > 1)
                    state = isOut;
                else
                    state = preFalse;
                /* 
                    If state == in comment is false:
                    it is a special error that happens if user type (* and a / straight after) to close comment
                    that does not exist, if state is not a string and not a comment then a closing comment cannot be valid

                    If commentstrcharcount > 1 is false:
                    it means that the last 3 character in input were / than * and than / without anything between 
                    its a serious mistake in comment syntax
                */
            }
        }
        break;
    }

    case ASCII_ASTERISK:
    {
        if (state == inString)
            break;
        else
        {
            if (state == isOut && prev == ASCII_FORWARD_SLASH)
                state = inComment;
        }
        break;
    }

    case ASCII_NEW_LINE:
    {
        if (state == inComment)
        {
            printCurrentLineResult(True);
            state = inMultiLineComment;
        }
        else
            state = newLine;

        break;
    }

    default:
        break;
    }

    return state;
}
Bool evalSingleLine(char brackets[MAX_LINE_LENGTH], int length)
{
    int i, j = 0, k = 0, current = 0;
    Bool result = True;
    char open[MAX_LINE_LENGTH / 2] = {0}, closed[MAX_LINE_LENGTH / 2] = {0};
    if (length == 0) /* If there is no brackets at all on that line it can be valid automatically bracketswize.*/
        return True;

    else if (length == 1) /* If there is only one bracket character on that line it automatically not valid.*/

        return False;

    else
    {
        for (i = 0; brackets[i]; i++)
        {
            current = (int)brackets[i];
            if (isOpeningBracket(current))
            {
                open[j] = current;
                j++;
            }
            else if (isClosingBracket(current))
            {
                closed[k] = current;
                k++;

                if (k > j) /* If k > j return false because bracket sequence cannot hold more closing brackets then opening brackets!*/
                    return False;

                else if (j == k) /* If opened and closed brackets array length are equal its time to evaluate brackets sequence */
                {
                    if (j == 1)
                        result = areBracketsOfSameTypeButInverse(open[0], closed[0]);
                    else if (j > 1)
                        result = evalBracketSequence(open, closed, k);

                    if (result == False)
                        return False;
                    else
                    {
                        memset(open, 0, j);
                        memset(closed, 0, k);
                        j = k = 0;
                    }
                }
            }
        }
    }

    if (j != k)
        return False;
    return result;
}
Bool evalBracketSequence(char opening[MAX_LINE_LENGTH / 2], char closing[MAX_LINE_LENGTH / 2], int length)
{

    int i = 0, j = length - 1, result = True;
    while (i < length && j > 0)
    {
        if (areBracketsOfSameTypeButInverse((int)opening[i], (int)closing[j]))
        {
            i++;
            j--;
        }
        else
            return False;
    }
    return result;
}
Bool areBracketsOfSameTypeButInverse(int o, int c)
{
    if (o == ASCII_OPENING_SQUARE_BRACKETS && c == ASCII_CLOSING_SQUARE_BRACKETS)
        return True;
    else if (o == ASCII_OPENING_CURLY_BRACES && c == ASCII_CLOSING_CURLY_BRACES)
        return True;
    else if (o == ASCII_OPENING_ROUND_BRACKETS && c == ASCII_CLOSING_ROUND_BRACKETS)
        return True;
    else
        return False;
}
Bool isClosingBracket(int c)
{
    return (c == ASCII_CLOSING_SQUARE_BRACKETS || c == ASCII_CLOSING_CURLY_BRACES || c == ASCII_CLOSING_ROUND_BRACKETS) ? True : False;
}
Bool isOpeningBracket(int c)
{
    return (c == ASCII_OPENING_SQUARE_BRACKETS || c == ASCII_OPENING_CURLY_BRACES || c == ASCII_OPENING_ROUND_BRACKETS) ? True : False;
}

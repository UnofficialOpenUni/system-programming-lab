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

Bool isOpeningBracket(int asciValue);
Bool isClosingBracket(int asciValue);
Bool areBracketsOfSameTypeButInverse(int o, int c);
Bool evalBracketSequence(char opening[MAX_LINE_LENGTH / 2], char closing[MAX_LINE_LENGTH / 2], int length);
Bool evalSingleLine(char line[MAX_LINE_LENGTH], int length);
State handleState(State prevState, int current, int prev, int commentStrCharCount);
void getTextAndAnalyzeFully();
void printCurrentLineResult(Bool result);
void evalTextGlobally(Bool lastResult, char lastLine[MAX_LINE_LENGTH], int lastChar, int closedCount, int openCount);

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
    char line[MAX_LINE_LENGTH] = {0};
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
                    line[j] = c;
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
                singleLineResult = evalSingleLine(line, j);

            if (globalResult)
            {
                /*
                    IF GLOBAL RESULT HAVE NOT BEEN SET TO FALSE YET BY FIRST CASE OF LINE BEING NOT VALID AND NOT SPECIAL ONE
                    AT THE SAME TIME - THEN WE ARE CHECKING IF THIS NON VALID LINE IS SPECIAL ONE,
                    IF THIS LINE IS SPECIAL IN A VALID WAY, WE COUNT AND REMEMBER THIS, THE FIRST TIME CURRENT LINE IS NOT SPECIAL
                    AND NOT VALID OR SPECIAL LINES BALANCE BREAKS, WE SET GLOBAL RESULT TO FALSE AND NEVER ENTER THIS IF BLOCK AGAIN
                */

                if (!singleLineResult && isPossiblySpecialLine)
                {
                    if (line[0] == ASCII_OPENING_CURLY_BRACES)
                        lonelyOpenBracetsCount++;
                    else
                        lonelyCloseBracetsCount++;

                    if (lonelyCloseBracetsCount > lonelyOpenBracetsCount)
                        globalResult = False;
                }
            }
            printCurrentLineResult(singleLineResult);

            /* now we reset all variables we need for next line input evaluation */
            memset(line, 0, j);
            currentState = isOut;
            singleLineResult = True;
            preDetermentResult = -1;
            j = prevChar = 0;
            isPossiblySpecialLine = True;
            /*
               just before we make another iteration of this while loop which means user necesserly inserted
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

    evalTextGlobally(globalResult, line, prevChar, lonelyCloseBracetsCount, lonelyOpenBracetsCount);
}

void evalTextGlobally(Bool lastResult, char lastLine[MAX_LINE_LENGTH], int lastChar, int closedCount, int openCount)
{
    Bool lastSingleLineResult = True;
    if (lastChar != ASCII_NEW_LINE)
    {
        lastSingleLineResult = evalSingleLine(lastLine, strlen(lastLine));
        printCurrentLineResult(lastSingleLineResult);
    }

    if (lastResult && !lastSingleLineResult && strlen(lastLine) == 1)
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
        /* /*/
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
                {
                    /* 
                    SPECIAL ERROR THAT HAPPENS IF USER TYPE (* AND A / STRAIGHT AFTER) TO CLOSE COMMENT
                    THAT DOES NOT EXIST,IF STATE IS NOT A STRING AND NOT A COMMENT THEN A CLOSING COMMENTCANNOT BE VALID

                    OR IF last 3 character in input were / than * and than / without anything between its a mistake in comment syntax*/

                    state = preFalse;
                    break;
                }
            }

            break;
        }
    }

    case ASCII_ASTERISK:
    {
        if (state == inString)
            break;
        else
        {
            if (state == isOut && prev == ASCII_FORWARD_SLASH)
            {
                state = inComment;
            }

            break;
        }
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

Bool evalSingleLine(char line[MAX_LINE_LENGTH], int length)
{
    int i, j = 0, k = 0, current = 0;
    Bool result = True;
    char open[MAX_LINE_LENGTH / 2] = {0}, closed[MAX_LINE_LENGTH / 2] = {0};
    /* if no trimmed characters were saved to line variable currently,
    it means that we have not enter any input that need to be evalutate, there is nothing
    that influence the state we are in (string, comment,etc) and not any type of brackets
    on that line so it can be valid automatically.
    */
    if (length == 0)
        return True;

    /* if there is only one character on this line it cannot possibly hold valid opening and closing brackets,
    therefor automatically not valid.*/
    else if (length == 1)
        return False;

    else
    {
        for (i = 0; line[i]; i++)
        {
            current = (int)line[i];
            if (isOpeningBracket(current))
            {
                open[j] = current;
                j++;
            }
            else if (isClosingBracket(current))
            {
                closed[k] = current;
                k++;
                /* 
                if k > j return false because bracket sequence cannot hold more closing
                brackets then opening brackets!
            */
                if (k > j)
                    return False;

                /* is length are equal its time to evaluate brackets sequence */
                else if (j == k)
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

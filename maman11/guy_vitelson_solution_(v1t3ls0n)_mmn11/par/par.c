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
Bool evalSingleLine(char line[MAX_LINE_LENGTH]);
State handleState(State prevState, int current, int prev);

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
    State currentState = isOut;
    int preDetermentResult = -1, c, j, lastCharBeforeEOF, prevChar, lonelyOpenBracetsCount, lonelyCloseBracetsCount;
    c = j = lastCharBeforeEOF = prevChar = lonelyCloseBracetsCount = lonelyOpenBracetsCount = 0;
    char line[MAX_LINE_LENGTH] = {0};
    printf("The Line (First line) You Entered is:\n");
    while ((c = getchar()) != EOF)
    {
        lastCharBeforeEOF = c;
        putchar(c);
        if (isspace(c) != 0 && c != ASCII_NEW_LINE)
            c = ASCII_EMPTY_SPACE;
        currentState = handleState(currentState, c, prevChar);

        switch (currentState)
        {
        case preFalse:
        {
            preDetermentResult = False;
            break;
        }

        case inComment:
        {
            preDetermentResult = j > 0 ? -1 : True;
            break;
        }
        case inString:
        {
            preDetermentResult = j > 0 ? -1 : True;
            break;
        }

        case isOut:
        {
            if (c != ASCII_EMPTY_SPACE)
            {
                line[j] = c;
                j++;
            }

            break;
        }

        case newLine:
        {
            if (preDetermentResult != -1)
            {

                singleLineResult = preDetermentResult;
                preDetermentResult = -1;
            }
            else
            {

                if (j == 0)
                    singleLineResult = True;
                else if (j > 0)
                {
                    if (j > 1)
                        singleLineResult = evalSingleLine(line);
                    else if (j == 1)
                    {
                        singleLineResult = False;

                        if (globalResult == True)
                        {
                            /*
            IF GLOBAL RESULT HAVE NOT BEEN SET TO FALSE YET BY FIRST CASE OF LINE BEING NOT VALID AND NOT SPECIAL ONE
            AT THE SAME TIME - THEN WE ARE CHECKING IF THIS NON VALID LINE IS SPECIAL ONE,
             IF THIS LINE IS SPECIAL IN A VALID WAY, WE COUNT AND REMEMBER THIS, THE FIRST TIME CURRENT LINE IS NOT SPECIAL
             AND NOT VALID OR SPECIAL LINES BALANCE BREAKS, WE SET GLOBAL RESULT TO FALSE AND NEVER ENTER THIS IF BLOCK AGAIN
            */
                            if (line[0] == ASCII_OPENING_CURLY_BRACES || line[0] == ASCII_CLOSING_CURLY_BRACES)
                            {
                                if (line[0] == ASCII_OPENING_CURLY_BRACES)
                                    lonelyOpenBracetsCount++;
                                else
                                    lonelyCloseBracetsCount++;

                                if (lonelyCloseBracetsCount > lonelyOpenBracetsCount)
                                    globalResult = False;
                            }
                            else
                                globalResult = False;
                        }
                    }
                }
            }

            printCurrentLineResult(singleLineResult);
            memset(line, 0, j);
            prevChar = 0;
            currentState = isOut;
            singleLineResult = True;
            j = 0;
            printf("The Line You Entered is:\n");
        }
        }
        prevChar = c;
    }

    evalTextGlobally(globalResult, line, lastCharBeforeEOF, lonelyCloseBracetsCount, lonelyOpenBracetsCount);
}

void evalTextGlobally(Bool lastResult, char lastLine[MAX_LINE_LENGTH], int lastChar, int closedCount, int openCount)
{
    Bool lastSingleLineResult = True;

    if (lastChar != ASCII_NEW_LINE)
    {
        if (strlen(lastLine) > 1)
            lastSingleLineResult = evalSingleLine(lastLine);
        else if (strlen(lastLine) == 1)
            lastSingleLineResult = False;
        lastResult = lastResult && lastSingleLineResult;
        printCurrentLineResult(lastSingleLineResult);
    }

    if (lastResult && lastChar != ASCII_NEW_LINE)
    {
        if (lastChar == ASCII_CLOSING_CURLY_BRACES)
            closedCount++;
        else if (lastChar == ASCII_OPENING_CURLY_BRACES)
            lastResult = False;
    }

    else if (lastResult && closedCount != openCount)
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

State handleState(State prevState, int current, int prev)
{
    State state = prevState;

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
                if (state == inComment)
                    state = isOut;
                else
                {
                    /* SPECIAL ERROR THAT HAPPENS IF USER TYPE (* AND A / STRAIGHT AFTER) TO CLOSE COMMENT
                        THAT DOES NOT EXIST,IF STATE IS NOT A STRING AND NOT A COMMENT THEN A CLOSING COMMENTCANNOT BE VALID */
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
                state = inComment;

            break;
        }
    }

    case ASCII_NEW_LINE:
    {

        state = state != inComment ? newLine : inComment;
        break;
    }

    default:
        break;
    }

    return state;
}

Bool evalSingleLine(char line[MAX_LINE_LENGTH])
{
    int i, j = 0, k = 0, current = 0;
    Bool result = True;
    char open[MAX_LINE_LENGTH / 2] = {0}, closed[MAX_LINE_LENGTH / 2] = {0};
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

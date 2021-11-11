
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 100
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

void getTextAndEvalGlobally();
void printCurrentLineResult(Bool result);
void printGlobalResult(Bool lastResult, int lastChar, int closedCount, int openCount);

int main()
{
    printf("~ In this program each line of your code will be evaluated seperately,\nand result will show up immediately as you press enter to start a new line.\nAt the end of you input you will see the evaluation result for the whole text you've entered.\nThe global result takes count of special lines with correct open or closed curly braces.~\n\n *** Good Luck :) ***\n\n\n");
    getTextAndEvalGlobally();
    return 0;
}
void getTextAndEvalGlobally()
{
    Bool globalResult = True;
    Bool singleLineResult = True;
    State state = isOut;

    int preDetermentResult = -1, c, j, lastCharBeforeEOF, prevImportantChar, lonelyOpenBracetsCount, lonelyCloseBracetsCount;
    c = j = lastCharBeforeEOF = prevImportantChar = lonelyCloseBracetsCount = lonelyOpenBracetsCount = 0;
    char line[MAX_LINE_LENGTH] = {0};

    while ((c = getchar()) != EOF)
    {

        /* 
        IF TABS/ENTERS AND ALL KIND OF WHITE SPACE THAT ARE NOT A NEW LINE
         COUNTS FOR ME WHITE SPACE AND HANDLED BY THE FIRST CASE OF THE SWITCH CASE
         */
        if (isspace(c) && c != ASCII_NEW_LINE)
            c = ASCII_EMPTY_SPACE;

        lastCharBeforeEOF = c;

        switch (c)
        {
        case ASCII_EMPTY_SPACE:
        {
            prevImportantChar = c;
            break;
        }
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
                if (prevImportantChar == ASCII_ASTERISK)
                {
                    if (state == inComment)
                        state = isOut;
                    else
                    {
                        /* SPECIAL ERROR THAT HAPPENS IF USER TYPE (* AND A / STRAIGHT AFTER) TO CLOSE COMMENT
                        THAT DOES NOT EXIST,IF STATE IS NOT A STRING AND NOT A COMMENT THEN A CLOSING COMMENTCANNOT BE VALID */
                        state = isOut;
                        preDetermentResult = False;
                        break;
                    }
                }
                else
                    prevImportantChar = ASCII_FORWARD_SLASH;

                break;
            }
        }

        case ASCII_ASTERISK:
        {
            if (state == inString)
                break;
            else
            {
                if (state == isOut && prevImportantChar == ASCII_FORWARD_SLASH)
                    state = inComment;
                else
                    prevImportantChar = ASCII_ASTERISK;

                break;
            }
        }

        /* THIS CASE IS THE ONE THAT FORCES US TO EVALUATE THE CURRENT LINE: */
        case ASCII_NEW_LINE:
        {
            if (preDetermentResult != -1)
                singleLineResult = preDetermentResult;
            /* WE NEED TO EVALUATE BRACKETS ONLY IF THEY APPER NORMALLY, NOT INSIDE A COMMENT OR A STRING*/
            else if (state == isOut)
                singleLineResult = evalSingleLine(line);
            
            /*This is for the case comment is starting in the end of a line that need to be checked. the line[j] char array is saving only trimmed relevant code 
            that isnot part of string or comment expression, thus, it need to be evaluated on a single line level.*/
            else if(state==inComment && j>0) /* j  value is equal to the current line length, its like writing strlen(line), as j is the counter index of line array. */
                            singleLineResult = evalSingleLine(line);
            
            /*****************************************************************************************************************************
            ~ Never the less, This case check (state==inComment && j>0), is done only  for the sake of the requirements of this mmn11
             although it violates the actual rules of evaluating brackets in C language!
           
            ~ I am writing here something that is outside of the scope of this mmn... but I think is correct...
            because a string of code as this one: "if(x>y){ /* .... \n" in C is evaluated only when we get outside the multi line comment
            and if the next curly brackets are closing ones } it will be valid! else it won't. it is just like special lines we have here of single
            { or } only in the real world of C.
            *****************************************************************************************************************************/
    
            
            /* IF WE ARE IN A STRING OR COMMENT THE LINE MUST BE TRUE */
            else
                singleLineResult = True;

            /*
            IF GLOBAL RESULT HAVE NOT BEEN SET TO FALSE YET BY FIRST CASE OF LINE BEING NOT VALID AND NOT SPECIAL ONE
            AT THE SAME TIME - THEN WE ARE CHECKING IF THIS NON VALID LINE IS SPECIAL ONE,
             IF THIS LINE IS SPECIAL IN A VALID WAY, WE COUNT AND REMEMBER THIS, THE FIRST TIME CURRENT LINE IS NOT SPECIAL
             AND NOT VALID OR SPECIAL LINES BALANCE BREAKS, WE SET GLOBAL RESULT TO FALSE AND NEVER ENTER THIS IF BLOCK AGAIN
            */
            if (globalResult == True && singleLineResult == False)
            {
                if (strlen(line) == 1 && (line[0] == ASCII_OPENING_CURLY_BRACES || line[0] == ASCII_CLOSING_CURLY_BRACES))
                {
                    if (line[0] == ASCII_OPENING_CURLY_BRACES)
                        lonelyOpenBracetsCount++;
                    else
                        lonelyCloseBracetsCount++;

                    if (lonelyCloseBracetsCount > lonelyOpenBracetsCount)
                        globalResult = False;
                }
                else
                {
                    globalResult = False;
                }
            }

            printCurrentLineResult(singleLineResult);

            prevImportantChar = 0;
            memset(line, 0, j);
            j = 0;
            preDetermentResult = -1;
            if (state == inString)
                state = isOut;
        }
        default:
        {
            if (!isspace(c) && state == isOut)
            {
                line[j] = c;
                j++;
            }
        }
        }
    }

    printGlobalResult(globalResult, lastCharBeforeEOF, lonelyCloseBracetsCount, lonelyOpenBracetsCount);
}

void printGlobalResult(Bool lastResult, int lastChar, int closedCount, int openCount)
{

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
}

Bool evalSingleLine(char line[MAX_LINE_LENGTH])
{
    int i, j = 0, k = 0, current = 0;
    Bool result = True;
    char open[MAX_LINE_LENGTH / 2] = {0}, closed[MAX_LINE_LENGTH / 2] = {0};

    for (i = 0; line[i]; i++)
    {
        if (result == False)
            return False;
        current = (int)line[i];

        if (isOpeningBracket(current))
        {
            if (strlen(closed) > 0)
                result = False;
            else
            {
                open[j] = current;
                j++;
            }
        }
        else if (isClosingBracket(current))
        {
            closed[k] = current;
            k++;
            if (strlen(open) == 0)
                result = False;
            else if (strlen(open) == 1 && strlen(closed) == 1)
            {
                result = areBracketsOfSameTypeButInverse((int)open[0], (int)closed[0]);
                j = k = 0;
                closed[0] = open[0] = '\0';
            }
        }
    }

    if (j != k)
        return False;

    else if (j == k && j > 0)
        return evalBracketSequence(open, closed, strlen(closed));
    else
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

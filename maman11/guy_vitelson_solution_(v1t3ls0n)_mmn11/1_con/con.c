#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LENGTH 81
#define MIN_SEQ_LENGTH 3

typedef enum
{
    Num = 2,
    Upper = 3,
    Lower = 4,
    NonDigit = -1
} DigitType;

typedef enum
{
    False,
    True
} Bool;

void contract(char[MAX_STR_LENGTH], char[MAX_STR_LENGTH], int);
DigitType getCharType(int);
Bool isNextCharFollowingCurrent(int, int);
int main()
{
    char s1[MAX_STR_LENGTH], s2[MAX_STR_LENGTH];
    int length;
    printf("\nThis program purpose is to shorten any string of text you want to,\nas long as it's max character size is not over 80 characters...\n\n");
    printf("Please enter string of text:\n\n");
    fgets(s1, MAX_STR_LENGTH, stdin);
    length = strlen(s1);
    printf("You entered:\n%s\n\n", s1);
    contract(s1, s2, length);
    printf("The Resulted shorter text we made for you is:\n%s\n\nThank you and goodbye.\n\n", s2);

    return 0;
}

DigitType getCharType(int asciValue)
{
    if (islower(asciValue))
        return Lower;
    else if (isupper(asciValue))
        return Upper;
    else if (isdigit(asciValue))
        return Num;
    else
        return NonDigit;
}

Bool isNextCharFollowingCurrent(int next, int current)
{
    /*  
    checking if the current character in the string and the next one 
    are of the same type (number,lowercase digit,uppercase digit and so forth)
    */
    Bool areTypesMatch = getCharType(next) == getCharType(current) ? 1 : 0;

    /* validating next char are digits or characters and not special characters*/
    Bool areTypesValid = areTypesMatch && getCharType(current) != NonDigit ? 1 : 0;
    /* checking the ascii values of the current character and the next one to see it they are sequential*/
    Bool areValuesSequentials = ((next - current) == 1) ? 1 : 0;

    /* if both next and current are of the same type (both are numbers/lowercase digits/etc) and have sequential ascii values
    then this function will return true (1) else it will return false (0) 
    */
    return areTypesValid && areValuesSequentials;
}

void contract(char str1[MAX_STR_LENGTH], char str2[MAX_STR_LENGTH], int length)
{
    int i, k, count = 0, startIndex = 0, endIndex = 0;
    Bool isItSequential = False;
    for (i = k = 0; i < length; i++)
    {

        isItSequential = isNextCharFollowingCurrent((int)str1[i + 1], (int)str1[i]);

        /* continue current - following chars sequence*/
        if (isItSequential && count > 0)
        {
            endIndex = i + 1;
            count++;
        }
        /* start new - following chars sequence*/
        else if (isItSequential && count == 0)
        {
            startIndex = i;
            endIndex = i + 1;
            count = 1;
        }
        /* end current sequence (and minimize with '-') :
        Insert the minimized content from the original string into the 
        result string (str2) with '-' char between first to last char of the sequence*/
        else if (!isItSequential && count >= (MIN_SEQ_LENGTH - 1))
        {
            str2[k] = str1[startIndex];
            str2[++k] = '-';
            str2[++k] = str1[endIndex];
            k++;
            count = 0;
            startIndex = endIndex = i + 1;
        }

        /* end current sequence (without minimizing) :
         because the following sequence length is smaller then the minimun required 
         (shoud be with at least 3 character). */

        else if (!isItSequential && count > 0)
        {

            str2[k] = str1[startIndex];
            str2[++k] = str1[endIndex];
            k++;
            count = 0;
        }

        /* else just copy current regular character to the new sequence
        (current char value does not follow the next value and we are not currently inside a sequence) */
        else
        {
            str2[k] = str1[i];
            k++;
            count = 0;
        }
    }
}

/*
Desired Output Examples:

Example 1:
Input:  abcdef#LLMN 67890123#HIJKMNOpqrstu(?@AB,1124-8)
Output: a-f#LL-N 6-90-3#H-KM-Op-u(?@AB,1124-8)

Example 2:
Input:  ABC
Output: A-C

Example 3:
Input:  AB
Output: AB

Example 4:
Input:  abcdefg
Output  a-g

Example 5:
Input:  0123456
Output  0-6

Example 6:
Input:  012
Output  0-2

Example 7:
Input:  12
Output  12
 */

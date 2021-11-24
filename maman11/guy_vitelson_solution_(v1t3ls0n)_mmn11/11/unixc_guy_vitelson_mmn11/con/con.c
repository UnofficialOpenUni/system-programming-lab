/* 
    con.c 

    ### Program Description ###
    The program takes an string input of text from the user and shortens the its content by using '-' character
    between any consecutive of 3 or more alpha numeric character within that stirng.
    
    Author: Guy Vitelson
    Date: 21/11/2021
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LENGTH 81 /* This is the maximum input string length we allow the user to insert for a line. */
#define MIN_SEQ_LENGTH 3
/* 3 is the minimum amount of following character required in order to really minimize (shorten it) any string input with '-' char,
between first and last following character of the sequence, less than 3 will actually make it longer.
For example: 
MIN_SEQ_LENGTH equals 3 ABC (3) => A-C (3) same amount :)
MIN_SEQ_LENGTH equals 4 ABCD (4) => A-D (3) shorter :)
MIN_SEQ_LENGTH equals 2 AB (2) => A-B (3) longer?! ):
 */

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


void contract(char str1[MAX_STR_LENGTH], char str2[MAX_STR_LENGTH], int length);
DigitType getCharType(int asciiValue);
Bool isNextCharFollowingCurrent(int next, int current);

int main()
{
    char s1[MAX_STR_LENGTH], s2[MAX_STR_LENGTH];
    int length;
    printf("\n############################################################################\n");
    printf("\nThis program purpose is to shorten any string of text you want to\nAs long as it's max character size is not over 80 characters.\n");
    printf("\n##############################################################################");
    printf("\n\n*** Please Insert Text: ***\n\n");
    fgets(s1, MAX_STR_LENGTH, stdin);
    length = strlen(s1);
    printf("\nThe Text You Have Inserted Is:\n\n%s\n\n", s1);
    contract(s1, s2, length);
    printf("\nAnd Our Result Is:\n\n%s\n\n*** The Result Is The Shorter Version Of The Text You Have Enterd. ***\n\nThank You And Goodbye :)\n\n\n", s2);

    return 0;
}


/* @ Function: getCharType 
   @ Arguemnts: The function get one argument that is an integer which represents asciiValue of a char in the original string and returns
   DigitType typedef variable.
   @ Desciption : The function checks if the value of its asciiValue argument is a type of  number, lowercase character, uppercase character 
   or it is not a alphanumeric digit.
*/
DigitType getCharType(int asciiValue)
{
    if (islower(asciiValue))
        return Lower;
    else if (isupper(asciiValue))
        return Upper;
    else if (isdigit(asciiValue))
        return Num;
    else
        return NonDigit;
}

/* @ Function: isNextCharFollowingCurrent 
   @ Arguemnts: The functions get 2 integers, first one represent the next character in the origial string we are iterating over in contact
   and the next one represens the current character we are iterating on in contract.
   @ Desciption : The function checks the value of the first argument(next) is the consecutive alpha-numeric character 
   of the value of the second argument (current) and then returns True or False (1 or 0) typedef variable.
*/

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


/* @ Function: contract 
   @ Arguments: str1 is the original string, str2 is a clean string variable that will hold the new minimized string the function will create
   and length is the length of the original string(str1).
   @ Desciption: The function takes a string of text and shortens parts of the string that have 3 or more consecutive alphanumeric characters.
*/
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
    /* make last char of shorter string result the end of that string. */
    str2[k] = '\0';
}

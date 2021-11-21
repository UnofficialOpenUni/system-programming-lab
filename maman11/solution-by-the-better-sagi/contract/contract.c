#include <ctype.h>
#include <stdio.h>

#define MAX_LENGTH 81

void contract(char[], char[]);
char* tryAddSeq(char[],int,int);

int main()
{
    char input[MAX_LENGTH];  
    char output[MAX_LENGTH]; 

    while(fgets(input, MAX_LENGTH, stdin))
    {
        contract(input, output);
        printf("\nInput: \n%s\n", input);
        printf("\nShortened Output: \n%s\n", output);
    }
    return 0;
}

void contract(char s1[], char s2[])
{
    char* currPoint = s1;
    char currChar;
    int firstChar = isalnum(*currPoint) ? *currPoint++ : -1; /* Defines a start of a seqeunce. Checks if the first char of s1 is can be a start of a sequence*/
    int sLength = 0; /* Length of the sequence */
    while((currChar=*currPoint++) != '\0')
    {
        if(!isalnum(currChar))
        {
            /* Add the sequence existing until now */
            s2=tryAddSeq(s2, firstChar, sLength);
            firstChar = *(currPoint++);
            sLength=0;
            /* Add the special character to the string */
            s2=tryAddSeq(s2,currChar,0);
            continue;
        }
        /* Is the current character a following to the sequene? If so, increase the length of the sequence */
        if((currChar-1) == firstChar+sLength){
            sLength++;
        }
        else
        {
            /* Current character is not part of a sequence, deal with the sequence so far. */
            s2=tryAddSeq(s2, firstChar, sLength);
            firstChar = currChar;
            sLength=0;
        }
    }
    /* Adding the unhandaled sequence afer finishing with the loop */
    s2=tryAddSeq(s2, firstChar, sLength);
    *s2='\0';
} 

/* Adding the sequence to the array, returns the current location of the array(After the sequence was added) */
char* tryAddSeq(char s[],int first, int length)
{
    if(first==-1) return s;
    switch(length)
    {
        case 0:
            *s++ = first;
            break;
        case 1:
            s[0] = first;
            s[1] = first+1;
            s+=2;
            break;
        default:
            s[0]=first;
            s[1]='-';
            s[2]=first+length;
            s+=3;
            break;
    }
    return s;
}

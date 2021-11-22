#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 101

void expand(char *s1, char *s2);
enum chartypes {DIGIT, LETTER, CAP_LETTER};

int main()
{
    char s1[MAX_LENGTH], s2[MAX_LENGTH];
    printf("enter a shortened line of input to expand\n");
    if (fgets(s1, MAX_LENGTH, stdin)!=NULL) {
        s1[(strcspn(s1, "\n"))] = '\0';
        expand(s1, s2);
        printf("Input was: %s\nOutput is: %s\n", s1, s2);
    }
    else
        printf("Error!\n");
    return 0;
}

void expand(char *s1, char *s2)
{
    char *temp;
    int type, i;
    while (*s1) {
        if (isalnum(*s1)) {
            temp = s1; 
            type = (isdigit(*s1)) ? DIGIT: (*s1 < 'a') ? CAP_LETTER: LETTER;
        }
        else if (*s1=='-' && isalnum(*(s1+1))) {
            s1++;
            if (((type == DIGIT && isdigit(*s1)) || (type == LETTER && islower(*s1)) || (type == CAP_LETTER && isupper(*s1))) && ((*s1)-(*temp)>1))
                for (i=1; i<*s1-*temp; i++)
                    *s2++ = *temp+i;
            else
                s1--;
        }
        *s2++ = *s1++;
    }
    *s2 = '\0';
}


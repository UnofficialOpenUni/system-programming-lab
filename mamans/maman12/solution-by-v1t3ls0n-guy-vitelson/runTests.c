#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LEN 200
#define MAX_PATH_LEN 50
#define NUMBER_OF_TESTS 16

const char PATH[] = "";
const char PROG[] = "magic";
const char TEST[] = "tests/";
const char RESULT[] = "res/";

int main(int argc, char *argv[])
{
    int i;
    char prog[MAX_PATH_LEN], test[MAX_PATH_LEN], result[MAX_PATH_LEN];
    char command[MAX_COMMAND_LEN];

    snprintf(prog, MAX_PATH_LEN, "%s%s", PATH, PROG);
    snprintf(test, MAX_PATH_LEN, "%s%s", PATH, TEST);
    snprintf(result, MAX_PATH_LEN, "%s%s", PATH, RESULT);
    for (i = 1; i <= NUMBER_OF_TESTS; i++)
    {
        snprintf(command, MAX_COMMAND_LEN, "%s<%skelet%d.txt>%spelet%d.txt", prog, test, i, result, i);
        system(command);
    }

    if (i != NUMBER_OF_TESTS)
        return -1;
    return 0;
}
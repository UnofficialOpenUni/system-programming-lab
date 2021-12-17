#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 200
#define MAX_PATH_LEN 50

const char PATH[] = "../magic/";
const char PROG[] = "magic";
const char TEST[] = "tests/";
const char RESULT[] = "results/";

int main(int argc, char *argv[])
{
	int i;
	char prog[MAX_PATH_LEN], test[MAX_PATH_LEN], test2[MAX_PATH_LEN], result[MAX_PATH_LEN];
	char testname[MAX_PATH_LEN], command[MAX_COMMAND_LEN];
	FILE *fp;

	printf("Please type the global general name of your tests files: ");
	if(fgets(testname, MAX_PATH_LEN, stdin) == NULL) {
		fprintf(stderr, "Error saving test name!");
		return -1;
	}
	testname[strcspn(testname, "\n")] = '\0';
	snprintf(prog, MAX_PATH_LEN, "%s%s", PATH, PROG);
	snprintf(test,  MAX_PATH_LEN, "%s%s%s", PATH, TEST, testname);
	snprintf(result,  MAX_PATH_LEN, "%s%s%s", PATH, RESULT, testname);
	for (i=1; snprintf(test2, MAX_PATH_LEN, "%s%d.txt", test, i) && (fp=fopen(test2, "r"))!= NULL; i++) {
		snprintf(command, MAX_COMMAND_LEN, "%s<%s%d.txt>%s%d_result.txt", prog, test, i, result, i);
		system(command);
		fclose(fp);
	}
	return 0;
}

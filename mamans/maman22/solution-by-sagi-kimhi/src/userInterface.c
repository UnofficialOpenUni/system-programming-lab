#include "userInterface.h"

/* printUserIntroMessage: prints a detailed user introduction message to the program. */
void printUserIntroMessage(void)
{
	printf("\n******************************** COMPLEX CALCULATOR ********************************\n");
	printf("This is a complex number calculator.\n");
	printf("The calculator has 6 usable variables which maybe used for the various operations.\n");
	printf("The names of the variables are:\n\t- A\n\t- B\n\t- C\n\t- D\n\t- E\n\t- F\n\n");
	printf("The available operations for the variables are as follows:\n\n");
	printf("# read_comp - assigns a complex value to a complex variable. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| read_comp <complex_variable_name>, <real_value>, <image_value> |");
	printf("# print_comp - print a compplex variable. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| print_comp <complex_variable_name> |");
	printf("# add_comp - calculate the sum of two complex variables. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| add_comp <complex_variable_name>, <complex_variable_name> |");
	printf("# sub_comp - calculate the difference of two complex variables. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| sub_comp <complex_variable_name>, <complex_variable_name> |");
	printf("# mult_comp_real - multiply a complex variable by a real value. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| mult_comp_real <complex_variable_name>, <real_value> |");
	printf("# mult_comp_img - multiply a complex variable by an image value. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| mult_comp_img <complex_variable_name>, <image_value> |");
	printf("# mult_comp_comp - multiply two complex variables. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| mult_comp_comp <complex_variable_name>, <complex_variable_name> |");
	printf("# abs_comp - calculates the absolute value of a complex variable. \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| abs_comp <complex_variable_name> |");
	printf("# stop - this is the only proper way to halt the program! - \n  Usage:\n\n");
	printf("\t%-60s\n\n\n", "| stop |");
    printf("In order to avoid future errors please make sure you are only using capital\n");
    printf("A-F letters for the variables, and lower case commands for the actual commands.\n\n");
    printf("Good luck and have fun!\n");
	printf("*************************************************************************************\n\n");
}

void requestInput(void)
{
    printf("\n\nPlease enter your next command line (max 80 characters):\n");
}

int printError(InputFlag _flag)
{
    fflush(stdin);
    printf("\n***Error: ");
    switch (_flag) {
        case UNDEF_CMD_NAME:
            printf("Undefined command name\n");
            break;
        case UNDEF_COMP_VAR:
            printf("Undefined complex variable\n");
            break;
        case UNDEF_FLT_VAR:
            printf("Invalid parameter-not a number\n");
            break;
        case MISSING_PARAM:
            printf("Missing parameter\n");
            break;
        case EXTRA_CMD_TEXT:
            printf("Extraneous text after end of command\n");
            break;
        case MULTIPLE_COMMAS:
            printf("Multiple consecutive commas\n");
            break;
        case INVALID_COMMA:
            printf("Illegal comma\n");
            break;
        case MISSING_COMMA:
            printf("Missing comma/s\n");
            break;
        case INPUT_OVERFLOW:
            printf("Input was longer than 80 characters\n");
            break;
        case REACHED_EOF:
            printf("EOF Detected - use the stop command instead to properly halt the program.\n");
            exit(EXIT_FAILURE);
    }
    return -1;
}

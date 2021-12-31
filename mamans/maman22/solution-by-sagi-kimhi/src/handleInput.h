#ifndef _HANDLE_INPUT_H
#define _HANDLE_INPUT_H
#include <stdarg.h>
#include <ctype.h>
#include "hashTable.h"
#include "userInterface.h"
#include "mycomp.h"
#include "complex.h"

#define IsSeperator(ch) (isspace((ch)) || (ch)==',')
#define FORMAT_MIN (strlen("%x,%f,%f")+1)

/* gets the next line of input up to n characters specified by lim */
int getLine(char *line, char lim);

/* scans a command from a given line and sets destOp to point to the appropriate operation from opTable */
int scanCmd(char *line, CompOp *opTable[TABLE_SIZE], CompOp **destOp);

/* scans the parameters specified by format from the string and sets them to the arguments.
 * the behavior is undefined if not enough arguments are provided for the given format. */
int scanParamsf(Complex *cVars, char *string, char *format, ...);

#endif

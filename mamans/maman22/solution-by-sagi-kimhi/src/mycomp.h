#include "hashTable.h"
#include "userInterface.h"
#include "handleInput.h"
#include "complex.h"

#define MAX_COMP_PARAMS 2
#define MAX_FLOAT_PARAMS 2

#ifndef _COMP_VARS_
#define _COMP_VARS_
typedef struct complex_vars{
        complex A;
        complex B;
        complex C;
        complex D;
        complex E;
        complex F;
} Complex;
#endif

#ifndef _MY_COMP_PTYPES_
#define _MY_COMP_PTYPES_

/* scans the line and executes it if the line is found to be valid */
int runCmdLine(char *line, CompOp *opTable[TABLE_SIZE], Complex *cVars);

/* returns a pointer the the complex var from the Complex structure that was specified by the char argument.
 * Returns NULL upon failure. */
complex *getVar(char var, Complex *compVars);

#endif

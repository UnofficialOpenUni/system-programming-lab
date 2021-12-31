#ifndef _USER_INTERFACE_H
#define _USER_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>

#ifndef _FLAGS_
#define _FLAGS_
#include <limits.h>
typedef enum _inputFlags {
    UNDEF_CMD_NAME=SCHAR_MIN,
    UNDEF_COMP_VAR,
    UNDEF_FLT_VAR,
    MISSING_PARAM,
    EXTRA_CMD_TEXT,
    MULTIPLE_COMMAS,
    INVALID_COMMA,
    MISSING_COMMA,
    INPUT_OVERFLOW,
    REACHED_EOF
} InputFlag;
#endif

void printUserIntroMessage(void);
void requestInput(void);
int printError(InputFlag _flag);
#endif

#include "handleInput.h"

int getLine(char *line, char lim)
{
    if (!line || lim<MIN_CMD_LEN)
        return -1;   
    if (!fgets(line, lim, stdin)) {
        if (feof(stdin))
            return printError(REACHED_EOF);
        return -1;
    }
    printf("%s", line);
    if (strpbrk(line, "\n")==NULL) {
        if (feof(stdin))
            printError(REACHED_EOF);
        return printError(INPUT_OVERFLOW);
    }
    return 1;
}

int scanCmd(char *line, CompOp *opTable[TABLE_SIZE], CompOp **destOp)
{
    int i, j;
    char cmd[MAX_CMD_LEN+1];
    if (!line)
        return -1;
    for (i=j=0; line[i]; i++) {
        if (isspace(line[i])) {
            if (!j)
                continue;
            break;
        }
        if (line[i]==',')
            return printError(INVALID_COMMA);
        if (islower(line[i]) || (j && line[i]=='_')) {
            if (j>=MAX_CMD_LEN)
                return printError(UNDEF_CMD_NAME);
            cmd[j++]=line[i];
            continue;
        }
        return printError(UNDEF_CMD_NAME);
    }
    cmd[j] = '\0';
    if (((*destOp) = search(opTable, cmd))==NULL)
        return printError(UNDEF_CMD_NAME);
    return i;
}

int scanParamsf(Complex *cVars, char *string, char *format, ...)
{
    va_list argPtr;
    char *fp, *sp;
    
    if (!string || !format)
        return -1;

    sp=string;
    while (isspace(*sp))
        sp++;
    if (*sp==',')
        return printError(INVALID_COMMA);

    va_start(argPtr, format);
    for (fp=format; *fp; fp++) {
        if (*fp == ',') {
            int commas=0;
            while (isspace(*sp) || *sp==',') {
                if (commas>1) {
                    va_end(argPtr);
                    return printError(MULTIPLE_COMMAS);
                }
                if (*sp==',')
                    commas++;
                sp++;
            }
            if (!commas) {
                va_end(argPtr);
                return printError(MISSING_COMMA);
            }
            continue;
        }
        if ((*fp)!='%')
            continue;
        switch (*++fp) {
            complex **cmplxPtr=NULL;
            float *fltPtr=NULL;
            case 'x':
                if (!*sp) {
                    va_end(argPtr);
                    return printError(MISSING_PARAM);
                }
                cmplxPtr=va_arg(argPtr, complex **);
                if (!isupper(sp[0]) || !IsSeperator(sp[1]) || !((*cmplxPtr)=getVar(sp[0], cVars))) {
                    va_end(argPtr);
                    return printError(UNDEF_COMP_VAR);
                }
                sp++;
                continue;

            case 'f':
                if (!*sp) {
                    va_end(argPtr);
                    return printError(MISSING_PARAM);
                }
                fltPtr=va_arg(argPtr, float *);
                if (sscanf(sp, "%f", fltPtr)!=1) {
                    va_end(argPtr);
                    return printError(UNDEF_FLT_VAR);
                }
                if (sp[0]=='+' || sp[0]=='-')
                    sp++;
                while (isdigit(sp[0]))
                    sp++;
                if ((*sp)!='.')
                    continue;
                else
                    while (isdigit(*++sp))
                        ;
                continue;
        }
    }
    va_end(argPtr);
    while (sp[0] && isspace(sp[0]))
        sp++;
    if (sp[0]==',')
        return printError(INVALID_COMMA);
    if (sp[0])
        return printError(EXTRA_CMD_TEXT);
    return 1;
}

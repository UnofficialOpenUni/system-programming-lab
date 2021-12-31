#include "mycomp.h"

int main(int argc, char **argv)
{
    char line[MAX_LINE_LEN];
    Complex cVars = {{0,0}};
    CompOp *opTable[TABLE_SIZE];
    
    initTable(opTable);
    printUserIntroMessage();
    while (1) {
        requestInput();
        if (getLine(line, MAX_LINE_LEN)!=1)
            continue;
        runCmdLine(line, opTable, &cVars);
    }
    
    return 0;
}


static int checkParamsAndExecute(char *params, CompOp *operation, Complex *cVars);

int runCmdLine(char *line, CompOp *opTable[TABLE_SIZE], Complex *cVars)
{
    int i=0;
    char *params=NULL;
    CompOp *operation=NULL;
    if (!line || !opTable || !cVars)
        return -1;
    if ((i=scanCmd(line, opTable, &operation))<0)
        return -1;
    params = &line[i];
    return checkParamsAndExecute(params, operation, cVars);
}

static int checkParamsAndExecute(char *params, CompOp *operation, Complex *cVars)
{
    complex *result;
    if (!params || !operation || !cVars)
        return -1;

    switch (operation->opCode) {
        complex *cmplxParam[MAX_COMP_PARAMS] = {NULL, NULL};
        float fltParam[MAX_FLOAT_PARAMS] = {0.0, 0.0};

        case STOP:
            return stop();

        case READ_COMP:
            if (scanParamsf(cVars, params, "%x,%f,%f", &cmplxParam[0], fltParam, fltParam+1)<0)
                return -1;
            return read_comp(cmplxParam[0], fltParam[0], fltParam[1]);

        case PRINT_COMP:
            if (scanParamsf(cVars, params, "%x", &cmplxParam[0])<0)
                return -1;
            return print_comp(cmplxParam[0]);

        case ADD_COMP:
            if (scanParamsf(cVars, params, "%x,%x", &cmplxParam[0], &cmplxParam[1])<0)
                return -1;
            if (!(result=add_comp(cmplxParam[0], cmplxParam[1])))
                return -1;
            print_comp(result);
            break;

        case SUB_COMP:
            if (scanParamsf(cVars, params, "%x,%x", &cmplxParam[0], &cmplxParam[1])<0)
                return -1;
            if (!(result = sub_comp(cmplxParam[0], cmplxParam[1])))
                return -1;
            print_comp(result);
            break;

        case MULT_COMP_REAL:
            if (scanParamsf(cVars, params, "%x,%f", &cmplxParam[0], fltParam)<0)
                return -1;
            if (!(result = mult_comp_real(cmplxParam[0], fltParam[0])))
                return -1;
            print_comp(result);
            break;

        case MULT_COMP_IMG:
            if (scanParamsf(cVars, params, "%x,%f", &cmplxParam[0], fltParam)<0)
                return -1;
            if (!(result = mult_comp_img(cmplxParam[0], fltParam[0])))
                return -1;
            print_comp(result);
            break;

        case MULT_COMP_COMP:
            if (scanParamsf(cVars, params, "%x,%x", &cmplxParam[0], &cmplxParam[1])<0)
                return -1;
            if (!(result = mult_comp_comp(cmplxParam[0], cmplxParam[1])))
                return -1;
            print_comp(result);
            break;

        case ABS_COMP:
            if (scanParamsf(cVars, params, "%x", &cmplxParam[0])<0)
                return -1;
            printf("%f\n", abs_comp(cmplxParam[0]));
            return 1;
    }
    free(result);
    return 1;
}

complex *getVar(char var, Complex *compVars)
{
    if (!compVars)
        return NULL;
    if (var<'A' || var>'F')
        return NULL;
    switch (var) {
        case 'A': return &compVars->A;
        case 'B': return &compVars->B;
        case 'C': return &compVars->C;
        case 'D': return &compVars->D;
        case 'E': return &compVars->E;
        case 'F': return &compVars->F;
    }
    return NULL;
}

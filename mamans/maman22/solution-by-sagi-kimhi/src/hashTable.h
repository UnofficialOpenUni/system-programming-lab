#ifndef _HASH_TAB_H
#define _HASH_TAB_H
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 17 /* prime number with less than 2/3 load factor compared to num of operations */

#ifndef _SIZES_
#define _SIZES_
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
#endif

#ifndef _X_MACROS_
#define _X_MACROS_
/* X Macros: */
#define LOAD_OPERATION(OPERATION) \
    OPERATION(READ_COMP) = 0, \
    OPERATION(PRINT_COMP), \
    OPERATION(ADD_COMP), \
    OPERATION(SUB_COMP), \
    OPERATION(MULT_COMP_REAL), \
    OPERATION(MULT_COMP_IMG), \
    OPERATION(MULT_COMP_COMP), \
    OPERATION(ABS_COMP), \
    OPERATION(STOP)

#define GENERATE_ENUM(ENUM) ENUM
#define GENERATE_STRING(STRING) #STRING
#endif

#ifndef _COMPLEX_OPERATIONS_
#define _COMPLEX_OPERATIONS_
typedef enum COMPLEX_OPS {
    LOAD_OPERATION(GENERATE_ENUM)
} OpCode;

typedef struct complex_operation {
    OpCode opCode;
    char *operation;
} CompOp;
#endif

/* initializes a complex operations hash table */
int initTable(CompOp *opTab[TABLE_SIZE]);

/* searches a complex operation in the operation table with an identical opKey */
CompOp *search(CompOp *opTab[TABLE_SIZE], char *opKey);

#endif

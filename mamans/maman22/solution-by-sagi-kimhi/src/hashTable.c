#include "hashTable.h"

static CompOp *insert(CompOp *opTab[TABLE_SIZE], CompOp *compOp);
int initTable(CompOp *opTab[TABLE_SIZE])
{
	unsigned char operation;
	static CompOp OpTable[] = {
    {READ_COMP, "read_comp"}, 
    {PRINT_COMP, "print_comp"}, 
    {ADD_COMP, "add_comp"},
    {SUB_COMP, "sub_comp"},
    {MULT_COMP_REAL, "mult_comp_real"},
    {MULT_COMP_IMG, "mult_comp_img"},
    {MULT_COMP_COMP, "mult_comp_comp"},
    {ABS_COMP, "abs_comp"},
    {STOP, "stop"}
    };

	if (!opTab)
		return 0;
	memset(opTab, 0, TABLE_SIZE * sizeof(CompOp **));
    for (operation = READ_COMP; operation <= STOP; operation++)
        insert(opTab, &OpTable[operation]);
	return 1;
}

/* hash: returnes a hash value for the given text key argument. */
static uint32_t hash(char *key)
{
	uint16_t hash = 5381;
	int32_t c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}

/*	hash1: default function for generating an index in a table from a given hash value. */
static uint32_t hash1(uint32_t hashVal)
{
	return (hashVal%TABLE_SIZE); /* [0,m-1] */
}

/*	hash2: second function for hash table index generation from a hash value
	to be used only for double hashing. this alone will not return a valid index for a key. */
static uint32_t hash2(uint32_t hashVal)
{
	return ((hashVal%(TABLE_SIZE-1))+1); /* [1,m-1] */
}

/*	doubleHash: a function used for double hashing to generate a new index in the case of encountering
	a collision with the index returned by hash1 function. */
static uint32_t doubleHash(uint32_t h1, uint32_t h2, uint32_t fact)
{
	return ((h1+h2*fact) % TABLE_SIZE);
}

CompOp *insert(CompOp *opTab[TABLE_SIZE], CompOp *compOp)
{
	uint32_t hkey, startVal, stepVal, fact, index;
	if (!opTab || !compOp || (search(opTab, compOp->operation)!=NULL))
		return NULL;
	hkey = hash(compOp->operation);
	index = startVal = hash1(hkey);
	stepVal = hash2(hkey);
	fact = 1;
	while (opTab[index])
		index = doubleHash(startVal, stepVal, fact++);
	return (opTab[index] = compOp);
}

CompOp *search(CompOp *opTab[TABLE_SIZE], char *opKey)
{
	uint32_t hVal, startVal, stepVal, fact, index;
	if (!opTab || !opKey)
		return NULL;
	hVal = hash(opKey);
	index = startVal = hash1(hVal);
	stepVal = hash2(hVal);
	fact = 1;
	while (opTab[index]) {
		if (fact>1 && index == startVal)
			return NULL;
		if (!strcmp(opKey, opTab[index]->operation))
			return opTab[index];
		index = doubleHash(startVal, stepVal, fact++);
	}
	return NULL;
}

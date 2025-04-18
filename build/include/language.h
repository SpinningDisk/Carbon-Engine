#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "engine.h"

typedef enum{
    PRINT_VAR,
    STORE,
    JMP,
    JMP_GT0,
    JMP_LT0,
    WHILE_COND,
    // for in future versions; just a scratch
    BLOCK_END,
    EXPRESSION_CONST,
    EXPRESSION_VAR,
}instructions;
typedef enum{
    TYPE_INT,
    TYPE_STR,
    TYPE_ARR,
    TYPE_NULL,
}ceTypes;
char* ceTypesReadable(ceTypes Type);
typedef enum{
    BC_TYPE_INT,
    BC_TYPE_STR,
    BC_TYPE_ARR,
    BC_TYPE_NULL,
    BC_TYPE_VAR,
}bcTypes;
typedef struct{
    unsigned int line;
    instructions opcode;
    int operantAmount;
    void** operants;
    bcTypes* type;
}bytecode;
typedef struct{
    char* name;
    void* data;
    size_t size;
    ceTypes type;
}ceVariable;
typedef struct{
    ceVariable* variables;
    unsigned int variableAmount;
    char** variableNames;
    bytecode* programHistory;
}CEVM;

CEVM bootVM(void);
void shutdownVM(void);
CEVM executeInstruction(CEVM VM, bytecode Bytecode);
CEVM storeGlobal(CEVM VM, ceVariable Variable);
#endif
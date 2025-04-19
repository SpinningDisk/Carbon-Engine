#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "engine.h"
#include <stddef.h>


typedef enum{
    PRINT_VAR,
    
    STORE,
    LOAD,
    PUSH,

    JMP,
    JMP_GT,
    JMP_LT,
    
    BLOCK_START,
    BLOCK_END,

    ADD,
    SUB,
    MUL,
    DIV,
}instruction;
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
    instruction opcode;
    int operantAmount;
    void** operants;
    bcTypes* types;
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
    unsigned int programHistoryLength;
    void** stack;
    void** heap;
}CEVM;

CEVM bootVM(void);
void shutdownVM(void);
CEVM executeInstruction(CEVM VM, bytecode Bytecode);
CEVM storeGlobal(CEVM VM, ceVariable Variable);
#endif
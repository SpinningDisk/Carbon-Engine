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
    void** data;
    unsigned int len;
}stack_queue;
typedef struct{
    ceVariable* variables;
    unsigned int variableAmount;
    char** variableNames;
    bytecode* programHistory;
    unsigned int programHistoryLength;
    stack_queue queue;
    stack_queue stack;      // this fucks stuff up: I guess, due 
    // to void**, it cannot assign to data behind the first void**, 
    // which means here queue has priority, and as such CAN assign 
    // and realloc, but this one cannot
}CEVM;
char* ceTypesReadable(ceTypes Type);


stack_queue stackPush_Enqueue(stack_queue Stack, void* Elm);
void* stackPop(stack_queue* Stack);
void* stackPeek(stack_queue* Stack);

bytecode createBytecode(instruction Opcode, int operant_Amount, void** Operants, bcTypes* Types);

CEVM bootVM(void);
CEVM appendInstruction(CEVM VM, instruction Instruction, int Operant_Amount, void** Operants, bcTypes* Types);
CEVM appendBytecode(CEVM VM, bytecode Bytecode);
CEVM executeInstruction(CEVM VM, bytecode Bytecode);
CEVM storeGlobal(CEVM VM, ceVariable Variable);
#endif
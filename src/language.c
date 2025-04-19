#include "../include/engine.h"
#include <stdint.h>
#include <malloc.h>
#include <float.h>
#include <string.h>
#include <stdio.h>


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

// bytecode specific things;
bytecode createBytecode(instruction Opcode, int Operant_Amount, void** Operants, bcTypes* Types){
    bytecode New_Code;
    New_Code.opcode = Opcode;
    New_Code.operantAmount = Operant_Amount;
    New_Code.operants = Operants;
    New_Code.types = Types;
    return New_Code;
}

// VM things
CEVM bootVM(void){
    CEVM VM;
    VM.variables = (ceVariable*)malloc(sizeof(ceVariable));
    VM.variableNames = (char**)malloc(sizeof(char*));
    VM.variableAmount = 0;
    VM.programHistory = (bytecode*)malloc(sizeof(bytecode));
    return VM;
}

// bytecode + VM things
CEVM appendInstruction(CEVM VM, instruction Instruction, int Operant_Amount, void** Operants, bcTypes* Types){
    bytecode* Temp_ProgramHistory = realloc(VM.programHistory, sizeof(bytecode)*(VM.programHistoryLength+1));
    if(Temp_ProgramHistory==NULL){
        fprintf(stderr, "Fatal Memory Error: Not enough Space left\n");
        return VM;
    }

    bytecode New_Code;
    New_Code.opcode = Instruction;
    switch(Operant_Amount){
        case -1:
            fprintf(stderr, "Warning: no operant Amount specified in bytecode; asuming standart\n");
            switch(Instruction){
                case STORE|JMP_GT|JMP_LT:
                    New_Code.operantAmount = 2;
                    New_Code.operants = (void**)malloc(sizeof(void*)*2);
                    New_Code.operants[0] = Operants[0];
                    New_Code.operants[1] = Operants[1];
                    break;
                case JMP|BLOCK_START|BLOCK_END|PUSH|LOAD:
                    New_Code.operants = (void**)malloc(sizeof(void*));
                    New_Code.operantAmount = 1;
                    break;
                default:
                    fprintf(stderr, "Fatal byecode Error: could not declare standart operant Amount\n");
                    return VM;
            }
    }
    

    VM.programHistory = Temp_ProgramHistory;
    VM.programHistory[VM.programHistoryLength] = New_Code;
    return VM;
}
CEVM executeInstruction(CEVM VM, bytecode Bytecode){
    switch(Bytecode.opcode){
        case PRINT_VAR:
            printf("printing something...\n");
            break;
        case STORE:
            ceVariable new_Variable;
            switch(Bytecode.operantAmount){
                case 1:
                    new_Variable.name = (char*)Bytecode.operants[0];
                    break;
                case 2:
                    new_Variable.name = (char*)Bytecode.operants[0];
                    new_Variable.data = Bytecode.operants[1];
                    break;
                default:
                    fprintf(stderr, "Error: Fatal Internal Error: Bytecode ASSIGN contains too many operants\n");
                    return VM;
            }
    }
    return VM;
}

CEVM storeGlobal(CEVM VM, ceVariable Variable){
    ceVariable* temp_Variables = realloc(VM.variables, sizeof(ceVariable)*(VM.variableAmount+1));
    if(temp_Variables==NULL){
        fprintf(stderr, "Critical Memory Error: Not enough memory available!\n");
    }
    char** temp_Variable_Names = (char**)realloc(VM.variableNames, sizeof(char*)*(VM.variableAmount+1));
    if(temp_Variable_Names==NULL){
        fprintf(stderr, "Critical Memory Error: Not enough memory available!\n");
    }
    VM.variables = temp_Variables;
    VM.variables[VM.variableAmount] = Variable;
    VM.variableNames = temp_Variable_Names;
    VM.variableNames[VM.variableAmount] = Variable.name;
    VM.variableAmount++;
    return VM;
}       // search here; do print inbetween lines for second assign
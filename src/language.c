#include "../include/engine.h"
#include <stdint.h>
#include <malloc.h>
#include <float.h>
#include <string.h>
#include <stdio.h>


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
char* ceTypesReadable(ceTypes Type){
    char* ret = (char*)malloc(sizeof(char)*8);
    switch(Type){
        case TYPE_INT:
            return "int";
            break;
        case TYPE_STR:
            return "str";
            break;
        case TYPE_ARR:
            return "array";
            break;
        case TYPE_NULL:
            return "NULL";
            break;
        default:
            return "NODEF";
            break;
    }
}
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

CEVM bootVM(void){
    CEVM VM;
    VM.variables = (ceVariable*)malloc(sizeof(ceVariable));
    VM.variableNames = (char*)malloc(sizeof(char*));
    VM.variableAmount = 0;
    VM.programHistory = (bytecode*)malloc(sizeof(bytecode));
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
    char** temp_Variable_Names = (char*)realloc(VM.variableNames, sizeof(char*)*(VM.variableAmount+1));
    if(temp_Variable_Names==NULL){
        fprintf(stderr, "Critical Memory Error: Not enough memory available!\n");
    }
    VM.variableNames[VM.variableAmount] = Variable.name;
    VM.variables[VM.variableAmount] = Variable;
    
    printf("VM: got variable of type %d, name: %s, value: %d, size: %lu;\n", (int)Variable.type, Variable.name, (int)Variable.data, Variable.size);
    printf("VM: stored as: type %d; name %s/%s; value %d; size %lu\n", VM.variables[VM.variableAmount].type, VM.variableNames[VM.variableAmount], VM.variables[VM.variableAmount].name, (int)VM.variables[VM.variableAmount].data, VM.variables[VM.variableAmount].size);
    VM.variableAmount++;
    return VM;
}       // search here; do print inbetween lines for second assign
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
    stack_queue stack;
}CEVM;

char* ceTypesReadable(ceTypes Type){
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
            return "invalid";
    }
};

// stack stuff
stack_queue stackPush_Enqueue(stack_queue Stack, void* Elm){
    void** Temp_Stack_Data = malloc(sizeof(void*)*(Stack.len+1));
    for(int i=0; i<Stack.len;i++){
        Temp_Stack_Data[i] = Stack.data[i];
    }           // for some reason, realloc crashes here, so we sadly copy manually
    if(Temp_Stack_Data==NULL){
        fprintf(stderr, "Critical Memory Error during PUSH opperator\n");
        return Stack;
    }
    Temp_Stack_Data[Stack.len] = Elm;
    Stack.data = Temp_Stack_Data;
    //printf("stack contains: %d\n", (int)Stack.data[Stack.len]);
    Stack.len++;
    return Stack;
}

// bytecode specific things;
bytecode createBytecode(instruction Opcode, int Operant_Amount, void** Operants, bcTypes* Types){
    bytecode New_Code;
    New_Code.opcode = Opcode;
    New_Code.operantAmount = Operant_Amount;
    New_Code.operants = Operants;
    New_Code.operants = (void**)malloc(sizeof(void*)*Operant_Amount);
    for(int i=0; i<Operant_Amount; i++){
        New_Code.operants[i] = (void*)malloc(sizeof(ceVariable));
        New_Code.operants[i] = Operants[i];
    }
    New_Code.types = (bcTypes*)malloc(sizeof(bcTypes)*Operant_Amount);
    *New_Code.types = *Types;
    free(Operants);
    free(Types);
    printf("types: %d\n", New_Code.types[0]);
    printf("value: %d\n", (int)New_Code.operants[0]);
    return New_Code;
}

// VM things
CEVM bootVM(void){
    CEVM VM;
    VM.variables = (ceVariable*)malloc(sizeof(ceVariable));
    VM.variableNames = (char**)malloc(sizeof(char*));
    VM.variableAmount = 0;
    VM.programHistory = (bytecode*)malloc(sizeof(bytecode));
    stack_queue Stack;
    Stack.data = (void**)malloc(sizeof(void*));
    Stack.len = 0;
    stack_queue Queue;
    Queue.data = (void**)malloc(sizeof(void*));
    Queue.len = 0;
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

CEVM appendBytecode(CEVM VM, bytecode Bytecode){
    printf("performing ");
    /*switch(Bytecode.opcode){
        case PRINT_VAR:
            printf("\"print\" ");
            break;
        case STORE:
            printf("\"store\" ");
            break;
        case LOAD:
            printf("\"load\" ");
            break;
        case PUSH:
            printf("\"push\" ");
            break;
        case JMP:
            printf("\"jump\" ");
            break;
        case JMP_GT:
            printf("\"jump if greater than\" ");
            break;
        case JMP_LT:
            printf("\"jump if less than\" ");
            break;
        case BLOCK_START:
            printf("\"block start\" ");
            break;
        case BLOCK_END:
            printf("\"block end\" ");
            break;
        case ADD:
            printf("addition ");
            break;
        case SUB:
            printf("subtraction ");
            break;
        case MUL:
            printf("multiplicattion ");
            break;
        case DIV:
            printf("division ");
            break; 
    }
    printf("on");
    printf(" ");
    for(int i=0; i<Bytecode.operantAmount;i++){
        switch(Bytecode.types[i]){
            case BC_TYPE_INT:
                printf("%d", (int)Bytecode.operants[i]);
                break;
            case BC_TYPE_STR:
                printf("%s", (char*)Bytecode.operants[i]);
                break;
            case BC_TYPE_ARR:
                printf("NJI\n");
                break;
            case BC_TYPE_NULL:
                printf("NULL");
                break;
            case BC_TYPE_VAR:
                ceVariable Test = *(ceVariable*)(Bytecode.operants[i]);
                break;
                //printf("(%s)", (ceVariable*)(*Bytecode.operants[i])->name);
                //break;
        }
        printf(", ");
    };
    printf("\n");*/
    bytecode* Temp_ProgramHistory = realloc(VM.programHistory, sizeof(bytecode)*(VM.programHistoryLength+1));
    if(Temp_ProgramHistory==NULL){
        fprintf(stderr, "Critical memory Error during bytecode storing\n");
        return VM;
    }
    Temp_ProgramHistory[VM.programHistoryLength] = Bytecode;
    *VM.programHistory = *Temp_ProgramHistory;
    free(Temp_ProgramHistory);
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
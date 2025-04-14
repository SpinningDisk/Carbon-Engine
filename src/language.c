#include "../include/engine.h"
#include <stdint.h>
#include <malloc.h>
#include <float.h>
#include <string.h>
#include <stdio.h>

typedef enum{
    CEType_int = sizeof(int),
    CEType_string = sizeof(char*),
    CEType_object = sizeof(object),
    CEType_euler = sizeof(float)*3*3,
    CEType_quaternion = sizeof(float)*4,
    //expand
}CETypes;

typedef struct{
    char* name;
    CETypes type;
    void* data;
}CESvariable;

typedef struct{
    CESvariable* variables;
    char** variableNames;
    unsigned int variableAmount;
    char** subProgram;
}CESframe;

CESframe __init_frame__(){
    CESframe Program;
    Program.variables = (CESvariable*)malloc(sizeof(CESvariable));
    Program.variableAmount = 0;
    return Program;
}

CESframe storeVariable(CESframe Program, CESvariable Variable){
    CESvariable* New_Variables = realloc(Program.variables, (Program.variableAmount+1)*sizeof(CESvariable));
    char** New_Names = realloc(Program.variableNames, sizeof(char*)*(Program.variableAmount+1));
    if(New_Variables==NULL){
        fprintf(stderr, "Error during variable declaration: not enough memory available!\nreturning\n");
    };
    if(New_Names==NULL){
        fprintf(stderr, "Error during variable declaration: not enough memory available!\nreturning\n");
    };
    Program.variables = New_Variables;
    Program.variables[Program.variableAmount] = Variable;

    New_Names[Program.variableAmount] = Variable.name;
    Program.variableNames = New_Names;
    Program.variableAmount++;
    return Program;

}
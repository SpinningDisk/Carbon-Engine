#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "engine.h"


typedef enum{
    CEType_int,
    CEType_string,
    CEType_object,
    CEType_euler,
    CEType_quaternion,
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
}CESframe;

CESframe __init_frame__();
CESframe storeVariable(CESframe Program, CESvariable Variable);



#endif
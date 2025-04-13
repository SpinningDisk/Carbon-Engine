#include <stdint.h>
#include <malloc.h>
#include <float.h>
#include <string.h>
#include <stdio.h>
#include "../include/engine.h"


typedef int ceT_Int[1];
//typedef int_fast8_t ceT_Int;
typedef char* ceT_String;

typedef enum{
    ceT_Int_id,
    ceT_String_id,
    ceT_Array_id,
    ceT_HashTable_id,
    ceT_EulerRotation_id,
    ceT_Quaternion_id,

    ceT_Object_id,
    ceT_Scene_id,
    ceT_Project_id,
}CEtypes_id;
typedef struct{
    char* name;
    CEtypes_id type;
    void* data;
    int livetime;
}CEdata;
typedef struct{
    void** data;
    CEtypes_id* types;
    size_t capacity;
    size_t length;
}ceT_Array;
typedef struct{
    ceT_Array keys;
    ceT_Array values;
}ceT_HashTable;
typedef float ceT_EulerRotation[4][4][4];
typedef float ceT_Quaternion[5];
typedef object ceT_Object;
typedef scene ceT_Scene;
typedef project ceT_Project;


typedef struct{
    int programCounter;
    int tabLevel;
    CEdata* data;
    unsigned int variableAmount;
}CEprogram;

CEprogram __init_programm__(){
    CEprogram Program;
    Program.programCounter = 0;
    Program.tabLevel = 0;
    Program.data = (CEdata*)malloc(sizeof(CEdata));
    Program.variableAmount = 0;
    return Program;
}


// base functions in interpreter
CEprogram create(char* Line, CEprogram Program){
    if(Line[0]=='\t'){
        printf("hit tab at 0!\n");
    }else if(Line[0]==' '){
        printf("hit space at 0!\n");
    };
    return Program;
}


void garbage_collect(){
    return;
}
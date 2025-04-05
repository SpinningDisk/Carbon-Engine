#include <stdint.h>
#include <float.h>
#include <string.h>
#include "engine.h"

typedef enum{
    ceT_Int;
    ceT_String;
    ceT_Array;
    ceT_HashTable;
    ceT_EulerRotation;
    ceT_Quaternion;

    ceT_Object;
    ceT_Scene;
    ceT_Project;
}CEtypes_id;
typedef struct{
    char* name;
    CEtypes_id type;
    void* data;
    int livetime;
}CEdata;
typedef int_fast8_t ceT_Int;
typedef char* ceT_String;
typedef struct{
    void** data;
    CEtypes_id* types;
    size_t capacity;
    size_t length;
}ceT_Array;
typedef struct{
    ceT_Array keys;
    ceT_Array values;
}ceT_HashTable
typedef float[4][4][4] ceT_EulerRotation;
typedef float[5] ceT_Quaternion;
typedef object ceT_Object;
typedef scene ceT_Scene;
typedef project ceT_Project;


typedef struct{
    int programCounter;
    int tabLevel;
    CEdata* data;
    unsigned int variableAmount;
}CEprogram;

CEprogramm __init_programm__(){
    CEprogram Program;
    Program.programCounter = 0;
    Program.tabLevel = 0;
    Program.CEdata = (CEdata*)malloc(sizeof(CEdata));
    Program.variableAmount = 0;
}


// base functions in interpreter
create(char* Line, CEprogram)


void garbage_collect(){
    return;
}
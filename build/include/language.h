#ifndef LANGUAGE_H
#define LANGUAGE_H

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
    char* sub_program;
    CEdata* data;
    unsigned int variableAmount;
}CEprogram;


#endif
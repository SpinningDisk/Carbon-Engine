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
}CETypes;
typedef struct{
    char* name;
    char* type;
    void* data;
    int livetime;
}CEdata;

typedef struct{

}
typedef struct{
    int programCounter;
    int tabLevel;
    CEdata* data;
    unsigned int Variable_Amount;
}CEprogram;

CEprogramm __init_programm__(){
    CEprogram Program;
    Program.
}


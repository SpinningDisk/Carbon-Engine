// structs and their children (??? parameter??? values??? ...) will be written lowercase camelCase
// variables inside functions will be written in uppercase Snake_case
/*
kwarg keys (arg values):
1: vertex
2: object
3: scene
4: project*/
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

/* 
Objects shall have a Name, and ID (for reference in Scenes), a type (e.g: solid, camera, light, beziér curve, etc.); 
a list of vertices (or just one, in case of cam, light, ...), a center (for repositioning), and a something I forgot
*/

//own types
typedef float vertex[4];
typedef struct{
    char* name;
    int type;
    vertex center;
    union{
        struct{
            vertex* vertices;
            unsigned int vertexAmount;
        };
    };
    int* id;
}object;
typedef struct{
    char* name;
    object* objects;
    unsigned int objectAmount;
    // some settings
}scene;


//init functions
object __init_object__(char* Name, int Type){
    object Object;
    Object.name = Name;
    Object.type = Type;
    vertex Center = {0, 0, 0, '\0'};
    for(int i=0; i<5; i++){
        Object.center[i] = Center[i];
    }
    Object.vertexAmount = 0;
    Object.id = malloc(sizeof(int));
    *Object.id = -1;
    return Object;
}
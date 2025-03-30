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
typedef vertex connection[2];
typedef connection* area;
typedef struct{
    char* name;
    int type;
    vertex center;
    vertex* vertices;
    connection* connnections;
    area* areas;
    unsigned int vertexAmount;
    int id;
}object;
typedef struct{
    char* name;
    object* objects;
    int objectAmount;
    char** objectNames;
    int id;
    // some settings
}scene;
typedef scene* Project;


//init functions
object __init_object__(char* Name, int Type){
    object Object;
    Object.name = Name;
    Object.type = Type;
    vertex Center = {0, 0, 0, '\0'};
    for(int i=0; i<5; i++){
        Object.center[i] = Center[i];
    }
    Object.vertices = (vertex*)malloc(0);
    Object.vertexAmount = 0;
    Object.id = -1;
    return Object;
}
scene __init_scene__(char* Name){
    scene Scene;
    Scene.name = Name;
    Scene.objects = (object*)malloc(0);
    Scene.objectAmount = 0;
    Scene.objectNames = (char**)malloc(sizeof(char*));
    Scene.objectNames[0] = (char*)malloc(sizeof(char));
    Scene.id = -1;
    return Scene;
}



// append functions
object appendVertexToObject(vertex Vertex, object Object){
    Object.vertexAmount++;
    Object.vertices = realloc(Object.vertices, sizeof(vertex)*Object.vertexAmount);
    for(int i=0; i<4; i++){
        Object.vertices[Object.vertexAmount-1][i] = Vertex[i];
    }
    return Object;
}
scene appendObjectToScene(object Object, scene Scene){
    Object.id = Scene.objectAmount;
    Scene.objects = realloc(Scene.objects, sizeof(object)*(Scene.objectAmount+1));
    Scene.objects[Scene.objectAmount] = Object;
    Scene.objectNames = (char**)realloc(Scene.objectNames, sizeof(char*)*(Scene.objectAmount+1));
    //Scene.objectNames[Scene.objectAmount] = Object.name;
    Scene.objectAmount++;
    return Scene;
}
// structs and their children (??? parameter??? values??? ...) will be written lowercase camelCase
// variables inside functions will be written in uppercase Snake_case
#include "functions.h"
#include <stdlib.h>
/* 
Objects shall have a Name, and ID (for reference in Scenes), a type (e.g: solid, camera, light, beziér curve, etc.); 
a list of vertices (or just one, in case of cam, light, ...), a center (for repositioning), and a something I forgot
*/

typedef struct{
    float x;
    float y;
    float z;
    unsigned int id;
}vertex;
typedef struct{
    vertex start;
    vertex end;
    unsigned int id;
}edge;
typedef struct{
    edge* edges;
    unsigned int id;
}face;
typedef struct{
    char* name;
    unsigned int type;
    int id;
    vertex* vertices;
    edge* edges;
    face* faces;
    vertex center;
    unsigned int vertexCount;
    unsigned int edgeCount;
    unsigned int faceCount;
}object;
typedef struct{
    char* name;
    unsigned int id;
    unsigned int objectCount;
    char** objectNames;
    object* objects;
}scene;
typedef struct{
    char** sceneNames;
    scene* scenes;
}project;

int retOne(){
    return 1;
}
// init functios

// standart shapes

// clear functions
void clearObjects(object* Objects){
    for(int i=0; i<sizeof(*Objects)/sizeof(object); i++){
        Objects[i].name = (char*)malloc(1);
        Objects[i].type = 0;
        Objects[i].id = 0;
        Objects[i].vertices = (vertex*)malloc(1);
        Objects[i].edges = (edge*)malloc(1);
        Objects[i].faces = (face*)malloc(1);
        vertex center;
        center.x = 0;
        center.y = 0;
        center.z = 0;
        center.id = 0;
        Objects[i].center = center;
        Objects[i].vertexCount = 1;
        Objects[i].edgeCount = 0;
        Objects[i].faceCount = 0;
    }
    return;
}



void clearScenes(scene* Scenes){
    for(int i=0; i<sizeof(*Scenes)/sizeof(scene); i++){
        Scenes[i].name = (char*)malloc(1);
        Scenes[i].id = 0;
        Scenes[i].objectCount = 0;
        Scenes[i].objectNames = (char**)malloc(sizeof(char*));
        Scenes[i].objectNames[0] = (char*)malloc(1);
        clearObjects(Scenes[i].objects);
    }
    return;
}

void clearProject(){
    return;
}
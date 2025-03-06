// structs and their children (??? parameter??? values??? ...) will be written lowercase camelCase
// variables inside functions will be written in uppercase Snake_case

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
    unsigned int  vertexCount;
}object;
typedef struct{
    char* name;
    unsigned int id;
    unsigned int objectCout;
    char** objectNames;
    object* objects;
}scene;
typedef struct{
    char** sceneNames;
    scene* scenes;
}project;


// init functios

// standart shapes

// clear functions
void clearObject(object* Object){
    free(Object);
}
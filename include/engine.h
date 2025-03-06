#ifndef ENGINE_H
#define ENGINE_H


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
    float center[4];
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


// clean functions

void clearObject(object* Object);
#endif
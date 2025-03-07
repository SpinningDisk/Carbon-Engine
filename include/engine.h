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

int retOne();
// clean functions

void clearObjects(object* Objects);
void clearScenes(scene* Scenes);
#endif
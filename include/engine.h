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
    unsigned int objectCount;
    char** objectNames;
    object* objects;
}scene;
typedef struct{
    char** sceneNames;
    scene* scenes;
    unsigned int sceneCount
}project;

// init functions
object __init_object__(scene Scene, unsigned int Type, char* Name);
scene __init_scene__(project Project, char* Name);
project __init_project__();

// clean functions
object* clearObjects(object* Objects);
scene* clearScenes(scene* Scenes);
project* clearProjects(project* Projects);
#endif
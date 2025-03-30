#ifndef ENGINE_H
#define ENGINE_H

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
    int id;
    // some settings
}scene;
typedef scene* Project;


// init functions
object __init_object__(char* Name, int Type);
scene __init_scene__(char* Name);


// append functions
object appendVertexToObject(vertex Vertex, object Object);
scene appendObjectToScene(object Object, scene Scene);

#endif
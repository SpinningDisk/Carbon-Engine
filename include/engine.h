#ifndef ENGINE_H
#define ENGINE_H

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

object __init_object__(char* Name, int Type);

#endif
#ifndef ENGINE_H
#define ENGINE_H


struct _vertex{
    float x;
    float y;
    float z;
};

struct _obj{
    char* Name;

    struct _vertex* vertices;
    unsigned int vertexAmount;

    unsigned int* edges[2];
    unsigned int edgeAmount;
    
    unsigned int** areas;
    unsigned int areaAmount;
};

struct _scn{
    char* name;
    struct _obj* objects;
    int objectAmount;
};

struct _vertex default_vertex();
struct _obj default_obj();
struct _scn default_scn();
typedef struct{
    void* addon;
    
    void* (*vertex_)();
    void* (*obj_)();
    void* (*scn_)();
 
    void* (*setVertex_)(void*, void*);
}_kernel;

_kernel __binder__();
#endif

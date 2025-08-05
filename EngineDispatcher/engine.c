#include "../build/include/kernel.h"
#include <stdio.h>


// Table.h
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


typedef struct{
    void* addon;
    
    void* (*vertex_)();
    void* (*obj_)();
    void* (*scn_)();

    void* (*setVertex_)(void*, void*);
}_kernel;

// 

struct _vertex default_vertex(){
    struct _vertex v = {0};
    return v;
}

struct _obj default_obj() {
    struct _obj o = {0};
    return o;
}

struct _scn default_scn() {
    struct _scn s = {0};
    return s;
}
struct _vertex default_setVertex(void* vVertex, void* vPos){
    float Pos[3] = {*(float*)vPos, *(float*)vPos+sizeof(float), *(float*)vPos+2*sizeof(float)};
    struct _vertex Vertex= *(struct _vertex*)vVertex;
    Vertex.x = Pos[0];
    Vertex.y = Pos[1];
    Vertex.z = Pos[2];
    return Vertex;
}


_kernel __binder__(){
    _kernel Kernel;
    _customKernel customKernel = load_customKernel();
    
    Kernel.vertex_ = customKernel.__vertex__ ? (void*)customKernel.__vertex__ : (void*)&default_vertex;
    Kernel.obj_    = customKernel.__obj__    ? (void*)customKernel.__obj__    : (void*)&default_obj;
    Kernel.scn_    = customKernel.__scn__    ? (void*)customKernel.__scn__    : (void*)&default_scn;
    Kernel.setVertex_ = customKernel.__setVertex__ ? (void*)customKernel.__setVertex__ : (void*)&default_setVertex;
    // need to find out how to find functions within customKernel here
    return Kernel;
}

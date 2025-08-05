#ifndef KERNEL_H
#define KERNEL_H


void hello();
struct vertex{
    float x;
    float y;
    float z;
};
struct obj{
    char* name;
    struct vertex* vertices;
    unsigned int* edges[3];
    unsigned int edgeAmount;
    unsigned int** areas;
    unsigned int areAmount;
    struct vertex center;
    int id;
};
struct scn{
    char* name;
    struct obj* objects;
    unsigned int objectAmount;
    char** objectNames;
};
struct vertex _vertex();
struct obj _obj();
struct scn _scn();

typedef struct{
    struct{
        int a;
    }addon;
    struct vertex (*__vertex__)();
    struct obj (*__obj__)();
    struct scn (*__scn__)();

    void* (*__setVertex__)();
}_customKernel;

_customKernel load_customKernel();


// remove this (belongs in EngineDispatcher/Table.h)
#endif

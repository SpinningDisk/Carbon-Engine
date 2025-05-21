#include <stdio.h>

typedef struct{
    float x;
    float y;
    float z;
}vertex;
typedef struct{
    char* name;
    vertex* vertices;
    unsigned int* edges[3];
    unsigned int** areas;
    vertex center;
    int id;
}object;

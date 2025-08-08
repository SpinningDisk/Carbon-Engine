#include "../include/libfastfunctions.h"
struct _KERNEL{
    void* addon;
    void* (*_vertex)();
    void* (*_object)(void**);
    void* (*_transform)(void**);
};

struct _FLBCK_VERTEX{
    float cords[3];
};

struct _FLBCK_OBJECT{
    struct _FLBCK_VERTEX* vertices;
    unsigned short vertexAmount;
};
// fallback transformation function; first element of void is the object, second is the translation vector, third is the scale and fourth contains rotation
// this function is supposed to run on half of a toaster, so no center, and no trigonometry(/trigonometri?)
#include <stdio.h>
void* _FLBCK_TRANSFORM(void** args){
    struct _FLBCK_OBJECT* Object = (struct _FLBCK_OBJECT*)args[0];
    struct _FLBCK_VERTEX* Move = (struct _FLBCK_VERTEX*)(*(void**)((char*)args+sizeof(struct _FLBCK_OBJECT)));
    struct _FLBCK_VERTEX* Scale = (struct _FLBCK_VERTEX*)(*(void**)((char*)args+sizeof(struct _FLBCK_OBJECT)+1*sizeof(struct _FLBCK_VERTEX)));
    struct _FLBCK_VERTEX rotation = *(struct _FLBCK_VERTEX*)(*(void**)((char*)args+sizeof(struct _FLBCK_OBJECT)+2*sizeof(struct _FLBCK_VERTEX)));
    unsigned short selection[3] = (float[3])(*(void**)((char*)args+sizeof(struct _FLBCK_OBJECT)+3*sizeof(struct _FLBCK_VERTEX)));
    float degX = rotation.cords[0];
    float degY = rotation.cords[1];
    float degZ = rotation.cords[2];

    float rotation_matrix[3][3][3] = {{{1, 0,             0,            },      {fastCos(degY),  0, fastSin(degY) },        {fastCos(degZ), -fastSin(degZ), 0}},
                                      {{0, fastCos(degX), -fastSin(degX)},      {0,              1, 0,            },        {fastSin(degZ), fastCos(degZ),  0}},
                                      {{1, fastSin(degX), fastCos(degX) },      {-fastSin(degY), 0, fastCos(degY) },        {0,             0,              1}}};       // (xyz, row, col)
    for(unsigned short i=0; i<Object->vertexAmount; i++){
        // Move
        Object->vertices[i].cords[0] = Object->vertices[i].cords[0]+Move[i].cords[0];
        Object->vertices[i].cords[1] = Object->vertices[i].cords[1]+Move[i].cords[1];
        Object->vertices[i].cords[2] = Object->vertices[i].cords[2]+Move[i].cords[2];
        
        // Scale
        Object->vertices[i].cords[0] = Object->vertices[i].cords[0]*Scale[i].cords[0];
        Object->vertices[i].cords[1] = Object->vertices[i].cords[1]*Scale[i].cords[1];
        Object->vertices[i].cords[2] = Object->vertices[i].cords[2]*Scale[i].cords[2];
        
        // Rotate
        // first rotation
        Object->vertices[i].cords[0] = rotation_matrix[0][0][0]*Object->vertices[i].cords[0] + rotation_matrix[0][0][1]*Object->vertices[i].cords[1] + rotation_matrix[0][0][2]*Object->vertices[i].cords[2];
        Object->vertices[i].cords[1] = rotation_matrix[0][1][0]*Object->vertices[i].cords[0] + rotation_matrix[0][1][1]*Object->vertices[i].cords[1] + rotation_matrix[0][1][2]*Object->vertices[i].cords[2];
        Object->vertices[i].cords[2] = rotation_matrix[0][2][0]*Object->vertices[i].cords[0] + rotation_matrix[0][2][1]*Object->vertices[i].cords[1] + rotation_matrix[0][2][2]*Object->vertices[i].cords[2];
        
        // second rotation
        Object->vertices[i].cords[0] = rotation_matrix[1][0][0]*Object->vertices[i].cords[0] + rotation_matrix[1][0][1]*Object->vertices[i].cords[1] + rotation_matrix[1][0][2]*Object->vertices[i].cords[2];
        Object->vertices[i].cords[1] = rotation_matrix[1][1][0]*Object->vertices[i].cords[0] + rotation_matrix[1][1][1]*Object->vertices[i].cords[1] + rotation_matrix[1][1][2]*Object->vertices[i].cords[2];
        Object->vertices[i].cords[2] = rotation_matrix[1][2][0]*Object->vertices[i].cords[0] + rotation_matrix[1][2][1]*Object->vertices[i].cords[1] + rotation_matrix[1][2][2]*Object->vertices[i].cords[2];
        
        // third rotation
        Object->vertices[i].cords[0] = rotation_matrix[2][0][0]*Object->vertices[i].cords[0] + rotation_matrix[2][0][1]*Object->vertices[i].cords[1] + rotation_matrix[2][0][2]*Object->vertices[i].cords[2];
        Object->vertices[i].cords[1] = rotation_matrix[2][1][0]*Object->vertices[i].cords[0] + rotation_matrix[2][1][1]*Object->vertices[i].cords[1] + rotation_matrix[2][1][2]*Object->vertices[i].cords[2];
        Object->vertices[i].cords[2] = rotation_matrix[2][2][0]*Object->vertices[i].cords[0] + rotation_matrix[2][2][1]*Object->vertices[i].cords[1] + rotation_matrix[2][2][2]*Object->vertices[i].cords[2];
    };
    return Object;
}

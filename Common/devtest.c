#include "../include/libfastfunctions.h"
#include "../include/Binder.h"
#include <stdio.h>
#include <malloc.h>

int main(){
    struct _FLBCK_VERTEX vertex = {.cords={1.0f, 2.0f, 3.0f}};
    struct _FLBCK_OBJECT obj = {.vertices = &vertex, .vertexAmount=1};
    printf("object NULL with single vertex at (%f, %f, %f)\n", obj.vertices->cords[0],obj.vertices->cords[1], obj.vertices->cords[2]);
    
    struct _FLBCK_VERTEX Move = {.cords={0.0f, 0.0f, 0.0f}};
    struct _FLBCK_VERTEX Scale = {.cords={1.0f, 1.0f, 1.0f}};
    struct _FLBCK_VERTEX Rot = {.cords={90.0f, 0.0f, 0.0f}};
    
    void** package = (void**)malloc(sizeof(struct _FLBCK_OBJECT)+4*sizeof(struct _FLBCK_VERTEX));
    package[0] = &obj;
    *(void **)((char *)package+sizeof(struct _FLBCK_OBJECT)) = &Move;
    *(void**)((char*)package+sizeof(struct _FLBCK_OBJECT)+1*sizeof(struct _FLBCK_VERTEX)) = &Scale;
    *(void**)((char*)package+sizeof(struct _FLBCK_OBJECT)+2*sizeof(struct _FLBCK_VERTEX)) = &Rot;
    
    obj = *(struct _FLBCK_OBJECT*)_FLBCK_TRANSFORM(package);
    printf("object NULL with single vertex at (%f, %f, %f)\n", obj.vertices->cords[0],obj.vertices->cords[1], obj.vertices->cords[2]);

    printf("hai :3");
    return 0;
}

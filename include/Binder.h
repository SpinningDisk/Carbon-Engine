#ifndef BINDER_H
#define BINDER_H

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
void* _FLBCK_TRANSFORM(void** args);

#endif

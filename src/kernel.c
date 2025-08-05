#include <math.h>

struct vertex{
    float x;
    float y;
    float z;
};
struct obj{
    char* name;
    struct vertex* vertices;
    unsigned int vertexAmount;
    unsigned int* edges[3];
    unsigned int edgeAmount;
    unsigned int** areas;
    unsigned int areasVertexAmount;
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
struct vertex _vertex(){
    struct vertex Vertex;
    return Vertex;
}
struct obj _obj(){
    struct obj Obj;
    return Obj;
}
struct scn _scn(){
    struct scn Scn;
    return Scn;
}
struct vertex* rotate_vertex(struct obj* Object, unsigned int Index, struct vertex Angle){
    struct vertex Vertex = Object->vertices[Index];
    struct vertex LocalVertex;
    LocalVertex.x = Vertex.x - Object->center.x;
    LocalVertex.y = Vertex.y - Object->center.y;
    LocalVertex.z = Vertex.z - Object->center.z;
    
    // rotate around xy
    float rotation_matrix[2][2] = {{cos(Angle.x), -sin(Angle.x)}, {sin(Angle.x), cos(Angle.x)}};
    
    return &Vertex;
}
struct obj rotate_object(struct obj Object, struct vertex Angle){
    // later
    return Object;
}

typedef struct{
    struct{
        struct vertex* (*_rotate_vertex)(struct obj*, unsigned int index, struct vertex);
        struct obj (*_rotate_object)(struct obj, struct vertex);
    }addon;
    struct vertex (*__vertex__)();
    struct obj (*__obj__)();
    struct scn (*__scn__)();
}_customKernel;
_customKernel load_customKernel(){
    _customKernel customKernel;
    customKernel.addon._rotate_vertex = &rotate_vertex;
    customKernel.addon._rotate_object = &rotate_object;
    customKernel.__vertex__ = &_vertex;
    customKernel.__obj__ = &_obj;
    customKernel.__scn__ = &_scn;
    return customKernel;
}

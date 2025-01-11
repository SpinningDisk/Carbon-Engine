#ifndef ENGINE_H
#define ENGINE_H

int GetIndex(char* elm, char** array, int arr_size);

typedef struct vert{
    float x,y,z;
}vert;
typedef struct edges{
    int a,b;
}edge;
typedef struct face{
    int* edges;
}face;
typedef struct{
    unsigned int vertex_count;
    vert *vertices; 
    unsigned int edge_count;
    edge *edges;
    unsigned int face_count;
    face *faces;

    char *name;
    vert *center;
}obj;
typedef struct{
    obj *objects;
    unsigned int obj_count;
    char *name;
}scene;

obj __init_object__(obj object, char Name[31]);
vert* calculate_obj_center(vert* vertices, int vert_amount);
obj append_vert_to_obj(float x, float y, float z, obj object);
obj append_vert_to_obj_by_vert(vert new_vert, obj object);
obj change_vertex(unsigned int index, float new_x, float new_y, float new_z, obj object);
obj change_vertex_by_vert(unsigned int index, vert new_vert, obj object);
/*obj create_edge_by_index(int vert_a_index, int vert_b_index, obj object)*/
char* debug_obj(char* Name, scene Scene);
scene __init_scene__(scene Scene, char name[30]);
scene append_obj_to_scene_by_object(scene Scene, obj Object);
void debug_scn(scene Scene);
scene create_obj(scene Scene, char* Name, unsigned int vert_amount, vert* verts);
obj move_object_vec(obj Object);
obj move_object_pos(obj Object);
scene move_object(scene Scene);



#endif
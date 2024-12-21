#ifndef BACKEND_H
#define BACKEND_H

int GetIndex(char key[], char* values[32][16]);

typedef struct vert{
    float x,y,z;
}vert;
typedef struct{
    unsigned int vertex_count;
    vert *vertices; 
    char *name;
    vert *center;
}obj;
typedef struct{
    obj *objects;
    unsigned int obj_count;
    char *name;
}scene;

obj __init_object__(obj object, char Name[30]);
vert* calculate_obj_center(vert* vertices, int vert_amount);
obj append_vert_to_obj(float x, float y, float z, obj object);
obj append_vert_to_obj_by_vert(vert new_vert, obj object);
obj change_vertex(unsigned int index, float new_x, float new_y, float new_z, obj object);
obj change_vertex_by_vert(unsigned int index, vert new_vert, obj object);
void debug_obj(obj object);
scene __init_scene__(scene Scene, char name[30]);
scene append_obj_to_scene_by_object(scene Scene, obj Object);
void debug_scn(scene Scene);
scene create_obj(scene Scene);
obj move_object_vec(obj Object);
obj move_object_pos(obj Object);
scene move_object(scene Scene);



#endif
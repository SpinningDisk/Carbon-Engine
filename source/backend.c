#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


int GetIndex(char key[], char *values[32][16]){
    int arr_size = (int)(sizeof(*values)/sizeof(*values[0]));
    for(int i=0;i<arr_size; i++){
        if(*values[i]!=NULL){
            if(strcmp(key, *values[i])==0){
                return i;
            };
        };
    };
    return -1;
};


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


obj __init_object__(obj object, char Name[30]){
    object.vertices = (vert*)malloc(sizeof(vert));
    object.name = (char*)malloc(strlen(Name)*sizeof(char));
    for(int i=0; i<strlen(Name); i++){
        object.name[i] = Name[i];
    };
    vert base_vert;
    base_vert.x = 0.0f;
    base_vert.y = 0.0f;
    base_vert.z = 0.0f;
    object.vertices[0] = base_vert;
    object.vertex_count = 1;
    
    object.center = (vert*)malloc(sizeof(vert));
    object.center[0].x = 0.0f;
    object.center[0].y = 0.0f;
    object.center[0].z = 0.0f;
    
    return object;
};
vert* calculate_obj_center(vert* vertices, int vert_amount){
    vert *new_center = (vert*)malloc(sizeof(vert));
    float new_cords[3];
    for(int i=0;i<vert_amount;i++){
        new_cords[0] += vertices[i].x/vert_amount;
        new_cords[1] += vertices[i].y/vert_amount;
        new_cords[2] += vertices[i].z/vert_amount;  
        printf("%f, %f, %f for %d\n", vertices[i].x, vertices[i].y, vertices[i].z, i);
    };
    new_center[0].x = new_cords[0];
    new_center[0].y = new_cords[1];
    new_center[0].z = new_cords[2];
    printf("coc:    returning: %f, %f, %f\n", new_center[0].x, new_center[0].y, new_center[0].z);               //if x<1:   cannot take x value of .b (need 0.b): will result in corrupted y (try: create->name->2->1,0,0->.5,0,0; notice the .5, not 0.5);
    return new_center;
};
obj append_vert_to_obj(float x, float y, float z, obj object){
    vert appended_vert;
    appended_vert.x = x;
    appended_vert.y = y;
    appended_vert.z = z;
    vert* new_verts = (vert*)realloc(object.vertices, (object.vertex_count+1)*sizeof(vert));
    object.vertices = new_verts;
    object.vertices[object.vertex_count] = appended_vert;
    object.vertex_count++;
    return object;
};
obj append_vert_to_obj_by_vert(vert new_vert, obj object){
    vert* new_verts = (vert*)realloc(object.vertices, (object.vertex_count+1)*sizeof(vert));
    object.vertices = new_verts;
    object.vertices[object.vertex_count] = new_vert;
    object.vertex_count++;
    return object;
}
obj change_vertex(unsigned int index, float new_x, float new_y, float new_z, obj object){
    vert new_vert;
    new_vert.x = new_x;
    new_vert.y = new_y;
    new_vert.z = new_z;
    object.vertices[index] = new_vert;
    return object;
}
obj change_vertex_by_vert(unsigned int index, vert new_vert, obj object){
    object.vertices[index] = new_vert;
    return object;
}
void debug_obj(obj object){
    printf("obj-debuger:    \n");
    printf("    debuggin: '%s'\n", object.name);
    printf("        vertices:\n");
    for (int i=0; i<object.vertex_count+1; i++){
        printf("            %f, %f, %f\n", object.vertices[i].x, object.vertices[i].y, object.vertices[i].z);
    };
    printf("        vertex_count:\n");
    printf("            %d\n", object.vertex_count+1);
    printf("        center:\n");
    printf("            %f, %f, %f", object.center[0].x, object.center[0].y, object.center[0].z);
}


scene __init_scene__(scene Scene, char name[30]){
    Scene.objects = (obj*)malloc(sizeof(obj));
    Scene.name = (char*)malloc(strlen(name)*sizeof(char));
    for(int i=0; i<strlen(name); i++){
        Scene.name[i] = name[i];
    };
    obj base_cube;
    char base_cube_name[30] = "cube";
    base_cube = __init_object__(base_cube, base_cube_name);
    vert vert1;
    vert1.x = -0.5f;
    vert1.y = -0.5f;
    vert1.z = -0.5f;
    vert vert2;
    vert2.x = 0.5f;
    vert2.y = -0.5f;
    vert2.z = -0.5f;
    vert vert3;
    vert3.x = -0.5f;
    vert3.y = 0.5f;
    vert3.z = -0.5f;
    vert vert4;
    vert4.x = 0.5f;
    vert4.y = 0.5f;
    vert4.z = -0.5f;
    vert vert5;
    vert5.x = -0.5f;
    vert5.y = -0.5f;
    vert5.z = 0.5f;
    vert vert6;
    vert6.x = 0.5f;
    vert6.y = -0.5f;
    vert6.z = 0.5f;
    vert vert7;
    vert7.x = -0.5f;
    vert7.y = 0.5f;
    vert7.z = 0.5f;
    vert vert8;
    vert8.x = 0.5f;
    vert8.y = 0.5f;
    vert8.z = 0.5f;

    base_cube = change_vertex_by_vert(0, vert1, base_cube);
    base_cube = append_vert_to_obj_by_vert(vert2,  base_cube);
    base_cube = append_vert_to_obj_by_vert(vert3, base_cube);
    base_cube = append_vert_to_obj_by_vert(vert4, base_cube);
    base_cube = append_vert_to_obj_by_vert(vert5, base_cube);
    base_cube = append_vert_to_obj_by_vert(vert6, base_cube);
    base_cube = append_vert_to_obj_by_vert(vert7, base_cube);
    base_cube = append_vert_to_obj_by_vert(vert8, base_cube);

    Scene.objects[0] = base_cube;


    Scene.obj_count=1;

    return Scene;
}
scene append_obj_to_scene_by_object(scene Scene, obj Object){
    Scene.objects = (obj*)realloc(Scene.objects, sizeof(obj)*(Scene.obj_count+1));
    Scene.objects[Scene.obj_count] = Object;
    Scene.obj_count++;
    return Scene;
}
void debug_scn(scene Scene){
    printf("scn-debugger:\n");
    printf("    debugging: '%s'\n", Scene.name);
    printf("        obj-amount: %d\n", Scene.obj_count);
    for(int i=0; i<Scene.obj_count; i++){
        printf("        obj-debuger:    \n");
        printf("            debuggin: '%s'\n", Scene.objects[Scene.obj_count-1-i].name);
        printf("                vertices:\n");
        for (int j=0; j<Scene.objects[Scene.obj_count-1-i].vertex_count+1; j++){
            printf("                    %f, %f, %f\n", Scene.objects[Scene.obj_count-1-i].vertices[j].x, Scene.objects[Scene.obj_count-1-i].vertices[j].y, Scene.objects[Scene.obj_count-1-i].vertices[j].z);
        };
        printf("                vertex_count:\n");
        printf("                    %d\n", Scene.objects[Scene.obj_count-1-i].vertex_count+1);
        printf("                center:\n");
        printf("                    %f, %f, %f\n", Scene.objects[Scene.obj_count-1-i].center[0].x, Scene.objects[Scene.obj_count-1-i].center[0].y, Scene.objects[Scene.obj_count-1-i].center[0].z);
    
        };
        return;
}


scene create_obj(scene Scene){
    char name[30];
    unsigned int vert_amount;
    obj new_obj;
    printf("------------------------------------------------------------ Enter Name of new object------------------------------------------------------------");
    printf("\n@ ");
    scanf("%29s", &name);
    if(strlen(name)>=29){
        printf("too long name!\nsign-limit:29");
        Scene = create_obj(Scene);
        return Scene;
    };
    for(int i=0;i<Scene.obj_count;i++){
        if(strcmp(Scene.objects[i].name, name)==0){
            printf("object already exists; please chose a different name\n");
            Scene = create_obj(Scene);
            return Scene;
        };
    };
    printf("------------------------------------------------------------ Enter amount of vertices------------------------------------------------------------");
    printf("\n# ");
    scanf("%u", &vert_amount);
    if(vert_amount>25){
        printf("woa! that's a lot'a vertices!\n\tAre you sure you want to create %u amount of vertices?\n\t(not the amount you entered? report at: example.com)\n>");       //add actual github;
        char enter_masive_amount[1];
        scanf("%1s", &enter_masive_amount);
        if(strcmp("y", enter_masive_amount)==0){
            if(strcmp("n", enter_masive_amount)){
            }else{
                create_obj(Scene);
            };
        }else{
            create_obj(Scene);
        };
    };
    new_obj = __init_object__(new_obj, name);
    for(int i=0;i<vert_amount;i++){
        float coords[3];
        printf("------------------------------------------------------------ please enter x coordinate for vertex %d----------------------------------------\n##", i);
        scanf("%f", &coords[0]);
        printf("------------------------------------------------------------ please enter y coordinate for vertex %d----------------------------------------\n##", i);
        scanf("%f", &coords[1]);
        printf("------------------------------------------------------------ please enter z coordinate for vertex %d----------------------------------------\n##", i);
        scanf("%f", &coords[2]);
        new_obj = append_vert_to_obj(coords[0], coords[1], coords[2], new_obj);
    };
    new_obj.center = calculate_obj_center(new_obj.vertices, new_obj.vertex_count);

    Scene = append_obj_to_scene_by_object(Scene, new_obj);
    return Scene;
};

obj move_object_vec(obj Object){
    float vector[3];
    printf("------------------------------------------------------------enter x coordinate of vector:------------------------------------------------------------\n##");
    scanf("%f", &vector[0]);
    printf("------------------------------------------------------------enter y coordinate of vector:------------------------------------------------------------\n##");
    scanf("%f", &vector[1]);
    printf("------------------------------------------------------------enter z coordinate of vector:------------------------------------------------------------\n##");
    scanf("%f", &vector[2]);
    for(int i=0; i<Object.vertex_count;i++){
        Object.vertices[i].x = Object.vertices[i].x+vector[0];
        Object.vertices[i].y = Object.vertices[i].y+vector[1];
        Object.vertices[i].z = Object.vertices[i].z+vector[2];
    };
    Object.center[0].x = Object.center[0].x+vector[0];
    Object.center[0].y = Object.center[0].y+vector[1];
    Object.center[0].z = Object.center[0].z+vector[2];
    return Object;
};
obj move_object_pos(obj Object){
    printf("using position as method of movement\n");
    return Object;
};
scene move_object(scene Scene){
    char name[30];
    char vec_or_pos[9];
    printf("------------------------------------------------------------ enter name of object to move------------------------------------------------------------ \n@ ");
    scanf("%29s", &name);
        obj Object;
    bool obj_found = false;
    for(int i=0;i<Scene.obj_count;i++){
        if(strcmp(name, Scene.objects[i].name)==0){
            printf("found %s at index %d\n", Scene.objects[i].name, i);
            obj Object = Scene.objects[i];
            obj_found = true;
            break;
        };
    };
    switch(obj_found) {
        case false:
            printf("invalid name/name not found\n");
            Scene = move_object(Scene);
            return Scene;
        case true:
            break;
    };
    if(strlen(name)>=29){
        printf("name too long\n\tit is very likely that this object doesn't exist\n\tin case it does, please report this as a bug at: example.com\n");
        Scene = move_object(Scene);
        return Scene;
    };
    printf("------------------------------------------------------------ enter wether to use vector or new position---------------------------------------------- \n>");
    scanf("%8s", &vec_or_pos);
    

    if(strlen(vec_or_pos)>=8){
        printf("no such action found\n\tplease try again\n");
        Scene = move_object(Scene);
        return Scene;
    };
    if(strcmp("vector", vec_or_pos)==0){
        Object = move_object_vec(Object);
    }else if(strcmp("vec", vec_or_pos)==0){
        Object = move_object_vec(Object);
    }else if(strcmp("position", vec_or_pos)==0){
        Object = move_object_pos(Object);
    }else if((strcmp("pos", vec_or_pos)==0)){
        Object = move_object_pos(Object);
    }else{
        printf("received: %s; not an option\n", vec_or_pos);
        Scene = move_object(Scene);
    };
    return Scene;
};
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
}obj;


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
    object.vertex_count = 0;
    return object;
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
}

typedef struct{
    obj *objects;
    unsigned int obj_count;
    char *name;
}scene;
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
        printf("                    %d\n", Scene.objects[Scene.obj_count-1-i].vertex_count+1);    }
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
    Scene = append_obj_to_scene_by_object(Scene, new_obj);
    return Scene;
};

scene move_object_vec(scene Scene){                                         //and this has conflicting types;
    printf("------------------------------------------------------------ using vector as method of movement-------------------------------------------------\n@ ");
    return Scene;
};
scene move_object_pos(scene Scene){
    printf("using position as method of movement\n");
    return Scene;
};
scene move_object(scene Scene){
    char name[30];
    char vec_or_pos[9];
    printf("------------------------------------------------------------ enter name of object to move------------------------------------------------------------ \n@ ");
    scanf("%29s", &name);
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
        Scene = move_object_vec(Scene);                             //for some goddamn reason, this is an int;
    }else if(strcmp("vec", vec_or_pos)==0){
        Scene = move_object_vec(Scene);
    }else if(strcmp("position", vec_or_pos)==0){
        Scene = move_object_pos(Scene);
    }else if((strcmp("pos", vec_or_pos)==0)){
        Scene = move_object_pos(Scene);
    }else{
        printf("received: %s; not found in if-else tree\n", vec_or_pos);
        Scene = move_object(Scene);
    };
    return Scene;
};

int main(scene prev_Scene){
    scene Scene;
    if(prev_Scene.obj_count!=0){
        char test_name[30] = "this is a test";
        Scene = __init_scene__(Scene, test_name);
    }else{
        Scene = prev_Scene;
    };
    while(1){
        char action[16] = "";
        printf(">> ");
        scanf("%15s", &action);                         
        if(strlen(action)>=15){
            printf("no such action found;\n\tplease try again!\n\tand because this program is stupid, \n\twe have decided to just exit it now!\n");
            break;
        };
        char *ops[32][16] = {"create"};
        *ops[1] = "move";
        *ops[2] = "move_vert";
        *ops[3] = "mv";
        *ops[4] = "append_vert";
        *ops[5] = "ap";
        *ops[6] = "help";
        *ops[7] = "exit";
        *ops[8] = "default";
        *ops[9] = "def";
        *ops[10] = "save";
        *ops[11] = "debug_object";
        *ops[12] = "debug_scene";
        *ops[13] = "edit_object";
        *ops[14] = "edit_scene";
        *ops[15] = "create_link";
        *ops[16] = "cl";
        *ops[17] = "create_face";
        *ops[18] = "cf";
        int action_index = GetIndex(action, ops);
        bool close_program = false;
        switch(action_index){                               //turn this into binary search (perchance through maps, which eliminates need for GetIndex);
            case -1:
                printf("not a valid option;\n");
                break;
            case 0:
                Scene = create_obj(Scene);
                break;
            case 1:
                move_object(Scene);
                break;
            case 2:
                printf("moving vertex...\n");
                break;
            case 3:
                printf("moving vertex...\n");
                break;
            case 4:
                printf("appending vert...\n");
                break;
            case 5:
                printf("appending vert...\n");
                break;
            case 6:
                printf("printing this menue...\n");
                printf("...\n");
                printf("...wait a second...\n");
                break;
            case 7:
                printf("bye!\n");
                close_program = true;
                break;
            case 8:
                printf("creating one of many def objects...\n");
                break;
            case 9:
                printf("creating one of many def objects...\n");
                break;
            case 10:
                printf("writing to 'Scene.ce'\n");
                break;
            case 11:
                for(int i=0;i<Scene.obj_count;i++){
                    debug_obj(Scene.objects[i]);
                }
                // store names in a list, get index, and then debug that
                break;
            case 12:
                debug_scn(Scene);
                break;
            case 13:

        };
        if(close_program==true){
            break;
        };

    };
    for(int object_count=0; object_count<Scene.obj_count; object_count++){
        free(Scene.objects[object_count].vertices);
    };
    return 0;
}
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


scene create_obj_loc(scene Scene){
    char Name[31];
    unsigned int vert_count;
    vert* verts = (vert*)malloc(sizeof(vert));
    char bin[31];


    printf("------------------------------------------------------------ Name of Object ------------------------------------------------------------\n@");
    fgets(bin, sizeof(Name), stdin);
    if (fgets(Name, sizeof(Name), stdin) != NULL) {
        size_t len = strlen(Name);
        if (len > 0 && Name[len - 1] == '\n') {
            Name[len - 1] = '\0'; 
        };
    } else {
        fprintf(stderr, "Error reading input.\n");
        return Scene; 
    };
    
    printf("------------------------------------------------------------ vert ammount ---------------------------------------------------------------\n#");
    scanf("%d", &vert_count);
    if(vert_count<0){
        fprintf(stderr, "Error interpreting vert amount (negative)");
        exit(1);
    }
    switch(vert_count){
        case 0:
            break;
        default:
            for(int i=0; i<vert_count; i++){
                vert new_vert;
                vert *tmp_verts = realloc(verts, i*sizeof(vert)+sizeof(vert));
                verts = tmp_verts;
                printf("------------------------------------------------------------ vert coords x ---------------------------------------------------------------\n##");
                scanf("%f", &new_vert.x);
                printf("\n");
                printf("------------------------------------------------------------ vert coords y ---------------------------------------------------------------\n##");
                scanf("%f", &new_vert.y);
                printf("\n");
                printf("------------------------------------------------------------ vert coords z ---------------------------------------------------------------\n##");
                scanf("%f", &new_vert.z);
                verts[i] = new_vert;
            }
    }
    obj new_obj = __init_object__(new_obj, Name);
    new_obj.vertices = verts;
    
    Scene = create_obj(Scene, Name, vert_count, verts);

    return Scene;
}

scene move_object_loc(scene Scene){
    char Name[31];
    unsigned int vert_count;
    vert* verts = (vert*)malloc(sizeof(vert));
    char bin[31];


    printf("------------------------------------------------------------ Name of Object ------------------------------------------------------------\n@");
    fgets(bin, sizeof(Name), stdin);
    if (fgets(Name, sizeof(Name), stdin) != NULL) {
        size_t len = strlen(Name);
        if (len > 0 && Name[len - 1] == '\n') {
            Name[len - 1] = '\0'; 
        };
    } else {
        fprintf(stderr, "Error reading input.\n");
        return Scene; 
    };

    char** scene_obj_names = (char**)malloc(sizeof(char*)*Scene.obj_count);
    for(int i=0;i<Scene.obj_count;i++){
        scene_obj_names[i] = (char*)malloc(sizeof(char)*sizeof(Scene.objects[i].name));
        strcpy(scene_obj_names[i], Scene.objects[i].name);
    };
    int Index = GetIndex(Name, scene_obj_names, Scene.obj_count);
    switch(Index){
        case -1:
            printf("could not find object '%s' in scene object array: (", Name);
            for(int i=0; i<Scene.obj_count; i++){
                printf("%s, ", scene_obj_names[i]);
            };
            printf(")");
            return scene;
        default:
            break;
    };

    
    return Scene;
}

int main(){
    char SceneName[30] = "Scene";
    scene Scene = __init_scene__(Scene, SceneName);
    while(1){
        char action[16] = "";
        printf(">> ");
        scanf("%15s", action);                         
        if(strlen(action)>=15){
            printf("no such action found;\n\tplease try again!\n\tand because this program is stupid, \n\twe have decided to just exit it now!\n");
            break;
        };

        int ops_num = 18;
        char** ops = (char**)malloc(sizeof(char*)*ops_num);
        ops[0] = (char*)malloc(sizeof(char)*5);
        ops[0] = "create";
        ops[1] = (char*)malloc(sizeof(char)*10);
        ops[1] = "move";
        ops[2] = (char*)malloc(sizeof(char)*3);
        ops[2] = "move_vert";
        ops[3] = (char*)malloc(sizeof(char)*12);
        ops[3] = "move_vert";
        ops[4] = (char*)malloc(sizeof(char)*3);
        ops[4] = "append_vert";
        ops[5] = (char*)malloc(sizeof(char)*5);
        ops[5] = "ap";
        ops[6] = (char*)malloc(sizeof(char)*5);
        ops[6] = "help";
        ops[7] = (char*)malloc(sizeof(char)*8);
        ops[7] = "exit";
        ops[8] = (char*)malloc(sizeof(char)*4);
        ops[8] = "default";
        ops[9] = (char*)malloc(sizeof(char)*5);
        ops[9] = "def";
        ops[10] = (char*)malloc(sizeof(char)*13);
        ops[10] = "save";
        ops[11] = (char*)malloc(sizeof(char)*12);
        ops[11] = "debug_object";
        ops[12] = (char*)malloc(sizeof(char)*12);
        ops[12] = "debug_scene";
        ops[13] = (char*)malloc(sizeof(char)*11);
        ops[13] = "edit_object";
        ops[14] = (char*)malloc(sizeof(char)*12);
        ops[14] = "edit_scene";
        ops[15] = (char*)malloc(sizeof(char)*3);
        ops[15] = "create_link";
        ops[16] = (char*)malloc(sizeof(char)*12);
        ops[16] = "cl";
        ops[17] = (char*)malloc(sizeof(char)*3);
        ops[17] = "create_face";
        ops[18] = (char*)malloc(sizeof(char)*7);
        ops[18] = "cf";

        int action_index = GetIndex(action, ops, ops_num);
        bool close_program = false;

        // Vars that need to be initialized BEFORE switch for some reason (prob bcaus' swtich is a function)
        char* search_name = (char*)malloc(sizeof(char)*31);
        char bin[sizeof(search_name)];

        switch(action_index){                               //turn this into binary search (perchance through maps, which eliminates need for GetIndex);
            case -1:
                printf("not a valid option;\n");
                break;
            case 0:
                Scene = create_obj_loc(Scene);
                break;
            case 1:
                move_object_loc(Scene);
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
                printf("yea I cannot be fucked doing this right now/I'm too bloody lazy to do said task. maybe I'll let the Transformes decide the fate of this monolog\n");
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
                printf("------------------------------------------------------------ Name of Object ------------------------------------------------------------\n@");
                fgets(bin, sizeof(bin), stdin);
                if (fgets(search_name, sizeof(search_name), stdin) != NULL) {
                    size_t len = strlen(search_name);
                    if (len > 0 && search_name[len - 1] == '\n') {
                        search_name[len - 1] = '\0'; 
                    };
                } else {
                    fprintf(stderr, "Error reading input.\n");
                    break; 
                };
                printf("main:       received: %s\n", search_name);

                char* msg = debug_obj(search_name, Scene);
                printf("%s\n", msg);
                break;
            case 12:
                debug_scn(Scene);
                break;
            case 13:
                printf("signal 13\n");
                break;
            case 14:
                printf("signal 14\n");
                break;
            case 15:
                printf("the case with no name");
                break;
            default:
                printf("NJI\n");
                break;
                


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
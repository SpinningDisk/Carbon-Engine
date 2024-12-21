#include "include/backend.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

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
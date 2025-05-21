#include "include/functions.h"
#include "include/engine.h"
#include "include/language.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*scene appendObjectToScene(scene Scene, object Object){
    Scene.objects = (object*)realloc(Scene.objects, sizeof(object)*(Scene.objectCount+2));
    printf("setting new object \"%s\" at array position %d\n", Object.name, Scene.objectCount);
    Scene.objects[Scene.objectCount] = Object;
    Scene.objectCount++;
    for(int i=0; i<Scene.objectCount; i++){
        printf("\tobject \"%s\" with ID %d at %d\n", Scene.objects[i].name, Scene.objects[i].id, i);
    }
    printf("\tname right before: %s\n", Scene.objects[Scene.objectCount-1].name);
    return Scene;
}*/



int main(){
    object hans = __init_object__("hans", 0);
    scene peter = __init_scene__("peter");
    peter = appendObjectToScene(hans, peter);
    printf("%s\n", peter.objects[0].name);
    return 0;
}

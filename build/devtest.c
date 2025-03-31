#include "include/functions.h"
#include "include/engine.h"
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
    //scene Main = __init_scene__("Main");
    scene Main = __init_scene__("a");
    printf("%s\n", Main.name);
	return 0;
}
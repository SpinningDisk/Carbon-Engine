#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    char* SName = "Main";
    char* OName = "Object1";
    char* OName2 = "Object2";
    vertex test1 = {0, 0, 0, '\0'};
    scene S1 = __init_scene__(SName);
	object HansHuberMueller = __init_object__(OName, 1);
	HansHuberMueller = appendVertexToObject(test1, HansHuberMueller);
    object Peter = __init_object__(OName2, 1);

    S1 = appendObjectToScene(HansHuberMueller, S1);
    HansHuberMueller = S1.objects[0];
    S1 = appendObjectToScene(Peter, S1);
    Peter = S1.objects[1];
    
    printf("Scne %s\n", S1.name);
    for(int i=0; i<S1.objectAmount; i++){
        printf("\tclaims to have object of name %s at ID %d\n", S1.objects[i].name, S1.objects[i].id);
    }
    printf("where %s has %d vertices of: \n", S1.objects[HansHuberMueller.id].name, S1.objects[HansHuberMueller.id].vertexAmount); 
    for(int i=0; i<S1.objects[HansHuberMueller.id].vertexAmount; i++){
        printf("\t%d: %f, %f, %f\n", i, S1.objects[HansHuberMueller.id].vertices[i][0], S1.objects[HansHuberMueller.id].vertices[i][1], S1.objects[HansHuberMueller.id].vertices[i][2]);
    }
    printf(" with intern name %s\n", HansHuberMueller.name);
	return 0;
}
// structs and their children (??? parameter??? values??? ...) will be written lowercase camelCase
// variables inside functions will be written in uppercase Snake_case
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* 
Objects shall have a Name, and ID (for reference in Scenes), a type (e.g: solid, camera, light, beziér curve, etc.); 
a list of vertices (or just one, in case of cam, light, ...), a center (for repositioning), and a something I forgot
*/

typedef struct{
    float x;
    float y;
    float z;
    unsigned int id;
}vertex;
typedef struct{
    vertex start;
    vertex end;
    unsigned int id;
}edge;
typedef struct{
    edge* edges;
    unsigned int id;
}face;
typedef struct{
    char* name;
    unsigned int type;
    int id;
    vertex* vertices;
    edge* edges;
    face* faces;
    vertex center;
    unsigned int vertexCount;
    unsigned int edgeCount;
    unsigned int faceCount;
}object;
typedef struct{
    char* name;
    unsigned int id;
    unsigned int objectCount;
    char** objectNames;
    object* objects;
}scene;
typedef struct{
    char** sceneNames;
    scene* scenes;
    unsigned int sceneCount;
}project;


// init functions
object __init_object__(scene Scene, unsigned int Type, char* Name){
    object Object;
    Object.name = Name;
    Object.id = Scene.objectCount+1;
    Object.type = Type;
    Object.vertices = (vertex*)malloc(1);
    Object.edges = (edge*)malloc(1);
    Object.faces = (face*)malloc(1);
    vertex Tmp_Center;
    Tmp_Center.x = 0;
    Tmp_Center.y = 0;
    Tmp_Center.z = 0;
    Tmp_Center.id = 0;
    Object.center = Tmp_Center;
    Object.vertexCount = 0;
    Object.edgeCount = 0;
    Object.faceCount = 0;
    return Object;
}

scene __init_scene__(char* Name){
    scene Scene;
    Scene.name = Name;
    Scene.id = 1;                                           //change
    Scene.objectCount = 0;
    Scene.objectNames = (char**)malloc(0);
    Scene.objects = (object*)malloc(0);
    return Scene;
}

project __init_project__(project Project){
    Project.sceneNames = (char**)malloc(sizeof(char*));
    Project.scenes = (scene*)malloc(sizeof(scene));
    Project.sceneCount = 0;
    return Project;
}

// append functions
object appendVertexToObject(object Object, vertex Vertex){
    return Object;
}

scene appendObjectToScene(scene Scene, object Object){
    /*Main.objects = (object*)realloc(Main.objects, sizeof(object)*(Main.objectCount+1));
	Main.objects[Main.objectCount] = O1;
	Main.objectCount++;*/
    printf("    object to append: %s\n", Object.name);
    Scene.objects = (object*)realloc(Scene.objects, sizeof(object)*(Scene.objectCount+1));
	Scene.objects[Scene.objectCount] = Object;
    printf("    internally stored as %s\n", Scene.objects[Scene.objectCount].name);
	Scene.objectCount++;
    Scene.objects = (object*)realloc(Scene.objects, sizeof(object)*(Scene.objectCount+2));
    printf("setting new object \"%s\" at array position %d\n", Object.name, Scene.objectCount);
    Scene.objects[Scene.objectCount] = Object;
    Scene.objectCount++;
    for(unsigned int i=0; i<Scene.objectCount; i++){
        printf("\tobject \"%s\" with ID %d at %d\n", Scene.objects[i].name, Scene.objects[i].id, i);
    }
    printf("\tname right before: %s\n", Scene.objects[Scene.objectCount-1].name);
    return Scene;
}
// standart shapes


// clear functions
object* clearObjects(object* Objects, unsigned int Object_Amount){
    for(unsigned int i=0; i<Object_Amount; i++){
        Objects[i].name = (char*)malloc(0);
        Objects[i].type = 0;
        Objects[i].id = 0;
        Objects[i].vertices = (vertex*)malloc(0);
        Objects[i].edges = (edge*)malloc(0);
        Objects[i].faces = (face*)malloc(0);
        vertex Center;
        Center.x = 0;
        Center.y = 0;
        Center.z = 0;
        Center.id = 0;
        Objects[i].center = Center;
        Objects[i].vertexCount = 0;
        Objects[i].edgeCount = 0;
        Objects[i].faceCount = 0;
    }
    return Objects;
}

scene* clearScenes(scene* Scenes, unsigned int Scene_Amount){
    for(unsigned int i=0; i<Scene_Amount; i++){
        Scenes[i].name = (char*)malloc(0);
        Scenes[i].id = 0;
        Scenes[i].objectCount = 0;
        Scenes[i].objectNames = (char**)malloc(sizeof(char*));
        Scenes[i].objectNames[0] = (char*)malloc(0);
        clearObjects(Scenes[i].objects, Scenes[i].objectCount);
    }
    return Scenes;
}

project* clearProjects(project* Projects){
    // nji
    
    return Projects;
}
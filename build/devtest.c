#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	project Hans = __init_project__();
	char* S1_Name = "hello,";
	char* S2_Name = "Hello,";
	char* O1_Name = "world!";
	char* O2_Name = "World!";
	char* O3_Name = " world!";
	char* O4_Name = " World!";
	scene Main = __init_scene__(Hans, S1_Name);
	scene Main1 = __init_scene__(Hans, S2_Name);

	object O_Test1 = __init_object__(Main, 0, O1_Name);
	Main = appendObjectsToScene(Main, &O_Test1, 1);
	object O_Test2 = __init_object__(Main, 0, O2_Name);
	Main = appendObjectsToScene(Main, &O_Test2, 1);
	Hans = appendScenesToProject(Hans, &Main, 1);
	object O_Test3 = __init_object__(Main1, 0, O3_Name);	
	Main1 = appendObjectsToScene(Main1, &O_Test3, 1);
	object O_Test4 = __init_object__(Main1, 0, O4_Name);
	Main1 = appendObjectsToScene(Main1, &O_Test4, 1);
	Hans = appendScenesToProject(Hans, &Main1, 1);


	scene* Scn_P = (scene*)malloc(sizeof(scene)*2);
	Scn_P[0] = Main;
	Scn_P[1] = Main1;

	Hans = appendScenesToProject(Hans, Scn_P, 2);

	printf("log starts here!: \n");
	printf("pick: %s\n", Main.objects[1].name);
	return 0;
	for(unsigned int k=0; k<Hans.sceneCount; k++){
		printf("name: %s\n", Hans.scenes[k].name);
		for(unsigned int i=0; i<Hans.scenes[k].objectCount; i++){
			printf("	name: %s\n", Hans.scenes[k].objects[i].name);
			for(unsigned int j=0; j<Main.objects[i].vertexCount; i++){
				printf("		vertex %d: %f, %f, %f\n", j, Hans.scenes[k].objects[i].vertices[j].x, Hans.scenes[k].objects[i].vertices[j].y, Hans.scenes[k].objects[i].vertices[j].z);
			}
		}
	}

	return 0;
}
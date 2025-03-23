#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	char* SName = "MainS";
	char* OName1 = "TestO1";
	char* OName2 = "TestO2";
	char* OName3 = "TestO3";
	char* OName4 = "TestO4";
	scene Main = __init_scene__(SName);
	object O1 = __init_object__(Main, 1, OName1);
	Main = appendObjectToScene(Main, O1);
	object O2 = __init_object__(Main, 1, OName2);
	Main = appendObjectToScene(Main, O2);
	object O3 = __init_object__(Main, 1, OName3);
	Main = appendObjectToScene(Main, O3);
	object O4 = __init_object__(Main, 1, OName4);
	Main = appendObjectToScene(Main, O4);
	
	for(unsigned int i=0; i<Main.objectCount; i++){
		printf("object %d", i);
		printf(" named: %s", Main.objects[i].name);
		printf(" of length %d\n", strlen(Main.objects[i].name));
	}

	/*Hans = appendScenesToProject(Hans, &Main, 1);
	object O_Test3 = __init_object__(Main1, 0, O3_Name);	
	Main1 = appendObjectsToScene(Main1, &O_Test3, 1);
	printf("Scene db at line 26:	name1: 	%s; 	name2: //\n", Main1.objects[0].name);
	object O_Test4 = __init_object__(Main1, 0, O4_Name);
	Main1 = appendObjectsToScene(Main1, &O_Test4, 1);
	printf("Scene db at line 29:	name1: 	%s; 	name2: //\n", Main.objects[0].name, Main1.objects[1].name);
	Hans = appendScenesToProject(Hans, &Main1, 1);


	scene* Scn_P = (scene*)malloc(sizeof(scene)*3);
	Scn_P[0] = Main;
	Scn_P[1] = Main1;

	Hans = appendScenesToProject(Hans, Scn_P, 2);

	printf("log starts here!: \n");
	printf("pick: %s\n", Main1.name);
	return 0;
	for(unsigned int k=0; k<Hans.sceneCount; k++){
		printf("name: %s\n", Hans.scenes[k].name);
		for(unsigned int i=0; i<Hans.scenes[k].objectCount; i++){
			printf("	name: %s\n", Hans.scenes[k].objects[i].name);
			for(unsigned int j=0; j<Main.objects[i].vertexCount; i++){
				printf("		vertex %d: %f, %f, %f\n", j, Hans.scenes[k].objects[i].vertices[j].x, Hans.scenes[k].objects[i].vertices[j].y, Hans.scenes[k].objects[i].vertices[j].z);
			}
		}
	}*/

	return 0;
}
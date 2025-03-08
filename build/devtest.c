#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	project Hans = __init_project__();
	char* S_Name = (char*)malloc(sizeof(char)*5);
	S_Name = "hello";
	scene Scene = __init_scene__(Hans, S_Name);
	/*
	printf("scene after: \n");
	printf("name: %s\n", Main.name);
	for(unsigned int i=0; i<=Main.objectCount; i++){
		printf("	name: %s\n", Main.objects[i].name);
		for(unsigned int j=0; j<=Main.objects[i].vertexCount; i++){
			printf("		vertex %d: %f, %f, %f\n", j, Main.objects[i].vertices[j].x, Main.objects[i].vertices[j].y, Main.objects[i].vertices[j].z);
		}
	}*/

	return 0;
}
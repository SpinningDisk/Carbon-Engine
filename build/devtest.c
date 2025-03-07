#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	scene s1;
	object obj1;
	char* Name1 = (char*)malloc(sizeof(char)*5);
	Name1 = "test";
	obj1.name = Name1;
	obj1.type = 0;
	obj1.id = 0;
	obj1.vertices = (vertex*)malloc(1+sizeof(vertex));
	vertex vert1;
	vert1.x = 0;
	vert1.y = 0;
	vert1.z = 0;
	obj1.vertices[0] = vert1;
	obj1.edges = (edge*)malloc(1);
	obj1.faces = (face*)malloc(1);
	obj1.center = vert1;
	obj1.vertexCount = 1;
	
	printf("obj test: \n");
	printf("	name: %s\n", obj1.name);
	printf("	vertex: %f, %f, %f\n", obj1.vertices[0].x, obj1.vertices[0].y, obj1.vertices[0].z);
	s1.objects = (object*)malloc(1+sizeof(object));
	s1.objects[0] = obj1;
	printf("scn test: \n");
	printf("	name: %s\n", s1.objects[0].name);
	printf("	vertex: %f, %f, %f\n", s1.objects[0].vertices[0].x, s1.objects[0].vertices[0].y, s1.objects[0].vertices[0].z);

	int test = retOne();
	//clearObjects(s1.objects);

	return 0;
}
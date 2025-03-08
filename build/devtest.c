#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	project P = __init_project__();
	char* Name = (char*)malloc(sizeof(char)*6);
	Name = "hello";
	scene Main = __init_scene__(P, Name);
	char* O_Name = (char*)malloc(sizeof(char)*5);
	O_Name = "world";
	object OTest = __init_object__(Main, 0, Name);



	return 0;
}
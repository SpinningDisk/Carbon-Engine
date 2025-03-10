#include "include/functions.h"
#include "include/engine.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	project Project = __init_project__();
	char* SName = "Hello, ";
	char* OName = "world!";
	scene Main = __init_scene__(Project, SName);
	return 0;
}
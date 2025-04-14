%{
#include <stdio.h>
#include <regex.h>
#include "../include/functions.h"
#include "../include/language.h"
#include "../include/engine.h"
project Project;
CESframe Program;
unsigned int Scene_Index;
%}

%%
.
\n {printf(">>");}

exit\(\) {
    printf("\n\tbye!\n");
    return 0;
}


%%

int yywrap(){}
int main(){
#include "../include/functions.h"
#include "../include/engine.h"
#include "../include/language.h"

Scene_Index = 0;
scene Scene  = __init_scene__("Main");
Project = realloc(Project, sizeof(scene)+1);
Project[0] = Scene;

Program = __init_frame__();

//program stuff


printf(">>");
yylex();
return 0;
}
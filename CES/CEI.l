%{
#include <stdio.h>
#include <regex.h>
%}

%%
.
\n {printf(">>");}

exit {printf("\n\tbye!\n");
return 0;}

create\([a-zA-Z_]+,""?[0-9]+\)  {
    char* name = yytext;
    name = memmove(name, name+7, strlen(name));
    name[strlen(name)-1] = '\0';
    printf("created object %s!\n" ,name);
}

%%

int yywrap(){}
int main(){
#include "../include/engine.h"

char* SName = "Main";
scene Main = __init_scene__(SName);             // link/compile with library
printf(">>");
yylex();
return 0;
}
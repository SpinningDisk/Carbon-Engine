%{
#include "../include/engine.h"
%}

%%
create\([a-zA-Z0-9]+\)  {char* name = (char*)malloc(1);
        if(strlen(yytext)>38){
            fprintf(stderr, "Name too long;");
            free(name);
            break;
        };
        for(int i=7; i<strlen(yytext)-1; i++){
            name = realloc(name, sizeof(name)+sizeof(char));
            name[i-7] = yytext[i];
        }
        printf("create: received %s", name);
        free(name);
        }
.
\n  {printf(">>");}
exit    {printf("           bye!\n");
        return 0;}
%%

int yywrap(){}
int main(){
printf(">>");
yylex();

return 0;
}
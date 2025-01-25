%{
#include "../include/engine.h"
int sstrlen = 32;
char* s_name = "System";
scene Scene;
%}

%%
create\([a-zA-Z0-9]+\)  {char* name = (char*)malloc(1);
        if(strlen(yytext)>sstrlen+8){
            fprintf(stderr, "Name too long;");
            free(name);
            break;
        };
        for(int i=7; i<strlen(yytext)-1; i++){
            name = realloc(name, sizeof(name)+sizeof(char));
            name[i-7] = yytext[i];
        }
        printf("create: received %s\n", name);
        obj tmp = __init_object__(tmp, name);
        Scene = append_obj_to_scene_by_object(Scene, tmp);
        }
info\(object,[a-zA-Z0-9]+\)  {char* name = (char*)malloc(1);
        if(strlen(yytext)>sstrlen+15){
            fprintf(stderr, "Name too long;");
            free(name);
            break;
        };
        for(int i=12; i<strlen(yytext)-1; i++){
            name = realloc(name, sizeof(name)+sizeof(char));
            name[i-12] = yytext[i];
        }
        printf("info: received %s\n", name);
        char* msg = debug_obj(name, Scene);
        printf("%s\n", msg);
        free(name);
        free(msg);
        }
.
\n  {printf(">>");}
exit    {printf("           bye!\n");
        return 0;}
%%

int yywrap(){}
int main(){
Scene = __init_scene__(Scene, s_name);
printf(">>");
yylex();

return 0;
}
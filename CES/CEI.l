%{
#include <stdio.h>
#include <regex.h>
#include "../include/functions.h"
//#include "../include/language.h"
#include "../include/engine.h"
scene Scene;
%}

%%
.
\n {printf(">>");}

exit {
    printf("\n\tbye!\n");
    return 0;}


create\([a-zA-Z_]+,[[:space:]]?[0-9]+\)  {
    char* Name = yytext;
    int type = 0;
    Name = memmove(Name, Name+7, strlen(Name));
    Name[strlen(Name)-1] = '\0';
    
    short exit = 0;
    for(int i=0; i<strlen(Name); i++){
        switch((int)Name[i]){
            case 44:
                Name[i] = '\0';
               for(int j=i+1; j<strlen(Name); j++){
                    type += ((int)Name[j]-48) * power(10, strlen(Name)-j-1); // char to int, then multiply by current position (left to right) -> 1234
                    /*                                                                            1 * 10**3 + 2*10**2...*/
                }
                i = strlen(Name);
                break;
            default:
                break;
        }
    }
    printf("creating object %s\n", Name);
    object Object = __init_object__(Name, type);
    Scene = appendObjectToScene(Object, Scene);

}

[[:alpha:]]+[[:space:]]=[[:space:]]\"*\"   {//"
    char* Variable_Name = yytext;
    
}

%%

int yywrap(){}
int main(){
#include "../include/functions.h"
#include "../include/engine.h"
//#include "../include/language.h"
Scene  = __init_scene__("Main");

printf(">>");
yylex();
return 0;
}
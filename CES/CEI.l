%{
#include <stdio.h>
#include <regex.h>
#include "../include/functions.h"
//#include "../include/language.h"
#include "../include/engine.h"
project Project;
unsigned int Scene_Index;
%}

%%
.
\n {printf(">>");}

exit {
    printf("\n\tbye!\n");
    return 0;}


create\([a-zA-Z_]+[" "]?[0-9]+\)  {
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
                    //                                                                            1 * 10**3 + 2*10**2...
                }
                i = strlen(Name);
                break;
            default:
                break;
        }
    }
    object Object = __init_object__(Name, type);
    Project[Scene_Index] = appendObjectToScene(Object, Project[Scene_Index]);
}
[\t]*[a-zA-Z]+[" "]?=[" "]?[-]?[0-9]+    {
    char* Var_Name;
    char* Value_As_Char;
    int* Var_Value;
    for(int i=0; i<strlen(yytext); i++){
        switch((int)yytext[i]){
            case 32: //space
                for(int j=i; j<strlen(yytext)-1;j++){
                    yytext[j] = yytext[j+1];
                }
                yytext[strlen(yytext)-1] = '\0';
                i--;
                break;
            case 61: //equals sign
                Var_Name = realloc(Var_Name, sizeof(char)*i);           //copy everything infront of equals
                memcpy(Var_Name, &yytext[0], i*sizeof(char));
                printf("got variable name %s\n", Var_Name);

                for(int j=i; j<strlen(yytext)-1;j++){
                    switch(yytext[j]){
                        case 32:
                            for(int k=j; k<strlen(yytext)-1;k++){
                                yytext[k] = yytext[k+1];
                            }
                            yytext[strlen(yytext)-1] = '\0';
                            j--;
                    }
                }
                Value_As_Char = realloc(Value_As_Char, sizeof(char)*(strlen(yytext)-i-1));      //copy everything behind equals
                memcpy(Value_As_Char, &yytext[i+1], (strlen(yytext)-i-1)*sizeof(char));
                printf("got variable value %s\n", Value_As_Char);

                break;
            default:
                printf("%c = %d\n", yytext[i], yytext[i]);
                break;
        }
    }
}
%%

int yywrap(){}
int main(){
#include "../include/functions.h"
#include "../include/engine.h"
//#include "../include/language.h"

Scene_Index = 0;
scene Scene  = __init_scene__("Main");
Project = realloc(Project, sizeof(scene)+1);
Project[0] = Scene;

//program stuff


printf(">>");
yylex();
return 0;
}
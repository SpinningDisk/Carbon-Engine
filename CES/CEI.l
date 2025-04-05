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
    return 0;
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
[\t]*[a-zA-Z]+[" "]?=[" "]?[-]?\"[^\"]+\"    {
    printf("hit string var!\n");
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
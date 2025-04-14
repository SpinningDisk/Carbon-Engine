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


create\([a-zA-Z_]+[" "]?[0-9]+\)  { 
    return 0;
}
[" "]*[a-zA-Z]+[" "]?=[" "]?[-]?[0-9]+    {
    char* Var_Name = (char*)malloc(sizeof(char));
    char* Value_As_Char = (char*)malloc(sizeof(char));
    int Var_Value = 1;
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
                char* Tmp = realloc(Var_Name, sizeof(char)*i);           //copy everything infront of equals
                Var_Name = Tmp;
                memcpy(Var_Name, &yytext[0], i*sizeof(char));

                for(int j=i; j<strlen(yytext)-1;j++){
                    switch(yytext[j]){
                        case 32:        // remove space
                            for(int k=j; k<strlen(yytext)-1;k++){
                                yytext[k] = yytext[k+1];
                            }
                            yytext[strlen(yytext)-1] = '\0';
                            j--;
                            break;
                        case 45:        // make negativ
                            Var_Value = -1;
                            break;
                    }
                }
                Value_As_Char = realloc(Value_As_Char, sizeof(char)*(strlen(yytext)-i-1));      //copy everything behind equals
                memcpy(Value_As_Char, &yytext[i+1], (strlen(yytext)-i-1)*sizeof(char));
                int Num_len = strlen(yytext)-i-1;          // numbers have multiple digits, so we need to make sure we only take the existing digits
                int tmp = 0;
                switch(Var_Value){
                    case -1:
                        for(int j=1; j<Num_len; j++){
                            tmp = tmp-((Value_As_Char[j]-48)*(power(10, (10, Num_len-j-1))));
                        }
                        break;
                    case 1:
                        for(int j=0; j<Num_len; j++){
                            tmp = tmp+((Value_As_Char[j]-48)*(power(10, (10, Num_len-j-1))));
                        }
                        break;
                }
                Var_Value = tmp;

                break;
            default:
                break;
        }       // Name stored in Var_Name; Value stored in Var_Value
    }
    switch(Program.variableAmount){
        case 0:
            break;
        default:
            break;
    }
        
    CESvariable New_Var;
    New_Var.name = Var_Name;
    New_Var.type = CEType_int;
    int* Var_Value_Ptr = (int*)malloc(sizeof(int));
    Var_Value_Ptr[0] = Var_Value;
    New_Var.data = Var_Value_Ptr;
    Program = storeVariable(Program, New_Var);
    
}

print\([a-zA-Z_]*\)  {
    char* Name = (char*)malloc((strlen(yytext)-7)*sizeof(char));
    memcpy(Name, &yytext[6], (strlen(yytext)-7)*sizeof(char));
    int Var_Index = return_Index(Name, Program.variableNames, Program.variableAmount);
    switch(Var_Index){
        case -1:
            fprintf(stderr, "No such variable: \"%s\"\n", Name);
            break;
        default:
        
            printf("%d\n", *(int*)Program.variables[Var_Index].data);
            break;
    }
}
log_vars    {printf("start\n");
    for(int i=0; i<Program.variableAmount;i++){
        printf("var at index %d:\n", i);
        printf("    in list as %s\n", Program.variableNames[i]);
        printf("    in Var as %s\n", Program.variables[i].name);
        printf("    stores value %d\n", *(int*)Program.variables[i].data);
    }
}
for\([a-zA-Z_\(\),]*\)\{   {
    printf("hit loop\n");
}


[" "]*([a-zA-Z_][a-zA-Z0-9_]*)[" "]?=[" "]?([a-zA-Z0-9_()+\-*/." "]+) {
    printf("I'm not going to implement that rn...\n");
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
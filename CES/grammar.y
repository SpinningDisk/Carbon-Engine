%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/functions.h"
#include "../include/language.h"
#include "../include/engine.h"
// yylex; yyerror
int yylex(void);
int yyerror(char* s);
extern CEVM VM;

void nameError(char* Name){
    fprintf(stderr, "IdentifierError: %s not defined in current Scope", Name);
}
%}
    
%union {
    int num;
    char* str;
    int null;
    int type;
}
    
%token <num> NUMBER
%token <str> PLUS MINUS MULTIPLY DIVIDE EQ IDENT PARENT_L PARENT_R STRING EXIT WHILE
%token <type> lTYPE

%type <null> assignment
%type <str> value
%type <num> condition
%type <num> expression
%type <num> term
%type <num> factor
%type <str> error


%%
input:
    | input line
    | EXIT      {printf("bye!\n"); return 0;}
    | error     {printf("\n"); return 0;}
;

line:
    expression '\n' {printf("= %d\n>>", $1);}
    | assignment '\n' {printf(">>");}
    | IDENT '\n'    {
        int var_Index = return_Index($1, VM.variableNames, VM.variableAmount);
        switch(var_Index){
            case -1:
                nameError($1);
                YYERROR;
                break;
        }
        switch(VM.variables[var_Index].type){
            case TYPE_INT:
                printf("%d\n>>", (int)VM.variables[var_Index].data);
                break;
            case TYPE_STR:
                printf("%s\n>>", (char*)VM.variables[var_Index].data);
                break;
            default:
                fprintf(stderr, "NJI\n");
        }
    }
    | loop      {printf("test\n>>");}
;

assignment:
    lTYPE IDENT EQ value     {
        // if anyone figures out why expression and EQ is part of IDENT, i'd be most greatfull
        ceVariable new_Variable;
        char* Name = (char*)malloc(sizeof(char)*(strlen($2)-strlen($2)));
        Name = $2;
        for(int i=0; i<strlen($2); i++){
            switch((int)Name[i]){
                case 61:            // equals sign
                    Name[i] = '\0';
                    break;
                case 32:            // space
                    memcpy(Name, &Name[0], strlen(Name)-1);
                    break;
                default:
                    break;
            }                
        }
        new_Variable.name = Name;
        new_Variable.type = (ceTypes)$1;
        switch((ceTypes)$1){
            case TYPE_INT:
                new_Variable.data = (void*)$4;
                new_Variable.size = sizeof(int);
                VM = storeGlobal(VM, new_Variable);
                break;
            case TYPE_STR:
                new_Variable.data = (void*)$4;
                new_Variable.size = sizeof(char*);
                VM = storeGlobal(VM, new_Variable);
                break;
        }

    }
;

value:
    expression
    | STRING       {
        char* String = strdup($1);
        memmove (String, String+1, strlen(String+1)+1);                        // removes the first element (Double quotes)
        String[strlen(String)-1]='\0';
        $$ = String;    
    }
;

loop:
    | WHILE PARENT_L condition PARENT_R     {printf("");}
;

condition:
    expression '<' expression   {
        if($1<$3){
            printf("True\n");
            $$ = 1;
        }else{
            printf("False\n");
            $$ = 0;
        }
    }
    | expression '>' expression{
        if($1>$3){
            printf("True");
            $$ = 1;
        }else{
            printf("False");
            $$ = 0;
        }
    }
    | expression '=''=' expression{
        if($1==$4){
            printf("True");
            $$ = 1;
        }else{
            printf("False");
            $$ = 0;
        }
    }

expression:
    expression PLUS expression {$$=$1+$3;}
    | expression MINUS expression {$$ = $1 - $3; }
    | term  { $$ = $1; }
;

term:
    term MULTIPLY term { $$ = $1 * $3; }
    | term DIVIDE term {
        if($3==0){
            fprintf(stderr, "Zero Divison Error!\n");
            $$ = 0;
        }else{
            $$ = $1/$3;
        }
    }
    | factor
;
factor:
    NUMBER              { 

        bytecode New_Code = createBytecode(PUSH, 1, (void**)$1, BC_TYPE_INT);
    }
    | IDENT             { 
        int var_Index = return_Index($1, VM.variableNames, VM.variableAmount);
        if(var_Index<0){
            char* newline_Stripped_Name = $1;
            newline_Stripped_Name[strlen(newline_Stripped_Name)-1] = '\0';
            fprintf(stderr, "NameError: \"%s\" not found in current scope\n", newline_Stripped_Name);
            $$ = 0;
        }else if(VM.variables[var_Index].type==TYPE_INT){
            $$ = (int)VM.variables[var_Index].data;
        }else{
            fprintf(stderr, "TypeError: cannot perform arithmetics with object of type %s\n", ceTypesReadable(VM.variables[var_Index].type));
        }
    }
    | PARENT_L expression PARENT_R  { $$ = $2; }
;    

%%
  
int yyerror(char *s) {
        fprintf(stderr, "Error: %s\n", s);

        return 1;
}
    
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
char* scope = "Global";
void nameError(char* Name){
    fprintf(stderr, "\e[1;31mIdentifierError: %s not defined in current Scope: \e[1;36m%s\e[0;37m", Name, scope);
}
void zeroDivisionError(){
    fprintf(stderr, "\e[1;31mZeroDivisionErro: Cannot divide through Zero\e[0;37m\n");
}
%}
    
%union {
    int num;
    char* str;
    int null;
    int type;
}
    
%token <num> NUMBER
%token <str> PLUS MINUS MULTIPLY DIVIDE EQ IDENT PARENT_L PARENT_R STRING EXIT WHILE printstack printqueue emptystack emptyqueue
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
    | input EXIT      {printf("bye!\n"); return 0;}
    | input printstack    {for(int i=0; i<VM.stack.len; i++){
        printf("stack elm %d = %d = %s\n", i, (int)VM.stack.data[i], (char*)VM.stack.data[i]);
    }}
    | input printqueue  {for(int i=0; i<VM.queue.len; i++){
        printf("queue elm %d = %d\n", i, (int)VM.queue.data[i]);
    }}
    | input emptystack  {
        VM.stack.data = (void**)malloc(sizeof(void*));
        VM.stack.len = 0;
    }
    | input emptyqueue  {
        VM.queue.data = (void**)malloc(sizeof(void*));
        VM.queue.len = 0;
    }
    | error     {printf("\n\e[1;34m>>\e[0;37m"); yyerrok;}
;

line:
    expression '\n' {printf("%d\n\e[1;34m>>\e[0;37m", $1);}
    | assignment '\n' {printf("\e[1;34m>>\e[0;37m");}
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
                printf("%d\n\e[1;34m>>\e[0;37m", (int)VM.variables[var_Index].data);
                break;
            case TYPE_STR:
                printf("%s\n\e[1;34m>>\e[0;37m", (char*)VM.variables[var_Index].data);
                break;
            default:
                fprintf(stderr, "NJI\n");
        }
    }
    | loop '\n'      {printf("\n\e[1;34m>>\e[0;37m");}
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
    | WHILE PARENT_L condition PARENT_R '{'     {printf("");}
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
    expression PLUS expression {$$=$1+$3; 
        instruction Opcode = ADD;
        switch(VM.stack.len){
            case 0:
                VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
                printf("stack empty\n");
                break;
            default:
            printf("got opcode of higher priority; poping stack\n");    
            if(stackPeek(&VM.stack)>Opcode+1){  // +1 here so we get from sub, which is MUL and DIV
                    for(int i=0;i<VM.stack.len-1;i++){
                        void* NextOpcode = stackPop(&VM.stack);
                        printf("received code: %d; ", (int)NextOpcode);
                        VM.queue = stackPush_Enqueue(VM.queue, NextOpcode);
                    }
                }
                VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
        }
    }
        
    | expression MINUS expression {$$ = $1 - $3;
        instruction Opcode = SUB;
        switch(VM.stack.len){
            case 0:
                VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
                printf("stack empty\n");
                break;
            default:
                if(stackPeek(&VM.stack)>Opcode){
                    printf("got opcode of higher priority; poping stack\n");
                    for(int i=0;i<VM.stack.len-1;i++){
                        void* NextOpcode = stackPop(&VM.stack);
                        VM.queue = stackPush_Enqueue(VM.queue, NextOpcode);
                    }
                }
                VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
        }}
    | term  { $$ = $1; }
;

term:
    term MULTIPLY term { $$ = $1 * $3;
        instruction Opcode = MUL;
        VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
        printf("added mul\n");}
    | term DIVIDE term {
        if($3==0){
            zeroDivisionError();
            $$ = 0;
        }else{
            instruction Opcode = DIV;
            VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
            $$ = $1/$3;
        }
    }
    | factor
;
factor:
    NUMBER              { 
        // store in stack so that we can apply shanting yard later in input;
        void* NumberPtr = (void*)$1;
        VM.queue = stackPush_Enqueue(VM.queue, NumberPtr);        
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
    | PARENT_L expression PARENT_R  {$$ = $2;}
; 
    // printf("got parrent R\n");
    // char* Opcode = ")";
    // int Found_Matching_Parent = 0;
    // int counter = 0;
    // return PARENT_R;
    // void* Opperator = stackPop(&VM.stack);
    // while(1){
    //     printf("got %s, not at len of %d\n", (char*)Opperator, VM.queue.len);
    //     VM.queue = stackPush_Enqueue(VM.queue, Opperator);
    //     if(counter==VM.stack.len){
    //         Found_Matching_Parent = 1;
    //     }
    // }
    // VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
    // return PARENT_R;
%%
  
int yyerror(char *s) {
        fprintf(stderr, "Error: %s\n", s);

        return 1;
}
    
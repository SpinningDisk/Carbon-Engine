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
    char* arrStr[];
    int null;
    int type;
    short short noReturn;
}
    
%token <num> NUMBER
%token <str> OPPER EQ IDENT PARENT_L PARENT_R STRING EXIT WHILE printstack printqueue emptystack emptyqueue
%token <type> lTYPE
%token <noReturn> SYSTEM

%type <arrStr> system_setting_args
%type <null> assignment
%type <str> value
%type <num> condition
%type <num> expression
%type <num> open_expression
%type <num> term
%type <num> factor
%type <str> error
%type <noReturn> system_setting


%%
input:
    | input line
    | input EXIT      {printf("bye!\n"); return 0;}
    | input printstack    {
        printf("got len %d\n", VM.stacks[0].len);
        for(int i=0; i<VM.stacks[0].len; i++){
            printf("stack elm %d = %d = %s\n", i, (int)VM.stacks[0].data[i], instructionsReadable((instruction)VM.stacks[0].data[i]));
        }
    }
    | input printqueue  {for(int i=0; i<VM.queues[0].len; i++){
        printf("queue elm %d = %d\n", i, (int)VM.queues[0].data[i]);
    }}
    | input emptystack  {
        VM.stacks[0].data = (void**)malloc(sizeof(void*));
        VM.stacks[0].len = 0;
    }
    | input emptyqueue  {
        VM.queues[0].data = (void**)malloc(sizeof(void*));
        VM.queues[0].len = 0;
    }
    | error     {printf("\n\e[1;34m>>\e[0;37m");}
;

line:
    expression '\n' {printf("\n\e[1;34m>>\e[0;37m");
        printf("\nline: jmpd\n");
        while(VM.stacks[0].len>0){
            printf("line: moved %s\n", instructionsReadable((instruction)stackPeek(&VM.stacks[0])));
            VM.queues[0] = stackPush_Enqueue(VM.queues[0], stackPop(&VM.stacks[0]));
        }
    }
    | assignment '\n' {printf("\e[1;34m>>\e[0;37m");}
    | system_setting '\n' {printf("\e[1;34m>>\e[0;37m");}
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

system_setting:
    SYSTEM system_setting_args      {
        printf("bison got system settings!\n");
    }
;
system_setting_args:
    system_setting_args';'system_setting_args{
        printf("got sub-system\n");
    }
    | IDENT EQ IDENT       {
        printf("got id %s to id %s\n", $1, $3);
        $$[0] = $1;
        $$[1] = $3;
    }
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
;
// memo to me: I think I just understood why we need to shunting yard/RP: 
// pop two elements of the stack (numbers/idents which can be retrieved)
// pop next element (Operator), and apply opperator to freshly popped elms, and push res to stack
// now we should have new two elms
// no: need to loop until opperator, and take however many elms opperator requires and apply that
// to the last n popped elms, then push; now rince and repeate above

// todo: get term and thus factor into expression

expression:
    expression OPPER expression {
        instruction Opperator;
        if($2[0]=='+'){
            Opperator = ADD;
        }else if($2[0]=='-'){
            Opperator = SUB;
        }else if($2[0]=='*'){
            Opperator = MUL;
        }else if($2[0]=='/'){
            Opperator = DIV;
        }
        switch(VM.stacks[0].len){
            case 0:
                break;
            default:
                switch(Opperator){
                    case ADD:
                        if(stackPeek(&VM.stacks[0])>Opperator+1){     // +1 so we start at sub and go up (mul, div, etc.)
                            printf("open: got higher priority (%s > %s)\n", instructionsReadable((instruction)stackPeek(&VM.stacks[0])), instructionsReadable(Opperator));
                            for(int i=0; i<VM.stacks[0].len; i++){
                                void* Top_Opperator = stackPop(&VM.stacks[0]);
                                printf("\tgot %s\n", instructionsReadable((instruction)Top_Opperator));
                                VM.queues[0] = stackPush_Enqueue(VM.queues[0], Top_Opperator);
                            }
                        }
                }
                printf("open: adding %s\n", instructionsReadable(Opperator));

        }
        // bytecode New;
        // New.opcode = Opperator;
        // New.operantAmount = 2;
        // New.
        // VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opperator);
    }
    | PARENT_L                  {
        printf("got left parent\n");
    }
    | PARENT_R                  {
        printf("got right parent\n");
    }
    | factor                    {
    }
;
/*
expression:
    expression PLUS expression {$$=$1+$3; 
        instruction Opcode = ADD;
        printf("ADD operator start: \n");
        switch(VM.stacks[0].len){
            case 0:
                VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
                printf("stack empty\n");
                break;
            default:
            if(stackPeek(&VM.stacks[0])>Opcode+1){  // +1 here so we get from sub, which is MUL and DIV
                printf("got opcode of higher priority (%d); poping stack of len %d\n", stackPeek(&VM.stacks[0]), VM.stacks[0].len);    
                for(int i=0;i<VM.stacks[0].len;i++){
                    void* NextOpcode = stackPop(&VM.stacks[0]);
                    printf("received code: %d;\n ", (int)NextOpcode);
                    VM.queues[0] = stackPush_Enqueue(VM.queues[0], NextOpcode);
                }
                for(int i=0; i<VM.stacks[0].len; i++){
                    printf("\tstack elm %d = %d = %s\n", i, (int)VM.stacks[0].data[i], instructionsReadable((instruction)VM.stacks[0].data[i]));
                }
            }
            VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
        }
        printf("ADD operator end;\n");
    }
        
    | expression MINUS expression {$$ = $1 - $3;
        instruction Opcode = SUB;
        printf("SUB operator start: \n");
        switch(VM.stacks[0].len){
            case 0:
                VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
                printf("stack empty\n");
                break;
            default:
            if(stackPeek(&VM.stacks[0])>Opcode){  // +1 here so we get from sub, which is MUL and DIV
                printf("got opcode of higher priority (%d); poping stack of len %d\n", stackPeek(&VM.stacks[0]), VM.stacks[0].len);    
                for(int i=0;i<VM.stacks[0].len;i++){
                    void* NextOpcode = stackPop(&VM.stacks[0]);
                    printf("received code: %d;\n ", (int)NextOpcode);
                    VM.queues[0] = stackPush_Enqueue(VM.queues[0], NextOpcode);
                }
                for(int i=0; i<VM.stacks[0].len; i++){
                    printf("\tstack elm %d = %d = %s\n", i, (int)VM.stacks[0].data[i], instructionsReadable((instruction)VM.stacks[0].data[i]));
                }
            }
            VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
        }
        printf("SUB end;\n");
    }
    | expression MULTIPLY expression { $$ = $1 * $3;
        instruction Opcode = MUL;
        printf("MUL opperator start: \n");
        VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
        printf("MUL opperator end;\n");}
    | expression DIVIDE expression {
        if($3==0){
            zeroDivisionError();
            $$ = 0;
        }else{
            instruction Opcode = DIV;
            VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
            $$ = $1/$3;
        }
    }
    | factor
;*/
factor:
    NUMBER              { 
        // store in stack so that we can apply shanting yard later in input/line;
        void* NumberPtr = (void*)$1;
        VM.queues[0] = stackPush_Enqueue(VM.queues[0], NumberPtr);        
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
    // void* Opperator = stackPop(&VM.stacks[0]);
    // while(1){
    //     printf("got %s, not at len of %d\n", (char*)Opperator, VM.queues[0].len);
    //     VM.queues[0] = stackPush_Enqueue(VM.queues[0], Opperator);
    //     if(counter==VM.stacks[0].len){
    //         Found_Matching_Parent = 1;
    //     }
    // }
    // VM.stacks[0] = stackPush_Enqueue(VM.stacks[0], (void*)Opcode);
    // return PARENT_R;
%%
  
int yyerror(char *s) {
        fprintf(stderr, "Error: %s\n", s);

        return 1;
}
    
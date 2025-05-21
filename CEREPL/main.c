#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <malloc.h>
#include <regex.h>
#include "../include/functions.h"

#define TOKEN_COUNT 2


char** tokens(){
    char** tokens = (char**)malloc(sizeof(char*)*(TOKEN_COUNT+1));
    tokens[0] = "exit()";
    tokens[1] = "help()";
    tokens[2] = "print";
    return tokens;
}

char** tokenize(char* input){
    /* 
        this tokenizer uses a finite state machine:
        0: start                        -> accepts anything
        1: function call                -> accepts expression then ","
        2: expression                   -> accepts ident then opperant, or just ident
        -1: fail                        -> state machine failed -> attempt to build something logical with previous ast and then continue and inform the user about this incident; if this fails, it returns 1 to the main process;
    */
    char** tokens = (char*)malloc(sizeof(char*)*3);
    int state = 0;
    int not_done = 1;
    while(not_done){
        switch(state){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case -1:
                break;
            default:
                fprintf(stderr, "\e[1;31mError:\n\tError while tokenizing; state machine out of bounds\n\e[0m");
        }
    }

}

int parse(){
    printf("\e[1;36m>> \e[0m");
    char input[128];
    fgets(input, 128, stdin);
    input[strlen(input)-1] = '\0';
        
    char* token = strtok(input, " ");
    char* function = token;
    
    switch(return_Index(input, tokens(), TOKEN_COUNT)){
        case 0:
            printf("bye!\n\t;)\n");
            return 1;
        case 1:
            printf("\e[1;35mvalid functions are:\n\t\e[1;32m");
            for(int i=0; i<TOKEN_COUNT; i++){
                printf("%s\n\t", tokens()[i]);
            }
            printf("\n\e[0m");
            break;
        case 2:
            int not_done = 1;
            while(not_done){
                
            }
        default:
            fprintf(stderr, "\e[1;31mError: \n\tSyntax Error: no such function \"%s\"\n\e[0m", input);
    }

    return 0;
}

int main(){
    int done = 0;
    while(!done){
        done = parse();
    }
    return 0;
}

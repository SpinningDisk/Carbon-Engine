#include "include/engine.h"
#include "include/language_base.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

long read_file_size(const char* path){
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    return fsize;
}

char* read_file(const char* path){
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    fseek(file, 0, SEEK_SET);
    long fsize = read_file_size(path);
    char *file_txt = malloc(fsize + 1);
    fread(file_txt, fsize, 1, file);
    fclose(file);
    file_txt[fsize] = 0;
    return file_txt;
}

int main(int argc, char *argv[]){
    const char *Path = argv[1];
    char* File_txt = read_file(Path);
    long File_size = read_file_size(Path);

    //graph Program_Graph = __init_graph__(graph tmp_graph);

    int Is_Tab[5] = {0, 0, 0, 0};
    char *Line = (char*)malloc(sizeof(char)*2);      // we store a line and a Token to be able to store the token, and then during early processing already reference elements such as Name inside a function 
    int Line_lenght = 1;                             
    char *Token_txt = (char*)malloc(sizeof(char)*2);     
    int Token_txt_lenght = 1;                      

    for(int character=0;character<File_size;character++){

        switch((int)File_txt[character]){
            case 10:
                // parse token for check (e.g: is token even complete and valid) and early processing (eg assigning variable name)
                /*printf("Hit line end:\n");
                for(int i=0; i<Line_lenght-1;i++){
                    printf("%c", Line[i]);
                };
                printf("\n");*/
                Line = (char*)realloc(Line, sizeof(char));
                Line_lenght = 1;
                switch(Token_txt_lenght){
                    case 1:
                        Token_txt = (char*)realloc(Token_txt, sizeof(char));
                        Token_txt_lenght = 1;
                        break;
                    default:
                        //printf("hit token end:\n");
                        for(int i=0;i<Token_txt_lenght-1;i++){
                            printf("%c", Token_txt[i]);
                        };
                        Token_txt = (char*)realloc(Token_txt, sizeof(char));
                        Token_txt_lenght = 1;
                        break;
                };
                printf("\n");
                break;
            case 41:
                //printf("hit token end:\n");
                for(int i=0;i<Token_txt_lenght-1;i++){
                    printf("%c", Token_txt[i]);
                };
                Token_txt = (char*)realloc(Token_txt, sizeof(char));
                Token_txt_lenght = 1;
                printf("\n");
                break;
            default:
                // if there's no newline or any stopping token, we append to current token and line;
                Line = (char*)realloc(Line, Line_lenght + 1); 
                Token_txt = (char*)realloc(Token_txt, Token_txt_lenght + 1); 
                Line[Line_lenght-1] = File_txt[character];
                Token_txt[Token_txt_lenght-1] = File_txt[character];
                Line_lenght++;
                Token_txt_lenght++;
                break;
        };
    };
    free(File_txt);
    free(Line); // Free allocated memory for Line
    free(Token_txt); // Free allocated memory for Token_txt
    return 0;
}
#include "include/engine.h"
#include "include/language_base.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

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


    graph tmp_graph;
    graph Program_Graph = __init_graph__(tmp_graph);
    // lexer starts here;
    regex_t function_create;
    int reti;
    reti = regcomp(&function_create, "^create\\(([[:alpha:]])+\\)$(\n|,)?", REG_EXTENDED); // we start with create ^create, then a litteral open bracket \\(. then a group of characters ([[:alpha:]]), which we repeate one or more times +. we then end with a closed bracket \\)
    switch(reti){
        case 0:
            break;
        default:
            printf("regcomp exit with %d", reti);
            return 1;
    };
    reti = regexec(&function_create, "create(ab),", 0, NULL, 0);
    switch(reti){
        case 0:
            char (*cargv)[2] = (unsigned int*)malloc(sizeof(unsigned int)*Cell.argc);
            cell create_cell = __init_cell__(create_cell, 2, )
            printf("match\n");
            break;
        case REG_NOMATCH:
            printf("no match\n");
            break;
        default:
            char msgbuf[100];
            regerror(reti, &function_create, msgbuf, sizeof(msgbuf));
            printf("failed:\n%s\n", msgbuf);
            return 0;

    };

    free(File_txt);
    return 0;
}
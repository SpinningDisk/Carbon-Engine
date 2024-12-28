#include "include/backend.h"
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

typedef struct cell{
    unsigned int argc;
    unsigned int* argv;
}cell;
cell __init_cell__(cell Cell, unsigned int argc, unsigned int* argv){
    Cell.argc = argc;
    Cell.argv = (unsigned int*)malloc(sizeof(unsigned int)*Cell.argc);
    for(int i=0; i<argc;i++){
        Cell.argv[i] = argv[i];
    };
    printf("ic:     argc: %d, argv: ", Cell.argc);
    for(int i=0; i<Cell.argc; i++){
        printf("%d, ", Cell.argv[i]);
    };
}
typedef struct graph{
    cell* cells;
    int* connections[2];
}graph;

int main(int argc, char *argv[]){
    const char *path = argv[1];
    char* file_txt = read_file(path);
    long file_size = read_file_size(path);

    cell TestCell;
    unsigned int* test_argv = (unsigned int*)malloc(sizeof(unsigned int)*2);
    test_argv[0] = -1;
    test_argv[1] = 5;
    TestCell = __init_cell__(TestCell, 2, test_argv);

    free(file_txt);
    return 0;
}
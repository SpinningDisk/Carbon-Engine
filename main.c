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
    const char *path = argv[1];
    char* file_txt = read_file(path);
    long file_size = read_file_size(path);
    
    int is_tab[5] = {0, 0, 0, 0};
    for(int character=0;character<file_size;character++){
        switch((int)file_txt[character]){
            case 10:
                break;
            default:
                printf("%c: %d\n", file_txt[character], (int)file_txt[character]);
                break;
        };

    };
    free(file_txt);
    return 0;
}
#include "include/backend.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>



int main(int argc, char *argv[]){
    const char *path = argv[1];
    FILE *file = fopen(path, "r");
    int display;
    char *file_cont = (char*)malloc(sizeof(char));
    if(file==NULL){
        printf("file '%s' could not be found", path);
    };
    int count = 0;
    while(1){
        display = fgetc(file);
        if(feof(file)){
            break;
        };
        printf("loop: %d; previous read: %c\n", count+1, file_cont[count-1]);
        file_cont = realloc(file_cont, count*sizeof(char));
        file_cont[count] = (char)display;
        count++;
    };
    fclose(file);
    printf("%s\n", file_cont);
    return 0;
}
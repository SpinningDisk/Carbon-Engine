#include <stdlib.h>
#include <stdio.h>

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
    printf("\n");
}
typedef struct graph{
    cell* cells;
    int* connections[2];
}graph;


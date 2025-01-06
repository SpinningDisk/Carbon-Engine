#include <stdlib.h>
#include <stdio.h>

typedef struct cell{
    unsigned int id;
    unsigned int argc;
    unsigned int* argv;
}cell;
cell __init_cell__(cell Cell, unsigned int argc, unsigned int* argv, unsigned int id){      // used to fill a cell at startup; we have an argument counter (argc), and arguments of type int
    Cell.id = id;
    Cell.argc = argc;
    Cell.argv = (unsigned int*)malloc(sizeof(unsigned int)*Cell.argc);
    for(int i=0; i<argc;i++){
        Cell.argv[i] = argv[i];
    };
    for(int i=0; i<Cell.argc-1; i++){
        printf("%d, ", Cell.argv[i]);
    };
    printf("\n");
    return Cell;
}
cell __mod_cell__(cell Cell, unsigned int argc, unsigned int* argv){                        // used during tokenization to append values (such as during x = 1, where we first call cell on x, then =, then 1)
    Cell.argc = argc;
    Cell.argv = realloc(Cell.argv, sizeof(unsigned int)*Cell.argc);
    Cell.argv = argv;
    return Cell;
}
typedef struct graph{
    cell* cells;
    int (*connections)[2];
    unsigned int cell_count;
}graph;
graph __init_graph__(graph Graph){
    Graph.cells = (cell*)malloc(sizeof(cell));
    Graph.connections = malloc(1 * sizeof(Graph.connections));
    Graph.cell_count = 0;
}
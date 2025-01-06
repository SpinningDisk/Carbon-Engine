#ifndef LANGUAGE_BASE_H
#define LANGUAGE_BASE_H


typedef struct cell{
    unsigned int id;
    unsigned int argc;
    unsigned int* argv;
}cell;
typedef struct graph{
    cell* cells;
    int (*connections)[2];
    unsigned int cell_count;
}graph;
cell __init_cell__(cell Cell, unsigned int argc, unsigned int* argv, unsigned int id);
cell __mod_cell__(cell Cell, unsigned int argc, unsigned int* argv);
graph __init_graph__(graph Graph);

#endif
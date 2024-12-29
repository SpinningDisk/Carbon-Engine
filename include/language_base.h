#ifndef LANGUAGE_BASE_H
#define LANGUAGE_BASE_H


typedef struct cell{
    unsigned int argc;
    unsigned int* argv;
}cell;
typedef struct graph{
    cell* cells;
    int* connections[2];
}graph;
cell __init_cell__(cell Cell, unsigned int argc, unsigned int* argv);

#endif
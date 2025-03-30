#ifndef LANGUAGE_H
#define LANGUAGE_H

typedef struct{
    char* name;
    char* type;
    void* data;
    int livetime;
}CEdata;
int req();

#endif
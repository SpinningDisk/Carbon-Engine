#include "./include/basefunctions.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    char** test = (char**)malloc(sizeof(char*)*3);
    test[0] = (char*)malloc(6);
    test[0] = "hello";
    test[1] = (char*)malloc(6);
    test[1] = "world";

    char* hans = (char*)malloc(6);
    hans = "hello";

    int index = GetIndex(hans, test, 2);
    printf("%d\n", index);
    return 0;
}
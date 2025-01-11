#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    char* test = (char*)malloc(sizeof(char)*6);
    test = "Hello";
    printf("%s, world!\n", test);
    return 0;
}
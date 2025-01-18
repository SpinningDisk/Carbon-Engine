#include <stdio.h>
#include "include/engine.h"
#include <string.h>
#include <stdlib.h>


int main(){
    char** TestArr = (char**)malloc(sizeof(char*)*5);
    TestArr[0] = (char*)malloc(sizeof(char)*6);
    TestArr[0] = "Hello";
    TestArr[1] = (char*)malloc(sizeof(char)*3);
    TestArr[1] = ", ";
    TestArr[2] = (char*)malloc(sizeof(char)*6);
    TestArr[2] = "World";
    TestArr[3] = (char*)malloc(sizeof(char)*2);
    TestArr[3] = "!";
    TestArr[4] = (char*)malloc(sizeof(char)*4);
    TestArr[4] = "End";

    char* TestVal = (char*)malloc(sizeof(char)*5);
    GetIndex(TestVal, TestArr, sizeof(TestArr)/sizeof(TestArr[0]));
    return 0;
}
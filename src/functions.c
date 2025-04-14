#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

int power(int base, int exponent){
    if(exponent>0){
        int res = base;
        for(int i=1; i<exponent; i++){
            res = res*base;
        }
        return res;
    }else if(exponent==0){
        return 1;
    }else{
        return 1/power(base, abs(exponent));
    }
}

int return_Index(char* Elm, char** Arr, int Arr_Len){
    for(int i=0; i<Arr_Len; i++){
        if(strcmp(Elm, Arr[i])==0){
            return i;
        }
    }
    return -1;
}
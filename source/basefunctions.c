#include <malloc.h>
#include <string.h>
#include <stdbool.h>


int GetIndex(char* elm, char** array, int arr_size){
    for(int i=0;i<arr_size;i++){
        switch(strcmp(array[i], elm)){
            case 0:
                return i;
            default:
                break;
        };
    };
    return -1;
};

char* append(char* s1, char* s2){
    int len = strlen(s1);
    int new_len = len+strlen(s2);
    char* out = (char*)malloc(new_len+1);
    for(int i=0; i<len; i++){
        out[i] = s1[i];
    }
    for(int i=len; i<new_len; i++){
        out[i] = s2[i];
    }
    out[new_len+1] = '\0';
    return out;
}
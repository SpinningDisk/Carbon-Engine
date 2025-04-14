#include <string.h>
#include <stdio.h>


int main(){
    char myStr[] = "1+2*3";
    char * myPtr = strtok(myStr, "+*");
    while(myPtr != NULL) {
        printf("%s\n", myPtr);
        myPtr = strtok(NULL, " ");
    }
}
#include <stdlib.h>
#include <stdio.h> 

int power(int base, int exponent){
    printf("running\n");
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
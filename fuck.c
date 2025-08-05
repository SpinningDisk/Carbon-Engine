#include <math.h>
#include <stdio.h>


float test(float in){
    return sin(in);
}
int main(){
    printf("sin(%f) is %f\n", 1.5, test(1.5));
    return 0;
}

#include <stdio.h>
#include "../include/engine.h"
#include "../include/functions.h"
#include "../include/language.h"
#include <stdlib.h> 
extern int yyparse(void);


CEVM VM;
int main(){
    // VM = bootVM();
    // int hans = 123;
    // VM.stack = stackPush_Enqueue(VM.stack, (void*)hans);
    // int peter = 234;
    // VM.stack = stackPush_Enqueue(VM.stack, (void*)peter);
    // printf("from len of %d", VM.stack.len);
    // void* test = stackPop(&VM.stack);
    // void* test2 = stackPop(&VM.stack);
    // printf(" to %d by retrieving %d and %d\n", VM.stack.len, (int)test, (int)test2);
    // return 0;
    printf("\n\e[1;34m>>\e[0;37m");
    yyparse();
    return 0;
}


// this input returns segv for some reason:
// as*(*()))2)s
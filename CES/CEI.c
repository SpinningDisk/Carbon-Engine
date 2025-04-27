#include <stdio.h>
#include "../include/engine.h"
#include "../include/functions.h"
#include "../include/language.h"
#include <stdlib.h> 
extern int yyparse(void);


CEVM VM;
int main(){
    VM = bootVM();
    // int hans = 123;
    // VM.stack = stackPush(VM.stack, (void*)hans);
    // int peter = 234;
    // VM.stack = stackPush(VM.stack, (void*)peter);
    //printf("%d\n", VM.stack.data[0]);
    // return 0;
    printf(">>");
    yyparse();
    return 0;
}


// this input returns segv for some reason:
// as*(*()))2)s
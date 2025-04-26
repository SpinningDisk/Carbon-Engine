#include <stdio.h>
#include "../include/engine.h"
#include "../include/functions.h"
#include "../include/language.h"
#include <stdlib.h> 
extern int yyparse(void);


CEVM VM;
int main(){
    VM = bootVM();
    VM.stack.data = realloc(VM.stack.data, sizeof(void**)*2);
    int hans = 123;
    VM.stack.data[0] = (void*)hans;
    printf("%d\n", VM.stack.data[0]);
    return 0;
    printf(">>");
    yyparse();
    return 0;
}


// this input returns segv for some reason:
// as*(*()))2)s
#include <stdio.h>
#include "../include/engine.h"
#include "../include/functions.h"
#include "../include/language.h"
extern int yyparse(void);


CEVM VM;
int main(){
    VM = bootVM();
    printf(">>");
    yyparse();
    return 0;
}


// this input returns segv for some reason:
// as*(*()))2)s
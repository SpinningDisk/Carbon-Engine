%{
//#include "../include/engine.h"
#include <stdio.h>
%}

%%
.
\n {printf(">>");}
exit {printf("\n\tbye!\n");
return 0;}
%%

int yywrap(){}
int main(){
printf(">>");
yylex();
return 0;
}
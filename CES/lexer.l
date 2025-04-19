%{
    #include "grammar.tab.h"
    #include "../include/language.h"
%}
    
%%
\n  {return '\n';}
exit\(\)                {return EXIT;}
while                   {return WHILE;}



[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }
" "?"+"" "?             { return PLUS; }
" "?"-"" "?             { return MINUS; }
" "?"*"" "?             { return MULTIPLY; }
" "?"/"" "?             { return DIVIDE; }
" "?"="" "?             { return EQ; }
" "?"("" "?             { return PARENT_L;}
" "?")"" "?             { return PARENT_R;}
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENT; }
\"[[:alpha:]]*\"        {//"; 
                         yylval.str = strdup(yytext); return STRING;}
" "?"int "              { yylval.type = (int)TYPE_INT; return lTYPE;}
" "?"str "              { yylval.type = (int)TYPE_STR; return lTYPE;}


.                       { return yytext[0];}
%%
int yywrap(){}
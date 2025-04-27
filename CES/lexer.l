%{
    #include "grammar.tab.h"
    #include "../include/language.h"
    extern CEVM VM;
%}
    
%%
\n  {return '\n';}
" "?"exit\(\)"" "?                {return EXIT;}
while                   {return WHILE;}

printstack\(\)          {return printstack;}
printqueue\(\)          {return printqueue;}
emptystack\(\)          {return emptystack;}
emptyqueue\(\)          {return emptyqueue;}

[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }
" "?"+"" "?             { return PLUS; }
" "?"-"" "?             { return MINUS; }
" "?"*"" "?             { return MULTIPLY; }
" "?"/"" "?             { return DIVIDE; }
" "?"="" "?             { return EQ; }
" "?"("" "?             { return PARENT_L;}
" "?")"" "?             { 
    // printf("got parrent R\n");
    // char* Opcode = ")";
    // int Found_Matching_Parent = 0;
    // int counter = 0;
    return PARENT_R;
    // void* Opperator = stackPop(&VM.stack);
    // while(1){
    //     printf("got %s, not at len of %d\n", (char*)Opperator, VM.queue.len);
    //     VM.queue = stackPush_Enqueue(VM.queue, Opperator);
    //     if(counter==VM.stack.len){
    //         Found_Matching_Parent = 1;
    //     }
    // }
    // VM.stack = stackPush_Enqueue(VM.stack, (void*)Opcode);
    // return PARENT_R;
    }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENT; }
\"[[:alpha:]]*\"        {//"; 
                         yylval.str = strdup(yytext); return STRING;}
" "?"int "              { yylval.type = (int)TYPE_INT; return lTYPE;}
" "?"str "              { yylval.type = (int)TYPE_STR; return lTYPE;}


.                       { return yytext[0];}
%%
int yywrap(){}
#!/bin/bash
flex syntax.l
clang lex.yy.c
clang  -I../include -L../lib -lengine -llanguage_base -lbasefunctions ./lex.yy.c -Wl,-rpath=../lib



$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)
		
	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.o)
	
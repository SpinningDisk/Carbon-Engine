#!/bin/bash
flex syntax.l
clang lex.yy.c
clang  -I../include -L../lib -lengine -llanguage_base -lbasefunctions ./lex.yy.c -Wl,-rpath=../lib
#!/bin/bash
flex syntax.l
clang lex.yy.c

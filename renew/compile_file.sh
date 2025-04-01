#!/bin/bash

clear

clang -o out.o -I./include -L./lib -lengine -llanguage_base -lbasefunctions ./run.c -Wl,-rpath=./lib -v  t
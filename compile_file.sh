#!/bin/bash

clear

clang -o out.o -I./include -L./lib -lengine -llanguage_base ./run.c -Wl,-rpath=./lib

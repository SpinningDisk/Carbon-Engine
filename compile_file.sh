#!/bin/bash

clear

gcc -o file.o -I./include -L./lib -lengine -llanguage_base ./main.c -Wl,-rpath=./lib
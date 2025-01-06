#!/bin/bash

clear

gcc -o out.o -I./include -L./lib -lengine -llanguage_base ./main.c -Wl,-rpath=./lib
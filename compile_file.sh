#!/bin/bash

clear && gcc -o file.o -I./include -L./lib -lbackend ./main.c -Wl,-rpath=./lib
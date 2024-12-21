#!/bin/bash

prodir=/home/thedisk/vsc-projects/Carbon-Engine

gcc -c -fPIC $prodir/source/backend.c -o $prodir/tmp/libbackend.o
gcc -shared -o $prodir/lib/libbackend.so $prodir/tmp/libbackend.o

rm $prodir/tmp/*
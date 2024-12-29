#!/bin/bash

prodir=/home/thedisk/gem-ecosystem/Carbon-Engine

gcc -c -fPIC $prodir/source/engine.c -o $prodir/tmp/libengine.o
gcc -shared -o $prodir/lib/libengine.so $prodir/tmp/libengine.o

gcc -c -fPIC $prodir/source/language_base.c -o $prodir/tmp/liblanguage_base.o
gcc -shared -o $prodir/lib/liblanguage_base.so $prodir/tmp/liblanguage_base.o


rm $prodir/tmp/*
#!/bin/bash

prodir=.

clang -c -fPIC $prodir/source/engine.c -o $prodir/tmp/libengine.o
clang -shared -o $prodir/lib/libengine.so $prodir/tmp/libengine.o

clang -c -fPIC $prodir/source/language_base.c -o $prodir/tmp/liblanguage_base.o
clang -shared -o $prodir/lib/liblanguage_base.so $prodir/tmp/liblanguage_base.o

rm $prodir/tmp/*;

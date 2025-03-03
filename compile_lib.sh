#!/bin/bash
clear

prodir=.

# clang -o out.o -I./include -L./lib -lengine -llanguage_base ./run.c -Wl,-rpath=./lib -v

clang -c -fPIC $prodir/source/basefunctions.c -o $prodir/tmp/libbasefunctions.o -Wall -Wextra
clang -shared -o $prodir/lib/libbasefunctions.so $prodir/tmp/libbasefunctions.o -Wall -Wextra

clang -c -fPIC $prodir/source/engine.c -o $prodir/tmp/libengine.o -v -Wall -Wextra
clang -shared -o $prodir/lib/libengine.so $prodir/tmp/libengine.o -lm -Wall -Wextra

clang -c -fPIC $prodir/source/language_base.c -o $prodir/tmp/liblanguage_base.o -Wall -Wextra
clang -shared -o $prodir/lib/liblanguage_base.so $prodir/tmp/liblanguage_base.o -Wall -Wextra

rm $prodir/tmp/*;

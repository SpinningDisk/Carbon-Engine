CC = clang
AR = llvm-ar
LD = LLD

EngineSrc = Engine
BinderSrc = KernelBinder
BinderFSrc = Binder
fastFunctionsFSrc = libfastfunctions
Src = Common
BuildLoc = build

all: static
.PHONY: clean static shared dev
clean:
	rm -rf $(BuildLoc)
	mkdir $(BuildLoc)
	mkdir $(BuildLoc)/lib
	mkdir $(BuildLoc)/include
	cp -r include/* $(BuildLoc)/include/
	mkdir $(BuildLoc)/tmp
static:
	# Functions: 
	$(CC) -c $(Src)/$(fastFunctionsFSrc).c -o $(BuildLoc)/tmp/$(fastFunctionsFSrc).o -Wall -Wextra
	$(AR) rcs $(BuildLoc)/lib/$(fastFunctionsFSrc).a $(BuildLoc)/tmp/$(fastFunctionsFSrc).o

	# Binder
	$(CC) -c $(BinderSrc)/$(BinderFSrc).c -o $(BuildLoc)/tmp/lib$(BinderFSrc).o -Wall -Wextra
	$(AR) rcs $(BuildLoc)/lib/lib$(BinderFSrc).a $(BuildLoc)/tmp/lib$(BinderFSrc).o
dev:
	clear
	make clean
	make static
	$(CC) -o $(BuildLoc)/main $(Src)/devtest.c -L$(BuildLoc)/lib -lBinder -lfastfunctions
	$(BuildLoc)/main

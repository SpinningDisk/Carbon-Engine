CC = clang

LibLoc = src/
LanguageLoc = CES/
OutLoc = build/
LibFunctionsSrc = functions.c 
LibEngineSrc = engine.c
LanguageSrc = CarbonEngineScript.l

LanguageOut = build/CES/CarbonEngineInterpreter.o

.PHONY: static shared CES app dev clean

# clang -o main.o -Wl,--whole-archive -I./include -L./lib -lengine -Wl,--no-whole-archive test.c -Wl,-rpath=./lib -Wall
static:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include
	ld -r $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -o $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)



# clang -o main.o -Wl,--whole-archive -I./include -L./lib -lfunctions -lengine -Wl,--no-whole-archive test.c -Wl,-rpath=./lib -Wall
shared:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	$(CC) -shared -o $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.so) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	
	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include -L$(OutLoc)lib
	$(CC) -shared -o $(OutLoc)lib/lib$(LibEngineSrc:.c=.so) $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -Wall -Wextra -I$(OutLoc)include



CES:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include
	ld -r $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -o $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)

	
	flex $(LanguageLoc)$(LanguageSrc)
	mv lex.yy.c $(OutLoc)tmp/lex.yy.c
	$(CC) -I$(OutLoc)include -L$(OutLoc)lib -lengine -lfunctions $(OutLoc)tmp/lex.yy.c -Wl,-rpath=$(OutLoc)lib
	mv a.out $(OutLoc)/CarbonEngineInterpreter

dev:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include
	ld -r $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -o $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)

	clang -o $(OutLoc)main.o -Wl,--whole-archive -I$(OutLoc)/include -L$(OutLoc)/lib -lfunctions -lengine -Wl,--no-whole-archive $(OutLoc)devtest.c -Wl,-rpath=$(OutLoc)/lib -Wall -Wextra	
	clear
	$(OutLoc)main.o
clean:
	rm -rf $(OutLoc)lib $(OutLoc)include $(OutLoc)tmp
	mkdir -p $(OutLoc)tmp $(OutLoc)lib $(OutLoc)include
	rm $(OutLoc)main.o
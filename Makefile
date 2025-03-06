CC = clang

LibLoc = src/
LanguageLoc = CES/
OutLoc = build/
LibFunctionsSrc = functions.c 
LibEngineSrc = engine.c
LanguageSrc = CarbonEngineScript.l

LanguageOut = build/CES/CarbonEngineInterpreter.o

.PHONY: static shared CES app clean

static:
	mkdir $(OutLoc)lib
	mkdir $(OutLoc)include
	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.o)

	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

shared:
	mkdir $(OutLoc)include
	mkdir $(OutLoc)lib
	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	$(CC) -shared -o $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.so) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	
	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra
	$(CC) -shared -o $(OutLoc)lib/lib$(LibEngineSrc:.c=.so) $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra

	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

CES:
	mkdir $(OutLoc)include
	mkdir $(OutLoc)lib
	
	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)
		
	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.o)
	
	
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

	
	flex $(LanguageLoc)$(LanguageSrc)
	mv lex.yy.c $(OutLoc)tmp/lex.yy.c
	$(CC) -I$(OutLoc)include -L$(OutLoc)lib -lengine -lfunctions $(OutLoc)tmp/lex.yy.c -Wl,-rpath=$(OutLoc)lib
	mv a.out $(OutLoc)/CarbonEngineInterpreter

clean:
	rm -rf build
	mkdir build
	mkdir build/tmp
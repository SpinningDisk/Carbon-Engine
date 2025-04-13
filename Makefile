CC = clang

LibLoc = src/
LanguageLoc = CES/
OutLoc = build/
LibFunctionsSrc = functions.c 
LibEngineSrc = engine.c
LanguageSrc = CEI.l
LibLanguageSrc = language.c


LanguageOut = build/CES/CarbonEngineInterpreter.o

.PHONY: static shared CEI app dev clean

# clang -o main.o -Wl,--whole-archive -I./include -L./lib -lengine -Wl,--no-whole-archive test.c -Wl,-rpath=./lib -Wall
static:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/
	cp include/language.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include
	ld -r $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -o $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)

	$(CC) -c -fPIC $(LibLoc)$(LibLanguageSrc) -o $(OutLoc)tmp/$(LibLanguageSrc:.c=.o) -Wall -Wextra
	ld -r $(OutLoc)tmp/$(LibLanguageSrc:.c=.o) -L $(OutLoc)lib -lfunctions -lengine -o $(OutLoc)tmp/$(LibLanguageSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibLanguageSrc:.c=.a) $(OutLoc)tmp/$(LibLanguageSrc:.c=.linked.o)


# clang -o main.o -Wl,--whole-archive -I./include -L./lib -lfunctions -lengine -Wl,--no-whole-archive test.c -Wl,-rpath=./lib -Wall
shared:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/
	cp include/language.h $(OutLoc)include/	

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	$(CC) -shared -o $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.so) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	
	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include -L$(OutLoc)lib
	$(CC) -shared -o $(OutLoc)lib/lib$(LibEngineSrc:.c=.so) $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -Wall -Wextra -I$(OutLoc)include

	$(CC) -c -fPIC $(LibLoc)$(LibLanguageSrc) -o $(OutLoc)tmp/$(LibLanguageSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include -L$(OutLoc)lib
	$(CC) -shared -o $(OutLoc)lib/lib$(LibLanguageSrc:.c=.so) $(OutLoc)tmp/$(LibLanguageSrc:.c=.o) -L$(OutLoc)lib -Wall -Wextra $(OutLoc)include -v


CEI:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/
	cp include/language.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include
	ld -r $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -o $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)

	
	flex $(LanguageLoc)$(LanguageSrc)
	mv lex.yy.c $(OutLoc)tmp/lex.yy.c
	$(CC) -o $(OutLoc)CarbonEngineInterpreter -Wl,--whole-archive -I$(OutLoc)/include -L$(OutLoc)/lib -lfunctions -lengine -Wl,--no-whole-archive $(OutLoc)tmp/lex.yy.c -Wl,-rpath=$(OutLoc)/lib -Wall -Wextra	

dev:
	cp include/engine.h $(OutLoc)include/
	cp include/functions.h $(OutLoc)include/

	$(CC) -c -fPIC $(LibLoc)$(LibFunctionsSrc) -o $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o) -Wall -Wextra
	ar rcs $(OutLoc)lib/lib$(LibFunctionsSrc:.c=.a) $(OutLoc)tmp/$(LibFunctionsSrc:.c=.o)

	$(CC) -c -fPIC $(LibLoc)$(LibEngineSrc) -o $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -Wall -Wextra -I$(OutLoc)include
	ld -r $(OutLoc)tmp/$(LibEngineSrc:.c=.o) -L$(OutLoc)lib -lfunctions -o $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)
	ar rcs $(OutLoc)lib/lib$(LibEngineSrc:.c=.a) $(OutLoc)tmp/$(LibEngineSrc:.c=.linked.o)

	$(CC) -o $(OutLoc)main.o -Wl,--whole-archive -I$(OutLoc)/include -L$(OutLoc)/lib -lfunctions -lengine -Wl,--no-whole-archive $(OutLoc)devtest.c -Wl,-rpath=$(OutLoc)/lib -Wall -Wextra	
	$(OutLoc)main.o
clean:
	rm -rf $(OutLoc)lib $(OutLoc)include $(OutLoc)tmp $(OutLoc)CarbonEngineInterpreter
	mkdir -p $(OutLoc)tmp $(OutLoc)lib $(OutLoc)include
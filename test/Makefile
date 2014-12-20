COMPILER=g++ -g -std=c++11

OPTS=-std=c++11 -pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing

COMPILE=$(COMPILER) $(OPTS) -I../src ../src/*.o

DEFAULT_LIBRARIES=-lgtest -lgtest_main -lpthread


all: Board Move
	$(COMPILE) *.cxx -o all.exe $(DEFAULT_LIBRARIES)


Board:
	$(COMPILE) $@.cxx -o $@.exe $(DEFAULT_LIBRARIES)


Move:
	$(COMPILE) $@.cxx -o $@.exe $(DEFAULT_LIBRARIES)


clean:
	rm *.exe

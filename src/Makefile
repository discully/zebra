COMPILER=g++ -g -c

OPTS=-std=c++11 -pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing

COMPILE=$(COMPILER) $(OPTS)


all: Board Move


Board:
	$(COMPILE) $@.cxx


Move:
	$(COMPILE) $@.cxx


clean:
	rm *.o

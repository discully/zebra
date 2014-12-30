COMPILER=g++ -g -c

OPTS=-std=c++11 -pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing

COMPILE=$(COMPILER) $(OPTS)


all: Board Game Human Move Player Rules Random


Board: Rules Move
	$(COMPILE) $@.cxx


Game: Board Move Player
	$(COMPILE) $@.cxx


Human: Player
	$(COMPILE) $@.cxx


Move: Rules
	$(COMPILE) $@.cxx


Player: Move
	$(COMPILE) $@.cxx


Random: Player
	$(COMPILE) $@.cxx


Rules:
	$(COMPILE) $@.cxx


clean:
	rm *.o

CORE_DIRECTORY=src
TEST_DIRECTORY=test

COMPILER=g++ -g

OPTS=-std=c++11 -pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing

COMPILE=$(COMPILER) $(CORE_DIRECTORY)/*.o $(OPTS)



game: core
	$(COMPILE) $(CORE_DIRECTORY)/zebra.cxx -o zebra.exe


core:
	cd src/ && make


test: core
	cd test/ && make


check: test
	test/all.exe


all: core test


clean_core:
	cd $(CORE_DIRECTORY)/ && make clean


clean_test:
	cd $(TEST_DIRECTORY)/ && make clean


clean: clean_test clean_core


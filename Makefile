CORE_DIRECTORY=src
TEST_DIRECTORY=test


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


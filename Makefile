all: test_string

test_string: test_string.o memory.o
	gcc -g test_string.o memory.o -o test_string

test_string.o: test_string.c memory.h
	gcc -g -c test_string.c -o test_string.o

memory.o: memory.c memory.h
	gcc -g -c memory.c -o memory.o

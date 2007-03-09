all: test_string

test_string: test_string.o memory.o
	gcc test_string.o memory.o -o test_string

test_string.o: test_string.c memory.h
	gcc -c test_string.c -o test_string.o

memory.o: memory.c memory.h
	gcc -c memory.c -o memory.o

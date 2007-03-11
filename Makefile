CC = gcc
CFLAGS = -g
LIBS = 


all: test_string test_read

test_string: test_string.o memory.o
	$(CC) $(CFLAGS) test_string.o memory.o -o test_string
test_read: test_read.o memory.o read.o print.o
	$(CC) $(CFLAGS) test_read.o read.o memory.o print.o -o test_read
test_read.o: test_read.c memory.h types.h print.h
	$(CC) $(CFLAGS) -c test_read.c -o test_read.o
test_string.o: test_string.c memory.h
	$(CC) $(CFLAGS) -c test_string.c -o test_string.o
read.o: read.c memory.h types.h
	$(CC) $(CFLAGS) -c read.c -o read.o
print.o: print.c print.h types.h memory.h
	$(CC) $(CFLAGS) -c print.c -o print.o
memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c -o memory.o

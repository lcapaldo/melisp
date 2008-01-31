CC = gcc
CFLAGS = -Wall -g
LIBS = 


all: test_repl

test_repl: test_repl.o memory.o read.o print.o eval.o symbols.o env.o list.o functions.o types.o
	$(CC) $(CFLAGS) test_repl.o read.o memory.o eval.o env.o symbols.o list.o functions.o print.o types.o -o test_repl
test_repl.o: test_repl.c memory.h types.h print.h eval.h
	$(CC) $(CFLAGS) -c test_repl.c -o test_repl.o
read.o: read.c memory.h types.h
	$(CC) $(CFLAGS) -c read.c -o read.o
print.o: print.c print.h types.h memory.h
	$(CC) $(CFLAGS) -c print.c -o print.o
memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c -o memory.o
eval.o: eval.c memory.h types.h eval.h env.h symbols.h
	$(CC) $(CFLAGS) -c eval.c -o eval.o
symbols.o: symbols.c symbols.h memory.h types.h
	$(CC) $(CFLAGS) -c symbols.c -o symbols.o
env.o: env.c env.h memory.h types.h
	$(CC) $(CFLAGS) -c env.c -o env.o
list.o: list.c list.h memory.h types.h
	$(CC) $(CFLAGS) -c list.c -o list.o
functions.o: functions.c functions.h memory.h types.h
	$(CC) $(CFLAGS) -c functions.c -o functions.o
types.o: types.h types.c memory.h
	$(CC) $(CFLAGS) -c types.c -o types.o
clean:
	rm *.o test_repl
nuke_backups:
	rm *~


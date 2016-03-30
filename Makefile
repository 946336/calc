CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

LDFLAGS = -lm

NOLINK = -c
OPTIMIZE = -O2

m'lady: main.c explist.o ast.o operator.o tokenize.o parse.o
	$(CC) $(CFLAGS) $(OPTIMIZE) $^ -o m\'lady $(LDFLAGS)

parse.o: parse.c parse.h ast.o explist.o operator.o tokenize.o
	$(CC) $(CFLAGS) $(NOLINK) $(OPTIMIZE) parse.c -o $@ $(LDFLAGS)

calc: main.c explist.o ast.o operator.o tokenize.o parse.o
	$(CC) $(CFLAGS) $(OPTIMIZE) $^ -o calc $(LDFLAGS)

explist.o: explist.h explist.c ast.o operator.o
	$(CC) $(CFLAGS) $(NOLINK) $(OPTIMIZE) explist.c -o $@ $(LDFLAGS)

ast.o: ast.c ast.h operator.o
	$(CC) $(CFLAGS) $(NOLINK) $(OPTIMIZE) ast.c -o $@ $(LDFLAGS)

operator.o: operator.c operator.h
	$(CC) $(CFLAGS) $(NOLINK) $(OPTIMIZE) operator.c -o $@ $(LDFLAGS)

tokenize.o: tokenize.h tokenize.c ast.o
	$(CC) $(CFLAGS) $(NOLINK) $(OPTIMIZE) tokenize.c -o $@ $(LDFLAGS)

solution: solution.c
	$(CC) $(CFLAGS) $(OPTIMIZE) solution.c -o calc $(LDFLAGS)


clean:
	rm -f *.o calc

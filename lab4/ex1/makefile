CC=gcc
CFLags=-Wall -Wextra -O2 -g

all: run

run:
	make clean
	make static
	$(CC) $(CFlags) -c main.c
	$(CC) $(CFlags) -c child.c
	$(CC) $(CFlags) main.o libparser.a -o main
	$(CC) $(CFlags) child.c -o child

static:
	$(CC) $(CFLags) -c parser.c
	ar rcs libparser.a parser.o

clean:
	rm -f *.o *.so *.a main child
CC=gcc
CFlags=-Wall -Wextra -O1 -g

all: run

run:
	make clean
	$(CC) $(CFlags) -c main.c
	$(CC) $(CFlags) main.o -o main

clean:
	rm -f *.o *.a main

test: run
	./main "skladnik1 | skladnik6 | skladnik3"

	./main "skladnik1 | skladnik2"

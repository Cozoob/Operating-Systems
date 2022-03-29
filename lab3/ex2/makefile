CC=gcc
CFlags=-Wall -Wextra -O2 -g

all: run

run:
	make clean
	$(CC) $(CFlags) -c main.c
	$(CC) $(CFlags) main.o -o main

clean:
	rm -f *.o *.txt main

clean-w:
	rm -f w*.txt
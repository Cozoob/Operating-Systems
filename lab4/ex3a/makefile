#!/bin/bash
CC=gcc
CFlags=-Wall -Wextra -O2 -g

all: run

run:
	make clean
	$(CC) $(CFlags) -c catcher.c
	$(CC) $(CFlags) -c sender.c
	$(CC) $(CFlags) -c main.c
	$(CC) $(CFlags) catcher.o -o catcher
	$(CC) $(CFlags) sender.o -o sender
	$(CC) $(CFlags) main.o -o main

clean:
	rm -f *.o *.a main catcher sender

test:
	./main 3000 kill
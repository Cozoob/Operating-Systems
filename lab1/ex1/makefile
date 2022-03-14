CC=gcc
CFlags=-Wall -Wextra -O0 -g

all: main_static main_shared

static:
		$(CC) $(CFlags) -c library.c
		ar rcs liblibrary.a library.o

shared:
		$(CC) $(CFlags) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc

main_static: static
		$(CC) $(CFlags) -c main.c
		$(CC) $(CFlags) main.o liblibrary.a -o main

main_shared: shared
		$(CC) $(CFlags) main.c -llibrary -L ./ -o main

clean:
		rm -f *.o *.so *.a main

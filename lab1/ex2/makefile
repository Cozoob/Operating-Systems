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
		rm -f *.o *.so *.a raport2.txt main

tests:
		rm -f raport2.txt

		make -s test_static

		make -s test_shared

test_static: static
		$(CC) -c main.c
		$(CC) main.o liblibrary.a -o main

		@echo "~~~~~~~~~~~~~~~~~~~STATIC TEST~~~~~~~~~~~~~~~~~~~" >> raport2.txt
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

test_shared: shared
		$(CC) main.c -llibrary -L ./ -o main

		@echo "~~~~~~~~~~~~~~~~~~~SHARED TEST~~~~~~~~~~~~~~~~~~~" >> raport2.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

small:
		@echo "\n########### SMALL TESTS ###########\n" >> raport2.txt
		@echo "7 files: file1, file2, file3, file7, file8, file9, file10\n" >> raport2.txt
		@ #makes it silent
		@./main 3 wc_files file1 file2 file3 file7 file8 file9 file10 wc_files file2 file1 file8 file9 wc_files file3 file7 remove_block 0 \
		remove_block 2 remove_block 1 create_table 5

medium:
		@echo "\n########### MEDIUM TESTS ###########\n" >> raport2.txt
		@echo "9 files: file1, ..., file5, file7, ..., file10\n" >> raport2.txt
		@ #makes it silent
		@./main 30 wc_files file4 file5  file1 file2 file3 file7 file8 file9 file10 \
		wc_files file1 file2 file3 file7 file8 file9 file10 file5 remove_block 0 \
		wc_files file4 file5 \
		remove_block 2 remove_block 1 remove_block 20 remove_block 10 \
     	create_table 50 create_table 70

large:
		@echo "\n########### LARGE TESTS ###########\n" >> raport2.txt
		@echo "10 files: file1 ... file10\n" >> raport2.txt
		@ #makes it silent
		@./main 300 wc_files file6 file1 file2 file3 file7 file8 file9 file10 \
		wc_files file6 \
		remove_block 0 remove_block 2 remove_block 1 \
		remove_block 3 remove_block 4 remove_block 5 remove_block 6 remove_block 7 remove_block 81 \
		remove_block 23 remove_block 34 remove_block 35 remove_block 32 remove_block 30 remove_block 31 \
		create_table 456 create_table 234 create_table 1000 create_table 200 create_table 178
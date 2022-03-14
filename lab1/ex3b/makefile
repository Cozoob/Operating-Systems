CC=gcc
CFlags1=-Wall -Wextra -O -g
CFLags2=-Wall -Wextra -O1 -g
CFlags3=-Wall -Wextra -O2 -g

all: tests

static:
		$(CC) $(CFlags1) -c library.c
		ar rcs liblibrary.a library.o

shared:
# 		DOES NOT WORK :( IDK WHY
#		echo $(CURDIR)
#		export LD_LIBRARY_PATH=$(CURDIR):$LD_LIBRARY_PATH
#		echo $(LD_LIBRARY_PATH)
		$(CC) $(CFlags1) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc


main_static: static
		$(CC) $(CFlags) -c main.c
		$(CC) $(CFlags) main.o liblibrary.a -o main

main_shared: shared
		$(CC) $(CFlags) main.c -llibrary -L ./ -o main

generator:
		$(CC) $(CFlags1) gen.c -L ./ -o gen

clean:
		rm -f *.o *.so *.a main file* gen results3b.txt

tests:
		rm -f results3b.txt

		make -s generator
		@./gen

		make -s test_static

		make -s test_shared

		make -s test_dynamic

test_static:
		#0
		$(CC) $(CFlags1) -c library.c
		ar rcs liblibrary.a library.o

		$(CC) -c main.c
		$(CC) main.o liblibrary.a -o main

		@echo "COMPILATION OPTION: O" >> results3b.txt
		@echo "~~~~~~~~~~~~~~~~~~~STATIC TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

        # 01
		$(CC) $(CFlags2) -c library.c
		ar rcs liblibrary.a library.o

		$(CC) -c main.c
		$(CC) main.o liblibrary.a -o main

		@echo "COMPILATION OPTION: O1" >> results3b.txt
		@echo "~~~~~~~~~~~~~~~~~~~STATIC TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

        # O2
		$(CC) $(CFlags3) -c library.c
		ar rcs liblibrary.a library.o

		$(CC) -c main.c
		$(CC) main.o liblibrary.a -o main

		@echo "COMPILATION OPTION: O2" >> results3b.txt
		@echo "~~~~~~~~~~~~~~~~~~~STATIC TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

test_shared:
		# O
		$(CC) $(CFlags1) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc

		@echo "COMPILATION OPTION: O" >> results3b.txt
		$(CC) main.c -llibrary -L ./ -o main
		@echo "~~~~~~~~~~~~~~~~~~~SHARED TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

        # O1

		$(CC) $(CFlags2) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc

		@echo "COMPILATION OPTION: O1" >> results3b.txt
		$(CC) main.c -llibrary -L ./ -o main
		@echo "~~~~~~~~~~~~~~~~~~~SHARED TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

		# O2
		$(CC) $(CFlags3) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc

		@echo "COMPILATION OPTION: O2" >> results3b.txt
		$(CC) main.c -llibrary -L ./ -o main
		@echo "~~~~~~~~~~~~~~~~~~~SHARED TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

test_dynamic:
		# O
		$(CC) $(CFlags1) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc
		$(CC) main2.c -o main.o -ldl -D dynamic

		@echo "COMPILATION OPTION: O" >> results3b.txt
		@echo "~~~~~~~~~~~~~~~~~~~DYNAMIC TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large


		# O1
		$(CC) $(CFlags2) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc
		$(CC) main2.c -o main.o -ldl -D dynamic

		@echo "COMPILATION OPTION: O1" >> results3b.txt
		@echo "~~~~~~~~~~~~~~~~~~~DYNAMIC TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large


		# O2
		$(CC) $(CFlags3) -c -fPIC library.c
		$(CC) -shared -o liblibrary.so library.o -lc
		$(CC) main2.c -o main.o -ldl -D dynamic

		@echo "COMPILATION OPTION: O2" >> results3b.txt
		@echo "~~~~~~~~~~~~~~~~~~~DYNAMIC TEST~~~~~~~~~~~~~~~~~~~" >> results3b.txt
		# --no-print-directory - to not print  “Entering/Leaving directory ...” messages
		make --no-print-directory small
		make --no-print-directory medium
		make --no-print-directory large

small:
		@echo "\n########### SMALL TESTS ###########\n" >> results3b.txt
		@echo "5 files: file1, ..., file5\n" >> results3b.txt
		@ #makes it silent
		@./main 3 wc_files file1 file2 file3 file4 file5 wc_files file2 file1 file3 wc_files file4 file5 remove_block 0\
		remove_block 2 remove_block 1 create_table 5

medium:
		@echo "\n########### MEDIUM TESTS ###########\n" >> results3b.txt
		@echo "7 files: file1, ..., file7\n" >> results3b.txt
		@ #makes it silent
		@./main 30 wc_files file4 file5 file1 file2 file3 file6 file7\
		wc_files file1 file2 file3 file5 remove_block 0\
		wc_files file4 file5 file7\
		remove_block 2 remove_block 1 remove_block 20 remove_block 10 create_table 50 create_table 70

large:
		@echo "\n########### LARGE TESTS ###########\n" >> results3b.txt
		@echo "9 files: file1, ..., file9\n" >> results3b.txt
		@ #makes it silent
		@./main 300 wc_files file6 file1 file2 file3 file7 file8 file9\
		wc_files file6\
		remove_block 0 remove_block 2 remove_block 1\
		remove_block 3 remove_block 4 remove_block 5 remove_block 6 remove_block 7 remove_block 81\
		remove_block 23 remove_block 34 remove_block 35 remove_block 32 remove_block 30 remove_block 31\
		create_table 456 create_table 234 create_table 1000 create_table 200 create_table 178
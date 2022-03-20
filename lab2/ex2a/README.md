# [POLISH]
Zadanie 2 (25%)

a) Używając funkcji biblioteki C: fread() i fwrite().

Napisz program, który przyjmuje 2 argumenty wiersza poleceń. 
Pierwszy z argumentów jest znakiem, drugi nazwą pliku. Program powinien policzyć ile razy 
występuje podany znak oraz liczbę wierszy pliku wejściowego, które zawierają dany znak. Zakładamy, 
że każdy wiersz w pliku kończy się znakiem przejścia do nowej linii. Przyjmujemy, że żaden wiersz nie przekracza długości 256 znaków.

#### Jak użyć:
* make - kompiluje pliki, aby uruchomić program.
* ./main c file - uruchamia program, który zlicza ilość wystąpień znaku "c" oraz wierszy w których występuje w pliku "file".
* (opcjonalnie) ./main - uruchamia program, który najpiew wczytuje nazwe pliku i znak a następnie robi to wyżej napisane...

# [ENGLISH]
Exercise 2 (25%) 

a) Using the functions of the C library: fread () and fwrite ().

Write a program that takes 2 command line arguments.
The first argument is a character, the second is a filename. The program should count how many times
the given character is present, and the number of lines in the input file that contain the given character. We assume
that each line in the file ends with a newline character. We assume that no line is longer than 256 characters.

#### How to use:
* make - compiles files to run the program.
* ./main c file - runs the program that counts the number of occurrences of the "c" character and the number of lines in which it appears in the "file" file.
* (optional) ./main - runs the program that reads the filename and character first, then does it as described above ...

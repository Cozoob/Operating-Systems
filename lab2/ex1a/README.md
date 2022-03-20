# [POLISH]
Zadanie 1 (25%)

a) Używając funkcji biblioteki C: fread() i fwrite().

Napisz program, który kopiuje zawartość jednego pliku do drugiego z usuwaniem pustych linii (zawierających tylko "whitespace characters"). 
Jeśli argumentów nie podano, wówczas nazwy plików mają być pobrane od użytkownika.

#### Jak użyć:
* make - kompiluje pliki, aby uruchomić program.
* ./main file1 file2 - uruchamia program, który przepisuje zawartość "file1" bez pustych lini do "file2".
* (opcjonalnie) ./main - uruchamia program, który najpiew wczytuje nazwy plików a następnie z pierwszego pliku przepisuje zawartość do drugiego bez pustych lini.

# [ENGLISH]
Exercise 1 (25%) 

a) Using the functions of the C library: fread () and fwrite ().

Write a program that copies the content of one file to another, deleting blank lines (containing only "whitespace characters"). 
If no arguments are given, then the file names are to be retrieved from the user.

#### How to use:
* make - compiles files to run the program.
* ./main file1 file2 - runs a program which writes the content of "file1" with no blank lines to "file2".
* (optional) ./main - runs the program that reads file names first and then rewrites the content from the first file to the second one without empty lines.

# [POLISH]

Zadanie 3 (40%)

Napisz program, który rozpoczynając od katalogu podanego jako pierwszy parametr uruchomienia, idąc w głąb drzewa katalogów, 
znajdzie pliki zawierające łańcuch podany jako drugi parametr uruchomienia programu. Przeszukiwanie każdego z podkatalogów
powinno odbyć się w osobnym procesie potomnym. Wydruk wyniku wyszukiwania poprzedź wypisaniem ścieżki względnej od katalogu
podanego jako argument uruchomienia oraz numeru PID procesu odpowiedzialnego za przeglądanie określonego (pod)katalogu. 
Przeszukiwanie powinno obejmować pliki tekstowe i pomijać pliki binarne/wykonywalne/obiektowe etc. Program jako trzeci parametr 
powinien przyjmować maksymalną głębokość przeszukiwania licząc od katalogu podanego jako pierwszy parametr.

#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main PATH STRING DEPTH - uruchamia program gdzie dla danej ścieżki PATH szuka łańcuch znaków STRING w pliku na głębokość DEPTH
np.: ./main ~/CLionProjects/lab3SysOpy/Aaa Ada 3
* make clean - czyści dodatkowo utworzone pliki

# [ENGLISH]

Task 3 (40%)

Write a program that, starting from the directory given as the first parameter, and going deeper into the directory tree, 
will find files containing the string given as the second parameter. Each subdirectory should be searched in a separate child process.
Before printing the search result, print the relative path from the directory given as the starting argument and the PID number of the process
responsible for browsing the specified (sub) directory. Searching should include text files and skip binaries / executables / object files etc.
As the third parameter, the program should assume the maximum depth of the search, counting from the directory given as the first parameter.

#### How to use:
* make - creates files to run the program
* ./main PATH STRING DEPTH - runs the program where for given path PATH it looks for the string STRING in files of maximum depth DEPTH
e.g.: ./main ~/CLionProjects/lab3SysOpy/Aaa Ada 3
* make clean - cleans additionally created files

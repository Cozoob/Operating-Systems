# [POLISH]
Zadanie 1. Alokacja tablicy ze wskaźnikami na bloki pamięci zawierające znaki (25%)

Zaprojektuj i przygotuj zestaw funkcji (bibliotekę) do zarządzania tablicą bloków, w których to blokach pamięci zapisywane są rezultaty operacji zliczania lini, słów i znaków (poleceniem wc) w plikach przekazywanych jako odpowiedni parametr.


Biblioteka powinna umożliwiać:

* utworzenie tablicy wskaźników w której będą przechowywane wskaźniki na bloki pamięci zawierające wyniki 
* przeprowadzenie zliczenia lini, słów i znaków dla zadanych plików i zapisanie wyniku zliczania w pliku tymczasowym
* zarezerwowanie bloku pamięci o rozmiarze odpowiadającym rozmiarowi pliku tymczasowego i zapisanie w tej pamięci jego zawartości, ustawienie w tablicy wskaźników wskazania na ten blok, funkcja powinna zwrócić indeks stworzonego bloku w tablicy,
* usunięcie z pamięci bloku o zadanym indeksie

Tablice / bloki powinny być alokowane przy pomocy funkcji calloc() (alokacja dynamiczna).

Przygotuj plik Makefile, zawierający polecenia kompilujące pliki źródłowe biblioteki oraz tworzące biblioteki w dwóch wersjach: statyczną i współdzieloną.

# [ENGLISH]
Task 1. Allocating an array with pointers to blocks of memory containing characters (25%)

Design and prepare a set of functions (library) for managing an array of blocks, in which memory blocks are saved the results of counting lines, words and characters (with the wc command) in files transferred as an appropriate parameter.


The library should enable:

* creating an array of pointers in which to store pointers to memory blocks containing the results
* carrying out counting lines, words and characters for given files and saving the count result in a temporary file
* reserving a memory block with a size corresponding to the size of the temporary file and saving its contents in this memory, setting an indication of this block in the index table, the function should return the index of the created block in the table,
* removing from memory a block with a given index

Arrays / blocks should be allocated using the calloc () function (dynamic allocation).

Prepare a Makefile containing commands compiling the library source files and creating libraries in two versions: static and shared.

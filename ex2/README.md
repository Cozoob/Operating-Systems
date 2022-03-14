# [POLISH]
Zadanie 2. Program korzystający z biblioteki (25%)

Napisz program testujący działanie funkcji z biblioteki z zadania 1.

Jako argumenty przekaż liczbę elementów tablicy głównej (liczbę par plików) oraz listę zadań do wykonania. Zadania mogą stanowić zadania zliczenia dla wszystkich plików  lub zadania usunięcia bloku o podanym indeksie.

Operacje mogą być specyfikowane w linii poleceń na przykład jak poniżej:

* create_table rozmiar — stworzenie tablicy o rozmiarze "rozmiar"
* wc_files file1.txt file2.txt … — zliczenie dla plików
* remove_block index — usuń z tablicy bloków o indeksie index

Program powinien stworzyć tablice bloków o zadanej liczbie elementów

W programie zmierz, wypisz na konsolę i zapisz do pliku z raportem czasy realizacji podstawowych operacji:

* Przeprowadzenie zliczeń plików — różna wielkość plików (małe, średnie, duże) oraz różna ilość plików na raz (1 - 10)
* Zapisanie, w pamięci, bloków o różnych rozmiarach (odpowiadających rozmiarom różnych przeprowadzonych zliczeń)
* Usunięcie zaalokowanych bloków o różnych rozmiarach  (odpowiadających rozmiarom różnych przeprowadzonych zliczeń)
* Na przemian  kilkakrotne dodanie i usunięcie zadanej liczby bloków 

Mierząc czasy poszczególnych operacji, zapisz trzy wartości: czas rzeczywisty, czas użytkownika i czas systemowy. Rezultaty umieść pliku raport2.txt i dołącz do archiwum zadania.


# [ENGLISH]
Task 2. Program using the library (25%)

Write a program that tests the operation of the functions from the library from task 1.

Pass the number of elements of the main array (the number of pairs of files) and the list of tasks to be performed as arguments. The tasks can be a count task for all files or a delete the block task with a given index.

Operations can be specified on the command line like this:

* create_table size - create an array of size "size"
* wc_files file1.txt file2.txt… - count files
* remove_block index - remove the block of index "index"

The program should create an array of blocks with a given number of elements

In the program, measure, write to the console and save to a file with a report the times of basic operations:

* Performing file counts - different file sizes (small, medium, large) and a different number of files at once (1 - 10)
* Store, in memory, blocks of different sizes (corresponding to the sizes of the different counts performed)
* Removal of allocated blocks of different sizes (corresponding to the sizes of different counts performed)
* Multiple additions and deletions of a given number of blocks alternately

As you measure times for individual operations, write down three values: real time, user time, and system time. Place the results in the report2.txt file and attach it to the task archive.

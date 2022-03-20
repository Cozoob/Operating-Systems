# [POLISH]
Zadanie 3 (50%)

a) Korzystając z funkcji opendir(), readdir() oraz funkcji z rodziny stat (25%).

Napisz program, który będzie przeglądał katalog podany jako argument i kolejno wszystkie jego podkatalogi. 
Program ma wypisać na standardowe wyjście następujące informacje o znalezionych plikach:

* Ścieżka bezwzględna pliku,
* Liczbę dowiązań,
* Rodzaj pliku (zwykły plik - file, katalog - dir, urządzenie znakowe - char dev, urządzenie blokowe - block dev, potok nazwany - fifo, link symboliczny - slink, soket - sock),
* Rozmiar w bajtach,
* Datę ostatniego dostępu,
* Datę ostatniej modyfikacji.

Na koniec ma wypisać na standardowe wyjście informacje o liczbach plików poszczególnych rodzajów, zawartych w tym katalogu i wszystkich jego podkatalogach. Powinny zostać zliczone: zwykłe pliki, katalogi, pliki specjalne znakowe, pliki specjalne blokowe, potoki/kolejki FIFO, linki symboliczne i sokety. 

Ścieżka podana jako argument wywołania może być względna lub bezwzględna. Program nie powinien podążać za dowiązaniami symbolicznymi do katalogów.

#### Jak użyć:
* make - kompiluje pliki, aby uruchomić program.
* ...

# [ENGLISH]
Exercise 3 (50%)

a) Using the functions opendir (), readdir () and functions from the stat family (25%).

Write a program that will browse the directory given as argument and all its subdirectories one by one.
The program should write to the standard output the following information about the files found:

* Absolute path of the file,
* The number of links,
* File type (regular file - file, directory - dir, character device - char dev, block device - block dev, named pipe - fifo, symbolic link - slink, sockets - sock),
* Size in bytes,
* Last access date,
* Date of last modification.

Finally, it should write to the standard output information about the number of files of each type, contained in this directory and all its subdirectories. Should be counted: regular files, directories, character special files, block special files, FIFO pipes / queues, symbolic links and sockets.

The path given as a call argument can be relative or absolute. The program should not follow symbolic links to directories.

#### How to use:
* make - compiles files to run the program.
* ...

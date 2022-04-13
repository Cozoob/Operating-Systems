# [POLISH]

Zadanie 1 (40%)

Napisz interpreter poleceń przechowywanych w pliku. Ścieżka do pliku to pierwszy argument wywołania programu.

Polecenia w pliku przechowywane  w następującej postaci: 

Definicja składników
składnik1 = prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progN arg1 ... argnN
składnik2 = prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progM arg1 ... argnM
...
składnikK = prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progZ arg1 ... argnZ

Wykonanie potoku
składnik1 | składnik2 | składnikK

Przykład

składnik1 = cat /etc/passwd | wc -l
składnik2 = ls | grep '^a'
składnik3 = grep 11

składnik1 | składnik3 # ⇔ cat /etc/passwd | wc -l | grep 11 
składnik1             # ⇔ cat /etc/passwd | wc -l
składnik2             # ⇔ ls | grep '^a'

Interpreter powinien uruchomić wszystkie polecenia w osobnych procesach, zapewniając przy użyciu potoków nienazwanych oraz funkcji dup2(), by wyjście standardowe procesu k było przekierowane do wejścia standardowego procesu (k+1)
Można założyć ograniczenie górne na ilość obsługiwanych argumentów oraz ilość połączonych komend w pojedynczym poleceniu (co najmniej 3).
Po uruchomieniu ciągu programów składających się na pojedyncze polecenie (linijkę) interpreter powinien oczekiwać na zakończenie wszystkich tych programów.

Program należy zaimplementować, korzystając z funkcji: pipe(), fork() oraz exec().

#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main - uruchamia program
* make clean - czyści dodatkowo utworzone pliki
* make test - uruchomienie przykładu

# [ENGLISH]

Exercise 1 (40%)

Write an interpreter for the commands stored in the file. The file path is the first argument of calling the program.

File commands stored as follows:

Definition of ingredients
component1 = prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progN arg1 ... argnN
component2 = prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progM arg1 ... argnM
...
K component = prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progZ arg1 ... argnZ

Pipe execution
component1 | component2 | component K.

Example

component1 = cat / etc / passwd | wc -l
component2 = ls | grep '^ a'
component3 = grep 11

component1 | component3 # ⇔ cat / etc / passwd | wc -l | grep 11
component1 # ⇔ cat / etc / passwd | wc -l
component2 # ⇔ ls | grep '^ a'

The interpreter should run all commands in separate processes, ensuring using unnamed pipes and the dup2 () function that the standard output of k is redirected to the standard input of the process (k + 1)
You can assume an upper limit on the number of supported arguments and the number of combined commands in a single command (at least 3).
After running a sequence of programs that make up a single command (a line), the interpreter should wait for all these programs to finish.

The program should be implemented using the functions: pipe (), fork () and exec ().

#### How to use:
* make - creates files to run the program
* ./main - runs the program
* make clean - cleans additionally created files
* make test - run an example

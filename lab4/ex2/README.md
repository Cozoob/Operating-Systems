# [POLISH]

Zadanie 2 (20%)

Przetestuj działanie trzech wybranych flag w funkcji sigation. Jedną z nich powinna być flaga SA_SIGINFO. 
Dla tej flagi zainstaluj procedurę obsługi sygnału (handler) dla odpowiednio dobranych sygnałów stosując składnie procedury 
handlera z trzema argumentami. Wypisz i skomentuj (przygotowując odpowiednie scenariusze) trzy różne informacje, a dodatkowo 
także numer sygnału oraz identyfikator PID procesu wysyłającego dostarczane w strukturze siginfo_t przekazywanej jako drugi argument funkcji handlera.

#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main - uruchamia program
* make clean - czyści dodatkowo utworzone pliki

# [ENGLISH]

Exercise 2 (20%)

Test the operation of the three selected flags in the sigation function. One of them should be the SA_SIGINFO flag.
For this flag, install the signal handler (handler) for appropriately selected signals using the procedure syntax
handler with three arguments. List and comment (preparing appropriate scenarios) three different pieces of information, plus
also the signal number and the PID of the sending process provided in the siginfo_t structure passed as the second argument of the handler function.

#### How to use:
* make - creates files to run the program
* ./main - runs the program
* make clean - cleans additionally created files

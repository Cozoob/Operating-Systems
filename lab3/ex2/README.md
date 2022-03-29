# [POLISH]

Napisz program, który liczy numerycznie wartość całki oznaczonej z funkcji 4/(x^2+1) w przedziale od 0 do 1 metodą prostokątów 
(z definicji całki oznaczonej Riemanna). Pierwszy parametr programu to szerokość każdego prostokąta, określająca dokładność obliczeń. 
Obliczenia należy rozdzielić na n procesów potomnych (n drugi parametr wywołania programu). Każdy z procesów powinien wynik swojej części
obliczeń wpisywać do pliku o nazwie "wN.txt" , gdzie N oznacza numer procesu potomnego liczony od 1 i nadawany procesom w kolejności ich tworzenia.
Proces macierzysty powinien oczekiwać na zakończenie wszystkich procesów potomnych po czym powinien dodać wyniki cząstkowe z plików stworzonych 
przez wszystkie procesy potomne i wyświetlić wynik na standardowym wyjściu. W programie zmierz, wypisz na konsolę i zapisz do pliku z raportem 
czasy realizacji dla różnej liczby procesów potomnych oraz różnych dokładności obliczeń. Dokładności obliczeń należy dobrać w ten sposób by obliczenia
trwały co najmniej kilka sekund.

#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main STEP N- uruchamia program dla N procesów-dzieci o kroku STEP
np.: ./main 0.0001 1000
* make clean - czyści dodatkowo utworzone pliki


# [ENGLISH]

Write a program that numerically calculates the value of the definite integral from the function 4/(x^2+1) in the range from 0 to 1 
using the rectangle method (from the definition of the Riemann definite integral). The first parameter of the program is the width of each rectangle,
which determines the accuracy of the calculations. The computation should be split into n child processes (n second parameter of the program call).
Each of the processes should write the result of its part of the calculations to a file named "wN.txt", where N stands for a child process number 
counted from 1 and assigned to the processes in the order of their creation. The parent process should wait for all child processes to finish, then 
add partial results from files created by all child processes and display the result on standard output. In the program, measure, write to the 
console and save to a file with a report the execution times for a different number of child processes and different calculation accuracy. 
The accuracy of the calculations should be selected in such a way that the calculations last at least a few seconds.

#### How to use:
* make - creates files to run the program
* ./main STEP N - runs the program for N child processes and for step STEP
e.g.: ./main 0.0001 1000
* make clean - cleans additionally created files

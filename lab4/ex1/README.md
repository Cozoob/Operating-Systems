# [POLISH]

Zadanie 1 (30%)

Napisz program demonstrujący, czy ustawienia dyspozycji dla sygnałów, ich maski oraz czekające sysgnały są dziedziczone po wykonaniu 
funkcji fork oraz exec.

W szczególności eksperymenty proszę wykonać dla sygnału SIGUSR1 w następujący sposób:
* Dziedziczenie ustawień sygnałów po wykonaniu funkcji fork. Proszę napisać program, który w zależności od wartości argumentu 
z linii poleceń, który może przyjmować wartości ignore, handler, mask lub pending, odpowiednio w procesie przodka ustawia 
ignorowanie, instaluje handler obsługujący sygnał wypisujący komunikat o jego otrzymaniu, maskuje ten sygnał oraz sprawdza 
(przy zamaskowaniu tego sygnału) czy wiszący/oczekujący sygnał jest widoczny w procesie, a następnie przy pomocy funkcji raise 
wysyła sygnał do samego siebie oraz wykonuje odpowiednie dla danej opcji działania, po czym tworzy potomka funkcją fork i ponownie
przy pomocy funkcji raise potomek wysyła sygnał do samego siebie (z wyjątkiem opcji pending, gdzie testowane jest sprawdzenie,
czy sygnał czekający w przodku jest widoczny w potomku).
* Dziedziczenie ustawień sygnałów po wykonaniu funkcji exec. W podobny sposób sprawdź jaki wpływ na ustawienia sygnałów ma wywołanie funkcji exec. 
Rozpatrz opcje:  ignore, mask i pending.


#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main OPTION - uruchamia program z argumentem OPTION (ignore/handler/mask/pending)
* make clean - czyści dodatkowo utworzone pliki

# [ENGLISH]

Exercise 1 (30%)

Write a program demonstrating whether the instruction settings for signals, their masks and pending signals are inherited after execution
fork and exec.

In particular, please perform the experiments for the SIGUSR1 signal as follows:
* Inheritance of signal settings after execution of fork function. I would like to write a program that depends on the value of the argument
from the command line, which can take the values ​​ignore, handler, mask or pending in the ancestor process as appropriate
ignore, installs a signal handler that prints the received message, masks the signal and checks
(when masking this signal) whether the hanging / waiting signal is visible in the process and then by the raise function
it sends a signal to itself and performs an appropriate action for the option, then creates a child with fork and again
the child sends a signal to itself with the raise function (except for the pending option, where the call is tested,
whether the signal waiting in the ancestor is visible in the child).
* Inheritance of signal settings after executing the exec function. In a similar way, check what effect calling the exec function has on signal settings.
Consider options: ignore, mask, and pending.

#### How to use:
* make - creates files to run the program
* ./main OPTION - runs the program with the argument OPTION (ignore/handler/mask/pending)
* make clean - cleans additionally created files

# [POLISH]

Zadanie 3 (20%)

Napisz dwa programy: sender program wysyłający sygnały SIGUSR1 i  catcher - program zliczający ilość odebranych sygnałów. 
Ilość sygnałów SIGUSR1 wysyłanych przez pierwszy program powinna być określana w parametrze wywołania tego programu. 
Program catcher jest uruchamiany najpierw, wypisuje swój numer PID i czeka na sygnały SIGUSR1 i SIGUSR2. Wszystkie pozostałe sygnały są blokowane.
Przyjmijmy, że czekanie na sygnały w poszczególnych procesach (w zależności od zadań) odbywa się wywołując funkcję sigsuspend. 
Program sender przyjmuje trzy parametry: PID procesu catcher, ilość sygnałów do wysłania i tryb wysłania sygnałów.

Po transmisji wszystkich sygnałów SIGUSR1 sender powinien wysłać sygnał SIGUSR2, po otrzymaniu którego catcher wysyła do sendera tyle 
sygnałów SIGUSR1, ile sam ich otrzymał a „transmisję” kończy wysłaniem sygnału SIGUSR2, wypisaniem liczby odebranych sygnałów i zakończeniem działania. 
PID sendera catcher pobiera ze struktury  siginfo_t po przechwyceniu od niego sygnału. Program sender po otrzymaniu sygnału SIGUSR2 wyświetla komunikat 
o ilości otrzymanych sygnałów SIGUSR1 oraz o tym, ile powinien ich otrzymać i kończy działanie.

UWAGA! W żaden sposób nie opóźniamy wysyłania sygnałów, wszelkie "gubienie" sygnałów jest zjawiskiem naturalnym.

b) Zmodyfikuj powyższe programy, dodając potwierdzenie odbioru sygnału po każdorazowym ich odebraniu przez program catcher. 
W tym celu, catcher wysyła do sendera sygnał SIGUSR1 informujący o odbiorze sygnału. Sender powinien wysłać kolejny sygnał dopiero po uzyskaniu 
tego potwierdzenia. Zapewnij rozwiązanie, w którym ilość sygnałów odebranych jest zgodna z ilością sygnałów wysłanych, i w którym nie dochodzi do 
zakleszczenia.


#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main - uruchamia program
* make clean - czyści dodatkowo utworzone pliki
* make test - uruchomienie przykładu

# [ENGLISH]

Exercise 3 (20%)

Write two programs: sender program that sends SIGUSR1 signals and catcher - program that counts the number of received signals.
The number of SIGUSR1 signals sent by the first program should be specified in the calling parameter of this program.
The catcher runs first, prints its PID, and waits for SIGUSR1 and SIGUSR2. All other signals are blocked.
Let's assume that waiting for signals in individual processes (depending on the tasks) is performed by calling the sigsuspend function.
The sender program takes three parameters: the PID of the catcher process, the number of signals to send, and the mode to send the signals.

After transmitting all SIGUSR1 signals, the sender should send the SIGUSR2 signal, after receiving which the catcher sends to the sender as many
how many SIGUSR1 signals he received himself and the "transmission" ends with sending the SIGUSR2 signal, writing out the number of received signals and finishing the operation.
The sender's PID catcher gets from the siginfo_t structure after catching the signal from it. When sender receives a SIGUSR2 signal, it displays a message
about the number of SIGUSR1 signals received and how many it should receive, and it finishes running.

ATTENTION! We do not delay the sending of signals in any way, any "loss" of signals is a natural phenomenon.

b) Modify the above programs by adding a signal receipt each time the catcher receives them. For this, the catcher sends a SIGUSR1 signal to the sender
informing about the reception of the signal. The sender should send another signal only after receiving this confirmation. Provide a solution where 
the number of signals received matches the number of signals sent, and no deadlock occurs.

#### How to use:
* make - creates files to run the program
* ./main - runs the program
* make clean - cleans additionally created files
* make test - runs the examplary command

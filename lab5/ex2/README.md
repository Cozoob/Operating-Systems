# [POLISH]

Zadanie 2 (20%)

Napisać program przyjmujący jeden (nadawca lub data) lub trzy argumenty (\<adresEmail\> \<tytuł\> \<treść\>):

* W przypadku wywołania z jednym argumentem uruchamiany jest (za pomocą popen()) program mail. 
  Program użytkownika ma wypisywać listę e-maili posortowaną alfabetycznie wg. adresów e-mail (argument nadawca) lub wg. daty otrzymania e-maili 
  (argument data)
* Jeżeli program zostanie wywołany z trzema argumentami, to (za pomocą popen()) uruchamiany jest program mail i za jego pomocą wysyłany jest e-mail 
  do określonego nadawcy z określonym tematem i treścią
  
#### Jak użyć:
* make - tworzy pliki do uruchomienia programu
* ./main - uruchamia program
* make clean - czyści dodatkowo utworzone pliki
  
# [ENGLISH]
Exercise 2 (20%)

Write a program that accepts one (sender or date) or three arguments (\<mailaddress\> <title> \<content\>):

* When invoked with one argument, the mail program is started (with popen ()).
   The user program is to print a list of e-mails sorted alphabetically by. e-mail addresses (sender argument) or by the date the e-mails were received
   (argument date)
* If the program is called with three arguments, then (using popen ()) the mail program is started and the e-mail is sent with it
   to a specific sender with a specific subject and content
  
#### How to use:
* make - creates files to run the program
* ./main - runs the program
* make clean - cleans additionally created files

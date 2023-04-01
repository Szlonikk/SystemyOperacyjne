========================================================================
Autor: Jakub Bednarz,                               Krakow, 26.03.2022
========================================================================

* Zawartosc:
============

Katalog zad2 zawiera 2 kody źródłowe do 1 zadania z ćw2
plik Makefile



------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
programu, a takze czyszczenia katalogu
i jego archiwizacji.

-> Aby uruchomic  program, nalezy wykonac komende:
       make
       następnie komende
       make procesy
       i na końcu komende
       make runb argument=./procesy.x

---> Dla pewnosci, ze wykonywane sa polecenia zdefiniowane w Makefile,
     a nie wbudowane polecenia make'a, uzyc opcji -r


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

       ODPOWIEDZ NA PYTANIE
        Powstanie n procesow

========================================================================

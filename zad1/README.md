# ĆWICZENIE 1: Procesy Potomne: fork

## Treść zadania

### Podpunkt (a)

Napisać program wypisujący identyfikatory UID, GID, PID, PPID i PGID dla danego procesu.

### Podpunkt (b)

Wywołać funkcję fork trzy razy (najlepiej w pętli for) i wypisać powyższe identyfikatory dla procesu macierzystego oraz wszystkich procesów potomnych.
Przy pomocy funkcji wait sprawić, aby proces macierzysty zaczekał na zakończenie wszystkich procesów potomnych.

### Podpunkt (c)

Jak w (b), tylko przy użyciu funkcji sleep (nie używać funkcji wait) sprawiać by procesy potomne były adoptowane przez proces init lub systemd;
poleceniem pstree -p z poziomu powłoki wyswietlić drzewo procesów w danym systemie i zidentyfikować proces adoptujący osierocone procesy.

### Podpunkt (d)

Jak w (b), tylko wstawić funkcję sleep w takich miejscach programu, aby procesy pojawiały się na ekranie grupowane pokoleniami od najstarszego do najmłodszego, a proces macierzysty kończył się dopiero po procesach potomnych (nie używać funkcji wait).

Na podstawie wyników programu sporządzić (w pliku tekstowym) "drzewo genealogiczne" tworzonych procesów z zaznaczonymi identyfikatorami PID, PPID i PGID.

### Podpunkt (e)

Jak w (b), tylko przy użyciu fukcji `setpgid` sprawić by każdy proces potomny stawał się liderem swojej własnej grupy procesów.

Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?

W celu narysowania drzewa genealogicznego procesów, najpierw skopiować do pliku tekstowego wydruk na ekranie z przykładowego uruchomienia programu, a następnie w kolejnych liniach wypisać wartości(PID,PPID,PGID) procesów z kolejnych pokoleń i połączyć je kreskami, np.

```text
                  (PID1,PPID1,PGID1)

             |                         |

    (PID2a,PPID2a,PGID2a)      (PID2b,PPID2b,PGID2b)
```
 
========================================================================
Autor: Jakub Bednarz,                               Krakow, 21.03.2022
========================================================================

* Zawartosc:
============
5 programów w języku C rozwiązujących zadania z zestawu pierwszego:
a.c
b.c
c.c
d.c
e.c

Plik nagłówkowy procesy.h zawierający funkcję wyświetlającą PID,UID,PPID,GID,PGID

Program Makefile kompilujący wszystkie zadania przy pomocy polecenia: make all
Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac: make clean
Aby zarchiwizować i kompresować zawartość katalogu należy użyć polecenia: make tar

Aby uruchamiać kolejne programy używać polecenia ./(nazwaprogramu)

Plik tekstowy z odpowiedziami na pytania: odpowiedzi.txt

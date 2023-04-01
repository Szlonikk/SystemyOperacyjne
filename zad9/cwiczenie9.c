#define _REENTRANT
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "watki.h"

#define max_liczba_watkow 10

int wynik;
unsigned int liczba_watkow;
unsigned int liczba_sekcji;
pthread_t watki[max_liczba_watkow];
pthread_mutex_t mutex;
const double min_dlugosc_czekania = 1.0;
const double max_dlugosc_czekania = 4.0 - min_dlugosc_czekania;

void ustaw_kursor (unsigned x, unsigned y) {
	printf ("\033[%d;%dH\033[2K", y, x);
}

void *watek_start (void *argument) {
	
	int licznik = 0;
	int numer_watku = *(int *)argument;
	srand (time (NULL));
	
	printf ("Wątek nr: %d, ID: %ld \n", numer_watku + 1, watki[numer_watku]);
	
	sleep (1);
	
	for (int i = 0; i < liczba_sekcji; i++) {
		
		ustaw_kursor (0, 4 + liczba_watkow + numer_watku);
		printf("\033[32mWatek nr: %d, SP: %d, wynik: %d \033[0m\n", numer_watku + 1, i + 1, wynik);
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);
		
		// sekcja krytyczna
		zamknij_mutex(&mutex);
		
		ustaw_kursor (25, 4 + liczba_watkow + numer_watku);
		printf("\033[1;31mWatek nr: %d, SK: %d, wynik: %d \033[0m\n", numer_watku + 1, i + 1, wynik);
		
		// dodaj 1 do liczby
		licznik = wynik;
		licznik++;
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);
		
		wynik = licznik;
		
		// koniec sekcji krytycznej
		otworz_mutex (&mutex);
		
		ustaw_kursor (0, 4 + liczba_watkow + numer_watku);
		printf("\033[32mWatek nr: %d, SP: %d, wynik: %d \033[0m\n", numer_watku + 1, i + 1, wynik);
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);
	}
	
	return 0;
}

int main (int argc, char *argv[]) {
	
	// sprawdzenie poprawności argumentów
	if (argc != 3) {
		printf ("Wywolaj program wpisujac: %s ilosc_watkow ilosc_sekcji\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	
	liczba_watkow = atoi(argv[1]);
	if (liczba_watkow > max_liczba_watkow) {
		printf ("Za duzo watkow, max %d!\n",max_liczba_watkow);
		exit (EXIT_FAILURE);
	}
	liczba_sekcji = atoi(argv[2]);
	
	inicjalizuj_mutex (&mutex);
	printf("Zainicjalizowano mutex o adresie %p\n", (void *)&mutex);
	
	wynik = 0;
	
	// utwórz podaną liczbę wątków
	for (int i = 0; i < liczba_watkow; i++) {
		
		int *pamiec = malloc (sizeof (int));
		*pamiec = i;
		
		// utwórz wątek i przekaż mu jako argument jego numer
		sleep ((double)i/liczba_watkow);
		watki[i] = utworz_watek (watek_start, (void *)pamiec);
	}
	
	// czekaj na zakończenie wątków
	for (int i = 0; i < liczba_watkow; i++) {
		polacz_watek (watki[i]);
	}
	
	ustaw_kursor (0, 4 + liczba_watkow * 2);
	
	// sprawdź czy synchronizacja się powiodła
	if (wynik != liczba_watkow * liczba_sekcji) {
		printf ("Porazka!\nOczekiwano: %d\nOtrzymano: %d\n", (liczba_watkow * liczba_sekcji), wynik);
	} else {
		printf ("Sukces!\nOtrzymano: %d\n",wynik);
	}
	
	usun_mutex (&mutex);
	
	return 0;
}

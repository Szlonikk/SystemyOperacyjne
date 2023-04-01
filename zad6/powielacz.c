#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define SCIEZKA "./"

/*
	Program powielacz tworzy podaną ilość kopii programu inkrementator który implementuje problem korzystania z zasobu współdzielonego
*/

char nazwa_semafora[20];
bool synchronizacja;

void wyjscie() {
	if (synchronizacja) {
		usun_semafor (nazwa_semafora);
	}
}

void sygnal_wyjscie(int signal) {
	if (synchronizacja) {
		printf ("Sygnał przerwania, usuwanie semafora\n");
		usun_semafor (nazwa_semafora);
	}
	_exit(EXIT_SUCCESS);
}

// argumenty [0] nazwa_programu [1] nazwa_podprogramu [2] ilosc_inkrementatorow [3] ilosc_sekcji_krytycznych [4] plik_we_wy [5] nazwa_semafora [6] synchronizacja
int main (int argc, char *argv[]) {
	
	// sprawdzenie poprawności argumentów
	if (argc != 7) {
		printf ("Wywołaj program wpisując: ./() nazwa_podprogramu ilosc_inkrementatorow ilosc_sekcji_krytycznych plik_we_wy nazwa_semafora czy_synchronizowac\n");
		exit (EXIT_FAILURE);
	}
	
	// obsługa atexit
	if (atexit (wyjscie) != 0) {
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	
	// obsługa sygnału ctrl+c
	if (signal (SIGINT, sygnal_wyjscie) == SIG_ERR) {
		perror("Signal error");
		exit(EXIT_FAILURE);
	}
	
	int ilosc_inkrementatorow;
	int plik;
	
	char temp[strlen(SCIEZKA) + strlen(argv[1]) + 1]; // ścieżka połączona z nazwą pliku
	
	ilosc_inkrementatorow = atoi (argv[2]);
	
	strcpy (nazwa_semafora, argv[5]);
	
	if (atoi (argv[6]) == 0) {
		synchronizacja = false;
	} else {
		synchronizacja = true;
	}
	
	// stwórz plik
	if ((plik = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
		printf ("Error otwarcia pliku %s do odczytu", argv[4]);
		perror ("Plik open error");
		exit (EXIT_FAILURE);
	}
	
	if (write (plik, "0", 2) == -1){
		perror("Plik write error");
		exit(EXIT_FAILURE);
	}
	
	if (close (plik) == -1) {
		perror ("Plik close error");
		exit (EXIT_FAILURE);
	}
	
	if (synchronizacja) {
		sem_t *semafor = stworz_semafor (nazwa_semafora);
		int wartosc_semafora;
		wartosc_semafor (semafor, &wartosc_semafora);
		printf ("Utworzono semafor %s (%p) o wartości %d\n", nazwa_semafora, (void *)semafor, wartosc_semafora);
	}
	
	for (int i = 0; i < ilosc_inkrementatorow; i++) {
		
		switch (fork ()) {
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				/* akcja dla procesu potomnego */
				
				sprintf (temp, "%s%s", SCIEZKA, argv[1]);
				execl (temp, argv[1], argv[3], argv[4], argv[5], argv[6], NULL); // uruchom inkrementator
				perror ("execl error");
				exit(EXIT_FAILURE);
				
				break;
				
			default:
				/* akcja dla procesu macierzystego */
				
				break;
				
		}
	}
	
	// Oczekiwanie na procesy potomne
	
	for (int i = 0; i < ilosc_inkrementatorow; i++) {
		if (wait (NULL) == -1) {
			perror ("Wait error");
			exit (EXIT_FAILURE);
		}
	}
	
	if ((plik = open (argv[4], O_RDONLY, 0644)) == -1) {
		printf ("Error otwarcia pliku %s do odczytu", argv[4]);
		perror ("Plik open error");
		exit (EXIT_FAILURE);
	}
	
	int odczyt;
	char bufor[10];
	
	odczyt = read(plik, &bufor, 10);
	if (odczyt == -1) {
		printf("Plik read error");
		exit(EXIT_FAILURE);
	} else if (odczyt == 0) {
		printf("Pusty plik error");
		exit(EXIT_FAILURE);
	} else {
		bufor [odczyt] = '\0';
		if (atoi(bufor) == (atoi (argv[2]) * atoi (argv[3]))) {
			printf ("\nKoniec powielania! Wynik: %s\n", bufor);
		} else {
			printf ("\nPorazka! Wynik: %s, oczekiwano: %d\n", bufor, (ilosc_inkrementatorow) * atoi (argv[3]));
		}
	}
	
	if (close (plik) == -1) {
		perror ("Plik close error");
		exit (EXIT_FAILURE);
	}
	
	return 0;
}
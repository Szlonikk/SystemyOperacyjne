#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include "kolejki.h"

mqd_t serwer;

void wyjscie(void) {
	kolejka_zamknij (serwer);
}

void sygnal_wyjscie(int signal) {
	printf ("\nSygnal przerwania, zamykanie i usuwanie kolejki\n");
	exit(EXIT_SUCCESS);
}

int main () {
	
	char kolejka_odpowiedz_nazwa[10];
	mqd_t kolejka_odpowiedz;
	char dzialanie[DLUGOSC_KOMUNIKATU];
	char tekst[DLUGOSC_KOMUNIKATU+10];
	const double max_dlugosc_czekania = 4.0;
	
	sprintf (kolejka_odpowiedz_nazwa, "/%d", getpid());
	
	// zaczekaj chwile zanim serwer się uruchomi
	sleep (1);
	
	serwer = kolejka_otworz (KOLEJKA_NAZWA, O_WRONLY);
	
	{
		struct mq_attr atrybuty = kolejka_pobierz_atrybuty (serwer);
		printf ("Otworzono kolejke \"%s\" o deskryptorze %d\n", KOLEJKA_NAZWA, serwer);
		printf ("mq_flags: = %ld\n", atrybuty.mq_flags);
		printf ("mq_maxmsg: = %ld\n", atrybuty.mq_maxmsg);
		printf ("mq_msgsize: = %ld\n", atrybuty.mq_msgsize);
		printf ("mq_curmsgs: = %ld\n\n", atrybuty.mq_curmsgs);
	}
	
	if (atexit (wyjscie) != 0) {
		perror("atexit error");
		_exit(EXIT_FAILURE);
	}
	
	if (signal (SIGINT,sygnal_wyjscie) == SIG_ERR) {
		perror("signal error");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	// czekaj losową ilość czasu
	sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);
	
	while (1) {
		
		// wpisz działanie
		printf ("Wpisz dzialanie\n");
		if (scanf ("%s", dzialanie) == EOF) {
			
			printf ("\n========================================================\n");
			printf ("koniec polecen!\n");
			exit(EXIT_SUCCESS);
		}
		// dopisz PID do komunikatu
		sprintf(tekst, "%d %s", getpid(), dzialanie);
		
		// wyślij zapytanie na serwer
		kolejka_wyslij(serwer, tekst, 1);
		printf ("\nWyslano dzialanie do serwera: %s\n", tekst);
		
		// utwórz kolejkę do odebrania odpowiedzi
		kolejka_odpowiedz = kolejka_utworz (kolejka_odpowiedz_nazwa, O_RDONLY);
		
		// oczekuj na odpowiedź z serwera
		printf ("Oczekiwanie na odpowiedz z serwera\n");
		kolejka_odbierz (kolejka_odpowiedz, tekst, NULL);
		printf ("Odpowiedz z serwera: %s\n\n", tekst);
		
		// zamknij i usuń kolejkę do odebrania odpowiedzi
		kolejka_zamknij (kolejka_odpowiedz);
		kolejka_usun (kolejka_odpowiedz_nazwa);
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);
	}
	
	// zamknij kolejkę serwera
	kolejka_zamknij (serwer);
		
	printf ("\nKlient: koniec procesu\n");
	
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	
	char buf[1024];
	char komunikat[1038];
	int plik;
	int potok;
	int odczyt;
	const size_t rozmiarDanychProducent = 50; // maks 1024
	const double maxDlugoscCzekania = 2.0;
	
	
	if (argc != 3) {
		
		printf ("Wywołaj program wpisując: ./ plik_we potok\n");
		exit (EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	if ((plik = open (argv[1], O_RDONLY, 0644)) == -1) {
		printf ("Błąd otwarcia pliku %s do odczytu\n", argv[1]);
		perror ("Plik - error");
		exit (EXIT_FAILURE);
	}
	
	if ((potok = open (argv[2], O_WRONLY, 0644)) == -1) {
		printf ("Błąd otwarcia potoku %s do odczytu\n", argv[2]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	
	// zapisywanie wyprodukowanych produktów do potoku
	while (1) {
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(maxDlugoscCzekania * 100)) / 100);
		
		odczyt = read(plik, &buf, rozmiarDanychProducent);
		if (odczyt == -1) {
			printf("Błąd odczytu z pliku\n");
			exit(EXIT_FAILURE);
		} else if (odczyt == 0) {
            printf("\nKoniec pliku producenta\n");
			break;
		} else {
			write (potok, &buf, odczyt);
			buf [odczyt] = '\0';
			sprintf (komunikat, "%s%s%s", "Produkcje: ", buf, "\n");
			write (STDOUT_FILENO, komunikat, strlen(komunikat));
		}
	}
	
	if (close (plik) == -1) {
		perror ("Zamykanie pliku wyjscia - error");
		exit (EXIT_FAILURE);
	}
	
	if (close (potok) == -1) {
		perror ("Zamykanie potoku - error");
		exit (EXIT_FAILURE);
	}
	
	return 0;
}
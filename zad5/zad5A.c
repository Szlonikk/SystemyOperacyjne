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
#include <signal.h>

char potok[20];
void wyjscie(void) {
	unlink (potok);
}

void sygnal_wyjscie(int signal) {
	printf ("Przerwanie - usuwanie potoku\n");
	exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[]) {

	char sciezka[100] = "./";
	strcpy (potok, argv[5]);
	

	if (argc != 6) {
		
		printf ("Wywołaj program wpisując: ./ prog_producent prog_konsument plik_we plik_wy potok\n");
		_exit (EXIT_FAILURE);
	}
	
	if (mkfifo(argv[5], 0644) == -1) {
		perror("Mkfifo error");
		_exit (EXIT_FAILURE);
	}
	
	if (atexit (wyjscie) != 0) {
		perror("Atexit error");
		_exit(EXIT_FAILURE);
	}
	
	if (signal (SIGINT,sygnal_wyjscie) == SIG_ERR) {
		perror("Signal error");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	for (int i = 0; i < 2; i++) {
		
		switch (fork ()) {
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				/* akcja dla procesu potomnego */
				
				if (i == 0) {
					char temp[100];
					sprintf (temp, "%s%s", sciezka, argv[1]);
					execl (temp, argv[1], argv[3], argv[5], NULL); // urucham program producenta
				} else {
					char temp[100];
					sprintf (temp, "%s%s", sciezka, argv[2]);
					execl (temp, argv[2], argv[4], argv[5], NULL); // urucham program konsumenta
				}
				
				break;
				
			default:
				/* akcja dla procesu macierzystego */
				
				break;
				
		}
	}
	
	// Oczekiwanie na procesy potomne
	
	while(wait (NULL) == 0) {
        if(wait(NULL)==-1){
		perror ("Wait - error");
		_exit (EXIT_FAILURE);
        }
	}
	
	
	
	return 0;
}

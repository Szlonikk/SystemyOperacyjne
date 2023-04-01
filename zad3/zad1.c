#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sig_hand(int syg)
{
    printf("PID: %d\n", getpid());
    printf("dotarl sygnal: %d.\n", syg);
    printf("proces zostal zabity\n");
}

int main(int argc, char *argv[])
{

    char *parametr = argv[1];
    int syg = atol(argv[2]);
    

    if (argc != 3 )
    { 
        printf("aby uruchomic, wpisz: ./nazwa programu <operacja dla sygnalu> [nr_sygnalu]\n");
        printf("parametry:\n k - operacja domyslna\n i - ignorowanie\n s - obsluga wlasna\n");
        fprintf(stderr, "niepoprawna liczba argumentow!\n");
        exit(1);
    }
    if (strcmp(parametr, "k") == 0)
    {
        if (signal(syg, SIG_DFL) == SIG_ERR)
        {
            perror("operacja zakonczona niepowodzeniem\n");
            exit(1);
        }
        else
        {
            
            
            exit(EXIT_SUCCESS);
        }
    }
    else if (strcmp(parametr, "i") == 0)
    {
        if (signal(syg, SIG_IGN) == SIG_ERR)
        {
            perror("operacja zakonczona niepowodzeniem\n");
            exit(1);
        }
        else
        {
            
            exit(EXIT_SUCCESS);
        }
    }
    else if (strcmp(parametr, "s") == 0)
    {
        if (signal(syg, sig_hand) != SIG_ERR)
        {
            perror("operacja zakonczona niepowodzeniem\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            sig_hand(syg);
            exit(EXIT_SUCCESS);
        }
    }
    else
    {
        pause();
    }
    return 0;
}

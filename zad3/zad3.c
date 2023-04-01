#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>


int main(int argc, char *argv[])
{
    int kill(pid_t pid, int sig);
    char *parametr = argv[1]; //przechowuje instrukcje
    int syg = atol(argv[2]);    //numer sygnalu

    int i = 0;
    if (argc != 3)
    {
        fprintf(stderr, "zla liczba argumnetow!\n");
        exit(1);
    }

    do
    {
        switch (fork())
        {
        case -1:
            perror("Execl - error\n");
            exit(1);
            break;
        case 0:
            execl("zad1", "zad1.c", parametr, syg, NULL); 
            break;
        default:
            wait(NULL);
            break;
        }
        i++;
    } while (i < 3);
    sleep(2);

    printf("sygnal %d wyslany do grupy procesow o ID: %d\n", syg, getpgrp());
    kill(-getpgrp(), syg);
    while (wait(NULL)>0)
    {
        printf("Ostatni proces!\n");
    }
    return 0;
}
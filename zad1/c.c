#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include "procesy.h"
int main()
{
   
    int i;
   


    // printf("\nPorces macierzysty: \n");
    printf("\n\nSTART!\n\n");
    procesy();
    // printf("\nPorces potomny: \n");

    for (i = 1; i <= 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("FORK ERROR!");
            exit(EXIT_FAILURE);
            break;
        case 0:
            sleep(6-i);
            procesy();
            break;
            
        default:

            break;
        };
    }

}

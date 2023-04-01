#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define PATH "./"
#define PATHNAME_MAX 4096
#define FILENAME_MAX 4096
void procesy(){
    printf("\n UID = %i\n GID = %i\n PID = %i\n PPID = %i\n PGID = %i\n", getuid(), getgid(), getpid(),getppid(),getpgid(getpid()))  ;
}

int main(int argc, char *argv[])
{
   
    int i;
    char pathName[PATHNAME_MAX];
    char fileName[FILENAME_MAX];
    if (argc != 2)
    {
        exit(1);
    }
    else
    {
        strcpy(fileName, argv[1]);
        sprintf(pathName, "%s%s", PATH, fileName);
    }


    // printf("\nPorces macierzysty: \n");
    printf("\n\nSTART!\n\n");
    procesy();
    // printf("\nPorces potomny: \n");

    printf("\nProcesy Potomne!\n\n");
    for (i = 1; i <= 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("FORK ERROR!");
            exit(EXIT_FAILURE);
            break;
        case 0:
            execlp(pathName, fileName,NULL);
            perror("EXECLP ERROR");
            _exit(2);
            
            
            break;
            
        default:
           
            if(wait(NULL)==-1){
                perror("WAIT ERROR");
                    exit(1);
            }
            
            break;
        };
    }
    
}

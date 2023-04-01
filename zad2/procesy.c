#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    printf("\n UID = %i\n GID = %i\n PID = %i\n PPID = %i\n PGID = %i\n", getuid(), getgid(), getpid(),getppid(),getpgid(getpid()))  ;
}
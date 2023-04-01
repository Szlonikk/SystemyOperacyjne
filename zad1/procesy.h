#ifndef PROCESY_H   
#define PROCESY_H 
void procesy(){
    printf("\n UID = %i\n GID = %i\n PID = %i\n PPID = %i\n PGID = %i\n", getuid(), getgid(), getpid(),getppid(),getpgid(getpid()))  ;
}
#endif

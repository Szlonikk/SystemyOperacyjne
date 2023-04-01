#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
 
 
 
int main(int argc, char *argv[]){
 
char *parametr = argv[1]; 
int syg = atol(argv[2]); /*nr sygnalu*/
int pid=fork(); /*proces potomny*/
int kill(pid_t pid, int sig);/*def kill'a*/

if (argc != 3) {
fprintf(stderr,"za malo argumentow!\n");
exit (1); }
 
switch(pid){
case -1:
perror("blad execl\n"); 
exit(EXIT_FAILURE);
break;
case 0:
if(execl("zad1","zad1.c",parametr,syg, NULL)!= -1){ 
perror("blad execl\n");
exit(EXIT_FAILURE);
}
break;
default:
sleep(1);

if(kill(pid,syg)<0 || kill(pid,syg)<0) /*wysyla sygnal za pomoca kill()*/
{
    perror("Kill - error");
    exit(EXIT_FAILURE);
}
break;
}
 
return 0;
 
}
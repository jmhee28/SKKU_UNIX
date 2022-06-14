#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
int count=0;
int N;
pid_t pid;
void sig_cont(int sig)
{
    printf("SIGCONT caught\n");
}
void sig_int(int sig)
{
    count++;
	if(count ==N)
        kill(0,SIGKILL);
    signal(SIGINT, sig_int);
}
 void sig_quit(int sig)
{
    
    printf("SIGQUIT caught, will be ignored\n");
    
} 
void sig_stop(int sig)
{
    printf("SIGTSTP caught. This process will stop\n");
    kill(0,SIGSTOP);
} 

int main(int argc, char** argv)
{
    N = atoi(argv[1]); 
    signal(SIGINT, sig_int);
    signal(SIGCONT,sig_cont);
    signal(SIGQUIT, sig_quit);
    signal(SIGTSTP, sig_stop);
    
    while (1) ;
    return 0;
}

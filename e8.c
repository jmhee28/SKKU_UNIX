#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int status;
    int i;
    char *l_args[] = {"ls", "-l", NULL};
    char *grep_args[] = {"grep", argv[1], NULL};
    char *wc_args[] = {"wc", NULL};
    int pipes[4];
    pipe(pipes);
    pipe(pipes + 2);
    if (fork() == 0)
    {
        dup2(pipes[1], 1);
        close(pipes[0]);
        close(pipes[1]);
        close(pipes[2]);
        close(pipes[3]);

        execvp(*l_args, l_args);
    }
    else
    {

        if (fork() == 0)
        {

            dup2(pipes[0], 0);

            dup2(pipes[3], 1);

            close(pipes[0]);
            close(pipes[1]);
            close(pipes[2]);
            close(pipes[3]);

            execvp(*grep_args, grep_args);
        }
        else
        {
            if (fork() == 0)
            {
                dup2(pipes[2], 0);
                close(pipes[0]);
                close(pipes[1]);
                close(pipes[2]);
                close(pipes[3]);

                execvp(*wc_args, wc_args);
            }
        }
    }

    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);

    for (i = 0; i < 3; i++)
        wait(&status);
}
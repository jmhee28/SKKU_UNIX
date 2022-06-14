#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
    int stat = 0;
    while (1) {
        if (fork() == 0) {
            char* cmd = NULL;
            size_t size = 0;
            getline(&cmd, &size, stdin);
            cmd[strlen(cmd) - 1] = '\0';
                        
            char* ptr = strtok(cmd, " ");
            char* arg[256];

            int i = 0;
            while (ptr != NULL) {
                arg[i++] = ptr;
                ptr = strtok(NULL, " ");
            }
            arg[i] = NULL;

            char path[100];
            sprintf(path, "/bin/%s", arg[0]);
            if (!strcmp("quit", arg[0])) {
                exit(2);
            }
            execv(path, arg);
            exit(0);
        }
        else {
            pid_t child_pid = wait(&stat);
            if (stat == (1 << 9)) {
                exit(0);
            }

        }
    }

}

#define _GNU_SOURCE
#include "net.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define PORT 1034

/*
- Spawn a child process to handle each request 
- Parent process should register a signal handler for the SIGCHLD signal 
    - (raised when a child process completes)
    - wait within that handler. 
- Consider a waitpid with WNOHANG and a loop to handle all pending child processes.
- The parent process should continue to accept new connections.
*/

pid_t spawn(void) {
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }
    return pid1;
}

void handle_action(int sig) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {
        if (WIFEXITED(status)) {
            printf("child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("child terminated by signal %d\n", WTERMSIG(status));
        }
    }
}

void setup(int signo) {
    struct sigaction action;
    if (sigemptyset(&action.sa_mask) == -1) {
        perror("sigemptyset");
        exit(1);
    }
    action.sa_flags = 0;
    action.sa_handler = handle_action;
    if (sigaction(signo, &action, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

void handle_request(int nfd)
{
    FILE *network = fdopen(nfd, "r");
    char *line = NULL;
    size_t size;
    ssize_t num;

    if (network == NULL)
    {
        perror("fdopen");
        close(nfd);
        return;
    }

    while ((num = getline(&line, &size, network)) >= 0)
    {
        printf("%s", line);
    }

    free(line);
    fclose(network);
}

void run_service(int fd)
{
    while (1)
    {
        int nfd = accept_connection(fd);
        if (nfd != -1)
        {
            pid_t pid = spawn();
            if (pid == 0)
            {
                printf("Connection established\n");
                handle_request(nfd);
                printf("Connection closed\n");
                exit(0);
            }
            else
            {
                close(nfd);
            }
        }
    }
}

int main(void)
{
    int fd = create_service(PORT);
    // printf("fd: %d\n", fd); - check if port is open


    setup(SIGCHLD);
    if (fd != -1)
    {
        printf("listening on port: %d\n", PORT);

        run_service(fd);

        close(fd);
    }

    return 0;
}

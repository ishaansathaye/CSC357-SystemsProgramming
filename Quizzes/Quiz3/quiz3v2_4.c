// Second Page Question
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pid_t spawn() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    return pid;
}

int process(int argc, char *argv[]) {
    pid_t pid1; pid_t pid2;
    int status;
    if ((pid1 = spawn()) == 0) {
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        exit(1);
    } else {
        if ((pid2 = spawn()) == 0) {
            execlp(argv[2], argv[2], NULL);
            perror("execlp");
            exit(1);
        }
    }
    pid_t pid3 = wait(&status);
    if (pid3 == pid1) {
        printf("Name: %s with Process %d terminated first\n", argv[1], pid1);
    } else {
        printf("Name: %s with Process %d terminated first\n", argv[2], pid2);
    }
    wait(&status);
    return 0;
    
}

int main(int argc, char *argv[]) {
    process(argc, argv);
    return 0;
}

/*
Requirement 1: Takes, as command-line arguments, an integer number of seconds and another command (optionally with arguments of its own)
Requirement 2: Spawn a child process to execute the argument command (with its command-line arguments)
Requirement 3: Set an alarm that will be triggered after the specified number of seconds (use sigaction). 
Requirement 4: Child killed and exit status non-zero if child process has not terminated by the time that the alarm has triggered
Requirement 5: Child terminates, then the exit status should be that of the child process
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>

pid_t pid;

pid_t spawn(void) {
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }
    return pid1;
}

void handle_action(int sig) {
    printf("killing child...\n");
    kill(pid, sig);
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

void child(char *command, char *args[]) {
    execvp(command, args);
    perror("execvp");
    exit(1);
}

void process(int seconds, char *command, char **cArgs) {
    setup(SIGALRM);
    struct itimerval timer;
    timer.it_value.tv_sec = seconds;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }
    pid = spawn();
    if (pid == 0) {
        child(command, cArgs);
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child exited with its status %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <seconds> <command> [args...]\n", argv[0]);
        exit(1);
    }
    int seconds = atoi(argv[1]);
    if (seconds < 0) {
        fprintf(stderr, "Invalid number of seconds: %d\n", seconds);
        exit(1);
    }
    char *command = argv[2];
    char **args = &argv[2];

    process(seconds, command, args);

    return 0;
}

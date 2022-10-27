/*
Write a program named fe_test. 
This program will behave similarly to the program from the first part, 
    but will use one of the "exec" system calls to execute the programs written in the Task 2. 
The parent should fork two child processes. 
One child process will "exec" the odds program. 
The other will "exec" the evens program. 
The parent process should properly wait for both child processes to terminate 
    but allow them to execute concurrently (i.e., wait after both children have been created).
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>

void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl))
    {
        perror("getrlimit");
        exit(-1);
    }
    rl.rlim_cur = max_procs;
    if (setrlimit(RLIMIT_NPROC, &rl))
    {
        perror("setrlimit");
        exit(-1);
    }
}

void odd_child(char *n) {
    char *path = "../Task2_OddsEvens/odds";
    int result = execl(path, path, n, NULL);
    if (result == -1) {
        perror("execl");
        exit(-1);
    }
}

void even_child(char *n) {
    char *path = "../Task2_OddsEvens/evens";
    execl(path, path, n, NULL);
}

void process(char *n) {
    pid_t pid1, pid2;
    int status1, status2;
    if ((pid1 = fork()) < 0) {
        perror("fork");
        exit(-1);
    } else if (pid1 == 0) {
        odd_child(n);
    } else {
        if ((pid2 = fork()) < 0) {
            perror("fork");
            exit(-1);
        } else if (pid2 == 0) {
            even_child(n);
        } else {
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
        }
    }
}

int main(int argc, char *argv[]) {
    limit_fork(500); // 500 for Mac, 100 for servers
    /* continue with program logic here */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        exit(-1);
    }
    char *n = argv[1];
    process(n);
    return 0;
}

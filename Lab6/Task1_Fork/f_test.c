/* Write a program named f_test. This program must take a single integer, N, as a command-line argument. 
This program must fork a child process. The child must print the odd numbers from 1 to N (inclusive) and then exit(), while the parent prints the even numbers from 1 to N (inclusive). 
The parent process should properly wait for the child process to terminate.

For the odd numbers, use “%d\n” as the format string for printf. For the even numbers, use “\t%d\n” as the format string for printf.

Run the program with a large enough value for N to observe an interleaving in the output.*/

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

pid_t spawn(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(-1);
    }
    return pid;
}

void child(int n) {
    int i;
    for (i = 1; i <= n; i += 2) {
        printf("%d\n", i);
    }
    exit(0);
}

void parent(int n) {
    int i;
    for (i = 2; i <= n; i += 2) {
        printf("\t%d\n", i);
    }
    wait(0);
}

void child_parent(int n) {
    if (spawn() == 0) {
        child(n);
    } else {
        parent(n);
    }

}

int main(int argc, char *argv[]) {
    limit_fork(500); // 500 for Mac, 100 for servers
    /* continue with program logic here */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        exit(-1);
    }
    int n = atoi(argv[1]);
    child_parent(n);
    return 0;
}

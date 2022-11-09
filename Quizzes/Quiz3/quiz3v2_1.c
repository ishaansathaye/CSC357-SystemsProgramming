// First Question on the First Page

// create processes that look like this:
//            parent (initial process)
//             /  \
//        child1 child2
//                 \
//              grandchild

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

void process() {
    pid_t pid1; pid_t pid2;
    int status;
    if ((pid1 = spawn()) == 0) {
        printf("Child 1: %d\n", getpid());
        exit(0);
    } else {
        if ((pid2 = spawn()) == 0) {
            printf("Child 2: %d\n", getpid());
            if ((pid2 = spawn()) == 0) {
                printf("Grandchild: %d\n", getpid());
                exit(0);
            }
            wait(&status);
            exit(0);
        } else {
            wait(&status);
            wait(&status);
            printf("Parent: %d\n", getpid());
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    process();
    return 0;
}

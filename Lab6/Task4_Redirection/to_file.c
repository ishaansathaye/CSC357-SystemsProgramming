/* Write a program named to_file. 
This program will take two command-line arguments. 
The first is the name of another program and the second is the name of a file (which need not yet exist).

Your program is going to use "exec" to run the specified program. 
Before doing so, however, your program will need to open the specified file and take the appropriate steps 
    to redirect standard output to the specified file. 
This setup is done so that the exec’d program will write its output to the file.

Recall discussions of file descriptions (including standard uses), open, and dup.
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h>

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

void child(char *program, char *file) {
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        exit(-1);
    }
    close(fd);
    execlp(program, program, NULL);
    perror("execlp");
    exit(-1);
}

void parent() {
    wait(0);
}

void process(char *program, char *file) {
    if (spawn() == 0) {
        child(program, file);
        exit(0);
    } else {
        parent();
    }
}

int main(int argc, char *argv[]) {
    limit_fork(500); // 500 for Mac, 100 for servers
    /* continue with program logic here */
    if (argc != 3) {
        printf("Usage: %s program file\n", argv[0]);
        exit(-1);
    }
    char *program = argv[1];
    char *file = argv[2];
    process(program, file);
    return 0;
}

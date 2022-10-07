// Reads the contents of that file using the read system call.

// Task 1: read
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define SIZE 8192

int main(int argc, char *argv[]) {
    int fd;
    char buf[SIZE];
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
    }
    while ((read(fd, buf, SIZE)) > 0) {}
    return 0;
}

// 1, 2, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, and 8192

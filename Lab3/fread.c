// Reads the contents of that file using the fread library function.

// Task 2: fread
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 8192

int main(int argc, char *argv[]) {
    char buf[SIZE];
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror(argv[1]);
        exit(1);
    }
    while ((fread(buf, SIZE, 1, fp)) > 0) {}
    fclose(fp);
    return 0;
}

// 1, 2, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, and 8192
// fread better for read 1 byte at a time, so for smaller bytes

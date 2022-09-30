#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_IDX 1
#define NUM_ARGS 2

void validate_args(int argc, char *argv[]) {
    if (argc != NUM_ARGS) {
        fprintf(stderr, "Usage: %s <filename>", argv[0]);
        exit(1);
    }
}

FILE *open_file(char *name, char *mode){
    FILE *fp = fopen(name, mode);
    if (fp == NULL) {
        perror(name);
        exit(1);
    }
    return fp;
}

void echo_contents(FILE *in) {
    char *line = NULL;
    size_t size;

    while ((getline(&line, &size, in)) > 0) {
        printf("%s", line);
    }

    free(line);
}

int main(int argc, char *argv[]) {
    validate_args(argc, argv);
    FILE *file = fopen(argv[FILE_IDX], "r");
    echo_contents(file);
    fclose(file);
    return 0;
}

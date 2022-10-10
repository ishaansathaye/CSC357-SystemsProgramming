// Read line from STDIN, print each word found on line, tokenize/separate string into words using strsep or strtok function

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(FILE *file) {
    const char delim[] = "  \n \t \r \v \f";
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    while ((read = getline(&line, &len, file)) > 0) {
        while ((token = strsep(&line, delim)) != NULL) {
            printf("%s\n", token);
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
    tokenize(stdin);
    return 0;
}

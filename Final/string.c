#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *remove_trailing(char *str){
    size_t size = strlen(str);
    while (size >= 0 && isspace(str[size-1])){
        str[size-1] = '\0';
        size--;
    }
    return str;
}

int main() {
    char *str = malloc(100);
    strcpy(str, "Hello World!                ");
    char *temp = remove_trailing(str);
    printf("%s\n", temp);
    return 0;
}


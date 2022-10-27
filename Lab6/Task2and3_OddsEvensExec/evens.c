/* Write two C programs: odds and evens. 
Each of these programs must take a single integer, N, as a command-line argument. odds prints the odd numbers from 1 to N (inclusive). 
evens prints the even numbers from 1 to N (inclusive); formatting for evens and odds should be as in task 1.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

void print_even(int n) {
    int i;
    for (i = 2; i <= n; i += 2) {
        printf("\t%d\n", i);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        exit(-1);
    }
    int n = atoi(argv[1]);
    print_even(n);
    return 0;
}
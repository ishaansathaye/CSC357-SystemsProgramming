#include <stdio.h>

void start() {}
void pause() {}

void init(int param[]) {
    for (int i = 0; i < 4; i++) {
        param[i] = i;
    }
}

void print(int param[]) {
    for (int i = 0; i < 4; i++) {
        printf("%d ", param[i]);
    }
}

int main(void) {
    int first = 9;
    int array[4];
    int last = 999;
    start();

    init(array);
    print(array);

    return 0;
}
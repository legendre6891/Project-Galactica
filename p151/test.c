#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int foo() {
    static int i = 2;

    printf("i: %d\n", i);
    i = 1;
    printf("i again: %d\n", i);
}

int main() {
    foo();
    foo();

    return 0;
}

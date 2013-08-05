#include <stdio.h>
#include <stdlib.h>
#include "../clib/prime_q.h"

int main(int argc, char **argv) {
    unsigned long int i, n;

    if (argc != 2) {
        fprintf(stderr, "Please enter an upper bound\n");
        return 1;
    }
    if (sscanf(argv[1], "%ld", &n) != 1) {
        fprintf(stderr, "Invalid int\n");
        return 1;
    }

    for (i = 1; i <= n; ++i)
        if (prime_q(i))
            printf("%ld\n", i);

    return 0;
}

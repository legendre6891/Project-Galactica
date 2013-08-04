#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

double rmax = (double)RAND_MAX;

int runweek() {
    static char stack[9];
    static short papers;
    static int t;
    static int num;
    static char *i;

    strcpy(stack, "F0000000");
    papers = 1;
    t = 0;

    while (papers > 0) {
        if (papers == 1)
            ++t;
        num = randNum(papers);
        switch (*(stack + num)) {
            case 'F':
                *(stack + num) = '8';
                memcpy(stack + papers, "421", 3);
                papers += 3;
                break;
            case '8':
                *(stack + num) = '4';
                memcpy(stack + papers, "21", 2);
                papers += 2;
                break;
            case '4':
                *(stack + num) = '2';
                *(stack + papers) = '1';
                papers += 1;
                break;
            case '2':
                *(stack + num) = '1';
                break;
            case '1':
                for (i = stack + num; i < stack + papers - num - 1; ++i)
                    *i = *(i + 1);
                --papers;
                break;
        }
    }
    return t - 2;
}

int randNum(max) {
    return (int)(rand() / rmax * max);
}

int main() {
    int n = 0, ones = 0;

    srand(time(NULL));
    while (1) {
        ++n;
        ones += runweek();
        if ((n & 0xffffff) == 0) {
            printf("%f %d %d\n", ones / (double)n, ones, n);
            fflush(stdout);
        }
        
    }
    return 0;
}

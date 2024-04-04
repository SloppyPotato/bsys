#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <value>\n", argv[0]);
        exit(1);
    }

    unsigned long long megabytes = strtoull(argv[1], NULL, 10)  * 1000000 * sizeof(char); // read in mb and convert to bytes

    char *p = (char *) malloc(megabytes);

    if (p == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    unsigned long long val = 0;
    unsigned long long print_target = 500 * 1000000 * sizeof(char);

    printf("%d\n", getpid());

    while (true) {
        if (val == megabytes - 1) {
            printf("Already written %llu mb\n", val / 1000000); // print last value before resetting
            val = 0;
        }
        p[val] = 'a';

        if (val % print_target == 0) {
            printf("Already written %llu mb\n", val / 1000000); // print every 100mb
        }

        val++;
    }
    
    free(p);
    return 0;
}


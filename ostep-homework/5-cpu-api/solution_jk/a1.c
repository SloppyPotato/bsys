#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // parent
    int rc = fork();
    int a = 10;

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        printf("child=%d\n", a);
        a += 10;
        printf("child+10=%d\n", a);
        exit(0);
    } else {
        // parent
        a += 10;
        printf("parent+10=%d\n", a);
    }

    return 0;
}


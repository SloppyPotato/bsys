#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    // parent
    int a = 10;
    printf("parent=%d\n", a);

    if (fork_or_die() == 0) {
        // child
        printf("child=%d\n", a);
        a += 10;
        printf("child+10=%d\n", a);
        exit(0);
    }

    // parent
    a += 10;
    printf("parent+10=%d\n", a);
    return 0;
}


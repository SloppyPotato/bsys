#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

void wait_or_die() {
    int rc = wait(NULL);
    assert(rc > 0);
}

int main(int argc, char *argv[]) {
    // parent
    if (fork_or_die() == 0) {
        // child
        int x = wait(NULL);
        printf("PID(CHILD): %d\n",x);
        exit(0);
    }
    int x = wait(NULL);
    printf("PID(PARENT): %d\n",x);

    return 0;
}
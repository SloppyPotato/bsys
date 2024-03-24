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

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    printf("parent\n");

    if (fork_or_die() == 0) {
        // child
        printf("child\n");
        exit(0);
    }

    return 0;
}


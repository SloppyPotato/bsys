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

    if (fork_or_die() == 0) {
        // child
        execl("/bin/ls", "ls", "-l", NULL);
        execle("/bin/ls", "ls", "-l", NULL, NULL);
        execlp("ls", "ls", "-l", NULL);
        execv("/bin/ls", (char *[]){"ls", "-l", NULL});
        execvp("ls", (char *[]){"ls", "-l", NULL});
        execvpe("/bin/ls", (char *[]){"ls", "-l", NULL}, (char *[]){"PATH=/bin", NULL});
        exit(0);
    }

    return 0;
}


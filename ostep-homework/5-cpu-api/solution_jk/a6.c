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

    // create a child process
    int pid = fork_or_die();
    if (pid == 0) {
        // child
        int status_child;
        pid_t x_child = waitpid(getpid(), &status_child, 0);
        printf("CHILD status: exit(%d)\n", status_child);
        printf("CHILD PID: %d\n", x_child);
        exit(0);
    }
    int status;
    pid_t x = waitpid(pid, &status, 0);
    printf("PARENT status: exit(%d)\n", status);
    printf("PARENT PID: %d\n", x);


    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

volatile int child_finished = 0;

void sigchild_handler(int sig) {
    child_finished = 1;
}

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a3.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    signal(SIGCHLD, sigchild_handler);

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        printf("hello\n");
        exit(0);
    } else {
        // parent
        while (!child_finished) {
            // wait for child to finish
        }
        printf("goodbye\n");

    }

    return 0;
}


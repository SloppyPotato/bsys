#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // parent
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        int status_child;
        pid_t x_child = waitpid(getpid(), &status_child, 0);
        printf("CHILD status: exit(%d)\n", status_child);
        printf("CHILD PID: %d\n", x_child);
        exit(0);
    } else {
        // parent
        int status;
        pid_t x = waitpid(rc, &status, 0);
        printf("PARENT status: exit(%d)\n", status);
        printf("PARENT PID: %d\n", x);
    }
    
    return 0;
}


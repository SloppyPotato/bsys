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
        int x = wait(NULL);
        printf("PID(CHILD): %d\n",x);
        exit(0);
    } else {
        // parent
        int x = wait(NULL);
        printf("PID(PARENT): %d\n",x);
    }

    return 0;
}


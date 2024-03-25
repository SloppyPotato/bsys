#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // parent
    close(STDOUT_FILENO);
    open("a2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child
        printf("child\n");
        exit(0);
    } else {
        // parent
        printf("parent\n");
    }

    return 0;
}


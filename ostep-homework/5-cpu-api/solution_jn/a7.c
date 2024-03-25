#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int rc = fork();
    if (rc < 0) {
        //fail
        return 1;
    } else if (rc == 0) {
        // child
        close(STDIN_FILENO);
        printf("please help\n");
    } else {
        // parent
        int status;
        waitpid(rc, &status, 0);
        printf("(parent of %d) waited - status %d\n", rc, status);
    }

    return 0;
}

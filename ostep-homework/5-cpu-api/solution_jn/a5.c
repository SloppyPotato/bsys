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
        char* exargs[3];
        exargs[0] = strdup("/bin/ls");
        exargs[1] = strdup(".");
        exargs[2] = NULL;
        execvp(exargs[0], exargs);
    } else {
        // parent
        int waitrc = wait(NULL);
        printf("(parent of %d) waited - %d\n", rc, waitrc);
    }

    return 0;
}

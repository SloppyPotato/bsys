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
        printf("(child) hello\n");
    } else {
        // parent
        wait(NULL);
        printf("(parent) goodbye\n");
    }
    
    return 0;
}

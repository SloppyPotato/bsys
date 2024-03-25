#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

volatile int is_child_finished = 0;

void sigchld_callback(int sig) {
    is_child_finished = 1;
}

int main(int argc, char* argv[]) {
    int rc = fork();
    signal(SIGCHLD, sigchld_callback);
    if (rc < 0) {
        //fail
        return 1;
    } else if (rc == 0) {
        // child
        printf("(child) hello\n");
    } else {
        // parent
        while(!is_child_finished) {}
        printf("(parent) goodbye\n");
    }
    
    return 0;
}

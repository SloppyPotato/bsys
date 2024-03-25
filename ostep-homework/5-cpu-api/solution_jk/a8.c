#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // parent
    int pipefd[2]; // File descriptors for the pipe
    pid_t child_1 = fork(); // Child 1
    int MAX_MSG = 256;
    char inbuf[MAX_MSG]; // Buffer for reading from the pipe
    char *msg = "Hello, World!";

    if  (child_1 < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    // Create the pipe
    pipe(pipefd);
    
    if  (child_1 == 0) {

        // Create Child 2
        int child_2 = fork();
        if (child_2 < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }

        if (child_2 == 0) {
        close(pipefd[1]); // Close the write end of the pipe
        read(pipefd[0], inbuf, MAX_MSG);
        printf("%s\n", inbuf);
        close(pipefd[0]); // Close the read end of the pipe
        exit(0);
        }

        // Child 1
        close(pipefd[0]); // Close the read end of the pipe
        write(pipefd[1], msg, MAX_MSG);
        close(pipefd[1]); // Close the write end of the pipe
        exit(0);
    }


    return 0;
}


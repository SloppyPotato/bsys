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
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe
        close(pipefd[0]); // Close the read end of the pipe
        fgets(inbuf, MAX_MSG, stdin); // Read from stdin
        printf("%s\n", inbuf);
        exit(0);
        }

        // Child 1
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
        close(pipefd[1]); // Close the write end of the pipe
        printf("%s\n", msg);
        fflush(stdout); // Flush stdout
        exit(0);
    }


    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // Using execl()
    pid = fork();
    if (pid == 0) {
        printf("Using execl()\n\n");
        execl("/bin/ls", "ls", NULL);
        // If execl() fails
        perror("execl");
        exit(EXIT_FAILURE);
    }
    wait(NULL); // Wait for the child process to finish
    
    // Using execle()
    pid = fork();
    if (pid == 0) {
        printf("using execle()\n\n");
        char *envp[] = { "PATH=/bin", NULL }; // Example environment variable
        execle("/bin/ls", "ls", NULL, envp);
        // If execle() fails
        perror("execle");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execlp()
    pid = fork();
    if (pid == 0) {
        printf("using execlp()\n\n");
        execlp("ls", "ls", NULL);
        // If execlp() fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execv()
    pid = fork();
    if (pid == 0) {
        printf("using execv()\n\n");
        char *args[] = { "/bin/ls", NULL };
        execv("/bin/ls", args);
        // If execv() fails
        perror("execv");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execvp()
    pid = fork();
    if (pid == 0) {
        printf("using execvp()\n\n");
        char *args[] = { "ls", NULL };
        execvp("ls", args);
        // If execvp() fails
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    // Using execvpe()
    pid = fork();
    if (pid == 0) {
        printf("using execvpe()\n\n");
        char *args[] = { "ls", NULL };
        char *envp[] = { "PATH=/bin", NULL }; // Example environment variable
        #include <unistd.h> // Include the necessary header file

        execvpe("ls", args, envp);
        // If execvpe() fails
        perror("execvpe");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    return 0;
}


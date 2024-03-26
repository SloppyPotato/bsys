#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    close(STDOUT_FILENO);
    open("./_test", O_CREAT|O_WRONLY|O_TRUNC);
    int x = 123;
    int rc = fork();
    if (rc < 0) {
        //fail
        return 1;
    } else if (rc == 0) {
        // child
        x = 42;
        printf("(child) x = %d\n", x);
    } else {
        // parent
        x = 2;
        wait(NULL);
        printf("(parent) x = %d\n", x);
    }
    
    return 0;
}

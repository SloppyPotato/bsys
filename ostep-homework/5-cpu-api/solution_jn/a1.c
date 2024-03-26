#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int x = 42;
    
    int rc = fork();
    if (rc < 0) {
        //fail
        return 1;
    } else if (rc == 0) {
        // child
        printf("(child) x = %d\n", x);
    } else {
        // parent
        printf("(parent) x = %d\n", x);
    }
    
    return 0;
}

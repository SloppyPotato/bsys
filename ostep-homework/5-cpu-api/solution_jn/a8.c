#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int pipo[2];
    int prc = pipe(pipo);
    int bufferSize = 256;
    
    if (prc != 0) {
        printf("krise\n");
        return 1;
    }
    
    int firstChild = fork();
    
    if (firstChild < 0) {
        printf("first child failure\n");
        return 1;
    }
    
    if (firstChild == 0) {
        // child 1
        close(pipo[0]);
        char* msg = "child 1 to child 2: hello";
        int writeStat = write(pipo[1], msg, bufferSize);
        printf("firstChild writeStat: %d\n", writeStat);
        return 0;
    }
    
    if (firstChild > 0) {
        // parent
        int secondChild = fork();
        
        if (secondChild < 0) {
            printf("second child failure\n");
            return 1;
        } else if (secondChild == 0) {
            // child 2
            close(pipo[1]);
            char msg[bufferSize];
            int readStat = read(pipo[0], msg, bufferSize);
            printf("secondChild readStat: %d\n", readStat);
            printf("%s%s%s\n", "\"", msg, "\"");
            return 0;
        } else {
            close(pipo[0]);
            close(pipo[1]);
            waitpid(firstChild, NULL, 0);
            waitpid(secondChild, NULL, 0);
            printf("finnish\n");
        }
    }

    return 0;
}

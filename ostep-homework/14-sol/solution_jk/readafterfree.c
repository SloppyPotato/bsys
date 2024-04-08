#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int* data = (int *) malloc(100 * sizeof(int));
    if (data == NULL) {
        return 1;
    }

    free(data);

    printf("Value of data[50]: %d\n", data[50]);

    return 0;
}
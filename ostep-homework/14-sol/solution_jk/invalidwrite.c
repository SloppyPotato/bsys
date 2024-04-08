#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int* data = (int *) malloc(100 * sizeof(int));
    if (data == NULL) {
        return 1;
    }

    data[100] = 0;

    free(data);

    return 0;
}
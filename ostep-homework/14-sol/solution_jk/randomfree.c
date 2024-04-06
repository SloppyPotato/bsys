#include <stdlib.h>

int main(int argc, char *argv[]) {

    int* data = (int *) malloc(100 * sizeof(int));
    if (data == NULL) {
        return 1;
    }



    free((data + 50 * sizeof(int)));

    return 0;
}
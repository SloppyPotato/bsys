#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    int *x = (int *) malloc(sizeof(int));
    if (x == NULL) {
        return 1;
    }
    *x = 10;

    return 0;
}
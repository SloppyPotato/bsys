#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int* pointer = NULL;

    printf("Value of pointer: %d\n", *pointer);

    return 0;
}

// Segmenation fault
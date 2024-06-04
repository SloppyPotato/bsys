#include <stdio.h>
#include <unistd.h>

int main() {
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of CPUs: %d\n", numCPU);
    return 0;
}

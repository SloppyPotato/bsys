#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval t1, t2;
    int i;

    gettimeofday(&t1, NULL);
    for (i = 0; i < 1000000; i++) {
        gettimeofday(&t2, NULL);
        if (t2.tv_usec != t1.tv_usec || t2.tv_sec != t1.tv_sec) {
            break;
        }
    }

    printf("Resolution: %ld microseconds\n", (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec);

    return 0;
}

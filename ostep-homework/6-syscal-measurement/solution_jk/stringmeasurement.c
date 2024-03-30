#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
    struct timeval pre, post;
    gettimeofday(&pre, NULL);
    printf("\tTEST STRING\n");
    gettimeofday(&post, NULL);
    long int act = (post.tv_sec - pre.tv_sec) * 1000000 + (post.tv_usec - pre.tv_usec);
    printf("\tTime: %ld microseconds\n", act);
    return act;
}


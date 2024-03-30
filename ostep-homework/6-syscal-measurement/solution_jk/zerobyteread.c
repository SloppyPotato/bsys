#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

static inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

//return ((uint64_t)hi << 32) | lo;: This line constructs a 64-bit unsigned integer by combining the values of hi and lo. 
//Since hi contains the higher bits and lo contains the lower bits, 
//hi is shifted left by 32 bits (<< 32) and then combined with lo using the bitwise OR (|) operator. 
//The result is a 64-bit integer representing the complete TSC value

// Function to get CPU frequency (TSC frequency) in Hz
static inline uint64_t get_tsc_freq() {
    uint32_t eax, edx;
    __asm__ __volatile__ ("cpuid" : "=a" (eax), "=d" (edx) : "a" (0x15));
    return ((uint64_t)edx << 32) | eax;
}

int main(int argc, char const *argv[])
{
    char buffer[1];
    __ssize_t bytes_read;
    struct timeval pre, post;



    int start = rdtsc();

    gettimeofday(&pre, NULL);
    
    bytes_read = read(0, buffer, 0);

    gettimeofday(&post, NULL);

    int end = rdtsc();

    // Convert elapsed CPU cycles to seconds
    int elapsed = end - start;


    if (bytes_read == 0)
    {
        long int act = (post.tv_sec - pre.tv_sec) * 1000000 + (post.tv_usec - pre.tv_usec);
        printf("\tTime: %ld microseconds\n", act);
        printf("\tTSC: %d\n", end - start); //Timestamp Counter
        return act;
    } else {
        printf("Error: read() did not return 0\n");
        return 1;
        }
}


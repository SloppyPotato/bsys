#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

int main(int argc, char *argv[]) {

    int total_measurements = 100;
    int sum_measurements = 0;

    // Define a CPU set with only CPU 0 enabled
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    // Set the CPU affinity for the current process
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    int parent_cpu = sched_getcpu();
    printf("Parent process\n");
    printf("CPU: %d\n", parent_cpu);

    for (size_t i = 0; i < total_measurements; i++) {
        int rc = fork();
        if (rc < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        if (rc == 0) {
            // child
            int cpu = sched_getcpu();
            printf("_______________________________________\n\n");
            printf("Child process %zu\n", i+1);
            printf("CPU: %d\n", cpu);
            execlp("/home/bsys/bsys/ostep-homework/6-syscal-measurement/solution_jk/zerobyteread", "zerobyteread", NULL);
            exit(0);
        } else {
            // parent
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                int child_exit_status = WEXITSTATUS(status);
                //printf("Child process %d exited with status: %d\n", i+1, child_exit_status);
                sum_measurements += child_exit_status;
            } else {
                printf("Child process %zu did not terminate normally.\n", i+1);
            }
        }
    }


    // Calculate average
    double average = (double)sum_measurements / total_measurements;
    printf("_______________________________________\n\n");
    printf("Average measurement: %.2f microseconds\n", average);

    return 0;
}


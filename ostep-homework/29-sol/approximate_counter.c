#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>

#define NUM_THREADS 8000
#define NUM_INCREMENTS 1000
#define UPDATE_THRESHOLD 10000

long counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
double timings[NUM_THREADS];

void* increment_counter(void* arg) {
    struct timeval start, end;
    long seconds, useconds;
    long mtime;
    int thread_num = *(int*)arg;
    long local_counter = 0;
    int update_count = 0;

    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_INCREMENTS; i++) {
        local_counter++;
        update_count++;

        if(update_count == UPDATE_THRESHOLD) {
            pthread_mutex_lock(&counter_mutex);
            counter += local_counter;
            pthread_mutex_unlock(&counter_mutex);
            local_counter = 0;
            update_count = 0;
        }
    }
    gettimeofday(&end, NULL);

    if(local_counter > 0) {
        pthread_mutex_lock(&counter_mutex);
        counter += local_counter;
        pthread_mutex_unlock(&counter_mutex);
    }

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    timings[thread_num] = mtime;

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i;
        pthread_create(&threads[i], NULL, increment_counter, &thread_nums[i]);
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double sum = 0;
    double min = timings[0];
    double max = timings[0];
    for(int i = 0; i < NUM_THREADS; i++) {
        sum += timings[i];
        if(timings[i] < min) min = timings[i];
        if(timings[i] > max) max = timings[i];
    }
    double avg = sum / NUM_THREADS;

    double sum_diff_sq = 0;
    for(int i = 0; i < NUM_THREADS; i++) {
        sum_diff_sq += (timings[i] - avg) * (timings[i] - avg);
    }
    double std_dev = sqrt(sum_diff_sq / NUM_THREADS);

    printf("Program ran for %.2f milliseconds with %d threads, incrementing %d times per thread, with a threshold of %d\n", max, NUM_THREADS, NUM_INCREMENTS, UPDATE_THRESHOLD);
    printf("Stats for threads:\n");
    printf("Avg: %.2f milliseconds\n", avg);
    printf("Min: %.2f milliseconds\n", min);
    printf("Max: %.2f milliseconds\n", max);
    printf("Std: %.2f milliseconds\n", std_dev);

    printf("Counter: %ld\n", counter);

    return 0;
}

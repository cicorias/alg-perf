#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (1 << 21) // 2^21

void loop_stride_256(int *a) {
    for (int i = 0; i < N; i += 256) {
        a[i]++;
    }
}

void loop_stride_257(int *a) {
    for (int i = 0; i < N; i += 257) {
        a[i]++;
    }
}

int main() {
    int *a = (int *)malloc(N * sizeof(int));
    if (a == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    struct timespec start, end;
    double time_taken;

    // Initialize array (optional, but good practice)
    for (int i = 0; i < N; i++) {
        a[i] = 0;
    }

    // Benchmark loop_stride_256
    clock_gettime(CLOCK_MONOTONIC, &start);
    loop_stride_256(a);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("Time taken by loop_stride_256: %f seconds\n", time_taken);

    // Re-initialize array for a fair comparison
    for (int i = 0; i < N; i++) {
        a[i] = 0;
    }

    // Benchmark loop_stride_257
    clock_gettime(CLOCK_MONOTONIC, &start);
    loop_stride_257(a);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("Time taken by loop_stride_257: %f seconds\n", time_taken);

    free(a);
    return EXIT_SUCCESS;
}
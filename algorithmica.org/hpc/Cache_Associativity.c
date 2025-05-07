#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // New include for strcmp
#include <math.h>   // New include for sqrt, pow

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

// NEW: Helper function to compare doubles for qsort
int compare_doubles(const void *a, const void *b) {
    double da = *(const double *)a;
    double db = *(const double *)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

// NEW: Helper function to calculate mean
double calculate_mean(double *data, int n) {
    if (n == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// NEW: Helper function to calculate median (sorts data in-place)
double calculate_median(double *data, int n) {
    if (n == 0) return 0.0;
    qsort(data, n, sizeof(double), compare_doubles);
    if (n % 2 == 1) {
        return data[n / 2];
    } else {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    }
}

// NEW: Helper function to calculate standard deviation (sample)
double calculate_std_dev(double *data, int n, double mean) {
    if (n <= 1) return 0.0; // Std dev is 0 or undefined for n <= 1
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(data[i] - mean, 2);
    }
    return sqrt(sum_sq_diff / (n - 1));
}

// NEW: Helper function to run benchmark and print statistics
void benchmark_and_print_stats(const char* func_name, void (*loop_func)(int*), int *arr, int arr_size_N, int num_iterations) {
    if (num_iterations <= 0) {
        printf("Warning: Number of iterations for %s is %d, skipping benchmark.\n", func_name, num_iterations);
        return;
    }
    double *times = (double *)malloc(num_iterations * sizeof(double));
    if (times == NULL) {
        perror("Failed to allocate memory for times array in benchmark_and_print_stats");
        return; 
    }

    struct timespec start_ts, end_ts;
    double time_taken_secs;

    printf("Benchmarking %s for %d iterations...\n", func_name, num_iterations);
    for (int k = 0; k < num_iterations; k++) {
        for (int i = 0; i < arr_size_N; i++) { // Re-initialize array for each run
            arr[i] = 0;
        }
        clock_gettime(CLOCK_MONOTONIC, &start_ts);
        loop_func(arr);
        clock_gettime(CLOCK_MONOTONIC, &end_ts);
        time_taken_secs = (end_ts.tv_sec - start_ts.tv_sec) * 1e9;
        time_taken_secs = (time_taken_secs + (end_ts.tv_nsec - start_ts.tv_nsec)) * 1e-9;
        times[k] = time_taken_secs;
    }

    double mean = calculate_mean(times, num_iterations);
    double median = calculate_median(times, num_iterations); // Sorts 'times'
    double std_dev = calculate_std_dev(times, num_iterations, mean);

    printf("Results for %s:\n", func_name);
    printf("  Mean:    %f seconds\n", mean);
    printf("  Median:  %f seconds\n", median);
    printf("  Std Dev: %f seconds\n", std_dev);
    printf("\n");

    free(times);
}

int main(int argc, char *argv[]) { // MODIFIED: Added argc, argv for command-line arguments
    // NEW: Parse command-line arguments for number of iterations
    int num_iterations = 1000; // Default number of iterations
    if (argc > 1) { 
        if (argc == 3 && strcmp(argv[1], "--iterations") == 0) {
            num_iterations = atoi(argv[2]);
            if (num_iterations <= 0) {
                fprintf(stderr, "Error: Number of iterations must be a positive integer.\n");
                return EXIT_FAILURE;
            }
        } else { 
            fprintf(stderr, "Usage: %s [--iterations N]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    int *a = (int *)malloc(N * sizeof(int));
    if (a == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    benchmark_and_print_stats("loop_stride_256", loop_stride_256, a, N, num_iterations);
    benchmark_and_print_stats("loop_stride_257", loop_stride_257, a, N, num_iterations);

    free(a);
    return EXIT_SUCCESS;
}
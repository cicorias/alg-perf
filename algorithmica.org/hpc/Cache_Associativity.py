# this is from https://en.algorithmica.org/hpc/cpu-cache/associativity/

import numpy as np
import time

N = 2**21

def benchmark_stride_256():
    a = np.zeros(N, dtype=np.int32)
    for i in range(0, N, 256):
        a[i] += 1
    return a # Return to ensure work isn't optimized away, though +=1 modifies in place

def benchmark_stride_257():
    a = np.zeros(N, dtype=np.int32)
    for i in range(0, N, 257):
        a[i] += 1
    return a # Return to ensure work isn't optimized away

if __name__ == "__main__":
    print(f"N = {N}")

    # Benchmark for stride 256
    start_time_256 = time.perf_counter()
    result_256 = benchmark_stride_256()
    end_time_256 = time.perf_counter()
    duration_256 = end_time_256 - start_time_256
    print(f"Time for stride 256: {duration_256:.6f} seconds")

    # Benchmark for stride 257
    start_time_257 = time.perf_counter()
    result_257 = benchmark_stride_257()
    end_time_257 = time.perf_counter()
    duration_257 = end_time_257 - start_time_257
    print(f"Time for stride 257: {duration_257:.6f} seconds")

    # Optional: verify a few elements to ensure loops ran
    # print(f"Sample from result_256 (first 5 modified): {[result_256[i*256] for i in range(min(5, N//256))]}")
    # print(f"Sample from result_257 (first 5 modified): {[result_257[i*257] for i in range(min(5, N//257))]}")


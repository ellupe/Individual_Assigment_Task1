import time
import psutil
import os
from MatrixMultiplier import generate_matrix, multiply_matrices

def get_memory_usage_kb():
    process = psutil.Process(os.getpid())
    return process.memory_info().rss / 1024  

def benchmark(n, runs=3):
    A = generate_matrix(n)
    B = generate_matrix(n)
    total = 0.0
    peak_mem = 0

    for r in range(runs):
        start_mem = get_memory_usage_kb()
        start = time.perf_counter()

        multiply_matrices(A, B, n)

        end = time.perf_counter()
        end_mem = get_memory_usage_kb()
        total += (end - start)
        peak_mem = max(peak_mem, end_mem - start_mem)

    return total / runs, peak_mem

if __name__ == "__main__":
    sizes = [128, 256, 512, 1024]
    runs = 5
    for n in sizes:
        avg_time, mem_kb = benchmark(n, runs)
        print(f"Python: {n}x{n} average = {avg_time:.6f} s, memory = {mem_kb:.2f} KB")

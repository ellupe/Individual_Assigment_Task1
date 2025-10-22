import time
from MatrixMultiplier import generate_matrix, multiply_matrices

def benchmark(n, runs=3):
    A = generate_matrix(n)
    B = generate_matrix(n)
    total = 0.0

    for r in range(runs):
        start = time.perf_counter()
        multiply_matrices(A, B, n)
        end = time.perf_counter()
        total += (end - start)
    return total / runs

if __name__ == "__main__":
    sizes = [128, 256, 512, 1024]
    runs = 5
    for n in sizes:
        avg_time = benchmark(n, runs)
        print(f"Python: {n}x{n} average = {avg_time:.6f} s")

#include "MatrixMultiplier.cpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <unistd.h> 

size_t getMemoryUsageKB() {
    std::ifstream statm("/proc/self/statm");
    long size, resident;
    statm >> size >> resident;
    statm.close();
    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
    return resident * page_size_kb;
}

double benchmark(int n, int runs, size_t &mem_usage) {
    auto A = generate_matrix(n);
    auto B = generate_matrix(n);
    double total = 0.0;
    size_t peak_mem = 0;

    for (int r = 0; r < runs; ++r) {
        auto start = std::chrono::high_resolution_clock::now();
        auto C = multiply(A, B, n);
        auto end = std::chrono::high_resolution_clock::now();

        total += std::chrono::duration<double>(end - start).count();
        size_t current_mem = getMemoryUsageKB();
        if (current_mem > peak_mem) peak_mem = current_mem;
    }
    mem_usage = peak_mem;
    return total / runs;
}

int main() {
    std::vector<int> sizes = {128, 256, 512, 1024};
    int runs = 5;

    for (int n : sizes) {
        size_t mem_kb;
        double avg_time = benchmark(n, runs, mem_kb);
        std::cout << "C++: " << n << "x" << n
                  << " average = " << avg_time << " s, "
                  << "memory = " << mem_kb << " KB" << std::endl;
    }
    return 0;
}

#include "MatrixMultiplier.cpp"
#include <iostream>
#include <chrono>
#include <vector>

double benchmark(int n, int runs) {
    auto A = generate_matrix(n);
    auto B = generate_matrix(n);
    double total = 0.0;

    for (int r = 0; r < runs; ++r) {
        auto start = std::chrono::high_resolution_clock::now();
        auto C = multiply(A, B, n);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double>(end - start).count();
    }
    return total / runs;
}

int main() {
    std::vector<int> sizes = {128, 256, 512, 1024};
    int runs = 5;

    for (int n : sizes) {
        double avg_time = benchmark(n, runs);
        std::cout << "C++: " << n << "x" << n
                  << " average = " << avg_time << " s" << std::endl;
    }
    return 0;
}

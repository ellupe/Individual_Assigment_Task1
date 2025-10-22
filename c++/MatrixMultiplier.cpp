#include <vector>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <vector>

std::vector<std::vector<double>> generate_matrix(int n) {
    std::vector<std::vector<double>> mat(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = static_cast<double>(rand()) / RAND_MAX;
    return mat;
}

std::vector<std::vector<double>> multiply(
    const std::vector<std::vector<double>> &A,
    const std::vector<std::vector<double>> &B,
    int n
) {
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}


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
    std::vector<int> sizes = {128, 256, 512};
    int runs = 3;

    for (int n : sizes) {
        double avg_time = benchmark(n, runs);
        std::cout << "C++: " << n << "x" << n
                  << " average = " << avg_time << " s" << std::endl;
    }
    return 0;
}

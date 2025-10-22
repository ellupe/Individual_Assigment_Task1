#include <vector>
#include <cstdlib>
#include <iostream>
#include <chrono>

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

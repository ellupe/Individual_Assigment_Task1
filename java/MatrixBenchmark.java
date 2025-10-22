public class MatrixBenchmark {
    public static double benchmark(int n, int runs) {
        double[][] A = MatrixMultiplier.generateMatrix(n);
        double[][] B = MatrixMultiplier.generateMatrix(n);
        double total = 0.0;

        for (int r = 0; r < runs; r++) {
            long start = System.nanoTime();
            MatrixMultiplier.multiply(A, B, n);
            long end = System.nanoTime();
            total += (end - start) / 1e9;
        }
        return total / runs;
    }

    public static void main(String[] args) {
        int[] sizes = {128, 256, 512, 1024};
        int runs = 5;
        for (int n : sizes) {
            double avg = benchmark(n, runs);
            System.out.printf("Java: %dx%d average = %.6f s%n", n, n, avg);
        }
    }
}

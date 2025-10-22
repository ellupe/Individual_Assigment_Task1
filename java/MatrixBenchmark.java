public class MatrixBenchmark {
    public static double benchmark(int n, int runs, long[] memUsage) {
        double[][] A = MatrixMultiplier.generateMatrix(n);
        double[][] B = MatrixMultiplier.generateMatrix(n);
        double total = 0.0;
        long peakMemory = 0;

        for (int r = 0; r < runs; r++) {
            System.gc();
            long beforeMem = usedMemory();
            long start = System.nanoTime();

            MatrixMultiplier.multiply(A, B, n);

            long end = System.nanoTime();
            long afterMem = usedMemory();
            total += (end - start) / 1e9;
            peakMemory = Math.max(peakMemory, afterMem - beforeMem);
        }
        memUsage[0] = peakMemory;
        return total / runs;
    }

    private static long usedMemory() {
        Runtime rt = Runtime.getRuntime();
        return (rt.totalMemory() - rt.freeMemory()) / 1024;
    }

    public static void main(String[] args) {
        int[] sizes = {128, 256, 512, 1024};
        int runs = 5;

        for (int n : sizes) {
            long[] memUsage = new long[1];
            double avg = benchmark(n, runs, memUsage);
            System.out.printf("Java: %dx%d average = %.6f s, memory = %d KB%n",
                    n, n, avg, memUsage[0]);
        }
    }
}

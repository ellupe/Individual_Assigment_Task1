import java.util.Random;

public class MatrixMultiplier {
    public static double[][] generateMatrix(int n) {
        Random random = new Random();
        double[][] mat = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = random.nextDouble();
        return mat;
    }

    public static double[][] multiply(double[][] A, double[][] B, int n) {
        double[][] C = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }
}

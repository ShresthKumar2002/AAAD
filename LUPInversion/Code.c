#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define EPSILON 1e-9

void LUPDecomposition(double A[N][N], int P[N]) {
    for (int i = 0; i < N; i++) P[i] = i;

    for (int k = 0; k < N; k++) {
        // Find pivot
        double max = 0.0;
        int k_prime = k;
        for (int i = k; i < N; i++) {
            if (fabs(A[i][k]) > max) {
                max = fabs(A[i][k]);
                k_prime = i;
            }
        }

        if (max < EPSILON) {
            printf("Matrix is singular or near-singular.\n");
            exit(EXIT_FAILURE);
        }

        // Swap rows in permutation and matrix
        int temp = P[k];
        P[k] = P[k_prime];
        P[k_prime] = temp;

        for (int j = 0; j < N; j++) {
            double tmp = A[k][j];
            A[k][j] = A[k_prime][j];
            A[k_prime][j] = tmp;
        }

        // Eliminate
        for (int i = k + 1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < N; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}

void LUPSolve(double A[N][N], int P[N], double b[N], double x[N]) {
    double y[N];

    // Forward solve Ly = Pb
    for (int i = 0; i < N; i++) {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }

    // Back solve Ux = y
    for (int i = N - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void InvertMatrix(double A[N][N], double inverse[N][N]) {
    int P[N];
    double A_copy[N][N];

    // Copy original matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A_copy[i][j] = A[i][j];

    LUPDecomposition(A_copy, P);

    for (int i = 0; i < N; i++) {
        double b[N] = {0};
        double x[N];
        b[i] = 1.0;  // Identity column

        LUPSolve(A_copy, P, b, x);

        // Store as column
        for (int j = 0; j < N; j++) {
            inverse[j][i] = x[j];
        }
    }
}

void printMatrix(double M[N][N], const char *name) {
    printf("%s =\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%10.4f ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiply(double A[N][N], double B[N][N], double result[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
}

int main() {
    double A[N][N] = {
        {4, 7, 2},
        {3, 6, 1},
        {2, 5, 3}
    };

    double A_inv[N][N];
    double check[N][N];

    InvertMatrix(A, A_inv);

    printMatrix(A, "Original A");
    printMatrix(A_inv, "Inverse A");

    multiply(A, A_inv, check);
    printMatrix(check, "A * A_inv (Should be Identity)");

    return 0;
}

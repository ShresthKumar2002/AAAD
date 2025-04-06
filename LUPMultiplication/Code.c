#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define EPSILON 1e-9

void LUPDecomposition(double A[N][N], int P[N]) {
    for (int i = 0; i < N; i++) P[i] = i;

    for (int k = 0; k < N; k++) {
        double p = 0.0;
        int k_prime = -1;
        for (int i = k; i < N; i++) {
            if (fabs(A[i][k]) > p) {
                p = fabs(A[i][k]);
                k_prime = i;
            }
        }

        if (p < EPSILON) {
            printf("Matrix is singular!\n");
            exit(EXIT_FAILURE);
        }

        int tmp = P[k];
        P[k] = P[k_prime];
        P[k_prime] = tmp;

        for (int j = 0; j < N; j++) {
            double t = A[k][j];
            A[k][j] = A[k_prime][j];
            A[k_prime][j] = t;
        }

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

    // Forward substitution
    for (int i = 0; i < N; i++) {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }

    // Backward substitution
    for (int i = N - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

int main() {
    // A better conditioned matrix
    double A[N][N] = {
        {3, 2, -1},
        {2, -2, 4},
        {-1, 0.5, -1}
    };

    double b[N] = {1, -2, 0};  // Known solution: x = {1, -2, -2}
    int P[N];
    double x[N];

    LUPDecomposition(A, P);
    LUPSolve(A, P, b, x);

    printf("Solution x:\n");
    for (int i = 0; i < N; i++) {
        printf("%8.4f\n", x[i]);
    }

    return 0;
}
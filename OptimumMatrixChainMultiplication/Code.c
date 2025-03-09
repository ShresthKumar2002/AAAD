#include <stdio.h>
#include <limits.h>

// Function to find the minimum number of multiplications
int matrixChainOrder(int p[], int n) {
    int m[n][n];

    // Initialize all diagonal elements to 0 (no cost for single matrix)
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // Solve the problem for increasing chain lengths
    for (int length = 2; length < n; length++) {
        for (int i = 1; i < n - length + 1; i++) {
            int j = i + length - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }

    return m[1][n - 1];
}

int main() {
    int n;
    printf("Enter the number of matrices (n): ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter the dimensions (array of size n+1): ");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    int minCost = matrixChainOrder(p, n + 1);
    printf("Minimum number of multiplications: %d\n", minCost);

    return 0;
}

#include <stdio.h>
#include <limits.h>

// Function to calculate the cost of the Optimal Binary Search Tree
void optimalBST(int keys[], int freq[], int n) {
    int cost[n][n]; // Cost of OBST for a range of keys

    // Initialize single key costs (diagonal elements)
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }

    // Fill the cost matrix for chain lengths from 2 to n
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            cost[i][j] = INT_MAX;

            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += freq[k];
            }

            // Try making every key in the range as the root
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) + sum;

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                }
            }
        }
    }

    // The final cost is stored in cost[0][n-1]
    printf("The minimum cost of the Optimal Binary Search Tree is: %d\n", cost[0][n - 1]);
}

int main() {
    int n;
    printf("Enter the number of keys: ");
    scanf("%d", &n);

    int keys[n], freq[n];
    printf("Enter the keys: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &keys[i]);
    }

    printf("Enter the frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &freq[i]);
    }

    optimalBST(keys, freq, n);

    return 0;
}

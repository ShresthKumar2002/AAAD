#include <stdio.h>
#include <string.h>

// Function to find the Longest Common Subsequence
int lcs(char *X, char *Y, int m, int n) {
    int dp[m + 1][n + 1];

    // Fill the dp table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // Base case
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // The length of the LCS is stored in dp[m][n]
    return dp[m][n];
}

int main() {
    char X[100], Y[100];

    printf("Enter the first string: ");
    scanf("%s", X);

    printf("Enter the second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int length = lcs(X, Y, m, n);
    printf("The length of the Longest Common Subsequence is: %d\n", length);

    return 0;
}

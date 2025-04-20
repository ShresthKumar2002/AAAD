#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For strtoll
#include <math.h>   // For pow

typedef struct {
    long long res;
    long long c;
} O;

O modularExponentiation(long long base, const char* b, long long mod) {
    O o;
    o.c = 0;
    o.res = 1;
    int len = strlen(b);

    // Iterate through the binary string from right to left
    for (int i = len - 1; i >= 0; i--) {
        o.res = (o.res * o.res) % mod; // Square the current result

        if (b[i] == '1') {
            o.c = o.c + (long long)pow(2, (len - 1) - i);
            o.res = (o.res * base) % mod; // Multiply by base if the bit is 1
        } else if (b[i] != '0') {
            fprintf(stderr, "Error: Invalid character in binary exponent string.\n");
            o.res = -1; // Indicate an error
            return o;
        }
    }
    return o;
}

int main() {
    long long a, n;
    char B[65]; // Assuming a maximum of 64 bits for the exponent

    printf("Enter base (a): ");
    scanf("%lld", &a);

    printf("Enter exponent (b) as a binary string: ");
    scanf("%s", B);

    printf("Enter modulus (n): ");
    scanf("%lld", &n);

    O result = modularExponentiation(a, B, n);

    if (result.res != -1) {
        printf("(%lld^%lld) mod %lld = %lld\n", a, result.c, n, result.res);
    }

    return 0;
}
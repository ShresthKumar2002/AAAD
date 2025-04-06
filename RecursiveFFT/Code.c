#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define PI 3.14159265358979323846

// Recursive FFT function
void fft_recursive(complex double *x, int n) {
    if (n <= 1) return;

    // Split even and odd
    complex double *even = malloc(n / 2 * sizeof(complex double));
    complex double *odd  = malloc(n / 2 * sizeof(complex double));

    for (int i = 0; i < n / 2; i++) {
        even[i] = x[2 * i];
        odd[i]  = x[2 * i + 1];
    }

    // Recursive calls
    fft_recursive(even, n / 2);
    fft_recursive(odd, n / 2);

    for (int k = 0; k < n / 2; k++) {
        complex double t = cexp(-2.0 * PI * I * k / n) * odd[k];
        x[k] = even[k] + t;
        x[k + n / 2] = even[k] - t;
    }

    free(even);
    free(odd);
}
int main() {
    int n = 8;
    complex double x[8] = {
        1.0 + 0.0*I, 1.0 + 0.0*I, 1.0 + 0.0*I, 1.0 + 0.0*I,
        0.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I
    };

    fft_recursive(x, n);

    printf("FFT result:\n");
    for (int i = 0; i < n; i++) {
        printf("X[%d] = %.4f + %.4fi\n", i, creal(x[i]), cimag(x[i]));
    }

    return 0;
}

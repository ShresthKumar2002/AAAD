#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

// Bit reversal for iterative FFT
unsigned int reverseBits(unsigned int x, int log2n) {
    unsigned int n = 0;
    for (int i = 0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

void fft_iterative(complex double *x, int n) {
    int log2n = log2(n);

    // Bit reversal reordering
    for (int i = 0; i < n; i++) {
        int j = reverseBits(i, log2n);
        if (i < j) {
            complex double temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
    }

    // Iterative FFT
    for (int s = 1; s <= log2n; s++) {
        int m = 1 << s;
        complex double wm = cexp(-2.0 * PI * I / m);
        for (int k = 0; k < n; k += m) {
            complex double w = 1.0 + 0.0 * I;
            for (int j = 0; j < m / 2; j++) {
                complex double t = w * x[k + j + m / 2];
                complex double u = x[k + j];
                x[k + j] = u + t;
                x[k + j + m / 2] = u - t;
                w *= wm;
            }
        }
    }
}

int main() {
    int n = 8;
    complex double x[8] = {
        1.0 + 0.0 * I, 1.0 + 0.0 * I, 1.0 + 0.0 * I, 1.0 + 0.0 * I,
        0.0 + 0.0 * I, 0.0 + 0.0 * I, 0.0 + 0.0 * I, 0.0 + 0.0 * I
    };

    fft_iterative(x, n);

    printf("FFT Result:\n");
    for (int i = 0; i < n; i++) {
        printf("X[%d] = %.4f + %.4fi\n", i, creal(x[i]), cimag(x[i]));
    }

    return 0;
}


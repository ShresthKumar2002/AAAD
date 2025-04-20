#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Structure for public and private keys
typedef struct {
    long long n; // Modulus
    long long key; // Public exponent (e) or private exponent (d)
} Key;

// Structure for RSA key pair
typedef struct {
    Key public_key;
    Key private_key;
} KeyPair;

// Function to calculate greatest common divisor (GCD)
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

// Function to implement Extended Euclidean Algorithm
long long extendedEuclid(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd_val = extendedEuclid(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd_val;
}

// Function to calculate modular multiplicative inverse
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extendedEuclid(a, m, &x, &y);
    if (g != 1) {
        fprintf(stderr, "Modular inverse does not exist (GCD != 1)\n");
        return -1; // Indicate failure
    } else {
        return (x % m + m) % m; // Ensure positive result
    }
}

// Function for modular exponentiation (used for encryption and decryption)
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Function to check if a number is prime (basic primality test)
int isPrime(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (long long i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Function to generate a large prime number (for simplicity, generates within a range)
long long generatePrime(long long min, long long max) {
    long long num;
    do {
        num = min + (rand() % (max - min + 1));
    } while (!isPrime(num));
    return num;
}

// Function to generate RSA key pair
KeyPair generateKeys() {
    KeyPair keys;
    srand(time(NULL));

    // Choose two distinct large prime numbers p and q
    long long p = generatePrime(100, 500); // Adjust range for larger primes in real applications
    long long q = generatePrime(600, 1000);
    while (p == q) {
        q = generatePrime(600, 1000);
    }

    // Calculate n = p * q (modulus)
    long long n = p * q;

    // Calculate Euler's totient function phi(n) = (p - 1) * (q - 1)
    long long phi_n = (p - 1) * (q - 1);

    // Choose an integer e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1 (public exponent)
    long long e = rand() % (phi_n - 2) + 2;
    while (gcd(e, phi_n) != 1) {
        e = rand() % (phi_n - 2) + 2;
    }

    // Calculate d, the modular multiplicative inverse of e modulo phi(n) (private exponent)
    long long d = modInverse(e, phi_n);
    if (d == -1) {
        fprintf(stderr, "Error generating private key\n");
        exit(1);
    }

    keys.public_key.n = n;
    keys.public_key.key = e;
    keys.private_key.n = n;
    keys.private_key.key = d;

    printf("Generated Prime p: %lld\n", p);
    printf("Generated Prime q: %lld\n", q);
    printf("Modulus n (p * q): %lld\n", n);
    printf("Euler's totient function phi(n): %lld\n", phi_n);
    printf("Public exponent e: %lld\n", e);
    printf("Private exponent d: %lld\n", d);

    return keys;
}

// Function to encrypt a message (represented as a long long integer)
long long encrypt(long long message, Key public_key) {
    return modularExponentiation(message, public_key.key, public_key.n);
}

// Function to decrypt a ciphertext (represented as a long long integer)
long long decrypt(long long ciphertext, Key private_key) {
    return modularExponentiation(ciphertext, private_key.key, private_key.n);
}

int main() {
    // Generate RSA key pair
    KeyPair keys = generateKeys();

    // Message to be encrypted (for simplicity, a small number)
    long long message = 123;
    printf("\nOriginal Message: %lld\n", message);

    // Encrypt the message
    long long ciphertext = encrypt(message, keys.public_key);
    printf("Ciphertext: %lld\n", ciphertext);

    // Decrypt the ciphertext
    long long decryptedMessage = decrypt(ciphertext, keys.private_key);
    printf("Decrypted Message: %lld\n", decryptedMessage);

    if (message == decryptedMessage) {
        printf("RSA implementation successful!\n");
    } else {
        printf("RSA implementation failed.\n");
    }

    return 0;
}
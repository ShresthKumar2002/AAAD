#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (similar to Quick Sort)
int partition(int A[], int p, int r) {
    int pivot = A[r];
    int i = p;

    for (int j = p; j < r; j++) {
        if (A[j] < pivot) {
            swap(&A[i], &A[j]);
            i++;
        }
    }
    swap(&A[i], &A[r]);
    return i;
}

// Selection function to find the i-th smallest element
int selection(int A[], int p, int r, int i) {
    if (p == r) {
        return A[p];
    }

    int q = partition(A, p, r);
    int k = q - p + 1; // Position of the pivot element in the sorted order

    if (i == k) {
        return A[q]; // Pivot is the i-th smallest element
    } else if (i < k) {
        return selection(A, p, q - 1, i); // Look in the left subarray
    } else {
        return selection(A, q + 1, r, i - k); // Look in the right subarray
    }
}

int main() {
    int n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int A[n];
    printf("Enter the elements of the array: ");
    for (int j = 0; j < n; j++) {
        scanf("%d", &A[j]);
    }

    printf("Enter the position of the smallest element to find (1-based index): ");
    scanf("%d", &i);

    int result = selection(A, 0, n - 1, i);
    printf("The %d-th smallest element is: %d\n", i, result);

    return 0;
}

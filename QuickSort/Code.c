#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random number in a given range
int ran(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function used by Quicksort
int partition(int arr[], int p, int r) {
    int pivot = arr[r];
    int i = p;

    for (int j = p; j < r; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

// Quicksort algorithm
void quickSort(int arr[], int p, int r) {
    if (p < r) {
        int k = ran(p, r); // Random pivot selection
        swap(&arr[k], &arr[r]);
        int q = partition(arr, p, r);
        quickSort(arr, p, q - 1);
        quickSort(arr, q + 1, r);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    clock_t start_time = clock(); // Start timer

    quickSort(arr, 0, n - 1);

    clock_t end_time = clock(); // End timer

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Execution time: %.6f seconds\n", elapsed_time);

    return 0;
}

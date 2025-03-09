#include <stdio.h>

// Structure to represent an item with value, weight, and ratio
typedef struct {
    int value;
    int weight;
    double ratio;
} Item;

// Function to compare two items based on their value-to-weight ratio
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) return 1;
    else if (itemA->ratio > itemB->ratio) return -1;
    else return 0;
}

// Function to perform the greedy knapsack algorithm
double greedyKnapsack(Item items[], int n, int capacity) {
    // Sort items by their value-to-weight ratio in descending order
    qsort(items, n, sizeof(Item), compare);

    double totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            // Take the entire item
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take a fraction of the item
            totalValue += items[i].ratio * capacity;
            break; // Knapsack is now full
        }
    }
    return totalValue;
}

int main() {
    int n, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    Item items[n];
    printf("Enter the value and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    double maxValue = greedyKnapsack(items, n, capacity);
    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}

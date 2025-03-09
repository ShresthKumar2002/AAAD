#include <stdio.h>
#include <stdlib.h>

// Structure to represent a task
typedef struct {
    int id;       // Task ID
    int deadline; // Deadline of the task
    int profit;   // Profit for completing the task
} Task;

// Function to compare tasks by profit (descending order)
int compareTasks(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskB->profit - taskA->profit;
}

// Function to perform task scheduling
void taskScheduling(Task tasks[], int n) {
    // Sort tasks by profit in descending order
    qsort(tasks, n, sizeof(Task), compareTasks);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (tasks[i].deadline > maxDeadline) {
            maxDeadline = tasks[i].deadline;
        }
    }

    int timeSlots[maxDeadline];
    for (int i = 0; i < maxDeadline; i++) {
        timeSlots[i] = -1; // Initialize all time slots as empty
    }

    int totalProfit = 0;

    printf("Scheduled Tasks:\n");
    for (int i = 0; i < n; i++) {
        for (int j = tasks[i].deadline - 1; j >= 0; j--) {
            if (timeSlots[j] == -1) { // If the slot is free
                timeSlots[j] = tasks[i].id;
                totalProfit += tasks[i].profit;
                printf("Task ID: %d, Deadline: %d, Profit: %d\n", tasks[i].id, tasks[i].deadline, tasks[i].profit);
                break;
            }
        }
    }

    printf("Total Profit: %d\n", totalProfit);
}

int main() {
    int n;
    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    printf("Enter the task details (ID, Deadline, Profit):\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d: ", i + 1);
        scanf("%d %d %d", &tasks[i].id, &tasks[i].deadline, &tasks[i].profit);
    }

    taskScheduling(tasks, n);

    return 0;
}

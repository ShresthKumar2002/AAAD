#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
typedef struct {
    int start;
    int finish;
} Activity;

// Function to compare activities based on their finish times
int compare(const void *a, const void *b) {
    Activity *activityA = (Activity *)a;
    Activity *activityB = (Activity *)b;
    return activityA->finish - activityB->finish;
}

// Function to perform the Activity Selection algorithm
void activitySelection(Activity activities[], int n) {
    // Sort activities by their finish times
    qsort(activities, n, sizeof(Activity), compare);

    printf("Selected Activities:\n");
    int lastFinishTime = activities[0].finish;
    printf("Activity: Start = %d, Finish = %d\n", activities[0].start, activities[0].finish);

    for (int i = 1; i < n; i++) {
        if (activities[i].start >= lastFinishTime) {
            printf("Activity: Start = %d, Finish = %d\n", activities[i].start, activities[i].finish);
            lastFinishTime = activities[i].finish;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of activities: ");
    scanf("%d", &n);

    Activity activities[n];
    printf("Enter the start and finish times of each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d: ", i + 1);
        scanf("%d %d", &activities[i].start, &activities[i].finish);
    }

    activitySelection(activities, n);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a point
typedef struct {
    int x, y;
} Point;

// A global point to be used for sorting points with respect to the first point
Point p0;

// Function to find the orientation of three points (p, q, r)
// Returns:
// 0 -> p, q, r are collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;            // Collinear
    return (val > 0) ? 1 : 2;          // Clockwise or Counterclockwise
}

// Function to calculate the square of the distance between two points
int distanceSquare(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Comparator function for sorting points
int compare(const void* p1, const void* p2) {
    Point* a = (Point*)p1;
    Point* b = (Point*)p2;

    int o = orientation(p0, *a, *b);
    if (o == 0) {
        return (distanceSquare(p0, *b) >= distanceSquare(p0, *a)) ? -1 : 1;
    }
    return (o == 2) ? -1 : 1;  // Counterclockwise comes first
}

// Function to swap two points
void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print the convex hull
void convexHull(Point points[], int n) {
    // Find the bottom-most point (or the leftmost point in case of a tie)
    int minY = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < minY) || (points[i].y == minY && points[i].x < points[minIndex].x)) {
            minY = points[i].y;
            minIndex = i;
        }
    }
    // Place the bottom-most point at the first position
    swap(&points[0], &points[minIndex]);
    p0 = points[0];

    // Sort the remaining points by polar angle with respect to p0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Initialize an array to hold the convex hull points
    Point hull[n];
    int hullSize = 0;

    // Build the convex hull
    for (int i = 0; i < n; i++) {
        while (hullSize >= 2 && orientation(hull[hullSize - 2], hull[hullSize - 1], points[i]) != 2) {
            hullSize--; // Remove the last point if it does not make a left turn
        }
        hull[hullSize++] = points[i];
    }

    // Print the convex hull points
    printf("Convex Hull Points:\n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }
}

int main() {
    // Test case
    int n = 8;
    Point points[] = {
        {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}, {4, 2}
    };

    convexHull(points, 
    n);

    return 0;
}

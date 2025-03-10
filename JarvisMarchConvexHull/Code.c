#include <stdio.h>

// Structure to represent a point
typedef struct {
    int x, y;
} Point;

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

// Function to print the convex hull
void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        return;
    }

    int hull[n]; // To store the indices of the points in the convex hull
    int hullCount = 0;
    
    int minY = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < minY) || (points[i].y == minY && points[i].x < points[minIndex].x)) {
            minY = points[i].y;
            minIndex = i;
        }
    }

    // Find the leftmost point
    int leftmost = minIndex;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x) {
            leftmost = i;
        }
    }

    // Wrap around the set of points
    int p = leftmost, q;
    do {
        hull[hullCount++] = p; // Add current point to the hull
        q = (p + 1) % n; // Next point to check

        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i; // Update q if i is more counterclockwise
            }
        }
        p = q; // Move to the next point
    } while (p != leftmost); // Continue until we reach the starting point

    // Print the convex hull points
    printf("Convex Hull Points:\n");
    for (int i = 0; i < hullCount; i++) {
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
    }
}

int main() {
    // Test case
    int n = 8;
    Point points[] = {
        {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}, {4, 2}
    };

    printf("Input Points:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }

    convexHull(points, n);

    return 0;
}

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int compareX(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

int compareY(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

double bruteForce(Point points[], int n, Point *p1, Point *p2) {
    double minDist = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                *p1 = points[i];
                *p2 = points[j];
            }
        }
    }
    return minDist;
}

double stripClosest(Point strip[], int size, double d, Point *p1, Point *p2) {
    double minDist = d;
    qsort(strip, size, sizeof(Point), compareY);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; j++) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                *p1 = strip[i];
                *p2 = strip[j];
            }
        }
    }
    return minDist;
}

double closestUtil(Point points[], int n, Point *p1, Point *p2) {
    if (n <= 3)
        return bruteForce(points, n, p1, p2);
    
    int mid = n / 2;
    Point midPoint = points[mid];
    
    Point leftP1, leftP2, rightP1, rightP2;
    double dl = closestUtil(points, mid, &leftP1, &leftP2);
    double dr = closestUtil(points + mid, n - mid, &rightP1, &rightP2);
    
    double d;
    if (dl < dr) {
        d = dl;
        *p1 = leftP1;
        *p2 = leftP2;
    } else {
        d = dr;
        *p1 = rightP1;
        *p2 = rightP2;
    }
    
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(points[i].x - midPoint.x) < d) {
            strip[j] = points[i], j++;
        }
    }
    
    Point stripP1, stripP2;
    double stripDist = stripClosest(strip, j, d, &stripP1, &stripP2);
    
    if (stripDist < d) {
        *p1 = stripP1;
        *p2 = stripP2;
        return stripDist;
    }
    return d;
}

double closestPair(Point points[], int n, Point *p1, Point *p2) {
    qsort(points, n, sizeof(Point), compareX);
    return closestUtil(points, n, p1, p2);
}

int main() {
    Point points[] = {{2.1, 3.2}, {1.2, 4.4}, {3.6, 1.8}, {5.0, 3.0}, {3.2, 4.1}};
    int n = sizeof(points) / sizeof(points[0]);
    Point p1, p2;
    double minDist = closestPair(points, n, &p1, &p2);
    printf("Closest pair: (%.1f, %.1f) and (%.1f, %.1f) with distance %.6f\n", p1.x, p1.y, p2.x, p2.y, minDist);
    return 0;
}

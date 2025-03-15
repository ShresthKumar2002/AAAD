#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define EPS 1e-9

// Point structure
typedef struct {
    double x, y;
} Point;

// Segment structure
typedef struct {
    Point p1, p2;
    int index;
} Segment;

// Event structure for Sweep Line Algorithm
typedef struct {
    double x;
    int type; // 0 = left endpoint, 1 = right endpoint
    Segment *s;
} Event;

// Node structure for Red-Black Tree
typedef struct RBNode {
    Segment *s;
    struct RBNode *left, *right, *parent;
    bool color; // 1 = Red, 0 = Black
} RBNode;

// Red-Black Tree structure
typedef struct {
    RBNode *root;
} RBTree;

// Comparator for ordering segments by y-coordinate
int compareSegments(Segment *s1, Segment *s2) {
    return (s1->p1.y < s2->p1.y) ? -1 : (s1->p1.y > s2->p1.y);
}

// Creates a new Red-Black Tree node
RBNode *createRBNode(Segment *s) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->s = s;
    node->left = node->right = node->parent = NULL;
    node->color = 1; // New nodes are always red
    return node;
}

// Inserts a segment into a simple BST (without balancing for now)
void rbInsert(RBTree *tree, Segment *s) {
    RBNode *newNode = createRBNode(s);
    if (!tree->root) {
        tree->root = newNode;
        return;
    }

    RBNode *curr = tree->root, *parent = NULL;
    while (curr) {
        parent = curr;
        if (compareSegments(s, curr->s) < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    newNode->parent = parent;
    if (compareSegments(s, parent->s) < 0)
        parent->left = newNode;
    else
        parent->right = newNode;
}

// Finds the predecessor (previous segment in y-order)
RBNode *findPredecessor(RBTree *tree, Segment *s) {
    RBNode *curr = tree->root, *prev = NULL;
    while (curr) {
        if (compareSegments(s, curr->s) > 0) {
            prev = curr;
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return prev;
}

// Finds the successor (next segment in y-order)
RBNode *findSuccessor(RBTree *tree, Segment *s) {
    RBNode *curr = tree->root, *next = NULL;
    while (curr) {
        if (compareSegments(s, curr->s) < 0) {
            next = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return next;
}

// Removes a segment from the RB Tree (simple delete without balancing)
void rbDelete(RBTree *tree, Segment *s) {
    RBNode *curr = tree->root, *parent = NULL;
    while (curr && curr->s != s) {
        parent = curr;
        if (compareSegments(s, curr->s) < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (!curr) return; // Not found

    if (!curr->left && !curr->right) {
        if (!parent) tree->root = NULL;
        else if (parent->left == curr) parent->left = NULL;
        else parent->right = NULL;
        free(curr);
    }
}

// Cross product function
double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// Compute orientation
double direction(Point a, Point b, Point c) {
    return crossProduct((Point){c.x - a.x, c.y - a.y}, (Point){b.x - a.x, b.y - a.y});
}

// Check if point `c` lies on segment `ab`
bool onSegment(Point a, Point b, Point c) {
    return (c.x >= fmin(a.x, b.x) && c.x <= fmax(a.x, b.x) &&
            c.y >= fmin(a.y, b.y) && c.y <= fmax(a.y, b.y));
}

// Check if two segments intersect
bool segmentsIntersect(Segment s1, Segment s2) {
    double d1 = direction(s1.p1, s1.p2, s2.p1);
    double d2 = direction(s1.p1, s1.p2, s2.p2);
    double d3 = direction(s2.p1, s2.p2, s1.p1);
    double d4 = direction(s2.p1, s2.p2, s1.p2);

    if (((d1 < 0) && (d2 > 0)) || ((d1 > 0) && (d2 < 0))) {
        if (((d3 < 0) && (d4 > 0)) || ((d3 > 0) && (d4 < 0))) {
            return true;
        }
    }
    if (fabs(d1) < EPS && onSegment(s1.p1, s1.p2, s2.p1)) return true;
    if (fabs(d2) < EPS && onSegment(s1.p1, s1.p2, s2.p2)) return true;
    if (fabs(d3) < EPS && onSegment(s2.p1, s2.p2, s1.p1)) return true;
    if (fabs(d4) < EPS && onSegment(s2.p1, s2.p2, s1.p2)) return true;

    return false;
}

// Comparator for event queue (sorted by x-coordinates)
int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a, *e2 = (Event *)b;
    return (e1->x < e2->x) ? -1 : (e1->x > e2->x);
}

// Finds intersections using Sweep Line Algorithm with Red-Black Tree
void findIntersections(Segment segments[], int n) {
    Event events[2 * n];
    int eventCount = 0;

    // Create event queue
    for (int i = 0; i < n; i++) {
        events[eventCount++] = (Event){segments[i].p1.x, 0, &segments[i]};
        events[eventCount++] = (Event){segments[i].p2.x, 1, &segments[i]};
    }

    // Sort events by x-coordinates
    qsort(events, eventCount, sizeof(Event), compareEvents);

    RBTree tree = {NULL};

    for (int i = 0; i < eventCount; i++) {
        Event event = events[i];

        if (event.type == 0) { // Left endpoint
            rbInsert(&tree, event.s);

            RBNode *prev = findPredecessor(&tree, event.s);
            RBNode *next = findSuccessor(&tree, event.s);

            if (prev && segmentsIntersect(*prev->s, *event.s))
                printf("Intersection detected between segment %d and %d\n", prev->s->index, event.s->index);
            if (next && segmentsIntersect(*next->s, *event.s))
                printf("Intersection detected between segment %d and %d\n", next->s->index, event.s->index);
        } else {
            rbDelete(&tree, event.s);
        }
    }
}

int main() {
    Segment segments[] = {
        {{1, 1}, {4, 4}, 0},
        {{1, 4}, {4, 1}, 1},
        {{2, 5}, {5, 2}, 2},
        {{3, 3}, {6, 0}, 3}
    };

    findIntersections(segments, 4);
    return 0;
}
